#ifndef __OPS_CAST_H__
#define __OPS_CAST_H__

#include "../type.h"

struct po_obj      ;
struct po_obj_trait;

typedef struct po_ops_cast                                        {
    struct po_obj* (*as)    (struct po_obj*, struct po_obj_trait*);
    i8_t           (*as_i8) (struct po_obj*);
    u8_t           (*as_u8) (struct po_obj*);

    i16_t          (*as_i16)(struct po_obj*);
    u16_t          (*as_u16)(struct po_obj*);
    
    i32_t          (*as_i32)(struct po_obj*);
    u32_t          (*as_u32)(struct po_obj*);
    
    i64_t          (*as_i64)(struct po_obj*);
    u64_t          (*as_u64)(struct po_obj*);
}   po_ops_cast;

#define po_make_cast_ops(par_as, par_as_i8, par_as_u8, par_as_i16, par_as_u16, par_as_i32, par_as_u32, par_as_i64, par_as_u64) {\
    .as     = ((struct po_obj*(*)(struct po_obj*, struct po_obj_trait*))(par_as)),\
    .as_i8  = ((i8_t          (*)(struct po_obj*)) (par_as_i8))                  ,\
    .as_u8  = ((u8_t          (*)(struct po_obj*)) (par_as_u8))                  ,\
    .as_i16 = ((i16_t         (*)(struct po_obj*))(par_as_i16))                  ,\
    .as_u16 = ((u16_t         (*)(struct po_obj*))(par_as_u16))                  ,\
    .as_i32 = ((i32_t         (*)(struct po_obj*))(par_as_i32))                  ,\
    .as_u32 = ((u32_t         (*)(struct po_obj*))(par_as_u32))                  ,\
    .as_i64 = ((i64_t         (*)(struct po_obj*))(par_as_i64))                  ,\
    .as_u64 = ((u64_t         (*)(struct po_obj*))(par_as_u64))                   \
}

struct po_obj* po_as    (struct po_obj*, struct po_obj_trait*);
i8_t           po_as_i8 (struct po_obj*);
u8_t           po_as_u8 (struct po_obj*);

i16_t          po_as_i16(struct po_obj*);
u16_t          po_as_u16(struct po_obj*);

i32_t          po_as_i32(struct po_obj*);
u32_t          po_as_u32(struct po_obj*);

i64_t          po_as_i64(struct po_obj*);
u64_t          po_as_u64(struct po_obj*);

#endif