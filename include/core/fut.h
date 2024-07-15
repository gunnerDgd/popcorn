#ifndef CORE_FUT_H
#define CORE_FUT_H

#include "obj.h"

#define        pp_fut_ready 0
#define        pp_fut_pend  1
#define        pp_fut_err   2
typedef struct pp_fut_ops {
    u64_t (*poll)(pp_obj*);
    void* (*ret) (pp_obj*);
}   pp_fut_ops;

#ifndef __cplusplus
#define pp_make_fut_ops(par_poll, par_ret) {\
    .poll = ((u64_t(*)(pp_obj*))(par_poll)),\
    .ret  = ((void*(*)(pp_obj*))(par_ret)) ,\
}
#endif

extern pp_obj_trait* pp_fut_t;
typedef struct       pp_fut  { u8_t pp_fut[128]; }   pp_fut;

u64_t  pp_fut_poll (pp_fut*);
void*  pp_fut_ret  (pp_fut*);

#endif