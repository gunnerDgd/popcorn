#ifndef __PO_DEV_DEV_H__
#define __PO_DEV_DEV_H__

#include <obj.h>
#include <str.h>
#include <linux/device.h>

struct po_class;

extern po_obj_trait *po_dev_t;
typedef struct       po_dev  {
    po_obj           head ;
    struct po_class *class;
    po_str           name;
    po_obj          *type;
    struct device   *dev ;
    dev_t            id  ;
}   po_dev;

bool_t po_dev_new  (po_dev*, u32_t, va_list);
bool_t po_dev_clone(po_dev*, po_dev*)       ;
void   po_dev_del  (po_dev*)                ;

bool_t po_dev_use  (po_dev*);
void   po_dev_free (po_dev*);

#endif
