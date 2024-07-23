#ifndef COLLECTIONS_MAP_H
#define COLLECTIONS_MAP_H

#include "list.h"

extern pp_obj_trait* pp_map_t;
typedef struct       pp_map  { u8_t pp_map[256]; } pp_map;

pp_pos* pp_map_move (pp_map*, any_t*);
pp_pos* pp_map_push (pp_map*, any_t);
void    pp_map_pop  (pp_map*, any_t);
pp_pos* pp_map_find (pp_map*, any_t);

bool_t  pp_map_empty(pp_map*);
pp_pos* pp_map_begin(pp_map*);
pp_pos* pp_map_end  (pp_map*);

#define pp_map_for(map, pos)                                          \
    pp_pos* pos = pp_map_begin((map)), *pos##_end = pp_map_end((map));\
    for( ; pos && (pos != pos##_end) ; pos = pp_next(pos))

#endif