#ifndef __PO_COLLECTIONS_MAP_H__
#define __PO_COLLECTIONS_MAP_H__

#include "list.h"

extern po_obj_trait* po_map_t;
typedef struct       po_map  {
    po_obj  head;
    po_list map ;
}   po_map;

bool_t    po_map_new  (po_map*, u32_t, va_list);
bool_t    po_map_clone(po_map*, po_map*)       ;
void      po_map_del  (po_map*)                ;

po_node*  po_map_push (po_map*, po_obj*);
po_node*  po_map_move (po_map*, po_obj*);
void      po_map_pop  (po_map*, any_t);
po_node*  po_map_find (po_map*, any_t);

bool_t    po_map_empty(po_map*);
po_node*  po_map_begin(po_map*);
po_node*  po_map_end  (po_map*);

#endif