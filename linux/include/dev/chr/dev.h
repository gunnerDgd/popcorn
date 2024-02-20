#ifndef __PO_DEV_CHR_DEV_H__
#define __PO_DEV_CHR_DEV_H__

#include <obj.h>

struct po_chr_read ;
struct po_chr_write;
struct po_chr_con  ;

extern po_obj_trait *po_chr_dev_t;
typedef struct       po_chr_dev { u8_t chr[512]; } po_chr_dev;

typedef union po_chr_stat   {
    struct                  {
        u64_t read       : 1;
        u64_t read_norm  : 1;
        u64_t write      : 1;
        u64_t write_norm : 1;
    };  u64_t all;
}   po_chr_stat;

typedef struct po_chr_ops                                   {
    bool_t           (*read) (po_obj*, struct po_chr_read *);
    bool_t           (*write)(po_obj*, struct po_chr_write*);
    bool_t           (*con)  (po_obj*, struct po_chr_con  *);
    struct po_event* (*poll) (po_obj*, po_chr_stat*)        ;
}   po_chr_ops;

#define po_make_chr_ops(par_read, par_write, par_con, par_poll)               {\
    .read  = ((bool_t          (*)(po_obj*, struct po_chr_read*)) (par_read)) ,\
    .write = ((bool_t          (*)(po_obj*, struct po_chr_write*))(par_write)),\
    .con   = ((bool_t          (*)(po_obj*, struct po_chr_con*))  (par_con))  ,\
    .poll  = ((struct po_event*(*)(po_obj*, po_chr_stat*))        (par_poll))  \
}
#endif
