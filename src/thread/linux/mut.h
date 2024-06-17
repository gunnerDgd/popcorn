#ifndef __PO_SYNC_MTX_H__
#define __PO_SYNC_MTX_H__

#include "../../po.h"
#include <linux/mutex.h>

extern po_obj_trait *po_mut_t;
typedef struct       po_mut  {
    po_obj       head;
    struct mutex mut ;
}   po_mut;

bool_t po_mut_new     (po_mut*, u32_t, va_list);
bool_t po_mut_clone   (po_mut*, po_mut*)       ;
void   po_mut_del     (po_mut*)                ;

bool_t po_mut_lock_try(po_mut*);
void   po_mut_lock    (po_mut*);
void   po_mut_unlock  (po_mut*);

#endif