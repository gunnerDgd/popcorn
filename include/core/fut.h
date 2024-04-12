#ifndef __FUT_H__
#define __FUT_H__

#include "obj.h"

#define        po_fut_ready 0
#define        po_fut_pend  1
#define        po_fut_err   2
typedef struct po_fut_ops {
    u64_t (*poll)(po_obj*);
    void* (*ret) (po_obj*);
}   po_fut_ops;

#ifndef __cplusplus
#define po_make_fut_ops(par_poll, par_ret) {\
    .poll = ((u64_t(*)(po_obj*))(par_poll)),\
    .ret  = ((void*(*)(po_obj*))(par_ret)) ,\
}
#endif

extern po_obj_trait* po_fut_t;
typedef struct       po_fut  { u8_t po_fut[128]; }   po_fut;

u64_t  po_fut_poll (po_fut*);
void*  po_fut_ret  (po_fut*);

#endif