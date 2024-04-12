#ifndef __SET_H__
#define __SET_H__

#include "../core.h"

extern po_obj_trait* po_set_root_t           ;
typedef struct       po_set_root             {
    po_obj              head                 ;
    po_obj             *node[PRESET_ARCH_BIT];
    struct po_set_root *sub [PRESET_ARCH_BIT];
    reg_t               free;
    reg_t               use ;
    reg_t               num ;
}   po_set_root;

bool_t  po_set_root_new  (po_set_root*, u32_t, va_list);
bool_t  po_set_root_clone(po_set_root*, po_set_root*)  ;
void    po_set_root_del  (po_set_root*)                ;

po_obj* po_set_root_acq  (po_set_root*)         ;
bool_t  po_set_root_rel  (po_set_root*, po_obj*);

extern po_obj_trait *po_set_t;
typedef struct       po_set  {
    po_obj       head;
    po_set_root* set ;
}   po_set;

bool_t  po_set_new  (po_set*, u32_t, va_list);
bool_t  po_set_clone(po_set*, po_set*)       ;
void    po_set_del  (po_set*)                ;

po_obj* po_set_acq  (po_set*)         ;
void    po_set_rel  (po_set*, po_obj*);

#endif