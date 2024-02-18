#ifndef __PO_DEV_CHR_CON_H__
#define __PO_DEV_CHR_CON_H__

#include <obj.h>
#include <fut.h>

extern po_obj_trait *po_chr_con_t;
typedef struct       po_chr_con { u8_t chr[128]; } po_chr_con;

void    po_chr_con_ret(po_chr_con*, u64_t);
u64_t   po_chr_con_arg(po_chr_con*)       ;
u64_t   po_chr_con_cmd(po_chr_con*)       ;
po_fut* po_chr_con_fut(po_chr_con*)       ;

#endif
