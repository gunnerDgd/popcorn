#include "dev_type.h"
#include "po_dev.h"

po_obj_trait po_dev_type_trait                                          = {
        .on_new   = (bool_t(*)(po_obj*, u32_t, va_list))&po_dev_type_new  ,
        .on_clone = (bool_t(*)(po_obj*, po_obj*))       &po_dev_type_clone,
        .on_ref   = 0                                                     ,
        .on_del   = (void  (*)(po_obj*))                &po_dev_type_del  ,
        .size     = sizeof(po_dev)
};

po_obj_trait *po_dev_type_t = &po_dev_type_trait;

static int
    po_dev_do_open
        (struct inode* par_inode, struct file* par)                                                           {
            if (!par_inode)                          return -EINVAL; u64_t        pos_type = imajor(par_inode);
            if (!par)                                return -EINVAL; u64_t        pos      = iminor(par_inode);

            if (!dev_type[pos_type])                 return -EINVAL; po_dev_type *ret_type = dev_type         [pos];
            if (!ret_type->dev.all[pos])             return -EINVAL; po_dev      *ret      = ret_type->dev.all[pos];

            if (trait_of(ret_type) != po_dev_type_t) return -EINVAL;
            if (trait_of(ret)      != po_dev_t)      return -EINVAL;
            if (ret->type != ret_type)               return -EINVAL;

            if (!par->private_data)                            {
                if (!ret->ops->on_new(ret->dev)) return -EINVAL;
                par->private_data = ret->hnd;
                return 0;
            }

            po_dev* ret_priv = po_list_get_as(par->private_data, po_dev*);
            if (!ret_priv)                      return -EINVAL;
            if (trait_of(ret_priv) != po_dev_t) return -EINVAL;
            if (!ret->ops->on_ref(ret->dev))    return -EINVAL;

            ref(ret_priv);
            return 0;
}

static int
    po_dev_do_close
        (struct inode* par_inode, struct file* par)                                   {
            if (!par_inode)         return -EINVAL; u64_t pos_type = imajor(par_inode);
            if (!par)               return -EINVAL; u64_t pos      = iminor(par_inode);
            if (!par->private_data) return -EINVAL;

            po_dev_type *ret_type = dev_type[pos_type]                        ;
            po_dev      *ret      = po_list_get_as(par->private_data, po_dev*);

            if (!ret)                                    return -EINVAL;
            if (!ret_type)                               return -EINVAL;

            if (trait_of(ret_type)     != po_dev_type_t) return -EINVAL;
            if (trait_of(ret)          != po_dev_t)      return -EINVAL;
            if (ret_type->dev.all[pos] != ret)           return -EINVAL;

            ret->ops->on_del(ret->dev);
            return 0;
}

static ssize_t
    po_dev_do_read
        (struct file* par, char* __user par_buf, size_t par_len, loff_t* par_off)        {
            if (!par)               return -EINVAL; u64_t pos_type = imajor(par->f_inode);
            if (!par->private_data) return -EINVAL; u64_t pos      = iminor(par->f_inode);
            if (!par_buf)           return -EINVAL;

            po_dev_type *ret_type = dev_type[pos_type];
            po_dev      *ret      = po_list_get_as(par->private_data, po_dev*);

            if (!ret)                                    return -EINVAL;
            if (!ret_type)                               return -EINVAL;

            if (trait_of(ret_type)     != po_dev_type_t) return -EINVAL;
            if (trait_of(ret)          != po_dev_t)      return -EINVAL;
            if (ret_type->dev.all[pos] != ret)           return -EINVAL;

            ret->state = po_dev_busy;
            po_buf *ret_buf = (po_buf*) make (po_buf_t) from (3, par_buf, par_len, par_off);
            i64_t   res     = ret->ops->on_read (ret->dev, ret_buf)                        ;

            del   (ret_buf); ret->state = po_dev_active;
            return res     ;
}

