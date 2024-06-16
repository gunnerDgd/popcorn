#ifndef __TASK_H__
#define __TASK_H__

#include "obj.h"

extern po_obj_trait *po_task_t;
typedef struct       po_task  {
    po_obj head;
    any_t(*fun)(any_t);
    any_t  arg;
}   po_task;

bool_t po_task_new  (po_task*, u32_t, va_list);
bool_t po_task_clone(po_task*, po_task*)      ;
void   po_task_del  (po_task*);
any_t  po_task_run  (po_task*);

#endif
