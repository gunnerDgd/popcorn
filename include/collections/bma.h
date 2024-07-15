#ifndef COLLECTIONS_BMA_H
#define COLLECTIONS_BMA_H

#include "../core.h"

extern pp_obj_trait *pp_bma_t;
typedef struct       pp_bma  { u8_t pp_bma[64]; } pp_bma;

bool_t pp_bma_lock_out(pp_bma*, any_t*);
bool_t pp_bma_lock_in (pp_bma*, any_t);
bool_t pp_bma_out     (pp_bma*, any_t*);
bool_t pp_bma_in      (pp_bma*, any_t);

#endif