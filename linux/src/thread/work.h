#ifndef __PO_SYNC_WORK_H__
#define __PO_SYNC_WORK_H__

#include <core.h>
#include <linux/workqueue.h>

typedef struct po_work_run {
    struct work_struct head;
    u64_t              stat;
    void* (*run)(void*);
    void   *arg;
    void   *ret;
}   po_work_run;

extern po_obj_trait *po_work_t;
typedef struct       po_work  {
    po_obj      head;
    po_work_run work;
}   po_work;

bool_t  po_work_new  (po_work*, u32_t, va_list);
bool_t  po_work_clone(po_work*, po_work*)      ;
void    po_work_del  (po_work*)                ;
po_fut* po_work_fut  (po_work*)                ;

#endif
