#ifndef __PO_FS_WRITE_H__
#define __PO_FS_WRITE_H__

#include <obj.h>
#include <fut.h>
#include <buf.h>

extern po_obj_trait *po_write_t;
typedef struct       po_write  { u8_t po_write[128]; } po_write;

po_buf_vec* po_write_to_buf_vec(po_write*)              ;
po_buf_vec* po_write_to_buf    (po_write*, po_buf*)     ;
void        po_write_to        (po_write*, u8_t*, u64_t);

void        po_write_ready     (po_write*)              ;
void        po_write_err       (po_write*, u64_t)       ;

u8_t*       po_write_buf       (po_write*)              ;
u64_t       po_write_len       (po_write*)              ;
po_fut*     po_write_fut       (po_write*)              ;

#endif