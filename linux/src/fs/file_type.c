#include "file_type.h"
#include "file.h"

#include "../thread/not.h"
#include "control.h"
#include "write.h"
#include "read.h"

#include <linux/poll.h>

static int
    po_file_do_open
        (struct inode* par, struct file* par_file)                               {
            po_file_type *type = container_of(par_file->f_op, po_file_type, type);
            if (po_trait_of(type) != po_file_type_t) return -EINVAL;
            if (par_file->f_op != &type->type)       return -EINVAL;
            if (!type->trait) return -EINVAL;
            if (!type->ops)   return -EINVAL;

            po_file* file = po_make(po_file) from (0)   ; if (!file) return -ENOMEM;
            file->type    = (po_file_type*) po_ref(type);
            file->file    = par_file;

            file->obj  = po_obj_new (null_t, type->trait, 2, type, file);
            if (!file->obj)       goto open_err;
            if (!type->ops->open)              {
                par_file->private_data = file;
                return 0;
            }

            if (!type->ops->open(file->obj)) goto open_err;
            par_file->private_data = file;
            return 0;
    open_err:
            po_del(file->type);
            po_del(file)      ;
            return -EINVAL;
}

static int
    po_file_do_close
        (struct inode* par, struct file* par_file)                               {
            po_file_type *type = container_of(par_file->f_op, po_file_type, type);
            po_file      *file = par_file->private_data;
            if (po_trait_of(type) != po_file_type_t) return -EINVAL;
            if (po_trait_of(file) != po_file_t)      return -EINVAL;
            if (par_file->f_op != &type->type)       return -EINVAL;
            if (!type->trait)                        return -EINVAL;
            if (!type->ops)                          return -EINVAL;

            if (type->ops->close) type->ops->close(file->obj);
            po_del(file->type);
            po_del(file)      ;
            return     0;
}

static ssize_t
    po_file_do_read
        (struct file* par, __user char* par_buf, size_t par_len, loff_t* par_off)          {
            po_read *read = po_make (po_read) from (3, par->private_data, par_buf, par_len);
            po_file *file = par->private_data;

            if (po_trait_of(file) != po_file_t) goto read_err;
            if (po_trait_of(read) != po_read_t) goto read_err;
            po_fut *fut = po_read_fut(read);

            if (par->f_flags & O_NONBLOCK)                                       {
                if (!file->type->ops->read_atomic)                  goto read_err;
                if (!file->type->ops->read_atomic(file->obj, read)) goto read_err;

                ssize_t ret = (ssize_t) po_fut_ret(fut);
                po_del(read);
                po_del(fut) ;
                return ret  ;
            }

            if   (!file->type->ops->read)                  goto read_err;
            if   (!file->type->ops->read(file->obj, read)) goto read_err;
            while(po_fut_poll(fut) == po_fut_pend) schedule();

            ssize_t ret = (ssize_t) po_fut_ret(fut);
            po_del (read);
            po_del (fut) ;
            return  ret  ;
    read_err:
            po_del   (read);
            po_del   (fut) ;
            return -EINVAL;
}

static ssize_t
    po_file_do_write
        (struct file* par, __user const char* par_buf, size_t par_len, loff_t* par_off)      {
            po_write *write = po_make (po_write) from (3, par->private_data, par_buf, par_len);
            po_file  *file  = par->private_data;

            if (po_trait_of(file)  != po_file_t)  goto write_err;
            if (po_trait_of(write) != po_write_t) goto write_err;
            po_fut *fut = po_write_fut(write);

            if (par->f_flags & O_NONBLOCK)                                          {
                if (!file->type->ops->write_atomic)                   goto write_err;
                if (!file->type->ops->write_atomic(file->obj, write)) goto write_err;

                ssize_t ret = (ssize_t) po_fut_ret(fut);
                po_del(write);
                po_del(fut)  ;
                return ret   ;
            }


            if   (!file->type->ops->write)                   goto write_err;
            if   (!file->type->ops->write(file->obj, write)) goto write_err;
            while(po_fut_poll(fut) == po_fut_pend) schedule();

            ssize_t ret = (ssize_t) po_fut_ret(fut);
            po_del(write);
            po_del(fut)  ;
            return ret   ;
    write_err:
            po_del (write);
            po_del (fut)  ;
            return -EINVAL;
}

static long
    po_file_do_control
        (struct file* par, unsigned int par_code, unsigned long par_arg)                             {
            po_control *control = po_make (po_control) from (3, par->private_data, par_code, par_arg);
            po_file    *file    = par->private_data;

            if (po_trait_of(control) != po_control_t) goto control_err;
            if (po_trait_of(file)    != po_file_t)    goto control_err;

            po_fut *fut = po_control_fut(control);
            if (!file->type->ops->control)                     goto control_err;
            if (!file->type->ops->control(file->obj, control)) goto control_err;
            if (par->f_flags & O_NONBLOCK)                                     {
                po_del(fut);
                return 0;
            }

            while(po_fut_poll(fut) == po_fut_pend) schedule();
            ssize_t ret = (ssize_t) po_fut_ret(fut);
            po_del(fut) ;
            return ret  ;
    control_err:
            po_del   (fut);
            return -EINVAL;
}

static __poll_t
    po_file_do_poll
        (struct file* par, struct poll_table_struct* par_poll) {
            po_file *file = par->private_data;
            po_poll  poll = { .all = 0ull }  ;

            if (po_trait_of(file) != po_file_t) return 0;
            if (!file->type->ops->poll)         return 0;
            po_not *not = file->type->ops->poll (par->private_data, &poll);
            u64_t   ret = 0ull;

            if (poll.write_norm) ret |= POLLOUT   ;
            if (poll.write)      ret |= POLLWRNORM;
            if (poll.read_norm)  ret |= POLLRDNORM;
            if (poll.read)       ret |= POLLIN    ;

            if (po_trait_of(not) == po_not_t) poll_wait(par, &not->not, par_poll);
            return ret;
}

struct file_operations po_file_type_ops   = {
        .open           = po_file_do_open   ,
        .release        = po_file_do_close  ,
        .read           = po_file_do_read   ,
        .write          = po_file_do_write  ,
        .unlocked_ioctl = po_file_do_control,
        .compat_ioctl   = po_file_do_control,
        .poll           = po_file_do_poll
};

po_obj_trait po_file_type_trait = po_make_trait (
    po_file_type_new    ,
    po_file_type_clone  ,
    null_t              ,
    po_file_type_del    ,
    sizeof(po_file_type),
    null_t
);

po_obj_trait *po_file_type_t = &po_file_type_trait;

bool_t
    po_file_type_new
        (po_file_type* par_type, u32_t par_count, va_list par)                                 {
            po_file_ops  *ops   = null_t; if (par_count > 0) ops   = va_arg(par, po_file_ops*) ;
            po_obj_trait *trait = null_t; if (par_count > 1) trait = va_arg(par, po_obj_trait*);
            if (!trait) return false_t;
            if (!ops)   return false_t;

            par_type->type  = po_file_type_ops;
            par_type->trait = trait;
            par_type->ops   = ops  ;
            return true_t;
}

bool_t
    po_file_type_clone
        (po_file_type* par, po_file_type* par_clone) {
            par->trait = par_clone->trait;
            par->type  = par_clone->type ;
            par->ops   = par_clone->ops  ;
            return true_t;
}

void
    po_file_type_del
        (po_file_type* par) {
}

#include <linux/module.h>

MODULE_LICENSE("GPL");
EXPORT_SYMBOL(po_file_type_t);