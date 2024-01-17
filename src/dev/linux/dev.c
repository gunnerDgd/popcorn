#include "details/dev.h"
#include "details/dev_type.h"

void*
    po_new_dev
        (const char* par_name, po_dev_type* par_type, po_dev_ops* par_ops, po_obj* par) {
            dev_t   dev_id = par_type->dev.count                             ;
            po_dev *dev    = (po_dev*) po_list_pop_front(&par_type->dev.free);

            if (!dev)                       {
                return make (po_dev_t) from (
                    5       ,
                    par_name,
                    par_type,
                    par_ops ,
                    par     ,
                    dev_id
                );
            }

            po_list_pop(&par_type->dev.free, dev->hnd)                            ;
            dev->hnd     = po_list_push_back(&par_type->dev.active, (po_obj*) dev);
            dev->state   = po_dev_active                                          ;
            dev->dev_hnd = device_create (
                par_type->cls        ,
                NULL                 ,
                par_type->id + dev_id,
                dev                  ,
                par_name
            );

            if (!dev->dev_hnd) goto create_failed; par_type->dev.all[dev_id] = dev;
            return dev->hnd;
    create_failed:
            po_list_pop(&par_type->dev.active, dev->hnd)                      ;
            dev->state = po_dev_free                                          ;
            dev->hnd   = po_list_push_back(&par_type->dev.free, (po_obj*) dev);
            return NULL;
}

void
    po_del_dev
        (void* par)                                   {
            po_dev *dev = po_list_get_as(par, po_dev*);
            if (!dev)                           return;
            if (trait_of(dev) != po_dev_t)      return;
            if (dev->state == po_dev_free)      return;

            po_dev_wait   (dev, po_dev_free)                       ;
            device_destroy(dev->type->cls, dev->type->id + dev->id);
            po_list_pop   (&dev->type->dev.active, dev->hnd)       ;

            dev->state                  = po_dev_free                                           ;
            dev->hnd                    = po_list_push_back(&dev->type->dev.free, (po_obj*) dev);
            dev->dev_hnd                = NULL                                                  ;
            dev->type->dev.all[dev->id] = NULL                                                  ;
}

void
    po_wait_dev
        (void* par, u64_t par_state)                  {
            po_dev *dev = po_list_get_as(par, po_dev*);
            if (!dev)                      return;
            if (trait_of(dev) != po_dev_t) return;

            po_dev_wait(dev, par_state);
}

po_str*
    po_name_dev
        (void* par)                                   {
            po_dev *dev = po_list_get_as(par, po_dev*);
            if (!dev)                      return NULL;
            if (trait_of(dev) != po_dev_t) return NULL;

            return po_dev_name(dev);
}

EXPORT_SYMBOL(po_new_dev) ;
EXPORT_SYMBOL(po_del_dev) ;

EXPORT_SYMBOL(po_wait_dev);
EXPORT_SYMBOL(po_name_dev);

EXPORT_SYMBOL(po_dev_t)   ;