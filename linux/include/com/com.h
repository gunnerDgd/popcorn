#ifndef __PO_COM_H__
#define __PO_COM_H__

#include <obj.h>
#include <str.h>

extern po_obj_trait *po_com_t;
typedef struct       po_com  { u8_t po_com[64]; }   po_com;

po_com* po_com_root    (void)            ;

po_com* po_com_sub_cstr(po_com*, cstr_t) ;
po_com* po_com_sub     (po_com*, po_str*);
po_com* po_com_sup     (po_com*)         ;
any_t   po_com_handle  (po_com*)         ;

#endif
