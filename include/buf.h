#ifndef __BUF_H__
#define __BUF_H__

#include "obj.h"

extern po_obj_trait *po_buf_vec_t;
extern po_obj_trait *po_buf_t    ;

typedef struct po_buf_vec { u8_t buf_vec[128]; } po_buf_vec;
typedef struct po_buf     { u8_t buf    [256]; } po_buf    ;

po_buf_vec* po_buf_vec_from_user (u8_t*, u64_t, po_mem*);
po_buf_vec* po_buf_vec_from      (u8_t*, u64_t)         ;

u64_t       po_buf_vec_copy_user (po_buf_vec*, u8_t*, u64_t)  ;
u64_t       po_buf_vec_copy      (po_buf_vec*, u8_t*, u64_t)  ;
bool_t      po_buf_vec_empty     (po_buf_vec*)                ;
u64_t       po_buf_vec_len       (po_buf_vec*)                ;

u64_t       po_buf_copy_user     (po_buf*, u8_t*, u64_t)      ;
u64_t       po_buf_copy          (po_buf*, u8_t*, u64_t)      ;

void        po_buf_push          (po_buf*, po_buf_vec*)       ;
po_buf_vec* po_buf_pop           (po_buf*)                    ;

#endif
