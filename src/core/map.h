#ifndef __PO_MAP_H__
#define __PO_MAP_H__

#include "obj.h"
#include "list.h"

typedef struct po_map_key         {
    bool_t (*eq)(po_obj*, po_obj*);
    bool_t (*lt)(po_obj*, po_obj*);
    bool_t (*gt)(po_obj*, po_obj*);
}   po_map_key;

extern  po_obj_trait* po_map_t   ;
typedef po_list_elem  po_map_elem;
typedef struct        po_map     {
    po_obj      head;
    po_map_key* key ;
    po_list     map ;
}   po_map;

bool_t       po_map_new    (po_map*, u32_t, va_list);
bool_t       po_map_clone  (po_map*, po_map*)       ;
void         po_map_del    (po_map*)                ;

po_map_elem* po_map_push   (po_map*, po_obj*)       ;
void         po_map_pop    (po_map*, po_map_elem*)  ;
po_map_elem* po_map_find   (po_map*, po_obj*)       ;

bool_t       po_map_empty  (po_map*)                ;
po_map_elem* po_map_begin  (po_map*)                ;
po_map_elem* po_map_end    (po_map*)                ;
po_map_elem* po_map_next   (po_map_elem*)           ;
po_map_elem* po_map_prev   (po_map_elem*)           ;
po_obj*      po_map_get    (po_map_elem*)           ;

#endif