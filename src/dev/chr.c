#include "chr.h"

po_chr_dev
    po_chr_dev_new
        (const char* par_name, po_ns* par_ns, po_chr* par_chr, po_dev_ops* par_ops, po_obj* par) {
            if (!par_chr)                         return NULL    ; po_dev* ret = NULL;
            if (trait_of(par_chr) != po_chr_t)    return NULL    ;
            if ((ret = po_chr_use(par_chr, ret))) return ret->hnd;

            ret = (po_dev*) make (po_dev_t) from  (
                4       ,
                par_name,
                par_ns  ,
                par_ops ,
                par
            );

            if (!ret)           return NULL;
            if (!po_chr_use(par_chr, ret)) {
                del (ret)  ;
                return NULL;
            }

            return ret->hnd;
}

void
    po_chr_dev_del
        (po_chr_dev par)                               {
            po_dev* dev = po_list_get_as(par, po_dev*) ;
            if (!dev)                            return;
            if (trait_of(dev) != po_dev_t)       return;

            po_chr_free((po_chr*) dev->type, dev);
}

i64_t
    po_chr_dev_read
        (po_chr_dev par, po_buf* par_buf)                                                             {
            if (!par)                            return -1; po_dev* dev = po_list_get_as(par, po_dev*);
            if (!dev)                            return -1;
            if (!par_buf)                        return -1;

            if (trait_of(par_buf) != po_buf_t)   return -1;
            if (trait_of(dev)     != po_dev_t)   return -1;

            if (!dev->type)                      return -1;
            if (trait_of(dev->type) != po_chr_t) return -1;

            return dev->ops->on_read (dev->obj, par_buf);
}

i64_t
    po_chr_dev_write
        (po_chr_dev par, po_buf* par_buf)                                                             {
            if (!par)                            return -1; po_dev* dev = po_list_get_as(par, po_dev*);
            if (!dev)                            return -1;
            if (!par_buf)                        return -1;

            if (trait_of(par_buf) != po_buf_t)   return -1;
            if (trait_of(dev)     != po_dev_t)   return -1;

            if (!dev->type)                      return -1;
            if (trait_of(dev->type) != po_chr_t) return -1;

            return dev->ops->on_write (dev->obj, par_buf);
}

i64_t
    po_chr_dev_control
        (po_chr_dev par, u32_t par_control, void* par_arg)                                            {
            if (!par)                            return -1; po_dev* dev = po_list_get_as(par, po_dev*);
            if (!dev)                            return -1;
            if (trait_of(dev)      != po_dev_t)  return -1;

            if (!dev->type)                      return -1;
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