#include <linux/module.h>
#include "../../core.h"

static int
    po_init(void)                                             {
        if (!po_make_at((po_obj*) &po, po) from (0)) return -1;
        po_info("[Popcorn] POPCORN subsystem Initialized");
        return 0;
}

static void
    po_deinit(void)                                      {
        po_info("[Popcorn] POPCORN subsystem Terminated");
        po_del(&po);
}

module_init(po_init)  ;
module_exit(po_deinit);

MODULE_LICENSE("GPL");