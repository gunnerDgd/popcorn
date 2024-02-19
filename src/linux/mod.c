#include <linux/module.h>

#include "../obj.h"
#include "../mem.h"

extern po_obj_trait *mod_t;
po_obj              *mod  ;

int __init
    po_init(void)           {
        po_set_mem(&po_heap);
        if (!mod_t) return -1; mod = po_obj_new(null_t, mod_t, 0);
        if (!mod)   return -1;
        return 0;
}

void __exit
    po_deinit(void) {
        po_del(mod);
}

MODULE_LICENSE("GPL");