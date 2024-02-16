#ifndef __PO_LINUX_CHR_DEV_H__
#define __PO_LINUX_CHR_DEV_H__

#include <linux/cdev.h>
#include <linux/fs.h>

#include <obj.h>
#include <atom.h>
#include <str.h>
#include <set.h>

struct po_chr    ;
struct po_chr_dev;
struct po_dev    ;

typedef struct po_chr_ops   {
    u64_t  (*read) (po_obj*);
    u64_t  (*write)(po_obj*);
}   po_chr_ops;

extern po_obj_trait* po_chr_type_t;
typedef struct       po_chr_type  {
    po_obj                 head;
    po_str                 name;
    struct file_operations type;
    struct po_chr         *chr;
    po_chr_ops            *ops;
    po_set                 dev;
    u64_t                  num;
    u64_t                  min;
    dev_t                  maj;
}   po_chr_type;

bool_t po_chr_type_new  (po_chr_type*, u32_t, va_list);
bool_t po_chr_type_clone(po_chr_type*, po_chr_type*)  ;
void   po_chr_type_del  (po_chr_type*)                ;

#endif