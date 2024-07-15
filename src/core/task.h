#ifndef CORE_TASK_H
#define CORE_TASK_H

#include "obj.h"

extern pp_obj_trait *pp_task_t;
typedef struct       pp_task  {
    pp_obj head;
    any_t(*fun)(any_t);
    any_t  arg;
}   pp_task;

any_t pp_task_run(pp_task*);

#endif
