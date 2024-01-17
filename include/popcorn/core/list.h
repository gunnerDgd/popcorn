#ifndef __PO_CORE_LIST_H__
#define __PO_CORE_LIST_H__

#include "obj.h"
#include "../mod.h"

extern po_obj_trait *po_list_t   ;
typedef struct       po_list     { u8_t handle[256]; } po_list;
typedef void*        po_list_elem;

po_mod po_list_elem po_list_push_back (po_list*, po_obj*)              ;
po_mod po_list_elem po_list_push_front(po_list*, po_obj*)              ;
po_mod po_list_elem po_list_push      (po_list*, po_obj*, po_list_elem);

po_mod po_obj*      po_list_pop_front (po_list*)                       ;
po_mod po_obj*      po_list_pop_back  (po_list*)                       ;
po_mod po_obj*      po_list_pop       (po_list*, po_list_elem)         ;

po_mod bool_t       po_list_empty     (po_list*)                       ;
po_mod po_list_elem po_list_begin     (po_list*)                       ;
po_mod po_list_elem po_list_end       (po_list*)                       ;
po_mod po_list_elem po_list_next      (po_list_elem)                   ;
po_mod po_list_elem po_list_prev      (po_list_elem)                   ;
po_mod po_obj*      po_list_get       (po_list_elem)                   ;
po_mod po_obj*      po_list_set       (po_list_elem, po_obj*)          ;

#define po_list_for(par, par_it)                                              \
    po_list_elem par_it = po_list_begin(par), par_it##_end = po_list_end(par);\
    for( ; par_it != par_it##_end ; par_it = po_list_next(par_it))

#define po_list_while(par, par_it)                                            \
    po_list_elem par_it = po_list_begin(par), par_it##_end = po_list_end(par);\
    while(par_it != par_it##_end)

#endif
