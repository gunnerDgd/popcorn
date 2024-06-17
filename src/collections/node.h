#ifndef __PO_COLLECTIONS_NODE_H__
#define __PO_COLLECTIONS_NODE_H__

#include "../po.h"

extern po_obj_trait *po_node_t ;
typedef struct       po_node   {
    po_obj          head       ;
    struct po_node *prev, *next;
    po_obj         *node       ;
}   po_node;

bool_t   po_node_new  (po_node*, u32_t, va_list);
bool_t   po_node_clone(po_node*, po_node*)      ;
void     po_node_del  (po_node*)                ;

po_obj*  po_node_value(po_node*)                ;
po_node* po_node_next (po_node*, po_node*)      ;
po_node* po_node_prev (po_node*, po_node*)      ;

#ifndef __cplusplus
#define po_next(par)               po_node_next (par, 0)
#define po_next_as(par, par_next)  po_node_next (par, par_next)
#define po_prev(par)               po_node_prev (par, 0)
#define po_prev_as(par, par_prev)  po_node_prev (par, par_prev)
#define po_value(par)              po_node_value(par)
#define po_value_as(par, par_type) ((par_type)po_node_value(par))
#endif

#endif