#ifndef __PO_DEV_CHR_DEV_H__
#define __PO_DEV_CHR_DEV_H__

#include <obj.h>

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

#endif
