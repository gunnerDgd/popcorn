#include <linux/module.h>

#include "../obj.h"
#include "../mem.h"

#include "../../core.h"

extern po_obj_trait *mod_t;
po_obj              *mod  ;

int __init
    po_init(void)                                                      {
        if (!po_obj_new_at((po_obj*) &po_core, po_core_t, 0)) return -1;
        if (!mod_t)                                           return -1; mod = po_obj_new(null_t, mod_t, 0);
        if (!mod)                                             return -1;
        return 0;
}

void __exit
    po_deinit(void) {
        po_del(mod);
}

module_init(po_init)  ;
module_exit(po_deinit);

MODULE_LICENSE("GPL");