#include "chr.h"
#include "dev.h"
#include "../dev.h"

#include "read.h"
#include "write.h"
#include "con.h"

#include "../../sync/not.h"

#include <linux/poll.h>

static int
    po_chr_dev_do_open
        (struct inode* par, struct file* par_file)                      {
            po_chr_dev *dev = container_of(par->i_cdev, po_chr_dev, chr);
            po_chr     *chr = container_of(par->i_fop , po_chr    , ops);
            if (po_trait_of(dev) != po_chr_dev_t) return -EINVAL;
            if (po_trait_of(chr) != po_chr_t)     return -EINVAL;
            par_file->private_data = po_obj_new                 (
                null_t    ,
                dev->trait,
                2         ,
                chr       ,
                dev
            );

            if (!par_file->private_data) return -EINVAL;
            po_ref(dev);
            po_ref(chr);
            return 0;
}

static int
    po_chr_dev_do_close
        (struct inode* par, struct file* par_file)                      {
            po_chr_dev *dev = container_of(par->i_cdev, po_chr_dev, chr);
            po_chr     *chr = container_of(par->i_fop , po_chr    , ops);
            if (po_trait_of(dev) != po_chr_dev_t) return -EINVAL;
            if (po_trait_of(chr) != po_chr_t)     return -EINVAL;
            po_del(par_file->private_data);
            po_del(dev);
            po_del(chr);
            return 0;
}

static ssize_t
    po_chr_dev_do_read
        (struct file* par, __user char* par_buf, size_t par_len, loff_t* par_off) {
            po_chr_dev *dev = container_of(par->f_inode->i_cdev, po_chr_dev, chr);
            po_chr     *chr = container_of(par->f_op           , po_chr    , ops);
            if (po_trait_of(dev)               != po_chr_dev_t) return -EINVAL;
            if (po_trait_of(chr)               != po_chr_t)     return -EINVAL;
            if (po_trait_of(par->private_data) != dev->trait)   return -EINVAL;
            po_chr_read* read = po_make (po_chr_read) from                    (
                3      ,
                dev    ,
                par_buf,
                par_len
            );

            po_fut *fut = po_chr_read_fut(read);
            if (!dev->ops->read(par->private_data, read)) {
                po_del  (read);
                return -EINVAL;
            }

            if (!(par->f_flags & O_NONBLOCK)) while(po_fut_poll(fut) == po_fut_pend) schedule();
            ssize_t ret = (ssize_t) po_fut_ret(fut);
            return  ret;
}

static ssize_t
    po_chr_dev_do_write
        (struct file* par, __user const char* par_buf, size_t par_len, loff_t* par_off) {
            po_chr_dev *dev = container_of(par->f_inode->i_cdev, po_chr_dev, chr);
            po_chr     *chr = container_of(par->f_op           , po_chr    , ops);
            if (po_trait_of(dev)               != po_chr_dev_t) return -EINVAL;
            if (po_trait_of(chr)               != po_chr_t)     return -EINVAL;
            if (po_trait_of(par->private_data) != dev->trait)   return -EINVAL;
            po_chr_write* write = po_make (po_chr_write) from                 (
                3      ,
                dev    ,
                par_buf,
                par_len
            );

            po_fut *fut = po_chr_write_fut(write);
            if (!dev->ops->write(par->private_data, write)) {
                po_del (write);
                po_del (fut)  ;
                return -EINVAL;
            }

            if (!(par->f_flags & O_NONBLOCK)) while(po_fut_poll(fut) == po_fut_pend) schedule();
            ssize_t ret = (ssize_t) po_fut_ret(fut);
            return  ret;
}

static long
    po_chr_dev_do_con
        (struct file* par, unsigned int par_cmd, unsigned long par_arg)          {
            po_chr_dev *dev = container_of(par->f_inode->i_cdev, po_chr_dev, chr);
            po_chr     *chr = container_of(par->f_op           , po_chr    , ops);
            if (po_trait_of(dev)               != po_chr_dev_t) return -EINVAL;
            if (po_trait_of(chr)               != po_chr_t)     return -EINVAL;
            if (po_trait_of(par->private_data) != dev->trait)   return -EINVAL;
            po_chr_con *con = po_make (po_chr_con) from                       (
                3      ,
                dev    ,
                par_cmd,
                par_arg
            );

            po_fut *fut = po_chr_con_fut(con);
            if (!dev->ops->con(par->private_data, con)) {
                po_del(con)   ;
                po_del(fut)   ;
                return -EINVAL;
            }

            ssize_t ret = (ssize_t) po_fut_ret(fut);
            return  ret;
}

static __poll_t
    po_chr_dev_do_poll
        (struct file* par, struct poll_table_struct* par_poll)                   {
            po_chr_dev *dev = container_of(par->f_inode->i_cdev, po_chr_dev, chr);
            po_chr     *chr = container_of(par->f_op           , po_chr    , ops);
            if (po_trait_of(dev)               != po_chr_dev_t) return -1;
            if (po_trait_of(chr)               != po_chr_t)     return -1;
            if (po_trait_of(par->private_data) != dev->trait)   return -1;
            po_chr_poll stat = { .all = 0ull }                          ;
            u64_t       ret  = 0ull                                     ;
            po_not     *poll = dev->ops->poll (par->private_data, &stat);
            if (stat.write_norm) ret |= POLLOUT   ;
            if (stat.write)      ret |= POLLWRNORM;
            if (stat.read_norm)  ret |= POLLRDNORM;
            if (stat.read)       ret |= POLLIN    ;

            if (po_trait_of(poll) == po_not_t) poll_wait(par, &poll->not, par_poll);
            return ret;
}

struct file_operations po_chr_dev_ops  = {
    .open           = po_chr_dev_do_open ,
    .release        = po_chr_dev_do_close,
    .read           = po_chr_dev_do_read ,
    .write          = po_chr_dev_do_write,
    .unlocked_ioctl = po_chr_dev_do_con  ,
    .compat_ioctl   = po_chr_dev_do_con  ,
    .poll           = po_chr_dev_do_poll
};

po_obj_trait po_chr_trait = po_make_trait (
    po_chr_new    ,
    po_chr_clone  ,
    null_t        ,
    po_chr_del    ,
    sizeof(po_chr),
    null_t
);

po_obj_trait *po_chr_t = &po_chr_trait;

bool_t
    po_chr_new
        (po_chr* par_chr, u32_t par_count, va_list par)                              {
            po_str* name = null_t    ; if (par_count > 0) name = va_arg(par, po_str*);
            u64_t   maj  = 0         ; if (par_count > 1) maj  = va_arg(par, u64_t)  ;
            u64_t   min  = shl(1, 19); if (par_count > 2) min  = va_arg(par, u64_t)  ;
            if (po_trait_of(name) != po_str_t)                goto new_err;
            if (!po_make_at(&par_chr->name, po_str) from (0)) goto new_err;
            po_str_push_back(&par_chr->name, name);

            if (alloc_chrdev_region(&par_chr->maj, maj, min, po_str_as_raw(name)) < 0) goto new_err;
            par_chr->ops = po_chr_dev_ops;
            par_chr->min = min           ;
            return true_t;
    new_err:
            po_del(&par_chr->name);
            return false_t;
}

bool_t
    po_chr_clone
        (po_chr* par, po_chr* par_clone)  {
            return false_t;
}

void
    po_chr_del
        (po_chr* par)                                   {
            unregister_chrdev_region(par->maj, par->min);
            po_del(&par->name);
}

MODULE_LICENSE("GPL");