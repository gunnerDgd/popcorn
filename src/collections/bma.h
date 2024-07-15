#ifndef COLLECTIONS_BMA_H
#define COLLECTIONS_BMA_H

#include "../core.h"

extern pp_obj_trait *pp_bma_t;
typedef struct       pp_bma  {
    pp_obj head;
    any_t  bma[PRESET_ARCH_BIT];
    reg_t  out;
    reg_t  in ;
}   pp_bma;

bool_t pp_bma_lock_out(pp_bma*, any_t*);
bool_t pp_bma_lock_in (pp_bma*, any_t);
bool_t pp_bma_out     (pp_bma*, any_t*);
bool_t pp_bma_in      (pp_bma*, any_t);

#endif