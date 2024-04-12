#ifndef __PO_FS_FILE_H__
#define __PO_FS_FILE_H__

#include <core.h>
#include <collections.h>

struct po_file_type;

extern po_obj_trait *po_file_t;
typedef struct       po_file  {
    po_obj               head;
    struct po_file_type *type;
    struct file         *file;
    po_obj              *obj;
}   po_file;

bool_t po_file_new  (po_file*, u32_t, va_list);
bool_t po_file_clone(po_file*, po_file*)      ;
void   po_file_del  (po_file*)                ;

#endif