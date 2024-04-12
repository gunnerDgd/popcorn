#ifndef __PO_SYNC_MTX_H__
#define __PO_SYNC_MTX_H__

#include <core.h>

extern po_obj_trait *po_mtx_t;
typedef struct       po_mtx  {
    po_obj       head;
    struct mutex mtx ;
}   po_mtx;

bool_t po_mtx_new     (po_mtx*, u32_t, va_list);
bool_t po_mtx_clone   (po_mtx*, po_mtx*)       ;
void   po_mtx_del     (po_mtx*)                ;

bool_t po_mtx_lock_try(po_mtx*);
void   po_mtx_lock    (po_mtx*);
void   po_mtx_unlock  (po_mtx*);

#endif