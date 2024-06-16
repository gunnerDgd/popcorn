#ifndef __BMA_H__
#define __BMA_H__

#include "../core.h"

extern po_obj_trait *po_bma_t;
typedef struct       po_bma  { u8_t po_set[64]; } po_bma;

bool_t po_bma_out_lock(po_bma*, any_t*);
bool_t po_bma_out     (po_bma*, any_t*);
bool_t po_bma_in_lock (po_bma*, any_t);
bool_t po_bma_in      (po_bma*, any_t);

#endif