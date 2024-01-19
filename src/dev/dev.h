#ifndef __PO_DEV_H__
#define __PO_DEV_H__

#ifdef PO_PRESET_LINUX
#include "details/linux_dev.h"
#endif

po_str* po_dev_name(void*);
po_obj* po_dev_type(void*);

#endif
