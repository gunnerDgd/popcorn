#include "ran.h"

po_ord_t
    po_ran_ord
        (po_ran* par, po_ran* par_ord)                         {
            if (po_trait_of(par) != po_ran_t) return po_ord_err;
            if (po_trait_of(par) != po_ran_t) return po_ord_err;

            if (par->end   < par_ord->begin) return po_ord_lt;
            if (par->begin > par_ord->end)   return po_ord_gt;
            return po_ord_eq;
}

po_ops_cmp po_ran_cmp = po_make_cmp_ops(po_ran_ord);
po_obj_ops po_ran_ops = {
    .cmp = &po_ran_cmp
};

po_obj_trait po_ran_trait = po_make_trait (
    po_ran_new    ,
    po_ran_clone  ,
    null_t        ,
    po_ran_del    ,
    sizeof(po_ran),
    &po_ran_ops
);

po_obj_trait *po_ran_t = &po_ran_trait;

bool_t
    po_ran_new
        (po_ran* par_ran, u32_t par_count, va_list par)                   {
            u64_t begin = 0; if (par_count > 0) begin = va_arg(par, u64_t);
            u64_t end   = 0; if (par_count > 1) end   = va_arg(par, u64_t);
            if (begin > end) return false_t;
            par_ran->begin = begin;
            par_ran->end   = end  ;
            return true_t;
}

bool_t
    po_ran_clone
        (po_ran* par, po_ran* par_clone) {
            par->begin = par_clone->begin;
            par->end   = par_clone->end  ;
            return true_t;
}

void
    po_ran_del
        (po_ran* par) {
}

u64_t
    po_ran_begin
        (po_ran* par)                                  {
            if (po_trait_of(par) != po_ran_t) return -1;
            return par->begin;
}

u64_t
    po_ran_end
        (po_ran* par)                                 {
            if (po_trait_of(par) != po_ran_t) return 0;
            return par->end;
}