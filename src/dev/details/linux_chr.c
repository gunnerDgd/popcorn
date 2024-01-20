#include "linux_chr.h"
#include "linux_dev.h"

#include <linux/vmalloc.h>

po_obj_trait po_chr_trait           = {
    .on_new   = as_new  (po_chr_new)  ,
    .on_clone = as_clone(po_chr_clone),
    .on_ref   = 0                     ,
    .on_del   = as_del  (po_chr_del)  ,
    .size     = sizeof(po_dev)
};

po_obj_trait *po_chr_t = &po_chr_trait;

static int
    po_chr_do_open
        (struct inode* par_inode, struct file* par)                                 {
            if (!par_inode)        return -EINVAL; u64_t pos_chr = imajor(par_inode);
            if (!par)              return -EINVAL; u64_t pos     = iminor(par_inode);

            if (pos_chr >= (4 KB)) return -EINVAL;
            if (pos     >= (1 KB)) return -EINVAL;

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

            if (pos_chr >= (4 KB))  return -EINVAL;
            if (pos     >= (1 KB))  return -EINVAL;

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

            if (pos_chr >= (4 KB))  return -EINVAL;
            if (pos     >= (1 KB))  return -EINVAL;

            po_chr  *ret_chr = chr[pos_chr]     ; if (!ret_chr) return -EINVAL;
            po_dev  *ret     = ret_chr->dev[pos]; if (!ret)     return -EINVAL;
            po_ubuf *buf     = (po_ubuf*) make (po_ubuf_t) from (
                3      ,
                par_buf,
                par_len,
                par_off
            );

            if (!buf)                          return -EINVAL;
            if (trait_of(ret_chr) != po_chr_t) return -EINVAL;
            if (trait_of(ret)     != po_dev_t) return -EINVAL;

            return ret->ops->on_read (ret->obj, buf);
}

static ssize_t
    po_chr_do_write
        (struct file* par, const char* __user par_buf, size_t par_len, loff_t* par_off) {
            if (!par)               return -EINVAL; u64_t pos_chr = imajor(par->f_inode);
            if (!par->private_data) return -EINVAL; u64_t pos     = iminor(par->f_inode);
            if (!par_buf)           return -EINVAL;

            if (pos_chr >= (4 KB))  return -EINVAL;
            if (pos     >= (1 KB))  return -EINVAL;

            po_chr  *ret_chr = chr[pos_chr]     ; if (!ret_chr) return -EINVAL;
            po_dev  *ret     = ret_chr->dev[pos]; if (!ret)     return -EINVAL;
            po_ubuf *buf     = (po_ubuf*) make (po_ubuf_t) from (
                3      ,
                par_buf,
                par_len,
                par_off
            );

            if (!buf)                          return -EINVAL;
            if (trait_of(ret_chr) != po_chr_t) return -EINVAL;
            if (trait_of(ret)     != po_dev_t) return -EINVAL;

            return ret->ops->on_write (ret->obj, buf);
}

