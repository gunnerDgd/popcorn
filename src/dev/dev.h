#ifndef __PO_DEV_H__
#define __PO_DEV_H__

#ifdef PO_PRESET_LINUX
#include "linux/details/po_dev.h"
#include "linux/details/dev_type.h"
#endif

void*   po_new_dev (const char*, po_dev_type*, po_dev_ops*, po_obj*);
void    po_del_dev (void*);

void    po_wait_dev(void*, u64_t);
po_str* po_name_dev(void*)       ;

#endif
