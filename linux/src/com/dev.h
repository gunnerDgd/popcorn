#ifndef __PO_COM_DEV_H__
#define __PO_COM_DEV_H__

#include <obj.h>
#include <str.h>

struct po_com;
struct po_com* po_com_dev_root       (void)   ;
struct po_com* po_com_dev_cstr       (cstr_t) ;
struct po_com* po_com_dev            (po_str*);

struct po_com* po_com_dev_power_cstr (cstr_t) ;
struct po_com* po_com_dev_power      (po_str*);

struct po_com* po_com_dev_subsys_cstr(cstr_t) ;
struct po_com* po_com_dev_subsys     (po_str*);

#endif
