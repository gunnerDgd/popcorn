#ifndef __PO_BOX_H__
#define __PO_BOX_H__

#include "obj.h"
#include "mem.h"

extern po_obj_trait* po_box_t;
typedef struct       po_box  {
    po_obj   head;
    po_mem*  res ;
    void*    mem ;
    u64_t    size;
}   po_box;

bool_t po_box_new  (po_box*, u32_t, va_list);
bool_t po_box_clone(po_box*, po_box*)       ;
bool_t po_box_ref  (po_box*)                ;
void   po_box_del  (po_box*)                ;

void*  po_box_ptr  (po_box*);
u64_t  po_box_size (po_box*);

#endif