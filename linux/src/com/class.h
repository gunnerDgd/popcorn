#ifndef __PO_COM_CLASS_H__
#define __PO_COM_CLASS_H__

#include <obj.h>
#include <str.h>

struct po_com;
struct po_com* po_com_class_root    (void)   ;
struct po_com* po_com_class_cstr    (cstr_t) ;
struct po_com* po_com_class         (po_str*);

struct po_com* po_com_class_dev_cstr(cstr_t , cstr_t) ;
struct po_com* po_com_class_dev     (po_str*, po_str*);

#endif
