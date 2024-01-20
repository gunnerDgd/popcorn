#ifndef __PO_LINUX_DEV_H__
#define __PO_LINUX_DEV_H__

#include <linux/cdev.h>
#include <linux/fs.h>

#include "../../mem/ubuf.h"
#include "linux_ns.h"

struct po_dev_type;
struct po_dev     ;

typedef struct po_dev_ops                      {
    bool_t (*on_new)    (po_obj*)              ;
    bool_t (*on_open)   (po_obj*)              ;
    void   (*on_close)  (po_obj*)              ;
    void   (*on_del)    (po_obj*)              ;

    i64_t  (*on_control)(po_obj*, u32_t, void*);
    i64_t  (*on_write)  (po_obj*, po_ubuf*)    ;
    i64_t  (*on_read)   (po_obj*, po_ubuf*)    ;
}   po_dev_ops;

extern po_obj_trait* po_dev_t;
typedef struct       po_dev  {
    po_obj         head ;
    po_str         name ;
    po_obj        *type ;
    po_ns         *ns   ;

    void          *hnd  ;
    struct file   *file ;
    struct device *dev  ;

    po_dev_ops    *ops  ;
    dev_t          id   ;
    po_obj        *obj  ;
}   po_dev;

bool_t  po_dev_new  (po_dev*, u32_t, va_list);
bool_t  po_dev_clone(po_dev*, po_dev*)       ;
void    po_dev_del  (po_dev*)                ;

#endif
