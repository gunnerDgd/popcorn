#ifndef __PO_COM_COM_H__
#define __PO_COM_COM_H__

#include <obj.h>
#include <str.h>

#include <linux/kobject.h>

extern po_obj_trait *po_com_t;
typedef struct       po_com  {
    po_obj              head;
    struct po_com      *sup;
    struct kernfs_node *dir;
    struct kobject     *com;
}   po_com;

po_com* po_com_root    (void);
bool_t  po_com_new     (po_com*, u32_t, va_list);
bool_t  po_com_clone   (po_com*, po_com*)       ;
void    po_com_del     (po_com*)                ;

po_com* po_com_sub_cstr(po_com*, cstr_t) ;
po_com* po_com_sub     (po_com*, po_str*);
po_com* po_com_sup     (po_com*)         ;
any_t   po_com_handle  (po_com*)         ;

#endif
