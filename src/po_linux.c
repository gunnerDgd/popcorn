#include "po_linux.h"
#include "core.h"

#include <linux/slab.h>

void*  po_heap_new (po_mem* par, u64_t par_size) { return kmalloc(par_size, GFP_KERNEL); }
void   po_heap_del (po_mem* par, void* par_mem)  { kfree(par_mem); }
po_mem po_heap   =             {
    .on_new      = &po_heap_new,
    .on_del      = &po_heap_del
};

static int  __init po_mod_new(void) { printk("POPCORN Kernel Module Framework Started\n"); po_set_mem(&po_heap); return 0; }
static void __exit po_mod_del(void) { printk("POPCORN Kernel Module Framework Ended\n")  ; }

module_init   (po_mod_new);
module_exit   (po_mod_del);
MODULE_LICENSE("GPL")     ;