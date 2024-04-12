#ifndef __PO_SYNC_NOT_H__
#define __PO_SYNC_NOT_H__

#include <core.h>

extern po_obj_trait *po_not_t;
typedef struct       po_not { u8_t po_not[64]; } po_not;

bool_t po_not_wait_until(po_not*, u64_t);
void   po_not_wait      (po_not*)       ;
void   po_not_wake      (po_not*)       ;

#endif
