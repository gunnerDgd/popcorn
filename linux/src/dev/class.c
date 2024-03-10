#include "class.h"
#include "dev.h"

int
    po_class_do_add
        (struct device *par)                                                                                            {
            po_class *class = container_of(par->class, po_class, class); if (po_trait_of(class) != po_class_t) return -1;
            po_dev   *dev   = po_new      (po_dev)                     ; if (!dev)                             return -1;
            dev->head.trait = po_dev_t    ;
            dev->head.ref   = 1           ;
            dev->head.mem   = po_get_mem();
            dev->dev        = par         ;

            if (!class->ops->add(class->obj, dev)) {
                po_drop(dev);
                return    -1;
            }

            po_ref(class);
            return 0;
}

void
    po_class_do_del
        (struct device *par)                                                                                         {
            po_class *class = container_of(par->class, po_class, class); if (po_trait_of(class) != po_class_t) return;
            po_dev   *dev   = po_new      (po_dev)                     ; if (!dev)                             return;
            dev->head.trait = po_dev_t    ;
            dev->head.ref   = 1           ;
            dev->head.mem   = po_get_mem();
            dev->dev        = par         ;

            if (!class->ops->add(class->obj, dev)) {
                po_drop(dev);
                return;
            }

            po_del(class);
}

struct class_interface po_class_do = {
    .add_dev    = po_class_do_add,
    .remove_dev = po_class_do_del
};

po_obj_trait po_class_trait = po_make_trait (
    po_class_new    ,
    po_class_clone  ,
    null_t          ,
    po_class_del    ,
    sizeof(po_class),
    null_t
);

po_obj_trait *po_class_t = &po_class_trait;

bool_t
    po_class_new
        (po_class* par_cls, u32_t par_count, va_list par) {
            cstr_t name = cstr_from_va(par);
            if (!name.str)   return false_t;
            if (!name.len)   return false_t;

            po_class_ops *ops  = null_t; if (par_count > 2) ops  = va_arg(par, po_class_ops*);
            po_obj       *obj  = null_t; if (par_count > 3) obj  = va_arg(par, po_obj*)      ;
            if (!po_make_at (&par_cls->name, po_str) from (0)) return false_t;
            po_str_push_back_cstr(&par_cls->name, name);

            par_cls->class.name = po_str_as_raw(&par_cls->name);
            if (class_register(&par_cls->class)) goto new_err;
            if (par_count == 2)                              {
                par_cls->obj = po_ref(obj);
                par_cls->ops = null_t     ;
                return true_t;
            }

            par_cls->type       = po_class_do    ;
            par_cls->type.class = &par_cls->class;
            if (!ops)      goto new_err;
            if (!ops->add) goto new_err;
            if (!ops->del) goto new_err;

            if (class_interface_register(&par_cls->type)) {
                class_unregister(&par_cls->class);
                po_del          (&par_cls->name) ;
                return false_t;
            }

            par_cls->obj = po_ref(obj);
            par_cls->ops = ops        ;
            return true_t;
    new_err:
            po_del(&par_cls->name);
            return false_t;
}

bool_t
    po_class_clone
        (po_class* par, po_class* par_clone) {
            return false_t;
}

void
    po_class_del
        (po_class* par)                            {
            class_interface_unregister(&par->type) ;
            class_unregister          (&par->class);
            po_del(&par->name);
            po_del(par->obj)  ;
}

struct po_dev*
    po_class_find_cstr
        (po_class* par, cstr_t par_find)                     {
            if (po_trait_of(par) != po_class_t) return null_t;
            if (!par_find.str)                  return null_t;
            if (!par_find.len)                  return null_t;
            return po_class_find_raw                         (
                par         ,
                par_find.str,
                par_find.len
            );
}

struct po_dev*
    po_class_find_raw
        (po_class* par, const char* par_str, u64_t par_len)  {
            if (po_trait_of(par) != po_class_t) return null_t;
            if (!par_str)                       return null_t;
            if (!par_len)                       return null_t;

            struct device *dev = class_find_device_by_name(&par->class, par_str); if (IS_ERR(dev)) return null_t;
            po_dev        *ret = po_new(po_dev)                                 ; if (!ret)        return null_t;
            ret->head.trait = po_dev_t    ;
            ret->head.mem   = po_get_mem();
            ret->head.ref   = 1           ;

            ret->dev = get_device(dev);
            return ret;
}

struct po_dev*
    po_class_find
        (po_class* par, po_str* par_find)                         {
            if (po_trait_of(par_find) != po_str_t)   return null_t;
            if (po_trait_of(par)      != po_class_t) return null_t;
            return po_class_find_raw                              (
                par                    ,
                po_str_as_raw(par_find),
                po_str_len   (par_find)
            );
}

#ifdef PO_PRESET_LINUX
#include <linux/module.h>

MODULE_LICENSE("GPL");
#endif