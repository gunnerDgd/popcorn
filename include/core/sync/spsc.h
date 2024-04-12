#ifndef __SYNC_SPSC_H__
#define __SYNC_SPSC_H__

#include "../obj.h"
#include "../mem.h"

extern po_obj_trait *po_spsc_t;
typedef struct       po_spsc  { u8_t po_spsc[16 KB]; }   po_spsc;

bool_t  po_spsc_enq_try(po_spsc*, po_obj*);
void    po_spsc_enq    (po_spsc*, po_obj*);
po_obj* po_spsc_deq_try(po_spsc*);
po_obj* po_spsc_deq    (po_spsc*);

#endif