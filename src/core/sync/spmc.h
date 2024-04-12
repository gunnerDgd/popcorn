#ifndef __SYNC_SPMC_H__
#define __SYNC_SPMC_H__

#include "../obj.h"
#include "../mem.h"

extern po_obj_trait *po_spmc_t;
typedef struct       po_spmc  {
    po_obj  head      ;
    po_obj *spmc[1 KB];
    u64_t   enq,
            deq;
}   po_spmc;

bool_t  po_spmc_new    (po_spmc*, u32_t, va_list);
bool_t  po_spmc_clone  (po_spmc*, po_spmc*)      ;
void    po_spmc_del    (po_spmc*)                ;

bool_t  po_spmc_enq_try(po_spmc*, po_obj*);
void    po_spmc_enq    (po_spmc*, po_obj*);
po_obj* po_spmc_deq_try(po_spmc*);
po_obj* po_spmc_deq    (po_spmc*);

#endif