static ssize_t
    po_dev_do_write
        (struct file* par, const char* __user par_buf, size_t par_len, loff_t* par_off)  {
            if (!par)               return -EINVAL; u64_t pos_type = imajor(par->f_inode);
            if (!par->private_data) return -EINVAL; u64_t pos      = iminor(par->f_inode);
            if (!par_buf)           return -EINVAL;

            po_dev_type *ret_type = dev_type[pos_type];
            po_dev      *ret      = po_list_get_as(par->private_data, po_dev*);

            if (!ret)                                    return -EINVAL;
            if (!ret_type)                               return -EINVAL;

            if (trait_of(ret_type)     != po_dev_type_t) return -EINVAL;
            if (trait_of(ret)          != po_dev_t)      return -EINVAL;
            if (ret_type->dev.all[pos] != ret)           return -EINVAL;

            ret->state = po_dev_busy;
            po_buf *ret_buf = (po_buf*) make (po_buf_t) from (3, par_buf, par_len, par_off);
            i64_t   res     = ret->ops->on_write (ret->dev, ret_buf)                       ;

            del   (ret_buf); ret->state = po_dev_active;
            return res     ;
}

static long
    po_dev_do_control
        (struct file* par, u32 par_code, unsigned long par_arg)                          {
            if (!par)               return -EINVAL; u64_t pos_type = imajor(par->f_inode);
            if (!par->private_data) return -EINVAL; u64_t pos      = iminor(par->f_inode);

            po_dev_type *ret_type = dev_type[pos_type]                        ;
            po_dev      *ret      = po_list_get_as(par->private_data, po_dev*);
            if (!ret)                                return -EINVAL;
            if (trait_of(ret) != po_dev_t)           return -EINVAL;

            if (!ret_type)                           return -EINVAL;
            if (trait_of(ret_type) != po_dev_type_t) return -EINVAL;

            ret->state = po_dev_busy  ; i64_t res = ret->ops->on_control (ret->dev, par_code, (void*)par_arg);
            ret->state = po_dev_active;
            return res;
}

po_dev_type           *dev_type[4096] = { NULL,  };
struct file_operations dev_type_ops   = {
    .open           = &po_dev_do_open   ,
    .release        = &po_dev_do_close  ,

    .read           = &po_dev_do_read   ,
    .write          = &po_dev_do_write  ,
    .compat_ioctl   = &po_dev_do_control,
    .unlocked_ioctl = &po_dev_do_control,
};

bool_t
    po_dev_type_new
        (po_dev_type* par_type, u32_t par_count, va_list par)                            {
            const char* name  = NULL; if (par_count > 0) name  = va_arg(par, const char*);
            u64_t       count = 1 MB; if (par_count > 1) count = va_arg(par, u64_t)      ;

            cdev_init(&par_type->hnd, &dev_type_ops);
            if (alloc_chrdev_region(&par_type->id, 0, count, name)       < 0) goto new_failed;
            if (cdev_add           (&par_type->hnd, par_type->id, count) < 0) goto new_failed;

            if (!make_at(&par_type->name      , po_str_t)  from (0)) goto new_failed;
            if (!make_at(&par_type->dev.active, po_list_t) from (0)) goto new_failed;
            if (!make_at(&par_type->dev.free  , po_list_t) from (0)) goto new_failed; par_type->cls = class_create(name);
            if (!par_type->cls)                                      goto new_failed;

            po_str_push_back_cstr(&par_type->name, name, strlen(name));
            return true_t;
    new_failed:
            if (par_type->id)  unregister_chrdev_region(par_type->id, 1 MB);
            if (par_type->cls) class_destroy           (par_type->cls)     ;

            del(&par_type->dev.active);
            del(&par_type->dev.free)  ;
            del(&par_type->name)      ;
            return false_t;
}

bool_t
    po_dev_type_clone
        (po_dev_type* par, po_dev_type* par_clone)  {
            return false_t;
}

void
    po_dev_type_del
        (po_dev_type* par)                                   {
            po_list_while(&par->dev.active, dev_it)          {
                po_dev *dev = po_list_get_as(dev_it, po_dev*);
                if (!dev)                      continue;
                if (trait_of(dev) != po_dev_t) continue;

                dev_it = po_list_next(dev_it);
                del(dev);
            }

            unregister_chrdev_region(par->id, 1 MB);
            class_destroy           (par->cls)     ;

            del(&par->dev.active);
            del(&par->dev.free)  ;
            del(&par->name)      ;
}