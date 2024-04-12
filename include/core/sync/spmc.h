#ifndef __SYNC_SPMC_H__
#define __SYNC_SPMC_H__

#include "../obj.h"
#include "../mem.h"

extern po_obj_trait *po_spmc_t;
typedef struct       po_spmc  { u8_t po_spmc[16 KB]; } po_spmc;

bool_t  po_spmc_enq_try(po_spmc*, po_obj*);
void    po_spmc_enq    (po_spmc*, po_obj*);
po_obj* po_spmc_deq_try(po_spmc*);
po_obj* po_spmc_deq    (po_spmc*);

#endif