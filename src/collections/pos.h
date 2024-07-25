#ifndef COLLECTIONS_POS_H
#define COLLECTIONS_POS_H

#include "../core.h"

extern pp_obj_trait *pp_pos_t ;
typedef struct       pp_pos   {
    pp_obj         head       ;
    struct pp_pos *prev, *next;
    union          {
        any_t   any;
        pp_obj* obj;

        u64_t   u64;
        i64_t   i64;

        u32_t   u32;
        i32_t   i32;

        u16_t   u16;
        i16_t   i16;

        u8_t    u8;
        i8_t    i8;
    };
}   pp_pos;

pp_pos* pp_pos_next (pp_pos*, pp_pos*);
pp_pos* pp_pos_prev (pp_pos*, pp_pos*);

#ifndef __cplusplus
#define pp_next(par)               pp_pos_next (par, null_t)
#define pp_next_as(par, par_next)  pp_pos_next (par, par_next)
#define pp_prev(par)               pp_pos_prev (par, null_t)
#define pp_prev_as(par, par_prev)  pp_pos_prev (par, par_prev)
#endif

#endif