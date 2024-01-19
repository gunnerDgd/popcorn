#include "dev.h"

po_str*
    po_dev_name
        (void* par)                                                                               {
            if (!par)                      return NULL; po_dev* dev = po_list_get_as(par, po_dev*);
            if (!dev)                      return NULL;
            if (trait_of(dev) != po_dev_t) return NULL;

            return &dev->name;
}

po_obj*
    po_dev_type
        (void* par)                                                                               {
            if (!par)                      return NULL; po_dev* dev = po_list_get_as(par, po_dev*);
            if (!dev)                      return NULL;
            if (trait_of(dev) != po_dev_t) return NULL;

            return (po_obj*) &dev->type;
}

#ifdef PO_PRESET_LINUX
#include <linux/module.h>

MODULE_LICENSE("GPL");
#endif