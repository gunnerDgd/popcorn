#ifndef __ATOM_H__
#define __ATOM_H__

#include "type.h"

#if PRESET_ARCH_BIT >= 32
u32_t po_lock_add32(u32_t*, u32_t);
u32_t po_lock_sub32(u32_t*, u32_t);
u32_t po_lock_inc32(u32_t*);
u32_t po_lock_dec32(u32_t*);

u32_t po_cas_inc32(u32_t*);
u32_t po_cas_dec32(u32_t*);
u32_t po_cas32    (u32_t*, u32_t, u32_t);
u32_t po_xchg32   (u32_t*, u32_t);

u32_t po_lock_cas_inc32(u32_t*);
u32_t po_lock_cas_dec32(u32_t*);
u32_t po_lock_cas32    (u32_t*, u32_t, u32_t);
u32_t po_lock_xchg32   (u32_t*, u32_t);
#endif

#if PRESET_ARCH_BIT >= 64
u64_t po_lock_add64(u64_t*, u64_t);
u64_t po_lock_sub64(u64_t*, u64_t);
u64_t po_lock_inc64(u64_t*);
u64_t po_lock_dec64(u64_t*);

u64_t po_cas_inc64(u64_t*);
u64_t po_cas_dec64(u64_t*);
u64_t po_cas64    (u64_t*, u64_t, u64_t);
u64_t po_xchg64   (u64_t*, u64_t);

u64_t po_lock_cas_inc64(u64_t*);
u64_t po_lock_cas_dec64(u64_t*);
u64_t po_lock_cas64    (u64_t*, u64_t, u64_t);
u64_t po_lock_xchg64   (u64_t*, u64_t);
#endif

#if PRESET_ARCH_BIT == 64
#define po_lock_add_ptr(par, par_arg) po_lock_add64(((u64_t*)(par)), ((u64_t)(par_arg)))
#define po_lock_sub_ptr(par, par_arg) po_lock_sub64(((u64_t*)(par)), ((u64_t)(par_arg))
#define po_lock_inc_ptr(par)          po_lock_inc64(((u64_t*)(par)))
#define po_lock_dec_ptr(par)          po_lock_dec64(((u64_t*)(par)))

#define po_cas_inc_ptr(par)                  po_cas_inc64(((u64_t*)(par)))
#define po_cas_dec_ptr(par)                  po_cas_dec64(((u64_t*)(par)))
#define po_cas_ptr(par, par_expect, par_arg) po_cas64    (((u64_t*)(par)), ((u64_t)(par_expect)), ((u64_t)(par_arg)))
#define po_xchg_ptr(par, par_arg)            po_xchg64   (((u64_t*)(par)), ((u64_t)(par_arg)))

#define po_lock_cas_inc_ptr(par)                  po_lock_cas_inc64(((u64_t*)(par)))
#define po_lock_cas_dec_ptr(par)                  po_lock_cas_dec64(((u64_t*)(par)))
#define po_lock_cas_ptr(par, par_expect, par_arg) po_lock_cas64    (((u64_t*)(par)), ((u64_t)(par_expect)), ((u64_t)(par_arg)))
#define po_lock_xchg_ptr(par, par_arg)            po_lock_xchg64   (((u64_t*)(par)), ((u64_t)(par_arg)))
#endif

#if PRESET_ARCH_BIT == 32
#define po_lock_add_ptr(par, par_arg) po_lock_add32(((u32_t*)(par)), ((u32_t)(par_arg)))
#define po_lock_sub_ptr(par, par_arg) po_lock_sub32(((u32_t*)(par)), ((u32_t)(par_arg)))
#define po_lock_inc_ptr(par)          po_lock_inc32(((u32_t*)(par)), ((u32_t)(par_arg)))
#define po_lock_dec_ptr(par)          po_lock_dec32(((u32_t*)(par)), ((u32_t)(par_arg)))

#define po_cas_inc_ptr(par)                  po_cas_inc32(((u32_t*)(par)))
#define po_cas_dec_ptr(par)                  po_cas_dec32(((u32_t*)(par)))
#define po_cas_ptr(par, par_expect, par_arg) po_cas32    (((u32_t*)(par)), ((u32_t)(par_expect)), ((u32_t)(par_arg)))
#define po_xchg_ptr(par, par_arg)            po_xchg32   (((u32_t*)(par)), ((u32_t)(par_arg)))

#define po_lock_cas_inc_ptr(par)                  po_lock_cas_inc32(((u32_t*)(par)))
#define po_lock_cas_dec_ptr(par)                  po_lock_cas_dec32(((u32_t*)(par)))
#define po_lock_cas_ptr(par, par_expect, par_arg) po_lock_cas32    (((u32_t*)(par)), ((u32_t)(par_expect)), ((u32_t)(par_arg)))
#define po_lock_xchg_ptr(par, par_arg)            po_lock_xchg32   (((u32_t*)(par)), ((u32_t)(par_arg)))
#endif

#endif