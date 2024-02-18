#ifndef __PO_SYNC_EVENT_H__
#define __PO_SYNC_EVENT_H__

#include <obj.h>
#include <linux/wait.h>

extern po_obj_trait *po_event_t;
typedef struct       po_event  {
    po_obj            head ;
    wait_queue_head_t event;
}   po_event;

bool_t po_event_new       (po_event*, u32_t, va_list);
bool_t po_event_clone     (po_event*, po_event*)     ;
void   po_event_del       (po_event*)                ;

bool_t po_event_wait_until(po_event*, u64_t);
void   po_event_wait      (po_event*)       ;
void   po_event_wake      (po_event*)       ;

#endif