#ifndef __LINUX_THD_H__
#define __LINUX_THD_H__

#include "../obj.h"
#include "../str.h"
#include "../fut.h"

#include <linux/kthread.h>
#include <linux/sched.h>
#include <linux/errno.h>
#include <linux/err.h>

struct po_task;
extern po_obj_trait *po_thd_t;
typedef struct       po_thd  {
    po_obj              head;
    struct po_task     *task;
    struct task_struct *thd ;
}   po_thd;

bool_t  po_thd_new  (po_thd*, u32_t, va_list);
bool_t  po_thd_clone(po_thd*, po_thd*)       ;
void    po_thd_del  (po_thd*)                ;
po_fut* po_thd_fut  (po_thd*)                ;

#endif
