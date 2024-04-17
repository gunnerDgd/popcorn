#ifndef __PO_CORE_BOX_H__
#define __PO_CORE_BOX_H__

#include "obj.h"

extern po_obj_trait* po_box_t;
typedef struct       po_box  { u8_t po_box[64]; } po_box;

void*  po_box_ptr  (po_box*);
u64_t  po_box_size (po_box*);

#endif