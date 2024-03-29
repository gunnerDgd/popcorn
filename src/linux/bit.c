#include "../bit.h"
#include <linux/module.h>
#include <linux/bitops.h>

MODULE_LICENSE("GPL");

#if PRESET_ARCH_BIT >= 32
u32_t po_btc32     (u32_t* par, u32_t par_arg) { return test_and_change_bit(par_arg, (volatile unsigned long*) par); }
u32_t po_btr32     (u32_t* par, u32_t par_arg) { return test_and_clear_bit (par_arg, (volatile unsigned long*) par); }
u32_t po_bts32     (u32_t* par, u32_t par_arg) { return test_and_set_bit   (par_arg, (volatile unsigned long*) par); }
u32_t po_bsr32     (u32_t  par)                { return fls(par); }
u32_t po_bsf32     (u32_t  par)                { return ffs(par); }

u32_t po_lock_btc32(u32_t* par, u32_t par_arg) { return test_and_change_bit(par_arg, (volatile unsigned long*) par); }
u32_t po_lock_btr32(u32_t* par, u32_t par_arg) { return test_and_clear_bit (par_arg, (volatile unsigned long*) par); }
u32_t po_lock_bts32(u32_t* par, u32_t par_arg) { return test_and_set_bit   (par_arg, (volatile unsigned long*) par); }

#endif

#if PRESET_ARCH_BIT >= 64
u64_t po_btc64     (u64_t* par, u64_t par_arg) { return test_and_change_bit(par_arg, (volatile unsigned long*) par); }
u64_t po_btr64     (u64_t* par, u64_t par_arg) { return test_and_clear_bit (par_arg, (volatile unsigned long*) par); }
u64_t po_bts64     (u64_t* par, u64_t par_arg) { return test_and_set_bit   (par_arg, (volatile unsigned long*) par); }
u64_t po_bsr64     (u64_t  par)                { return fls64(par); }
u64_t po_bsf64     (u64_t  par)                { return __ffs64((long long int)par); }

u64_t po_lock_btc64(u64_t* par, u64_t par_arg) { return test_and_change_bit(par_arg, (volatile unsigned long*) par); }
u64_t po_lock_btr64(u64_t* par, u64_t par_arg) { return test_and_clear_bit (par_arg, (volatile unsigned long*) par); }
u64_t po_lock_bts64(u64_t* par, u64_t par_arg) { return test_and_set_bit   (par_arg, (volatile unsigned long*) par); }

#endif