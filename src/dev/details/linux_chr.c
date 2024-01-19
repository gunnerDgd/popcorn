#include "linux_chr.h"
#include "linux_dev.h"

po_obj_trait po_chr_trait            = {
    .on_new   = as_new  (&po_chr_new)  ,
    .on_clone = as_clone(&po_chr_clone),
    .on_ref   = 0                      ,
    .on_del   = as_del  (&po_chr_del)  ,
    .size     = sizeof(po_dev)
};

po_obj_trait *po_chr_t = &po_chr_trait;

static int
    po_chr_do_open
        (struct inode* par_inode, struct file* par)                          {
            if (!par_inode) return -EINVAL; u64_t pos_chr = imajor(par_inode);
            if (!par)       return -EINVAL; u64_t pos     = iminor(par_inode);

            po_chr *ret_chr = chr[pos_chr]     ; if (!ret_chr) return -EINVAL;
            po_dev *ret     = ret_chr->dev[pos]; if (!ret)     return -EINVAL;

            if (trait_of(ret_chr) != po_chr_t)   return -EINVAL;
            if (trait_of(ret)     != po_dev_t)   return -EINVAL;
            if (!par->private_data)                            {
                par->private_data = ret                        ;
                if (!ret->ops->on_new(ret->obj)) return -EINVAL;
                return 0;
            }

            if (par->private_data != ret)     return -EINVAL;
            if (!ret->ops->on_open(ret->obj)) return -EINVAL;
            return 0;
}

static int
    po_chr_do_close
        (struct inode* par_inode, struct file* par)                                  {
            if (!par_inode)         return -EINVAL; u64_t pos_chr = imajor(par_inode);
            if (!par)               return -EINVAL; u64_t pos     = iminor(par_inode);
            if (!par->private_data) return -EINVAL;

            po_chr *ret_chr = chr[pos_chr]     ; if (!ret_chr) return -EINVAL;
            po_dev *ret     = ret_chr->dev[pos]; if (!ret)     return -EINVAL;

            if (trait_of(ret_chr) != po_chr_t) return -EINVAL;
            if (trait_of(ret)     != po_dev_t) return -EINVAL;

            ret->ops->on_close(ret->obj);
            return 0;
}

static ssize_t
    po_chr_do_read
        (struct file* par, char* __user par_buf, size_t par_len, loff_t* par_off)       {
            if (!par)               return -EINVAL; u64_t pos_chr = imajor(par->f_inode);
            if (!par->private_data) return -EINVAL; u64_t pos     = iminor(par->f_inode);
            if (!par_buf)           return -EINVAL;

            po_chr *ret_chr = chr[pos_chr]     ; if (!ret_chr) return -EINVAL;
            po_dev *ret     = ret_chr->dev[pos]; if (!ret)     return -EINVAL;

            if (trait_of(ret_chr) != po_chr_t) return -EINVAL;
            if (trait_of(ret)     != po_dev_t) return -EINVAL;

            po_buf *buf = (po_buf*) make (po_buf_t) from (3, par_buf, par_len, par_off);
            return ret->ops->on_read (ret->obj, buf);
}

static ssize_t
    po_chr_do_write
        (struct file* par, const char* __user par_buf, size_t par_len, loff_t* par_off) {
            if (!par)               return -EINVAL; u64_t pos_chr = imajor(par->f_inode);
            if (!par->private_data) return -EINVAL; u64_t pos     = iminor(par->f_inode);
            if (!par_buf)           return -EINVAL;

            po_chr *ret_chr = chr[pos_chr]     ; if (!ret_chr) return -EINVAL;
            po_dev *ret     = ret_chr->dev[pos]; if (!ret)     return -EINVAL;

            if (trait_of(ret_chr) != po_chr_t) return -EINVAL;
            if (trait_of(ret)     != po_dev_t) return -EINVAL;

            po_buf *buf = (po_buf*) make (po_buf_t) from (3, par_buf, par_len, par_off);
            return ret->ops->on_write (ret->obj, buf);
}

static long
    po_chr_do_control
        (struct file* par, u32 par_code, unsigned long par_arg)                         {
            if (!par)               return -EINVAL; u64_t pos_chr = imajor(par->f_inode);
            if (!par->private_data) return -EINVAL; u64_t pos     = iminor(par->f_inode);

            po_chr *ret_chr = chr[pos_chr]     ; if (!ret_chr) return -EINVAL;
            po_dev *ret     = ret_chr->dev[pos]; if (!ret)     return -EINVAL;

            if (trait_of(ret_chr) != po_chr_t) return -EINVAL;
            if (trait_of(ret)     != po_dev_t) return -EINVAL;

            return ret->ops->on_control (
                ret->obj       ,
                par_code       ,
                (void*) par_arg
            );
}

