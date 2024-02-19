#ifndef __PO_SYNC_WORK_H__
#define __PO_SYNC_WORK_H__

#include <obj.h>
#include <fut.h>

extern po_obj_trait *po_work_t;
typedef struct       po_work { u8_t po_work[128]; } po_work;

po_fut* po_work_fut (po_work*);

#endif
