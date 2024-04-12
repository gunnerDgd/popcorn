#ifndef __MAP_H__
#define __MAP_H__

#include "list.h"

extern po_obj_trait* po_map_t;
typedef struct       po_map  { u8_t po_map[256]; } po_map;

po_node*  po_map_push (po_map*, po_obj*)       ;
void      po_map_pop  (po_map*, po_obj*)       ;
po_node*  po_map_find (po_map*, po_obj*)       ;

bool_t    po_map_empty(po_map*)                ;
po_node*  po_map_begin(po_map*)                ;
po_node*  po_map_end  (po_map*)                ;

#endif