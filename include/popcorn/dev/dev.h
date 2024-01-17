#ifndef __PO_DEV_DEV_H__
#define __PO_DEV_DEV_H__

#include "../core.h"
#include "dev_type.h"

typedef void*  po_dev       ;
typedef struct po_dev_ops   {
    bool_t (*on_new)(po_dev);
    bool_t (*on_ref)(po_dev);
    void   (*on_del)(po_dev);
}   po_dev_ops;

po_dev  po_dev_create(const char*, po_dev_type, po_dev_ops*, po_obj*);
void    po_dev_free  (po_dev);
po_str* po_dev_name  (po_dev);

#endif
