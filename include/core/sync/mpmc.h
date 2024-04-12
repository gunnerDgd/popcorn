#ifndef __SYNC_MPMC_H__
#define __SYNC_MPMC_H__

#include "../obj.h"
#include "../mem.h"

extern po_obj_trait *po_mpmc_t;
typedef struct       po_mpmc  { u8_t po_mpmc[16 KB]; } po_mpmc;

bool_t  po_mpmc_enq_try(po_mpmc*, po_obj*);
void    po_mpmc_enq    (po_mpmc*, po_obj*);
po_obj* po_mpmc_deq_try(po_mpmc*);
po_obj* po_mpmc_deq    (po_mpmc*);

#endif