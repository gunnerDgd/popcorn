#include "str.h"

po_obj_trait po_str_trait = po_make_trait (
    po_str_new    ,
    po_str_clone  ,
    null_t        ,
    po_str_del    ,
    sizeof(po_str),
    null_t
);

po_obj_trait *po_str_t = &po_str_trait;

bool_t
    po_str_new
        (po_str* par_str, u32_t par_count, va_list par)                      {
            po_mem *mem = null_t; if (par_count > 0) mem = va_arg(par, void*);
            if (po_trait_of(mem) != po_mem_t) mem = po_get_mem();
            if (po_trait_of(mem) != po_mem_t) return false_t;

            if (!po_make_at(&par_str->str, po_seq) from (2, 16, mem)) return false_t;
            return true_t;
}

bool_t po_str_clone(po_str* par, po_str* par_clone) { return po_clone_at(&par->str, &par_clone->str); }
void   po_str_del  (po_str* par)		            { po_del(&par->str); }

void
    po_str_push_back
        (po_str* par, po_str* par_push)                  {
            if (po_trait_of(par_push) != po_str_t) return;
            if (po_trait_of(par_push) != po_str_t) return;
            u64_t   len = po_seq_len(&par_push->str);
            void   *src = po_seq_ptr(&par_push->str);
            po_seq *dst = &par->str;

            po_seq_push_back(dst, src, len);
}

void
    po_str_push_front
        (po_str* par, po_str* par_push)                  {
            if (po_trait_of(par_push) != po_str_t) return;
            if (po_trait_of(par_push) != po_str_t) return;
            u64_t   len = po_seq_len(&par_push->str);
            void   *src = po_seq_ptr(&par_push->str);
            po_seq *dst = &par->str;

            po_seq_push_front(dst, src, len);
}

void
    po_str_push
        (po_str* par, po_str* par_push, u64_t par_off)   {
            if (po_trait_of(par_push) != po_str_t) return;
            if (po_trait_of(par_push) != po_str_t) return;
            u64_t len = po_seq_len(&par_push->str);
            void *src = po_seq_ptr(&par_push->str);
            po_seq  *dst = &par->str;

            po_seq_push(dst, src, len, par_off);
}

void
    po_str_push_front_cstr
        (po_str* par, const char* par_push, u64_t par_len) {
            if (po_trait_of(par) != po_str_t) return;
            po_seq_push_front                       (
                &par->str,
                par_push ,
                par_len
            );
}

void
    po_str_push_back_cstr
        (po_str* par, const char* par_push, u64_t par_len) {
            if (po_trait_of(par) != po_str_t) return;
            po_seq_push_back                        (
                &par->str,
                par_push ,
                par_len
            );
}

void
    po_str_push_cstr
        (po_str* par, const char* par_push, u64_t par_len, u64_t par_off) {
            if (po_trait_of(par) != po_str_t) return;
            po_seq_push                             (
                &par->str,
                par_push ,
                par_len  ,
                par_off
            );
}

void
    po_str_pop_front
        (po_str* par, u64_t par_len)                {
            if (po_trait_of(par) != po_str_t) return;
            po_seq_pop_front(&par->str, par_len);
}

void
    po_str_pop_back
        (po_str* par, u64_t par_len)                {
            if (po_trait_of(par) != po_str_t) return;
            po_seq_pop_back(&par->str, par_len);
}

void
    po_str_pop
        (po_str* par, u64_t par_len, u64_t par_off) {
            if (po_trait_of(par) != po_str_t) return;
            po_seq_pop                              (
                &par->str,
                par_len,
                par_off
            );
}

void
po_str_prep_front
        (po_str* par, u64_t par_len)                {
            if (po_trait_of(par) != po_str_t) return;
            po_seq_prep_front(&par->str, par_len);
}

void
    po_str_prep_back
        (po_str* par, u64_t par_len)                {
            if (po_trait_of(par) != po_str_t) return;
            po_seq_prep_back (&par->str, par_len);
}

u64_t
    po_str_find
        (po_str* par, u64_t par_off, po_str* par_find)      {
            if (po_trait_of(par_find) != po_str_t) return -1;
            if (po_trait_of(par)      != po_str_t) return -1;
            return po_mem_find                              (
                po_str_ptr(par) + par_off,
                po_str_ptr(par_find)     ,
                po_str_len(par)          ,
                po_str_len(par_find)
            );
}

u64_t
    po_str_find_cstr
        (po_str* par, u64_t par_off, const char* par_find, u64_t par_len) {
            if (po_trait_of(par_find) != po_str_t) return -1;
            return po_mem_find                              (
                po_str_ptr(par) + par_off,
                par_find              ,
                po_str_len(par)          ,
                par_len
            );
}

po_ord_t
    po_str_ord_cstr
        (po_str* self, const char* ord, u64_t len)              {
            if (po_trait_of(self) != po_str_t) return po_ord_err;
            if (po_str_len (self) != len)      return po_ord_err;
            len = min(po_str_len(self), len);

            return po_mem_ord   (
                po_str_ptr(self),
                ord             ,
                len
            );
}