po_chr                *chr[4096]      = { NULL,  };
struct file_operations chr_ops        = {
    .open           = &po_chr_do_open   ,
    .release        = &po_chr_do_close  ,

    .read           = &po_chr_do_read   ,
    .write          = &po_chr_do_write  ,
    .compat_ioctl   = &po_chr_do_control,
    .unlocked_ioctl = &po_chr_do_control,
};

bool_t
    po_chr_new
        (po_chr* par_type, u32_t par_count, va_list par)  {
            const char* name  = va_arg(par, const char*);
            if (par_count != 1) return false_t;
            if (!name)          return false_t;

            cdev_init(&par_type->chr, &chr_ops);
            if (alloc_chrdev_region(&par_type->id, 0, 64 KB, name)       < 0) goto new_failed;
            if (cdev_add           (&par_type->chr, par_type->id, 64 KB) < 0) goto new_failed;

            if (!make_at(&par_type->name, po_str_t)  from (0)) goto new_failed;
            if (!make_at(&par_type->use , po_list_t) from (0)) goto new_failed;
            if (!make_at(&par_type->free, po_list_t) from (0)) goto new_failed;

            po_str_push_back_cstr(&par_type->name, name, strlen(name));
            par_type->num = 0;
            return true_t;
    new_failed:
            if (par_type->id) unregister_chrdev_region(par_type->id, 64 KB);
            del(&par_type->use) ;
            del(&par_type->free);
            del(&par_type->name);
            return false_t;
}

bool_t
    po_chr_clone
        (po_chr* par, po_chr* par_clone)  {
            return false_t;
}

void
    po_chr_del
        (po_chr* par)                                        {
            po_list_for(&par->use, dev_it)                   {
                po_dev *dev = po_list_get_as(dev_it, po_dev*); printk("chr_del - delete all use object\n");
                if (!dev)                      continue;
                if (trait_of(dev) != po_dev_t) continue;
                if (dev->type != par)          continue;

                po_chr_free(par, dev);
            }

            unregister_chrdev_region(par->id, 64 KB); printk("chr_del - delete region\n");
            cdev_del                (&par->chr)     ; printk("chr_del - delete cdev\n");

            chr[par->id] = NULL;
            del(&par->use)     ; printk("chr_del - delete use\n");
            del(&par->free)    ; printk("chr_del - delete free\n");
            del(&par->name)    ; printk("chr_del - delete name\n");
}

bool_t
    po_chr_use
        (po_chr* par, struct po_dev* par_dev)                                                   {
            if (!par)                          return false_t                                   ;
            if (!par_dev)                      par_dev = (po_dev*) po_list_pop_front(&par->free);
            if (!par_dev)                      return false_t                                   ;

            if (trait_of(par)     != po_chr_t) return false_t;
            if (trait_of(par_dev) != po_dev_t) return false_t;
            if (!par_dev->dev)                 return false_t;
            if (par_dev->id == -1)                                                  {
                par_dev->type = (po_obj*) par; if (par->num == 64 KB) return false_t;
                par_dev->id   = par->num     ;
            }

            if (par->dev[par_dev->id]) return false_t;
            par_dev->dev = device_create             (
                par_dev->ns->ns          ,
                NULL                     ,
                par->id + par_dev->id    ,
                par_dev                  ,
                po_str_ptr(&par_dev->name)
            );

            if (!par_dev->dev) return false_t;
            par_dev->hnd              = po_list_push_back(&par->use, (po_obj*) par_dev);
            par    ->dev[par_dev->id] = par_dev                                        ;
            par    ->num++;
            return true_t;
}

void
    po_chr_free
        (po_chr* par, struct po_dev* par_dev)           {
            if (!par)                             return;
            if (!par_dev)                         return;

            if (trait_of(par) != po_chr_t)        return;
            if (trait_of(par_dev) != po_dev_t)    return;

            if (!par_dev->ns)                     return;
            if (trait_of(par_dev->ns) != po_ns_t) return;
            if (par_dev->type != par)             return;

            device_destroy   (par_dev->ns->ns, par->id + par_dev->id);
            po_list_pop      (&par->use , par_dev->hnd)              ;

            par_dev->hnd          = po_list_push_back(&par->free, (po_obj*) par_dev);
            par->dev[par_dev->id] = NULL;
}

#ifdef PO_PRESET_LINUX
#include <linux/module.h>

MODULE_LICENSE("GPL");
#endif