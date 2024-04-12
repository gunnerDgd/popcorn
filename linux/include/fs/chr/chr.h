#ifndef __PO_FS_CHR_CHR_H__
#define __PO_FS_CHR_CHR_H__

#include <core.h>
#include <linux/cdev.h>

extern po_obj_trait *po_chr_t;
typedef struct       po_chr  { u8_t po_chr[256]; } po_chr;

#endif
