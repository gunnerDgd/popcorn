#ifndef __PO_CORE_LIST_H__
#define __PO_CORE_LIST_H__

#include "obj.h"

typedef struct po_list_elem         {
    po_obj               head       ;
    struct po_list_elem *prev, *next;
    struct po_list      *list       ;
    po_obj              *elem       ;
}   po_list_elem;

extern po_obj_trait* po_list_t;
typedef struct       po_list  {
    po_obj       head      ;
    po_mem      *res       ;
    po_list_elem begin, end;
}   po_list;

bool_t        po_list_new       (po_list*, u32_t, va_list)        ;
bool_t        po_list_clone     (po_list*, po_list*)              ;
void          po_list_del       (po_list*)                        ;

po_list_elem* po_list_push_back (po_list*, po_obj*)               ;
po_list_elem* po_list_push_front(po_list*, po_obj*)               ;
po_list_elem* po_list_push      (po_list*, po_obj*, po_list_elem*);

po_obj*       po_list_pop_front (po_list*)                        ;
po_obj*       po_list_pop_back  (po_list*)                        ;
po_obj*       po_list_pop       (po_list*, po_list_elem*)         ;

bool_t        po_list_empty     (po_list*)                        ;
po_list_elem* po_list_begin     (po_list*)                        ;
po_list_elem* po_list_end       (po_list*)                        ;
po_list_elem* po_list_next      (po_list_elem*)                   ;
po_list_elem* po_list_prev      (po_list_elem*)                   ;

po_obj*       po_list_get       (po_list_elem*)                   ;
po_obj*       po_list_set       (po_list_elem*, po_obj*)          ;
#define       po_list_get_as(par, par_type)          ((par_type)po_list_get(par))
#define       po_list_set_as(par, par_set, par_type) ((par_type)po_list_set(par, (po_obj*)par_set))

#define po_list_for(par, par_it)                                          \
    po_list_elem* par_it = po_list_begin(par), *par_it##_end = po_list_end(par);\
    for( ; par_it != par_it##_end ; par_it = po_list_next(par_it))

#define po_list_while(par, par_it)                                        \
    po_list_elem* par_it = po_list_begin(par), *par_it##_end = po_list_end(par);\
    while(par_it != par_it##_end)

#endif