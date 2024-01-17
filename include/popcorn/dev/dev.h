#ifndef __PO_DEV_DEV_H__
#define __PO_DEV_DEV_H__

#include "dev_type.h"
#include "../mem.h"

#define        po_dev_free   0
#define        po_dev_active 1
#define        po_dev_busy   2
typedef void*  po_dev                          ;
typedef struct po_dev_ops                      {
    bool_t (*on_new)    (po_obj*)              ;
    bool_t (*on_ref)    (po_obj*)              ;
    void   (*on_del)    (po_obj*)              ;

    i64_t  (*on_control)(po_obj*, u32_t, void*);
    i64_t  (*on_write)  (po_obj*, po_buf)      ;
    i64_t  (*on_read)   (po_obj*, po_buf)      ;
}   po_dev_ops;

po_mod po_dev  po_new_dev (const char*, po_dev_type, po_dev_ops*, po_obj*);
po_mod void    po_del_dev (po_dev)                                        ;
po_mod void    po_wait_dev(po_dev, u64_t)                                 ;
po_mod po_str* po_name_dev(po_dev)                                        ;

#endif
