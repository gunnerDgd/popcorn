#include "ns.h"

po_str*
    po_ns_name
        (po_ns* par)                              {
            if (!par)                     return 0;
            if (trait_of(par) != po_ns_t) return 0;
            return &par->name;
}

#ifdef PO_PRESET_LINUX
#include <linux/module.h>

MODULE_LICENSE("GPL");
#endif