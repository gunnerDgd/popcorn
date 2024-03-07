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
        (po_class* par_cls, u32_t par_count, va_list par)                                    {
            po_str       *name = null_t; if (par_count > 0) name = va_arg(par, po_str*)      ;
            po_class_ops *ops  = null_t; if (par_count > 1) ops  = va_arg(par, po_class_ops*);
            po_obj       *obj  = null_t; if (par_count > 2) obj  = va_arg(par, po_obj*)      ;
            if (po_trait_of (name) != po_str_t)                return false_t;
            if (!po_make_at (&par_cls->name, po_str) from (0)) return false_t;
            if (!ops)                                          return false_t;
            if (!ops->add)                                     return false_t;
            if (!ops->del)                                     return false_t;
            po_str_push_back(&par_cls->name, name);

            par_cls->class.name = po_str_as_raw(&par_cls->name);
            if (class_register(&par_cls->class))               {
                po_del(&par_cls->name);
                return false_t;
            }

            par_cls->type.add_dev        = po_class_do_add;
            par_cls->type.remove_dev     = po_class_do_del;
            par_cls->type.class          = &par_cls->class;
            if (class_interface_register(&par_cls->type)) {
                class_unregister(&par_cls->class);
                po_del          (&par_cls->name) ;
                return false_t;
            }

            par_cls->obj = po_ref(obj);
            par_cls->ops = ops        ;
            return true_t;
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

#ifdef PO_PRESET_LINUX
#include <linux/module.h>

MODULE_LICENSE("GPL");
#endif