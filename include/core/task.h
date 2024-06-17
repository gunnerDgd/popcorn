#ifndef __TASK_H__
#define __TASK_H__

#include "type.h"
#include "obj.h"

extern po_obj_trait *po_task_t;
typedef struct       po_task { u8_t task[64]; } po_task;

any_t po_task_run(po_task*);

#endif
