#ifndef __PO_LINUX_DEV_H__
#define __PO_LINUX_DEV_H__

#include <linux/cdev.h>
#include <linux/fs.h>

#include "../../../core.h"
#include "../../../mem/buf.h"

struct po_dev_type;
struct po_dev     ;

typedef struct po_dev_ops                      {
    bool_t (*on_new)    (po_obj*)              ;
    bool_t (*on_ref)    (po_obj*)              ;
    void   (*on_del)    (po_obj*)              ;

    i64_t  (*on_control)(po_obj*, u32_t, void*);
    i64_t  (*on_write)  (po_obj*, po_buf*)     ;
    i64_t  (*on_read)   (po_obj*, po_buf*)     ;
}   po_dev_ops;

#define              po_dev_free 0
#define              po_dev_use  1
#define              po_dev_busy 2
extern po_obj_trait* po_dev_t  ;
typedef struct       po_dev    {
    po_obj              head   ;
    u64_t               state  ;
    po_str              name   ;
    struct po_dev_type *type   ;
    po_dev_ops         *ops    ;

    dev_t               id     ;
    dev_t               idx    ;
    struct device      *dev_hnd;
    po_obj             *dev    ;
    po_list_elem       *hnd    ;

}   po_dev;

bool_t  po_dev_new  (po_dev*, u32_t, va_list);
bool_t  po_dev_clone(po_dev*, po_dev*)       ;
void    po_dev_del  (po_dev*)                ;

po_str* po_dev_name (po_dev*)       ;
void    po_dev_wait (po_dev*, u64_t);

MODULE_LICENSE("GPL");

#endif
