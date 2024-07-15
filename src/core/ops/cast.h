#ifndef CORE_OPS_CAST_H
#define CORE_OPS_CAST_H

#include "../type.h"

struct pp_obj      ;
struct pp_obj_trait;

typedef struct pp_cast                                            {
    struct pp_obj* (*as)    (struct pp_obj*, struct pp_obj_trait*);
    i8_t           (*as_i8) (struct pp_obj*);
    u8_t           (*as_u8) (struct pp_obj*);

    i16_t          (*as_i16)(struct pp_obj*);
    u16_t          (*as_u16)(struct pp_obj*);
    
    i32_t          (*as_i32)(struct pp_obj*);
    u32_t          (*as_u32)(struct pp_obj*);
    
    i64_t          (*as_i64)(struct pp_obj*);
    u64_t          (*as_u64)(struct pp_obj*);

    any_t          (*as_any)(struct pp_obj*);
}   pp_cast;

#define pp_make_cast(do_as, do_as_i8, do_as_u8, do_as_i16, do_as_u16, do_as_i32, do_as_u32, do_as_i64, do_as_u64, do_as_any) {\
    .as     = ((struct pp_obj*(*)(struct pp_obj*, struct pp_obj_trait*))(do_as)),\
    .as_i8  = ((i8_t          (*)(struct pp_obj*))(do_as_i8))                   ,\
    .as_u8  = ((u8_t          (*)(struct pp_obj*))(do_as_u8))                   ,\
    .as_i16 = ((i16_t         (*)(struct pp_obj*))(do_as_i16))                  ,\
    .as_u16 = ((u16_t         (*)(struct pp_obj*))(do_as_u16))                  ,\
    .as_i32 = ((i32_t         (*)(struct pp_obj*))(do_as_i32))                  ,\
    .as_u32 = ((u32_t         (*)(struct pp_obj*))(do_as_u32))                  ,\
    .as_i64 = ((i64_t         (*)(struct pp_obj*))(do_as_i64))                  ,\
    .as_u64 = ((u64_t         (*)(struct pp_obj*))(do_as_u64))                  ,\
    .as_any = ((any_t         (*)(struct pp_obj*))(do_as_any))                   \
}

struct pp_obj* pp_as    (struct pp_obj*, struct pp_obj_trait*);
i8_t           pp_as_i8 (struct pp_obj*);
u8_t           pp_as_u8 (struct pp_obj*);

i16_t          pp_as_i16(struct pp_obj*);
u16_t          pp_as_u16(struct pp_obj*);

i32_t          pp_as_i32(struct pp_obj*);
u32_t          pp_as_u32(struct pp_obj*);

i64_t          pp_as_i64(struct pp_obj*);
u64_t          pp_as_u64(struct pp_obj*);

any_t          pp_as_any(struct pp_obj*);

#endif