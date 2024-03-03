#ifndef __PO_COM_BUS_H__
#define __PO_COM_BUS_H__

#include <str.h>
#include <obj.h>

struct po_com;
struct po_com* po_com_bus_root(void)   ;
struct po_com* po_com_bus_cstr(cstr_t) ;
struct po_com* po_com_bus     (po_str*);

struct po_com* po_com_bus_dev_cstr (cstr_t) ;
struct po_com* po_com_bus_dev      (po_str*);

struct po_com* po_com_bus_drv_cstr (cstr_t) ;
struct po_com* po_com_bus_drv      (po_str*);

#endif