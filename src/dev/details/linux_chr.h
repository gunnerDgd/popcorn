#ifndef __PO_LINUX_CHR_H__
#define __PO_LINUX_CHR_H__

#include "linux_ns.h"

#include <linux/cdev.h>
#include <linux/fs.h>

struct po_dev;
struct po_chr;

extern struct po_chr*         chr    [4 KB]       ;
extern struct po_dev*         chr_dev[4 KB][64 KB];
extern struct file_operations chr_ops             ;

extern po_obj_trait *po_chr_t;
typedef struct       po_chr  {
    po_obj         head      ;
    po_str         name      ;
    struct cdev    chr       ;
    dev_t          id        ;

    po_list        free      ;
    po_list        use       ;
    u64_t          num       ;
}   po_chr;

bool_t         po_chr_new  (po_chr*, u32_t, va_list);
bool_t         po_chr_clone(po_chr*, po_chr*)       ;
void           po_chr_del  (po_chr*)                ;

struct po_dev* po_chr_use  (po_chr*, struct po_dev*);
void           po_chr_free (po_chr*, struct po_dev*);

#endif