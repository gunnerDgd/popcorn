#ifndef __LINUX_TASK_H__
#define __LINUX_TASK_H__

#include "../obj.h"
#include "../fut.h"

struct po_sched;
extern po_fut_ops    po_task_fut;
extern po_obj_trait *po_task_t  ;
typedef struct       po_task    {
    po_obj  head;
    u64_t   stat;
    void* (*run)(void*);
    void*   arg;
    void*   ret;
    po_obj *sup;
}   po_task;

bool_t  po_task_new  (po_task*, u32_t, va_list);
bool_t  po_task_clone(po_task*, po_task*)      ;
void    po_task_del  (po_task*)                ;

#endif
