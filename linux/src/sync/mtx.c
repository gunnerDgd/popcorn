#include "mtx.h"

bool_t
    po_mtx_new
        (po_mtx* par_mtx, u32_t par_count, va_list par) {
            mutex_init(&par_mtx->mtx);
            return true_t;
}

bool_t
    po_mtx_clone
        (po_mtx* par, po_mtx* par_clone) {
            return false_t;
}

void
    po_mtx_del
        (po_mtx* par)               {
            mutex_destroy(&par->mtx);
}

void
    po_mtx_lock
        (po_mtx* par)                               {
            if (po_trait_of(par) != po_mtx_t) return;
            mutex_lock(&par->mtx);
}

bool_t
    po_mtx_lock_try
        (po_mtx* par)                                       {
            if (po_trait_of(par) != po_mtx_t) return false_t;
            return mutex_trylock(&par->mtx);
}

void
    po_mtx_unlock
        (po_mtx* par)                               {
            if (po_trait_of(par) != po_mtx_t) return;
            mutex_unlock(&par->mtx);
}