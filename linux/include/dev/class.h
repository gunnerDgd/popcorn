#ifndef __PO_DEV_CLASS_H__
#define __PO_DEV_CLASS_H__

#include <core.h>
#include <collections.h>

struct po_dev;
typedef struct po_class_ops               {
    bool_t (*add)(po_obj*, struct po_dev*);
    bool_t (*del)(po_obj*, struct po_dev*);
}   po_class_ops;

extern po_obj_trait *po_class_t;
typedef struct       po_class { u8_t class[512]; } po_class;

struct po_dev* po_class_find_cstr(po_class*, const char*, u64_t);
struct po_dev* po_class_find     (po_class*, po_str*)           ;

#endif
