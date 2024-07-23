#include "str.h"

static pp_str*
    do_add
        (pp_str* self, pp_str* arg)                         {
            if (pp_trait_of(self) != pp_str_t) return null_t;
            if (pp_trait_of(arg)  != pp_str_t) return null_t;
            pp_str* ret = pp_make (pp_str) from (0);

            if (pp_trait_of(ret) != pp_str_t) return null_t;
            pp_seq_push_back(&ret->str, &self->str, pp_str_len(self));
            pp_seq_push_back(&ret->str, &arg ->str, pp_str_len(arg)) ;
            return ret;
}

static pp_str*
    do_add_eq
        (pp_str* self, pp_str* arg)                         {
            if (pp_trait_of(self) != pp_str_t) return null_t;
            if (pp_trait_of(arg)  != pp_str_t) return null_t;

            pp_seq_push_back(&self->str, &arg->str, pp_str_len(arg));
            return self;
}

static pp_str*
    do_mul
        (pp_str* self, u64_t num)                           {
            if (pp_trait_of(self) != pp_str_t) return null_t;
            if (!num)                          return null_t;
            pp_str* ret = pp_make (pp_str) from (0);

            if (pp_trait_of(ret) != pp_str_t) return null_t;
            while (num --) pp_seq_push_back(&ret->str, &self->str, pp_str_len(self));
            return ret;
}

static pp_arith
    do_arith = pp_make_arith (
        do_add   ,
        null_t   ,
        do_mul   ,
        null_t   ,
        null_t   ,
        do_add_eq,
        null_t   ,
        null_t   ,
        null_t   ,
        null_t
);

static pp_ord_t
    do_ord
        (pp_str* self, pp_str* arg)                             {
            if (pp_trait_of(self) != pp_str_t) return pp_ord_err;
            if (pp_trait_of(arg)  != pp_str_t) return pp_ord_err;
            u64_t len;

            len = min (pp_str_len(self), pp_str_len(arg));
            return pp_mem_ord    (
                pp_str_ptr(self),
                pp_str_ptr(arg) ,
                len
            );
}

static pp_cmp
    do_cmp = pp_make_cmp (
        do_ord
);

static pp_obj_ops
    do_ops =              {
        .arith = &do_arith,
        .cmp   = &do_cmp
};

static bool_t
    do_new
        (pp_str* self, u32_t count, va_list arg)                         {
            pp_mem *mem = null_t; if (count > 0) mem = va_arg(arg, any_t);
            if (pp_trait_of(mem) != pp_mem_t) mem = pp_get_mem();
            if (pp_trait_of(mem) != pp_mem_t) return false_t;

            if (!pp_make_at(&self->str, pp_seq) from (2, 16, mem)) return false_t;
            return true_t;
}

static bool_t
    do_clone
        (pp_str* self, pp_str* clone)                  {
            return pp_clone_at(&self->str, &clone->str);
}

static void
    do_del
        (pp_str* self)        {
            pp_del(&self->str);
}

static pp_obj_trait
    do_obj = pp_make_trait (
        do_new        ,
        do_clone      ,
        null_t        ,
        do_del        ,
        sizeof(pp_str),
        &do_ops
);

pp_obj_trait *pp_str_t = &do_obj;


void
    pp_str_push_front
        (pp_str* self, const char* push, u64_t len)  {
            if (pp_trait_of(self) != pp_str_t) return;
            pp_seq_push_front   (
                &self->str,
                push      ,
                len
            );
}

void
    pp_str_push_back
        (pp_str* self, const char* push, u64_t len)  {
            if (pp_trait_of(self) != pp_str_t) return;
            pp_seq_push_back    (
                &self->str,
                push      ,
                len
            );
}

void
    pp_str_push
        (pp_str* self, const char* push, u64_t len, u64_t off) {
            if (pp_trait_of(self) != pp_str_t) return;
            pp_seq_push    (
                &self->str,
                push      ,
                len       ,
                off
            );
}

void
    pp_str_pop_front
        (pp_str* self, u64_t len)                    {
            if (pp_trait_of(self) != pp_str_t) return;
            pp_seq_pop_front(&self->str, len);
}

void
    pp_str_pop_back
        (pp_str* self, u64_t len)                    {
            if (pp_trait_of(self) != pp_str_t) return;
            pp_seq_pop_back(&self->str, len);
}

void
    pp_str_pop
        (pp_str* self, u64_t len, u64_t off)         {
            if (pp_trait_of(self) != pp_str_t) return;
            pp_seq_pop     (
                &self->str,
                len       ,
                off
            );
}

