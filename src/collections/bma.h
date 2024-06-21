#ifndef __BMA_H__
#define __BMA_H__

#include "../core.h"

extern po_obj_trait *po_bma_t;
typedef struct       po_bma  {
    po_obj head;
    any_t  bma[PRESET_ARCH_BIT];
    reg_t  out;
    reg_t  in ;
}   po_bma;

bool_t po_bma_new  (po_bma*, u32_t, va_list);
bool_t po_bma_clone(po_bma*, po_bma*)       ;
void   po_bma_del  (po_bma*)                ;

bool_t po_bma_out_lock(po_bma*, any_t*);
bool_t po_bma_out     (po_bma*, any_t*);
bool_t po_bma_in_lock (po_bma*, any_t);
bool_t po_bma_in      (po_bma*, any_t);

#endif