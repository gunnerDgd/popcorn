#ifndef CORE_BOX_H
#define CORE_BOX_H

#include "obj.h"
#include "mem.h"

extern pp_obj_trait* pp_box_t;
typedef struct       pp_box  {
    pp_obj  head;
    pp_mem *mem;
    u64_t   len;
    void*   ptr;
}   pp_box;

void*  pp_box_ptr  (pp_box*);
u64_t  pp_box_len  (pp_box*);

#endif