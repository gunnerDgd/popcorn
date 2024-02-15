#ifndef __SCHED_H__
#define __SCHED_H__

#include "obj.h"
#include "fut.h"
#include "task.h"

extern po_obj_trait *po_sched_t;
typedef struct       po_sched { u8_t sched[16 KB]; } po_sched;

po_fut* po_sched_dispatch(po_sched*, po_task*);

#endif