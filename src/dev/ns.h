#ifndef __PO_DEV_NS_H__
#define __PO_DEV_NS_H__

#ifdef PO_PRESET_LINUX
#include "details/linux_ns.h"
#endif

po_str* po_ns_name(po_ns*);

#endif