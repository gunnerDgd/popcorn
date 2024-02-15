#ifndef __SYNC_MPSC_H__
#define __SYNC_MPSC_H__

#include "../obj.h"

extern po_obj_trait *po_mpsc_t;
typedef struct       po_mpsc  {
    po_obj  head;
    po_obj *mpsc[1 KB];
    u64_t   enq,
            deq;
}   po_mpsc;

bool_t po_mpsc_new     (po_mpsc*, u32_t, va_list);
bool_t po_mpsc_clone   (po_mpsc*, po_mpsc*)      ;
void   po_mpsc_del     (po_mpsc*)                ;

bool_t  po_mpsc_enq_try(po_mpsc*, po_obj*);
void    po_mpsc_enq    (po_mpsc*, po_obj*);
po_obj* po_mpsc_deq_try(po_mpsc*);
po_obj* po_mpsc_deq    (po_mpsc*);

#endif