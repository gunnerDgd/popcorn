#include "dev.h"
#include "class.h"

#include <bit.h>
#include <linux/fs.h>

po_obj_trait po_dev_trait = po_make_trait (
    po_dev_new    ,
    po_dev_clone  ,
    po_dev_ref    ,
    po_dev_del    ,
    sizeof(po_dev),
    null_t
);

po_obj_trait *po_dev_t = &po_dev_trait;

bool_t po_dev_new  (po_dev* par_dev, u32_t par_count, va_list par) { return false_t; }
bool_t po_dev_clone(po_dev* par, po_dev* par_dev)                  { return false_t; }
bool_t po_dev_ref  (po_dev* par)                                   { return false_t; }
void   po_dev_del  (po_dev* par)                                   {}