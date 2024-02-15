#ifndef __BIT_H__
#define __BIT_H__

#include "type.h"

#define shl(par, par_shift)  ((par) << (par_shift))
#define shr(par, par_shift)  ((par) >> (par_shift))
#define test(par, par_shift) ((par) & shl(1, par_shift))
#define mask(par)            ((shl(1, par) - 1))

#if PRESET_ARCH_BIT >= 32
u32_t po_btc32     (u32_t*, u32_t);
u32_t po_bsf32     (u32_t)        ;
u32_t po_btr32     (u32_t*, u32_t);
u32_t po_bts32     (u32_t*, u32_t);
u32_t po_bsr32     (u32_t)        ;

u32_t po_lock_btc32(u32_t*, u32_t);
u32_t po_lock_btr32(u32_t*, u32_t);
u32_t po_lock_bts32(u32_t*, u32_t);
#endif

#if PRESET_ARCH_BIT >= 64
u64_t po_btc64     (u64_t*, u64_t);
u64_t po_bsf64     (u64_t)        ;
u64_t po_btr64     (u64_t*, u64_t);
u64_t po_bts64     (u64_t*, u64_t);
u64_t po_bsr64     (u64_t)        ;

u64_t po_lock_btc64(u64_t*, u64_t);
u64_t po_lock_btr64(u64_t*, u64_t);
u64_t po_lock_bts64(u64_t*, u64_t);
#endif

#if PRESET_ARCH_BIT == 64
#define po_btc(par, par_arg) po_btc64(((u64_t*)par), ((u64_t)par_arg))
#define po_btr(par, par_arg) po_btr64(((u64_t*)par), ((u64_t)par_arg))
#define po_bts(par, par_arg) po_bts64(((u64_t*)par), ((u64_t)par_arg))

#define po_bsf(par)          po_bsf64(((u64_t)par))
#define po_bsr(par)          po_bsr64(((u64_t)par))

#define po_lock_btc(par, par_arg) po_lock_btc64(((u64_t*)par), ((u64_t)par_arg))
#define po_lock_btr(par, par_arg) po_lock_btr64(((u64_t*)par), ((u64_t)par_arg))
#define po_lock_bts(par, par_arg) po_lock_bts64(((u64_t*)par), ((u64_t)par_arg))
#endif

#if PRESET_ARCH_BIT == 32
#define po_btc(par, par_arg) po_btc32(((u32_t*)par), ((u32_t)par_arg))
#define po_btr(par, par_arg) po_btr32(((u32_t*)par), ((u32_t)par_arg))
#define po_bts(par, par_arg) po_bts32(((u32_t*)par), ((u32_t)par_arg))

#define po_bsf(par)          po_bsf32(((u32_t)par))
#define po_bsr(par)          po_bsr32(((u32_t)par))

#define po_lock_btc(par, par_arg) po_lock_btc32(((u32_t*)par), ((u32_t)par_arg))
#define po_lock_btr(par, par_arg) po_lock_btr32(((u32_t*)par), ((u32_t)par_arg))
#define po_lock_bts(par, par_arg) po_lock_bts32(((u32_t*)par), ((u32_t)par_arg))
#endif


#endif