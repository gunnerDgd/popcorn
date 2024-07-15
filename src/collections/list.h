#ifndef COLLECTIONS_LIST_H
#define COLLECTIONS_LIST_H

#include "pos.h"

extern pp_obj_trait* pp_list_t;
typedef struct       pp_list  {
    pp_obj  head      ;
    pp_pos  begin, end;
    pp_mem *mem       ;
}   pp_list;

pp_pos* pp_list_push_front(pp_list*, any_t);
pp_pos* pp_list_push_back (pp_list*, any_t);

pp_pos* pp_list_move_front(pp_list*, any_t*);
pp_pos* pp_list_move_back (pp_list*, any_t*);

any_t   pp_list_pop_front (pp_list*);
any_t   pp_list_pop_back  (pp_list*);

bool_t  pp_list_empty     (pp_list*);
pp_pos* pp_list_begin     (pp_list*);
pp_pos* pp_list_end       (pp_list*);

#define pp_list_for(list, pos)                                            \
    pp_pos* pos = pp_list_begin((list)), *pos##_end = pp_list_end((list));\
    for( ; pos && (pos != pos##_end) ; pos = pp_next(pos))

#endif
