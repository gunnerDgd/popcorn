#include "mod.h"
#include <linux/module.h>

static int  po_mod_do_start(void) { return po_start(); }
static void po_mod_do_end  (void) { po_end(); }

module_init   (po_mod_do_start);
module_exit   (po_mod_do_end)  ;
MODULE_LICENSE("GPL");