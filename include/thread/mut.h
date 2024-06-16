#ifndef __PO_THREAD_MTX_H__
#define __PO_THREAD_MTX_H__

#include "../core.h"

extern po_obj_trait   *po_mut_t;
typedef struct         po_mut { u8_t po_mtx[64]; } po_mut;

bool_t po_mut_lock_try(po_mut*);
void   po_mut_lock    (po_mut*);
void   po_mut_unlock  (po_mut*);

#endif