static long
    po_chr_do_control
        (struct file* par, u32 par_code, unsigned long par_arg)                         {
            if (!par)               return -EINVAL; u64_t pos_chr = imajor(par->f_inode);
            if (!par->private_data) return -EINVAL; u64_t pos     = iminor(par->f_inode);

            if (pos_chr >= (4 KB))  return -EINVAL;
            if (pos     >= (1 KB))  return -EINVAL;

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

po_chr                *chr[4 KB]     = { NULL,  };
struct file_operations chr_ops       = {
    .open           = po_chr_do_open   ,
    .release        = po_chr_do_close  ,

    .read           = po_chr_do_read   ,
    .write          = po_chr_do_write  ,
    .compat_ioctl   = po_chr_do_control,
    .unlocked_ioctl = po_chr_do_control
};

bool_t
    po_chr_new
        (po_chr* par_chr, u32_t par_count, va_list par) {
            const char* name  = va_arg(par, const char*);
            if (par_count != 1) return false_t;
            if (!name)          return false_t;

            cdev_init(&par_chr->chr, &chr_ops);
            if (alloc_chrdev_region(&par_chr->id , 0, 1 KB, name)     < 0) goto new_failed;
            if (cdev_add           (&par_chr->chr, par_chr->id, 1 KB) < 0) goto new_failed;

            if (!make_at(&par_chr->name, po_str_t)  from (0)) goto new_failed;
            if (!make_at(&par_chr->use , po_list_t) from (0)) goto new_failed;
            if (!make_at(&par_chr->free, po_list_t) from (0)) goto new_failed;

            po_str_push_back_cstr(&par_chr->name, name, strlen(name));
            chr[MAJOR(par_chr->id)] = par_chr;
            par_chr->num            = 0ull   ;
            return true_t;
    new_failed:
            cdev_del(&par_chr->chr);
            vfree   (par_chr->dev) ;

            del(&par_chr->use)     ;
            del(&par_chr->free)    ;
            del(&par_chr->name)    ;

            if (par_chr->id) unregister_chrdev_region(par_chr->id, 1 KB);
            return false_t;
}

bool_t
    po_chr_clone
        (po_chr* par, po_chr* par_clone)  {
            return false_t;
}

void
    po_chr_del
        (po_chr* par)                                     {
            po_list_while(&par->use, use)                 {
                po_dev *dev = po_list_get_as(use, po_dev*);
                if (!dev)                      goto next;
                if (trait_of(dev) != po_dev_t) goto next;
                if (dev->type != par)          goto next;

                use = po_list_next(use);
                po_chr_free(par, dev)  ;
                continue;
            next: use = po_list_next(use);
            }

            po_list_for(&par->free, free) del (po_list_get(free));
            unregister_chrdev_region(par->id, 1 KB);
            cdev_del                (&par->chr)    ;

            chr[MAJOR(par->id)] = NULL;
            del  (&par->use) ;
            del  (&par->free);
            del  (&par->name);
}

struct po_dev*
    po_chr_use
        (po_chr* par, struct po_dev* par_dev)                                                   {
            if (!par)                          return NULL                                      ;
            if (!par_dev)                      par_dev = (po_dev*) po_list_pop_front(&par->free);
            if (!par_dev)                      return NULL                                      ;

            if (trait_of(par)     != po_chr_t) return NULL;
            if (trait_of(par_dev) != po_dev_t) return NULL;
            if (par_dev->dev)                  return NULL;
            if (par_dev->id == -1)                                              {
                par_dev->type = (po_obj*) par; if (par->num == 1 KB) return NULL;
                par_dev->id   = par->num++   ;
            }

            par_dev->dev = device_create (
                par_dev->ns->ns          ,
                NULL                     ,
                par->id + par_dev->id    ,
                par_dev                  ,
                po_str_ptr(&par_dev->name)
            );

            if (!par_dev->dev) return NULL;
            par_dev->hnd              = po_list_push_back(&par->use, (po_obj*) par_dev);
            par    ->dev[par_dev->id] = par_dev;
            return par_dev;
}

void
    po_chr_free
        (po_chr* par, struct po_dev* par_dev)           {
            if (!par)                             return;
            if (!par_dev)                         return;

            if (trait_of(par)     != po_chr_t)    return;
            if (trait_of(par_dev) != po_dev_t)    return;

            if (!par_dev->ns)                     return;
            if (trait_of(par_dev->ns) != po_ns_t) return;
            if (par_dev->type != par)             return;

            if (!par_dev->ops)                    return;
            if (!par_dev->ops->on_del)            return;

            par_dev->ops->on_del(par_dev->obj);

            device_destroy(par_dev->ns->ns, par->id + par_dev->id);
            po_list_pop   (&par->use, par_dev->hnd)               ;

            par_dev->hnd              = po_list_push_back(&par->free, (po_obj*) par_dev);
            par    ->dev[par_dev->id] = NULL;
            par_dev->dev              = NULL;
}

#ifdef PO_PRESET_LINUX
#include <linux/module.h>

MODULE_LICENSE("GPL");
#endif