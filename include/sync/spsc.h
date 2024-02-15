#ifndef __SYNC_SPSC_H__
#define __SYNC_SPSC_H__

#include "../obj.h"

extern po_obj_trait *po_spsc_t;
typedef struct       po_spsc  {
    po_obj  head      ;
    po_obj* spsc[1 KB];
    u64_t   enq,
            deq;
}   po_spsc;

bool_t  po_spsc_new    (po_spsc*, u32_t, va_list);
bool_t  po_spsc_clone  (po_spsc*, po_spsc*)      ;
void    po_spsc_del    (po_spsc*)                ;

bool_t  po_spsc_enq_try(po_spsc*, po_obj*);
void    po_spsc_enq    (po_spsc*, po_obj*);
po_obj* po_spsc_deq_try(po_spsc*);
po_obj* po_spsc_deq    (po_spsc*);

#endif