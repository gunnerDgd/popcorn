#include "../print.h"

#include <linux/module.h>
#include <linux/printk.h>

void po_crit(const char* par) { pr_crit("%s\n", par); }
void po_info(const char* par) { pr_info("%s\n", par); }
void po_err (const char* par) { pr_err ("%s\n", par); }

EXPORT_SYMBOL(po_crit);
EXPORT_SYMBOL(po_info);
EXPORT_SYMBOL(po_err);