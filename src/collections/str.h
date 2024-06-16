#ifndef __PO_COLLECTIONS_STR_H__
#define __PO_COLLECTIONS_STR_H__

#include "seq.h"

extern po_obj_trait* po_str_t;
typedef struct       po_str  {
    po_obj head;
    po_seq str ;
}	po_str;

bool_t      po_str_new			   (po_str*, u32_t, va_list);
bool_t      po_str_clone		   (po_str*, po_str*)       ;
void        po_str_del			   (po_str*)		        ;

void	    po_str_prep_front	   (po_str*, u64_t);
void        po_str_prep_back	   (po_str*, u64_t);

void        po_str_push_back	   (po_str*, po_str*)	    ;
void        po_str_push_front	   (po_str*, po_str*)		;
void        po_str_push		       (po_str*, po_str*, u64_t);

void        po_str_push_front_cstr (po_str*, const char*, u64_t)	   ;
void        po_str_push_back_cstr  (po_str*, const char*, u64_t)	   ;
void        po_str_push_cstr	   (po_str*, const char*, u64_t, u64_t);

void        po_str_pop_front	   (po_str*, u64_t)       ;
void        po_str_pop_back	       (po_str*, u64_t)	      ;
void        po_str_pop		       (po_str*, u64_t, u64_t);

u64_t       po_str_find		       (po_str*, u64_t, po_str*)           ;
u64_t       po_str_find_cstr	   (po_str*, u64_t, const char*, u64_t);

po_ord_t    po_str_ord_cstr        (po_str*, const char*, u64_t);
po_ord_t    po_str_ord             (po_str*, po_str*)           ;

bool_t      po_str_eq		       (po_str*, po_str*)  ;
bool_t      po_str_gt		       (po_str*, po_str*)  ;
bool_t      po_str_lt		       (po_str*, po_str*)  ;

bool_t      po_str_eq_cstr	       (po_str*, const char*, u64_t);
bool_t      po_str_gt_cstr	       (po_str*, const char*, u64_t);
bool_t      po_str_lt_cstr         (po_str*, const char*, u64_t);

bool_t      po_str_begin	       (po_str*, po_str*);
bool_t	    po_str_end		       (po_str*, po_str*);

bool_t      po_str_begin_cstr      (po_str*, const char*, u64_t);
bool_t	    po_str_end_cstr        (po_str*, const char*, u64_t);

bool_t      po_str_empty           (po_str*);
u64_t       po_str_len             (po_str*);
const char* po_str_ptr             (po_str*);

#endif