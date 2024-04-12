#ifndef __SYNC_MPSC_H__
#define __SYNC_MPSC_H__

#include "../obj.h"
#include "../mem.h"

extern po_obj_trait *po_mpsc_t;
typedef struct       po_mpsc  { u8_t po_mpsc[16 KB]; } po_mpsc;

bool_t  po_mpsc_enq_try(po_mpsc*, po_obj*);
void    po_mpsc_enq    (po_mpsc*, po_obj*);
po_obj* po_mpsc_deq_try(po_mpsc*);
po_obj* po_mpsc_deq    (po_mpsc*);

#endif