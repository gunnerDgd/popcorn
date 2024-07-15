#ifndef CORE_BOX_H
#define CORE_BOX_H

#include "obj.h"

extern pp_obj_trait* pp_box_t;
typedef struct       pp_box  { u8_t pp_box[64]; } pp_box;

void*  pp_box_ptr(pp_box*);
u64_t  pp_box_len(pp_box*);

#endif