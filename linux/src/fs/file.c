#include "file.h"

po_obj_trait po_file_trait = po_make_trait (
    po_file_new    ,
    po_file_clone  ,
    po_file_ref    ,
    po_file_del    ,
    sizeof(po_file),
    null_t
);

po_obj_trait *po_file_t = &po_file_trait;

bool_t po_file_new  (po_file* par_file, u32_t par_count, va_list par) { return   false_t; }
bool_t po_file_clone(po_file* par, po_file* par_clone)                { return   false_t; }
bool_t po_file_ref  (po_file* par)                                    { return   false_t; }
void   po_file_del  (po_file* par)                                    { po_del(par->obj); }