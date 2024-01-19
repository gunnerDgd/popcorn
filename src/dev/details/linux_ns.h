#ifndef __PO_LINUX_NS_H__
#define __PO_LINUX_NS_H__

#include "../../core.h"
#include <linux/device.h>

extern po_obj_trait *po_ns_t;
typedef struct       po_ns  {
    po_obj        head;
    po_str        name;
    struct class *ns  ;
}   po_ns;

bool_t po_ns_new  (po_ns*, u32_t, va_list);
bool_t po_ns_clone(po_ns*, po_ns*)        ;
void   po_ns_del  (po_ns*)                ;

#endif