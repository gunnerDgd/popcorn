#ifndef __SET_H__
#define __SET_H__

#include "../core.h"

extern po_obj_trait *po_set_t;
typedef struct       po_set  { u8_t po_set[64]; } po_set;

po_obj* po_set_acq  (po_set*)         ;
void    po_set_rel  (po_set*, po_obj*);

#endif