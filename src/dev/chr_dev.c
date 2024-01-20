#include "chr_dev.h"

po_obj_trait po_chr_dev_trait           = {
    .on_new   = as_new  (po_chr_dev_new)  ,
    .on_clone = as_clone(po_chr_dev_clone),
    .on_ref   = NULL                      ,
    .on_del   = as_del  (po_chr_dev_del)  ,
    .size     = sizeof(po_chr_dev)
};

po_obj_trait* po_chr_dev_t = &po_chr_dev_trait;

bool_t
    po_chr_dev_new
        (po_chr_dev* par_dev, u32_t par_count, va_list par)                            {
            const char *name = NULL; if (par_count > 0) name = va_arg(par, const char*);
            po_ns      *ns   = NULL; if (par_count > 1) ns   = va_arg(par, po_ns     *);
            po_chr     *chr  = NULL; if (par_count > 2) chr  = va_arg(par, po_chr    *);
            po_dev_ops *ops  = NULL; if (par_count > 3) ops  = va_arg(par, po_dev_ops*);
            po_obj     *obj  = NULL; if (par_count > 4) obj  = va_arg(par, po_obj    *);

            if (!name)                     return false_t;
            if (!ns)                       return false_t;
            if (!chr)                      return false_t;
            if (!ops)                      return false_t;

            if (trait_of(ns)  != po_ns_t)  return false_t;
            if (trait_of(chr) != po_chr_t) return false_t;

            po_dev* ret = NULL;
            if ((ret = po_chr_use(chr, NULL))) {
                par_dev->dev = ret->hnd;
                return true_t;
            }

            ret = (po_dev*) make (po_dev_t) from  (
                4   ,
                name,
                ns  ,
                ops ,
                obj
            );

            if (!ret)     return false_t;
            if (!po_chr_use(chr, ret))  {
                del (ret)     ;
                return false_t;
            }

            par_dev->dev = ret->hnd          ;
            par_dev->chr = (po_chr*) ref(chr);
            return true_t;
}

bool_t
    po_chr_dev_clone
        (po_chr_dev* par, po_chr_dev* par_clone) {
            return false_t;
}

void
    po_chr_dev_del
        (po_chr_dev* par)                                  {
            po_dev *dev = po_list_get_as(par->dev, po_dev*);
            if (!dev)                      return;
            if (trait_of(dev) != po_dev_t) return;

            po_chr_free(par->chr, dev);
            del        (par->dev)     ;
}

i64_t
    po_chr_dev_read
        (po_chr_dev* par, po_ubuf* par_buf)                                                                 {
            if (!par)                             return -1; po_dev* dev = po_list_get_as(par->dev, po_dev*);
            if (!dev)                             return -1;
            if (!par_buf)                         return -1;

            if (trait_of(par_buf)   != po_ubuf_t) return -1;
            if (trait_of(dev)       != po_dev_t)  return -1;
            if (trait_of(dev->type) != po_chr_t)  return -1;
            if (dev->type != par->chr)            return -1;

            return dev->ops->on_read (dev->obj, par_buf);
}

i64_t
    po_chr_dev_write
        (po_chr_dev* par, po_ubuf* par_buf)                                                                 {
            if (!par)                             return -1; po_dev* dev = po_list_get_as(par->dev, po_dev*);
            if (!dev)                             return -1;
            if (!par_buf)                         return -1;

            if (trait_of(par_buf)   != po_ubuf_t) return -1;
            if (trait_of(dev)       != po_dev_t)  return -1;
            if (trait_of(dev->type) != po_chr_t)  return -1;
            if (dev->type != par->chr)            return -1;

            return dev->ops->on_write (dev->obj, par_buf);
}

i64_t
    po_chr_dev_control
        (po_chr_dev* par, u32_t par_control, void* par_arg)                                                {
            if (!par)                            return -1; po_dev* dev = po_list_get_as(par->dev, po_dev*);
            if (!dev)                            return -1;
            if (trait_of(dev) != po_dev_t)       return -1;

            if (dev->type != dev->type)          return -1;
            if (trait_of(dev->type) != po_chr_t) return -1;

            return dev->ops->on_control (
                   dev->obj   ,
                   par_control,
                   par_arg
            );
}

#ifdef PO_PRESET_LINUX
#include <linux/module.h>

MODULE_LICENSE("GPL");
#endif