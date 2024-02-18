#ifndef __RAN_H__
#define __RAN_H__

#include "obj.h"

extern po_obj_trait *po_ran_t;
typedef struct       po_ran  {
    po_obj head ;
    u64_t  begin,
           end  ;
}   po_ran;

bool_t po_ran_new  (po_ran*, u32_t, va_list);
bool_t po_ran_clone(po_ran*, po_ran*)       ;
void   po_ran_del  (po_ran*)                ;

u64_t  po_ran_begin(po_ran*);
u64_t  po_ran_end  (po_ran*);

#endif
