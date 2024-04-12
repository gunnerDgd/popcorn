#include "../atom.h"

#include <linux/module.h>
#include <linux/atomic.h>

MODULE_LICENSE("GPL");

#if PRESET_ARCH_BIT >= 32
u32_t po_lock_add32(u32_t* par, u32_t par_arg) { return atomic_add_return(par_arg, (atomic_t*) par); }
u32_t po_lock_sub32(u32_t* par, u32_t par_arg) { return atomic_sub_return(par_arg, (atomic_t*) par); }
u32_t po_lock_inc32(u32_t* par)                { return atomic_inc_return((atomic_t*) par); }
u32_t po_lock_dec32(u32_t* par)                { return atomic_dec_return((atomic_t*) par); }

u32_t po_cas32      (u32_t* par, u32_t par_old, u32_t par_new) { return atomic_cmpxchg((atomic_t*) par, par_old, par_new); }
u32_t po_xchg32     (u32_t* par, u32_t par_new)                { return atomic_xchg   ((atomic_t*) par, par_new); }

u32_t po_lock_cas32 (u32_t* par, u32_t par_old, u32_t par_new) { return atomic_cmpxchg((atomic_t*) par, par_old, par_new); }
u32_t po_lock_xchg32(u32_t* par, u32_t par_new)                { return atomic_xchg   ((atomic_t*) par, par_new); }

#endif

#if PRESET_ARCH_BIT >= 64
u64_t po_lock_add64(u64_t* par, u64_t par_arg) { return atomic64_add_return(par_arg, (atomic64_t*) par); }
u64_t po_lock_sub64(u64_t* par, u64_t par_arg) { return atomic64_sub_return(par_arg, (atomic64_t*) par); }
u64_t po_lock_inc64(u64_t* par)                { return atomic64_inc_return((atomic64_t*) par); }
u64_t po_lock_dec64(u64_t* par)                { return atomic64_dec_return((atomic64_t*) par); }

u64_t po_cas64      (u64_t* par, u64_t par_old, u64_t par_new) { return atomic64_cmpxchg((atomic64_t*) par, par_old, par_new); }
u64_t po_xchg64     (u64_t* par, u64_t par_new)                { return atomic64_xchg   ((atomic64_t*) par, par_new); }

u64_t po_lock_cas64 (u64_t* par, u64_t par_old, u64_t par_new) { return atomic64_cmpxchg((atomic64_t*) par, par_old, par_new); }
u64_t po_lock_xchg64(u64_t* par, u64_t par_new)                { return atomic64_xchg   ((atomic64_t*) par, par_new); }

#endif


#if PRESET_ARCH_BIT >= 32
u32_t
    po_lock_cas_inc32
        (u32_t* par)         {
            u32_t ret_inc = 0;
            u32_t ret     = 0;
            do                     {
                ret       = *par   ;
                ret_inc   = ret + 1;
            } while (po_lock_cas32(par, ret, ret_inc) != ret);

            return ret_inc;
}

u32_t
    po_lock_cas_dec32
        (u32_t* par)         {
            u32_t ret_dec = 0;
            u32_t ret     = 0;
            do                     {
                ret       = *par   ;
                ret_dec   = ret - 1;
            } while (po_lock_cas32(par, ret, ret_dec) != ret);

            return ret_dec;
}

u32_t
    po_cas_inc32
        (u32_t* par)         {
            u32_t ret_inc = 0;
            u32_t ret     = 0;
            do                     {
                ret       = *par   ;
                ret_inc   = ret + 1;
            } while (po_cas32(par, ret, ret_inc) != ret);

            return ret_inc;
}

u32_t
    po_cas_dec32
        (u32_t* par)         {
            u32_t ret_dec = 0;
            u32_t ret     = 0;
            do                     {
                ret       = *par   ;
                ret_dec   = ret - 1;
            } while (po_cas32(par, ret, ret_dec) != ret);

            return ret_dec;
}

#endif

#if PRESET_ARCH_BIT >= 64
u64_t
    po_lock_cas_inc64
        (u64_t* par)         {
            u64_t ret_inc = 0;
            u64_t ret     = 0;
            do                     {
                ret       = *par   ;
                ret_inc   = ret + 1;
            } while (po_lock_cas64(par, ret, ret_inc) != ret);

            return ret_inc;
}

u64_t
    po_lock_cas_dec64
        (u64_t* par)         {
            u64_t ret_dec = 0;
            u64_t ret     = 0;
            do                     {
                ret       = *par   ;
                ret_dec   = ret - 1;
            } while (po_lock_cas64(par, ret, ret_dec) != ret);

            return ret_dec;
}

u64_t
    po_cas_inc64
        (u64_t* par)         {
            u64_t ret_inc = 0;
            u64_t ret     = 0;
            do                     {
                ret       = *par   ;
                ret_inc   = ret + 1;
            } while (po_cas64(par, ret, ret_inc) != ret);

            return ret_inc;
}

u64_t
    po_cas_dec64
        (u64_t* par)         {
            u64_t ret_dec = 0;
            u64_t ret     = 0;
            do                     {
                ret       = *par   ;
                ret_dec   = ret - 1;
            } while (po_cas64(par, ret, ret_dec) != ret);

            return ret_dec;
}

#endif