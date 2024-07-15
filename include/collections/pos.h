#ifndef COLLECTIONS_POS_H
#define COLLECTIONS_POS_H

#include "../core.h"

extern pp_obj_trait *pp_pos_t;
typedef struct       pp_pos  { u8_t pp_pos[128]; } pp_pos;

pp_pos* pp_pos_next (pp_pos*, pp_pos*);
pp_pos* pp_pos_prev (pp_pos*, pp_pos*);

#ifndef __cplusplus
#define pp_next(par)               pp_pos_next (par, 0)
#define pp_next_as(par, par_next)  pp_pos_next (par, par_next)
#define pp_prev(par)               pp_pos_prev (par, 0)
#define pp_prev_as(par, par_prev)  pp_pos_prev (par, par_prev)
#endif

#endif