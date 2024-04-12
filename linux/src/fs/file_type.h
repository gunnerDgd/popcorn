#ifndef __PO_FS_FILE_TYPE_H__
#define __PO_FS_FILE_TYPE_H__

#include <core.h>
#include <collections.h>
#include <linux/fs.h>

struct po_control;
struct po_write  ;
struct po_read   ;

typedef union po_poll       {
    struct                  {
        u64_t read       : 1;
        u64_t read_norm  : 1;
        u64_t write      : 1;
        u64_t write_norm : 1;
    };  u64_t all;
}   po_poll;

typedef struct po_file_ops                                     {
    bool_t         (*control)     (po_obj*, struct po_control*);
    bool_t         (*read_atomic) (po_obj*, struct po_read   *);
    bool_t         (*read)        (po_obj*, struct po_read   *);
    bool_t         (*write_atomic)(po_obj*, struct po_write  *);
    bool_t         (*write)       (po_obj*, struct po_write  *);
    struct po_not* (*poll)        (po_obj*, po_poll*)          ;
    void           (*close)       (po_obj*)                    ;
    bool_t         (*open)        (po_obj*)                    ;
}   po_file_ops;

#define po_make_file_ops(par_open, par_close, par_read, par_read_atomic, par_write, par_write_atomic, par_control, par_poll) { \
    .read_atomic  = ((bool_t         (*)(po_obj*, struct po_read*))   (par_read_atomic)) ,\
    .read         = ((bool_t         (*)(po_obj*, struct po_read*))   (par_read))        ,\
    .write_atomic = ((bool_t         (*)(po_obj*, struct po_write*))  (par_write_atomic)),\
    .write        = ((bool_t         (*)(po_obj*, struct po_write*))  (par_write))       ,\
    .open         = ((bool_t         (*)(po_obj*))                    (par_open))        ,\
    .close        = ((void           (*)(po_obj*))                    (par_close))       ,\
    .control      = ((bool_t         (*)(po_obj*, struct po_control*))(par_control))     ,\
    .poll         = ((struct po_not* (*)(po_obj*, po_poll*))          (par_poll))         \
}

extern po_obj_trait *po_file_type_t;
typedef struct       po_file_type  {
    po_obj                 head ;
    po_obj_trait          *trait;
    struct file_operations type ;
    po_file_ops           *ops  ;
}   po_file_type;

bool_t po_file_type_new  (po_file_type*, u32_t, va_list);
bool_t po_file_type_clone(po_file_type*, po_file_type*) ;
void   po_file_type_del  (po_file_type*)                ;

#endif
