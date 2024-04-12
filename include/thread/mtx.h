#ifndef __PO_SYNC_MTX_H__
#define __PO_SYNC_MTX_H__

#include <core.h>

extern po_obj_trait   *po_mtx_t;
typedef struct         po_mtx { u8_t po_mtx[64]; } po_mtx;

bool_t po_mtx_lock_try(po_mtx*);
void   po_mtx_lock    (po_mtx*);
void   po_mtx_unlock  (po_mtx*);

#endif
