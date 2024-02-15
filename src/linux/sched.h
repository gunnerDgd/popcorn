#ifndef __LINUX_SCHED_H__
#define __LINUX_SCHED_H__

#include "../sync/mpsc.h"

#include "task.h"
#include "thd.h"

struct po_task;

extern po_obj_trait *po_sched_t;
typedef struct       po_sched  {
    po_obj  head ;
    po_task sched;
    po_mpsc task;
    po_thd  thd ;
}   po_sched;

bool_t  po_sched_new     (po_sched*, u32_t, va_list) ;
bool_t  po_sched_clone   (po_sched*, po_sched*)      ;
void    po_sched_del     (po_sched*)                 ;
po_fut* po_sched_dispatch(po_sched*, struct po_task*);

#endif