pp_ord_t
    pp_str_ord
        (pp_str* self, const char* arg, u64_t len)              {
            if (pp_trait_of(self) != pp_str_t) return pp_ord_err;
            if (!arg)                          return pp_ord_err;
            u8_t* pos = pp_str_ptr(self);

            for (u64_t i = 0 ; i < len ; ++i)        {
                if (pos[i] > arg[i]) return pp_ord_gt;
                if (pos[i] < arg[i]) return pp_ord_lt;
                if (arg[i] == '\0')  return pp_ord_gt;
            }

            if (arg[len] != '\0') return pp_ord_lt;
            return pp_ord_eq;
}

bool_t pp_str_gt_eq(pp_str* self, const char* arg, u64_t len) { pp_ord_t ord = pp_str_ord(self, arg, len); return ord == pp_ord_gt || ord == pp_ord_eq; }
bool_t pp_str_lt_eq(pp_str* self, const char* arg, u64_t len) { pp_ord_t ord = pp_str_ord(self, arg, len); return ord == pp_ord_lt || ord == pp_ord_eq; }

bool_t pp_str_gt(pp_str* self, const char* arg, u64_t len) { return pp_str_ord(self, arg, len) == pp_ord_gt; }
bool_t pp_str_lt(pp_str* self, const char* arg, u64_t len) { return pp_str_ord(self, arg, len) == pp_ord_lt; }
bool_t pp_str_eq(pp_str* self, const char* arg, u64_t len) { return pp_str_ord(self, arg, len) == pp_ord_eq; }
bool_t pp_str_ne(pp_str* self, const char* arg, u64_t len) { return pp_str_ord(self, arg, len) != pp_ord_eq; }

void
    pp_str_prep_front
        (pp_str* self, u64_t len)                    {
            if (pp_trait_of(self) != pp_str_t) return;
            pp_seq_prep_front(&self->str, len);
}

void
    pp_str_prep_back
        (pp_str* self, u64_t len)                    {
            if (pp_trait_of(self) != pp_str_t) return;
            pp_seq_prep_back (&self->str, len);
}

u64_t
    pp_str_find
        (pp_str* self, u64_t off, const char* find, u64_t len) {
            if (pp_trait_of(self) != pp_str_t) return -1;
            return pp_mem_find                          (
                pp_str_ptr(self) + off,
                find                  ,
                pp_str_len(self)      ,
                len
            );
}

bool_t
    pp_str_begin
        (pp_str* self, const char* cmp, u64_t len)           {
            if (pp_trait_of(self) != pp_str_t) return false_t;
            u64_t ret = pp_str_find          (
                self,
                0   ,
                cmp ,
                len
            );

            return ret == 0;
}

bool_t
    pp_str_end
        (pp_str* self, const char* cmp, u64_t len)           {
            if (pp_trait_of(self) != pp_str_t) return false_t;
            u64_t  off = pp_str_len  (self) - len;
            u64_t  ret = pp_str_find (
                self,
                off ,
                cmp ,
                len
            );

            return ret == off;
}

bool_t      pp_str_empty(pp_str* self) { if (pp_trait_of(self) != pp_str_t) return true_t; return pp_seq_empty(&self->str); }
u64_t       pp_str_len  (pp_str* self) { if (pp_trait_of(self) != pp_str_t) return 0;      return pp_seq_len  (&self->str); }
const char* pp_str_ptr  (pp_str* self) { if (pp_trait_of(self) != pp_str_t) return null_t; return pp_seq_ptr  (&self->str); }

#ifdef PRESET_LINUX
#include <linux/module.h>

MODULE_LICENSE("GPL");

EXPORT_SYMBOL(pp_str_prep_front);
EXPORT_SYMBOL(pp_str_prep_back);

EXPORT_SYMBOL(pp_str_push_front);
EXPORT_SYMBOL(pp_str_push_back);
EXPORT_SYMBOL(pp_str_push);

EXPORT_SYMBOL(pp_str_pop_front);
EXPORT_SYMBOL(pp_str_pop_back);
EXPORT_SYMBOL(pp_str_pop);

EXPORT_SYMBOL(pp_str_find);
EXPORT_SYMBOL(pp_str_begin);
EXPORT_SYMBOL(pp_str_end);
EXPORT_SYMBOL(pp_str_empty);
EXPORT_SYMBOL(pp_str_len);
EXPORT_SYMBOL(pp_str_ptr);
EXPORT_SYMBOL(pp_str_t);
#endif