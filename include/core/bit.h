#ifndef CORE_BIT_H
#define CORE_BIT_H

#include "type.h"

#define shl(par, par_shift)  ((par) << (par_shift))
#define shr(par, par_shift)  ((par) >> (par_shift))
#define test(par, par_shift) ((par) & shl(1, par_shift))
#define mask(par)            ((shl(1, par) - 1))

#if PRESET_ARCH_BIT >= 32
u32_t pp_btc32     (u32_t*, u32_t);
u32_t pp_bsf32     (u32_t)        ;
u32_t pp_btr32     (u32_t*, u32_t);
u32_t pp_bts32     (u32_t*, u32_t);
u32_t pp_bsr32     (u32_t)        ;

u32_t pp_lock_btc32(u32_t*, u32_t);
u32_t pp_lock_btr32(u32_t*, u32_t);
u32_t pp_lock_bts32(u32_t*, u32_t);
#endif

#if PRESET_ARCH_BIT >= 64
u64_t pp_btc64     (u64_t*, u64_t);
u64_t pp_bsf64     (u64_t)        ;
u64_t pp_btr64     (u64_t*, u64_t);
u64_t pp_bts64     (u64_t*, u64_t);
u64_t pp_bsr64     (u64_t)        ;

u64_t pp_lock_btc64(u64_t*, u64_t);
u64_t pp_lock_btr64(u64_t*, u64_t);
u64_t pp_lock_bts64(u64_t*, u64_t);
#endif

#if PRESET_ARCH_BIT == 64
#define pp_btc(par, par_arg) pp_btc64(((u64_t*)par), ((u64_t)par_arg))
#define pp_btr(par, par_arg) pp_btr64(((u64_t*)par), ((u64_t)par_arg))
#define pp_bts(par, par_arg) pp_bts64(((u64_t*)par), ((u64_t)par_arg))

#define pp_bsf(par)          pp_bsf64(((u64_t)par))
#define pp_bsr(par)          pp_bsr64(((u64_t)par))

#define pp_lock_btc(par, par_arg) pp_lock_btc64(((u64_t*)par), ((u64_t)par_arg))
#define pp_lock_btr(par, par_arg) pp_lock_btr64(((u64_t*)par), ((u64_t)par_arg))
#define pp_lock_bts(par, par_arg) pp_lock_bts64(((u64_t*)par), ((u64_t)par_arg))
#endif

#if PRESET_ARCH_BIT == 32
#define pp_btc(par, par_arg) pp_btc32(((u32_t*)par), ((u32_t)par_arg))
#define pp_btr(par, par_arg) pp_btr32(((u32_t*)par), ((u32_t)par_arg))
#define pp_bts(par, par_arg) pp_bts32(((u32_t*)par), ((u32_t)par_arg))

#define pp_bsf(par)          pp_bsf32(((u32_t)par))
#define pp_bsr(par)          pp_bsr32(((u32_t)par))

#define pp_lock_btc(par, par_arg) pp_lock_btc32(((u32_t*)par), ((u32_t)par_arg))
#define pp_lock_btr(par, par_arg) pp_lock_btr32(((u32_t*)par), ((u32_t)par_arg))
#define pp_lock_bts(par, par_arg) pp_lock_bts32(((u32_t*)par), ((u32_t)par_arg))
#endif


#endif