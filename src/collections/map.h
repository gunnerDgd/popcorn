#ifndef COLLECTIONS_MAP_H
#define COLLECTIONS_MAP_H

#include "list.h"

extern pp_obj_trait* pp_map_t;
typedef struct       pp_map  {
    pp_obj  head;
    pp_list map ;
}   pp_map;

pp_pos* pp_map_push (pp_map*, pp_obj*);
pp_pos* pp_map_move (pp_map*, pp_obj*);
void    pp_map_pop  (pp_map*, any_t);
pp_pos* pp_map_find (pp_map*, any_t);

bool_t  pp_map_empty(pp_map*);
pp_pos* pp_map_begin(pp_map*);
pp_pos* pp_map_end  (pp_map*);

#endif