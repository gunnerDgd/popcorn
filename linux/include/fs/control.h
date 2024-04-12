#ifndef __PO_FS_CONTROL_H__
#define __PO_FS_CONTROL_H__

#include <core.h>

extern po_obj_trait *po_control_t;
typedef struct       po_control  { u8_t po_control[128]; } po_control;

void    po_control_ready(po_control*, u64_t);
u64_t   po_control_code (po_control*)       ;
any_t   po_control_arg  (po_control*)       ;
po_fut* po_control_fut  (po_control*)       ;

#endif
