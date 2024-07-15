#ifndef CORE_ATOM_H
#define CORE_ATOM_H

#include "type.h"

#if PRESET_ARCH_BIT >= 32
u32_t pp_lock_add32    (u32_t*, u32_t);
u32_t pp_lock_sub32    (u32_t*, u32_t);
u32_t pp_lock_inc32    (u32_t*);
u32_t pp_lock_dec32    (u32_t*);

u32_t pp_cas_inc32     (u32_t*);
u32_t pp_cas_dec32     (u32_t*);
u32_t pp_cas32         (u32_t*, u32_t, u32_t);
u32_t pp_xchg32        (u32_t*, u32_t);

u32_t pp_lock_cas_inc32(u32_t*);
u32_t pp_lock_cas_dec32(u32_t*);
u32_t pp_lock_cas32    (u32_t*, u32_t, u32_t);
u32_t pp_lock_xchg32   (u32_t*, u32_t);
#endif

#if PRESET_ARCH_BIT >= 64
u64_t pp_lock_add64    (u64_t*, u64_t);
u64_t pp_lock_sub64    (u64_t*, u64_t);
u64_t pp_lock_inc64    (u64_t*);
u64_t pp_lock_dec64    (u64_t*);

u64_t pp_cas_inc64     (u64_t*);
u64_t pp_cas_dec64     (u64_t*);
u64_t pp_cas64         (u64_t*, u64_t, u64_t);
u64_t pp_xchg64        (u64_t*, u64_t);

u64_t pp_lock_cas_inc64(u64_t*);
u64_t pp_lock_cas_dec64(u64_t*);
u64_t pp_lock_cas64    (u64_t*, u64_t, u64_t);
u64_t pp_lock_xchg64   (u64_t*, u64_t);
#endif

#if PRESET_ARCH_BIT == 64
#define pp_lock_add(par, par_arg) pp_lock_add64(((u64_t*)(par)), ((u64_t)(par_arg)))
#define pp_lock_sub(par, par_arg) pp_lock_sub64(((u64_t*)(par)), ((u64_t)(par_arg))
#define pp_lock_inc(par)          pp_lock_inc64(((u64_t*)(par)))
#define pp_lock_dec(par)          pp_lock_dec64(((u64_t*)(par)))

#define pp_cas_inc(par)                  pp_cas_inc64(((u64_t*)(par)))
#define pp_cas_dec(par)                  pp_cas_dec64(((u64_t*)(par)))
#define pp_cas(par, par_expect, par_arg) pp_cas64    (((u64_t*)(par)), ((u64_t)(par_expect)), ((u64_t)(par_arg)))
#define pp_xchg(par, par_arg)            pp_xchg64   (((u64_t*)(par)), ((u64_t)(par_arg)))

#define pp_lock_cas_inc(par)                  pp_lock_cas_inc64(((u64_t*)(par)))
#define pp_lock_cas_dec(par)                  pp_lock_cas_dec64(((u64_t*)(par)))
#define pp_lock_cas(par, par_expect, par_arg) pp_lock_cas64    (((u64_t*)(par)), ((u64_t)(par_expect)), ((u64_t)(par_arg)))
#define pp_lock_xchg(par, par_arg)            pp_lock_xchg64   (((u64_t*)(par)), ((u64_t)(par_arg)))
#endif

#if PRESET_ARCH_BIT == 32
#define pp_lock_add(par, par_arg) pp_lock_add32(((u32_t*)(par)), ((u32_t)(par_arg)))
#define pp_lock_sub(par, par_arg) pp_lock_sub32(((u32_t*)(par)), ((u32_t)(par_arg)))
#define pp_lock_inc(par)          pp_lock_inc32(((u32_t*)(par)), ((u32_t)(par_arg)))
#define pp_lock_dec(par)          pp_lock_dec32(((u32_t*)(par)), ((u32_t)(par_arg)))

#define pp_cas_inc(par)                  pp_cas_inc32(((u32_t*)(par)))
#define pp_cas_dec(par)                  pp_cas_dec32(((u32_t*)(par)))
#define pp_cas(par, par_expect, par_arg) pp_cas32    (((u32_t*)(par)), ((u32_t)(par_expect)), ((u32_t)(par_arg)))
#define pp_xchg(par, par_arg)            pp_xchg32   (((u32_t*)(par)), ((u32_t)(par_arg)))

#define pp_lock_cas_inc(par)                  pp_lock_cas_inc32(((u32_t*)(par)))
#define pp_lock_cas_dec(par)                  pp_lock_cas_dec32(((u32_t*)(par)))
#define pp_lock_cas(par, par_expect, par_arg) pp_lock_cas32    (((u32_t*)(par)), ((u32_t)(par_expect)), ((u32_t)(par_arg)))
#define pp_lock_xchg(par, par_arg)            pp_lock_xchg32   (((u32_t*)(par)), ((u32_t)(par_arg)))
#endif

#endif