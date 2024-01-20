#include "linux_page.h"
#include <linux/vmalloc.h>

void* po_page_new (po_mem* par, u64_t par_size) { return vmalloc(par_size); }
void  po_page_del (po_mem* par, void* par_mem)  { vfree(par_mem); }

po_mem po_page =             {
    .on_new    = &po_page_new,
    .on_del    = &po_page_del
};