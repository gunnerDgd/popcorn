#ifndef __PO_DEV_DEV_H__
#define __PO_DEV_DEV_H__

#include <core.h>
#include <collections.h>
#include <linux/device.h>

struct po_class;
extern po_obj_trait *po_dev_t;
typedef struct       po_dev  {
    po_obj         head;
    struct device *dev ;
}   po_dev;

bool_t po_dev_new  (po_dev*, u32_t, va_list);
bool_t po_dev_clone(po_dev*, po_dev*)       ;
void   po_dev_del  (po_dev*)                ;

#endif
