#ifndef __SYNC_MPMC_H__
#define __SYNC_MPMC_H__

#include "../obj.h"
#include "../mem.h"

extern po_obj_trait *po_mpmc_t;
typedef struct       po_mpmc  {
    po_obj  head      ;
    po_obj* mpmc[1 KB];
    u64_t   enq,
            deq;
}   po_mpmc;

bool_t  po_mpmc_new    (po_mpmc*, u32_t, va_list);
bool_t  po_mpmc_clone  (po_mpmc*, po_mpmc*)      ;
void    po_mpmc_del    (po_mpmc*)                ;

bool_t  po_mpmc_enq_try(po_mpmc*, po_obj*);
void    po_mpmc_enq    (po_mpmc*, po_obj*);
po_obj* po_mpmc_deq_try(po_mpmc*);
po_obj* po_mpmc_deq    (po_mpmc*);

#endif