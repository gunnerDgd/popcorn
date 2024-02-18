#ifndef __PO_DEV_DEV_H__
#define __PO_DEV_DEV_H__

#include <obj.h>

extern po_obj_trait *po_dev_t;
typedef struct       po_dev { u8_t dev[256]; } po_dev;

bool_t po_dev_use  (po_dev*);
void   po_dev_free (po_dev*);

#endif
