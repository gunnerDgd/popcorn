#include <linux/module.h>

#include "../obj.h"
#include "../mem.h"

extern po_obj_trait *mod_trait;
po_obj              *mod      ;

int __init
    po_init()               {
        po_set_mem(&po_heap);
        if (!mod_trait) return -1; mod = po_obj_new(null_t, mod_trait, 0);
        if (!mod)       return -1;
        return 0;
}

void __exit
    po_deinit()    {
        po_del(mod);
}

MODULE_LICENSE("GPL");