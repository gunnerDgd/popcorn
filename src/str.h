#ifndef __STR_H__
#define __STR_H__

#include "obj.h"
#include "bit.h"

extern struct po_obj_trait* po_str_t;
typedef struct	            po_str  {
    po_obj	head ;
	u64_t   front,
		    back ,
		    size ,
		    len  ;
    po_mem *res  ;
	u8_t*   mem  ;
}	po_str;

bool_t      po_str_new			   (po_str*, u32_t, va_list);
bool_t      po_str_clone		   (po_str*, po_str*)       ;
void        po_str_del			   (po_str*)		        ;

void        po_str_rsv_back	       (po_str*, u64_t);
void	    po_str_rsv_front	   (po_str*, u64_t);

void        po_str_push_back	   (po_str*, po_str*)		  ;
void        po_str_push_front	   (po_str*, po_str*)		  ;
void        po_str_push		       (po_str*, u64_t, po_str*);

void        po_str_push_front_cstr (po_str*, cstr_t)       ;
void        po_str_push_back_cstr  (po_str*, cstr_t)	   ;
void        po_str_push_cstr	   (po_str*, u64_t, cstr_t);

void        po_str_push_front_raw  (po_str*,        const char*, u64_t);
void        po_str_push_back_raw   (po_str*,        const char*, u64_t);
void        po_str_push_raw  	   (po_str*, u64_t, const char*, u64_t);

void        po_str_pop_front	   (po_str*, u64_t)       ;
void        po_str_pop_back	       (po_str*, u64_t)	      ;
void        po_str_pop		       (po_str*, u64_t, u64_t);

u64_t       po_str_find		       (po_str*, u64_t, po_str*)           ;
u64_t       po_str_find_cstr	   (po_str*, u64_t, cstr_t)            ;
u64_t       po_str_find_raw 	   (po_str*, u64_t, const char*, u64_t);

bool_t      po_str_eq		       (po_str*, po_str*)  ;
bool_t      po_str_gt		       (po_str*, po_str*)  ;
bool_t      po_str_lt		       (po_str*, po_str*)  ;

bool_t      po_str_eq_cstr	       (po_str*, cstr_t);
bool_t      po_str_gt_cstr	       (po_str*, cstr_t);
bool_t      po_str_lt_cstr         (po_str*, cstr_t);

bool_t      po_str_eq_raw	       (po_str*, const char*, u64_t);
bool_t      po_str_gt_raw	       (po_str*, const char*, u64_t);
bool_t      po_str_lt_raw          (po_str*, const char*, u64_t);

bool_t      po_str_starts	       (po_str*, po_str*);
bool_t	    po_str_ends		       (po_str*, po_str*);

bool_t      po_str_starts_cstr    (po_str*, cstr_t);
bool_t	    po_str_ends_cstr      (po_str*, cstr_t);

bool_t      po_str_starts_raw     (po_str*, const char*, u64_t);
bool_t	    po_str_ends_raw       (po_str*, const char*, u64_t);

bool_t      po_str_empty          (po_str*);
u64_t       po_str_len            (po_str*);
const char* po_str_as_raw         (po_str*);
cstr_t	    po_str_as_cstr        (po_str*);

#endif