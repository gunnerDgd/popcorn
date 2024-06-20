#ifndef __THREAD_THD_H__
#define __THREAD_THD_H__

#include "../core.h"

extern po_obj_trait *po_thd_t;
typedef struct       po_thd { u8_t thd[64]; } po_thd;

po_fut* po_thd_fut(po_thd*);

#endif