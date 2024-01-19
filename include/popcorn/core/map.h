#ifndef __PO_CORE_MAP_H__
#define __PO_CORE_MAP_H__

#include "obj.h"
#include "list.h"

extern po_obj_trait *po_map_t     ;
typedef void        *po_map_elem     ;
typedef struct       po_map          { u8_t map[256]; } po_map;
typedef struct       po_map_key      {
    bool_t (*eq)(po_obj*, po_obj*);
    bool_t (*lt)(po_obj*, po_obj*);
    bool_t (*gt)(po_obj*, po_obj*);
}   po_map_key;

po_map_elem po_map_push   (po_map*, po_obj*)    ;
void        po_map_pop    (po_map*, po_map_elem);
po_map_elem po_map_find   (po_map*, po_obj*)    ;

bool_t      po_map_empty  (po_map*)             ;
po_map_elem po_map_begin  (po_map*)             ;
po_map_elem po_map_end    (po_map*)             ;
po_map_elem po_map_next   (po_map_elem)         ;
po_map_elem po_map_prev   (po_map_elem)         ;
po_obj*     po_map_get    (po_map_elem)         ;

#endif