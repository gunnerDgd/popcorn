#ifndef CORE_TASK_H
#define CORE_TASK_H

#include "type.h"
#include "obj.h"

extern pp_obj_trait *pp_task_t;
typedef struct       pp_task { u8_t task[64]; } pp_task;

any_t pp_task_run(pp_task*);

#endif