po_ord_t
    po_str_ord
        (po_str* self, po_str* ord)                             {
            if (po_trait_of(self) != po_str_t) return po_ord_err;
            if (po_trait_of(ord)  != po_str_t) return po_ord_err;
            u64_t len = min(po_str_len(self), po_str_len(ord));

            return po_mem_ord   (
                po_str_ptr(self),
                po_str_ptr(ord) ,
                len
            );
}


bool_t po_str_eq(po_str* self, po_str* ord) { return po_str_ord(self, ord) == po_ord_eq; }
bool_t po_str_gt(po_str* self, po_str* ord) { return po_str_ord(self, ord) == po_ord_gt; }
bool_t po_str_lt(po_str* self, po_str* ord) { return po_str_ord(self, ord) == po_ord_lt; }

bool_t po_str_eq_cstr(po_str* self, const char* ord, u64_t len) { return po_str_ord_cstr(self, ord, len) == po_ord_eq; }
bool_t po_str_gt_cstr(po_str* self, const char* ord, u64_t len) { return po_str_ord_cstr(self, ord, len) == po_ord_gt; }
bool_t po_str_lt_cstr(po_str* self, const char* ord, u64_t len) { return po_str_ord_cstr(self, ord, len) == po_ord_lt; }

bool_t
    po_str_begin
        (po_str* par, po_str* par_cmp)                          {
            if (po_trait_of(par_cmp) != po_str_t) return false_t;
            if (po_trait_of(par)     != po_str_t) return false_t;
            u64_t  ret = po_str_find(par, 0, par_cmp);
            return ret == 0;
}

bool_t
    po_str_end
        (po_str* par, po_str* par_cmp)                          {
            if (po_trait_of(par_cmp) != po_str_t) return false_t;
            if (po_trait_of(par)     != po_str_t) return false_t;
            u64_t  off = po_str_len (par) - po_str_len(par_cmp);
            u64_t  ret = po_str_find(par, off, par_cmp);
            return ret == off;
}

bool_t
    po_str_begin_cstr
        (po_str* par, const char* par_cmp, u64_t par_len)   {
            if (po_trait_of(par) != po_str_t) return false_t;
            u64_t ret = po_str_find_cstr                    (
                par    ,
                0      ,
                par_cmp,
                par_len
            );

            return ret == 0;
}

bool_t
    po_str_end_cstr
        (po_str* par, const char* par_cmp, u64_t par_len)   {
            if (po_trait_of(par) != po_str_t) return false_t;
            u64_t  off = po_str_len (par) - par_len;
            u64_t  ret = po_str_find_cstr          (
                par    ,
                off    ,
                par_cmp,
                par_len
            );

            return ret == off;
}

bool_t
    po_str_empty
        (po_str* par)                                      {
            if (po_trait_of(par) != po_str_t) return true_t;
            return po_seq_empty(&par->str);
}

u64_t
    po_str_len
        (po_str* par)                                 {
            if (po_trait_of(par) != po_str_t) return 0;
            return po_seq_len(&par->str);
}

const char*
    po_str_ptr
        (po_str* par)                                      {
            if (po_trait_of(par) != po_str_t) return null_t;
            return po_seq_ptr(&par->str);
}

#ifdef PRESET_LINUX
#include <linux/module.h>

MODULE_LICENSE("GPL");

EXPORT_SYMBOL(po_str_prep_front);
EXPORT_SYMBOL(po_str_prep_back);

EXPORT_SYMBOL(po_str_push_front_cstr);
EXPORT_SYMBOL(po_str_push_front);

EXPORT_SYMBOL(po_str_push_back_cstr);
EXPORT_SYMBOL(po_str_push_back);
EXPORT_SYMBOL(po_str_push);

EXPORT_SYMBOL(po_str_pop_front);
EXPORT_SYMBOL(po_str_pop_back);
EXPORT_SYMBOL(po_str_pop);

EXPORT_SYMBOL(po_str_find_cstr);
EXPORT_SYMBOL(po_str_find);

EXPORT_SYMBOL(po_str_ord_cstr);
EXPORT_SYMBOL(po_str_ord);

EXPORT_SYMBOL(po_str_eq);
EXPORT_SYMBOL(po_str_lt);
EXPORT_SYMBOL(po_str_gt);

EXPORT_SYMBOL(po_str_eq_cstr);
EXPORT_SYMBOL(po_str_lt_cstr);
EXPORT_SYMBOL(po_str_gt_cstr);

EXPORT_SYMBOL(po_str_begin_cstr);
EXPORT_SYMBOL(po_str_begin);
EXPORT_SYMBOL(po_str_end_cstr);
EXPORT_SYMBOL(po_str_end);
EXPORT_SYMBOL(po_str_empty);
EXPORT_SYMBOL(po_str_len);
EXPORT_SYMBOL(po_str_ptr);
EXPORT_SYMBOL(po_str_t);
#endif