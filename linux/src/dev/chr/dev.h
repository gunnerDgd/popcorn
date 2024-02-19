#ifndef __PO_DEV_CHR_DEV_H__
#define __PO_DEV_CHR_DEV_H__

#include <obj.h>
#include <str.h>
#include <linux/cdev.h>

struct po_chr_read ;
struct po_chr_write;
struct po_chr_con  ;

struct po_not    ;
struct po_chr_dev;
struct po_chr    ;
struct po_dev    ;

typedef union po_chr_poll   {
    struct                  {
        u64_t read       : 1;
        u64_t read_norm  : 1;
        u64_t write      : 1;
        u64_t write_norm : 1;
    };  u64_t all;
}   po_chr_poll;

typedef struct po_chr_ops                                 {
    bool_t         (*read) (po_obj*, struct po_chr_read *);
    bool_t         (*write)(po_obj*, struct po_chr_write*);
    bool_t         (*con)  (po_obj*, struct po_chr_con  *);
    struct po_not* (*poll) (po_obj*, po_chr_poll*)        ;
}   po_chr_ops;

extern po_obj_trait *po_chr_dev_t;
typedef struct       po_chr_dev  {
    po_obj             head ;
    po_obj_trait      *trait;
    po_str             name ;
    struct po_chr     *type ;
    struct po_chr_ops *ops;
    struct po_dev     *dev;
    struct cdev        chr;
    dev_t              id ;
}   po_chr_dev;

bool_t po_chr_dev_new  (po_chr_dev*, u32_t, va_list);
bool_t po_chr_dev_clone(po_chr_dev*, po_chr_dev*)   ;
void   po_chr_dev_del  (po_chr_dev*)                ;

#endif
