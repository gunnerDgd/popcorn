#ifndef __PO_BUF_H__
#define __PO_BUF_H__

#include "obj.h"
#include "list.h"

extern po_obj_trait *po_buf_vec_t;
typedef struct       po_buf_vec  {
    po_obj  head;
    po_mem *mem ;
    u8_t   *buf ;
    u64_t   len ;
    u64_t   off ;
}   po_buf_vec;

po_buf_vec* po_buf_vec_from_user (u8_t*, u64_t, po_mem*);
po_buf_vec* po_buf_vec_from      (u8_t*, u64_t)         ;

bool_t      po_buf_vec_new       (po_buf_vec*, u32_t, va_list);
bool_t      po_buf_vec_clone     (po_buf_vec*, po_buf_vec*)   ;
void        po_buf_vec_del       (po_buf_vec*)                ;

u64_t       po_buf_vec_copy_user (po_buf_vec*, u8_t*, u64_t)  ;
u64_t       po_buf_vec_copy      (po_buf_vec*, u8_t*, u64_t)  ;
bool_t      po_buf_vec_empty     (po_buf_vec*)                ;
u64_t       po_buf_vec_len       (po_buf_vec*)                ;

extern po_obj_trait *po_buf_t;
typedef struct       po_buf  {
    po_obj  head;
    po_list buf ;
}   po_buf;

bool_t      po_buf_new      (po_buf*, u32_t, va_list);
bool_t      po_buf_clone    (po_buf*, po_buf*)       ;
void        po_buf_del      (po_buf*)                ;

u64_t       po_buf_copy_user(po_buf*, u8_t*, u64_t)  ;
u64_t       po_buf_copy     (po_buf*, u8_t*, u64_t)  ;

void        po_buf_push     (po_buf*, po_buf_vec*)   ;
po_buf_vec* po_buf_pop      (po_buf*)                ;

#endif
