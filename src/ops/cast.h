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