#ifndef COLLECTIONS_SCQ_H
#define COLLECTIONS_SCQ_H

#include "../core.h"

extern pp_obj_trait *pp_scq_t;
typedef struct       pp_scq { u8_t scq[128]; } pp_scq;

bool_t  pp_scq_empty     (pp_scq*);

bool_t  pp_enq_lock_try  (pp_scq*, pp_obj*);
bool_t  pp_enq_lock      (pp_scq*, pp_obj*);

bool_t  pp_enq_try       (pp_scq*, pp_obj*);
bool_t  pp_enq           (pp_scq*, pp_obj*);

pp_obj* pp_deq_lock_try  (pp_scq*);
pp_obj* pp_deq_lock      (pp_scq*);

pp_obj* pp_deq_try       (pp_scq*);
pp_obj* pp_deq           (pp_scq*);

#endif
