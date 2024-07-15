#include "pos.h"

static i8_t  do_as_i8 (pp_pos* self) { if (pp_trait_of(self) != pp_pos_t) return 0; return self->i8; }
static u8_t  do_as_u8 (pp_pos* self) { if (pp_trait_of(self) != pp_pos_t) return 0; return self->u8; }

static i16_t do_as_i16(pp_pos* self) { if (pp_trait_of(self) != pp_pos_t) return 0; return self->i16; }
static u16_t do_as_u16(pp_pos* self) { if (pp_trait_of(self) != pp_pos_t) return 0; return self->u16; }

static i32_t do_as_i32(pp_pos* self) { if (pp_trait_of(self) != pp_pos_t) return 0; return self->i32; }
static u32_t do_as_u32(pp_pos* self) { if (pp_trait_of(self) != pp_pos_t) return 0; return self->u32; }

static i64_t do_as_i64(pp_pos* self) { if (pp_trait_of(self) != pp_pos_t) return 0; return self->i64; }
static u64_t do_as_u64(pp_pos* self) { if (pp_trait_of(self) != pp_pos_t) return 0; return self->u64; }

static any_t do_as_any(pp_pos* self) { if (pp_trait_of(self) != pp_pos_t) return null_t; return self->any; }

static pp_obj*
    do_as
        (pp_pos* self, pp_obj_trait *as)                    {
            if (pp_trait_of(self) != pp_pos_t) return null_t;
            if (!as)                           return null_t;
            pp_obj* ret = self->obj;

            if (pp_trait_of(ret) == as) return ret;
            return null_t;
}

static pp_cast
    do_cast = pp_make_cast (
        do_as    ,
        do_as_i8 ,
        do_as_u8 ,
        do_as_i16,
        do_as_u16,
        do_as_i32,
        do_as_u32,
        do_as_i64,
        do_as_u64,
        do_as_any
);

static pp_obj_ops
    do_ops =            {
        .cast = &do_cast
};

static bool_t
    do_new
        (pp_pos* self, u32_t count, va_list arg)                        {
            any_t pos  = null_t; if (count > 0) pos = va_arg(arg, any_t);
            self->next = null_t;
            self->prev = null_t;
            self->any  = pos;
            return true_t;
}

static bool_t
    do_clone
        (pp_pos* self, pp_pos* clone) {
            return false_t;
}

static void
    do_del
        (pp_pos* self)                                   {
            if (self->prev) self->prev->next = self->next;
            if (self->next) self->next->prev = self->prev;
}

static pp_obj_trait
    do_obj = pp_make_trait (
        do_new        ,
        do_clone      ,
        null_t        ,
        do_del        ,
        sizeof(pp_pos),
    null_t
);

pp_obj_trait* pp_pos_t = &do_obj;

pp_pos*
    pp_pos_next
        (pp_pos* self, pp_pos* next)                            {
            if (pp_trait_of(self) != pp_pos_t) return     null_t;
            if (!next)                         return self->next;

            if (pp_trait_of(next) != pp_pos_t) return null_t;
            self->next = next;
            next->prev = self;
            return next;
}

pp_pos*
    pp_pos_prev
        (pp_pos* self, pp_pos* prev)                            {
            if (pp_trait_of(self) != pp_pos_t) return     null_t;
            if (!prev)                         return self->prev;

            if (pp_trait_of(prev) != pp_pos_t) return null_t;
            self->prev = prev;
            prev->next = self;
            return prev;
}

#ifdef PRESET_LINUX
#include <linux/module.h>
MODULE_LICENSE("GPL");

EXPORT_SYMBOL(pp_pos_next);
EXPORT_SYMBOL(pp_pos_prev);
EXPORT_SYMBOL(pp_pos_t);
#endif