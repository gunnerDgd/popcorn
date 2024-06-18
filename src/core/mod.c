#include "obj.h"
#include "mod.h"

bool_t
    po_mod_do_new
        (struct po_mod* mod)                       {
            for (u64_t i = 0 ; mod[i].trait ; ++i) {
                if (po_trait_of(mod[i].mod)) {
                    po_ref     (mod[i].mod);
                    continue;
                }

                if (!po_obj_new_at(mod[i].mod,mod[i].trait, 0)) return false_t;
            }

            return true_t;
}

void
    po_mod_do_del
        (struct po_mod* mod)                       {
            for (u64_t i = 0 ; mod[i].trait ; ++i) {
                po_del (mod[i].mod);
            }
}

#ifdef PRESET_LINUX
#include <linux/module.h>
MODULE_LICENSE("GPL");

EXPORT_SYMBOL(po_mod_do_new);
EXPORT_SYMBOL(po_mod_do_del);
#endif