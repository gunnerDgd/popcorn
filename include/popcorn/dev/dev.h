#ifndef __PO_DEV_DEV_H__
#define __PO_DEV_DEV_H__

#include "../mem.h"

typedef void*  po_dev                          ;
typedef struct po_dev_ops                      {
    bool_t (*on_new)    (po_obj*)              ;
    bool_t (*on_open)   (po_obj*)              ;
    void   (*on_close)  (po_obj*)              ;
    void   (*on_del)    (po_obj*)              ;

    i64_t  (*on_control)(po_obj*, u32_t, void*);
    i64_t  (*on_write)  (po_obj*, po_ubuf)     ;
    i64_t  (*on_read)   (po_obj*, po_ubuf)     ;
}   po_dev_ops;
po_str* po_dev_name(po_dev);
po_obj* po_dev_type(po_dev);

#endif
