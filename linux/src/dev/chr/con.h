#ifndef __PO_DEV_CHR_CON_H__
#define __PO_DEV_CHR_CON_H__

#include <obj.h>
#include <fut.h>

struct po_chr_dev;

extern po_obj_trait *po_chr_con_t;
typedef struct       po_chr_con  {
    po_obj             head;
    u64_t              stat;
    u64_t              cmd;
    struct po_chr_dev *dev;
    u64_t              arg;
    u64_t              ret;
}   po_chr_con;

bool_t  po_chr_con_new  (po_chr_con*, u32_t, va_list);
bool_t  po_chr_con_clone(po_chr_con*, po_chr_con*)   ;
void    po_chr_con_del  (po_chr_con*);

void    po_chr_con_ret  (po_chr_con*, u64_t);
u64_t   po_chr_con_arg  (po_chr_con*)       ;
u64_t   po_chr_con_cmd  (po_chr_con*)       ;
po_fut* po_chr_con_fut  (po_chr_con*)       ;

#endif
