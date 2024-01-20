#ifndef __PO_CHR_H__
#define __PO_CHR_H__

#ifdef PO_PRESET_LINUX
#include "details/linux_chr.h"
#endif

po_str* po_chr_name (po_chr*);

#endif