#include <linux/module.h>
#include "../../core.h"

static int
    po_init(void)                                                      {
        if (!po_obj_new_at((po_obj*) &po_core, po_core_t, 0)) return -1;
        po_info("[Popcorn] POPCORN subsystem Initialized");
        return 0;
}

static void
    po_deinit(void)                                      {
        po_info("[Popcorn] POPCORN subsystem Terminated");
        po_del(&po_core);
}

module_init(po_init)  ;
module_exit(po_deinit);

MODULE_LICENSE("GPL");