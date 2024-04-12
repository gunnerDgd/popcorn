#ifndef __PO_SYNC_NOT_H__
#define __PO_SYNC_NOT_H__

#include <core.h>

#include <linux/wait.h>
#include <linux/sched.h>

extern po_obj_trait *po_not_t;
typedef struct       po_not  {
    po_obj            head;
    wait_queue_head_t not ;
}   po_not;

bool_t po_not_new       (po_not*, u32_t, va_list);
bool_t po_not_clone     (po_not*, po_not*)       ;
void   po_not_del       (po_not*)                ;

bool_t po_not_wait_until(po_not*, u64_t);
void   po_not_wait      (po_not*)       ;
void   po_not_wake      (po_not*)       ;

#endif