#ifndef __PO_DEV_CLASS_H__
#define __PO_DEV_CLASS_H__

#include <obj.h>
#include <str.h>

#include <linux/device.h>

extern po_obj_trait *po_class_t;
typedef struct       po_class  {
    po_obj        head ;
    struct class *class;
    po_str        name ;
}   po_class;

bool_t po_class_new  (po_class*, u32_t, va_list);
bool_t po_class_clone(po_class*, po_class*)     ;
void   po_class_del  (po_class*)                ;

#endif