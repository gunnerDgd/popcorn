#ifndef __PO_CORE_LINUX_OBJ_H__
#define __PO_CORE_LINUX_OBJ_H__

#include "mem.h"

#include "../type.h"
#include "../type_atom.h"

#include <linux/kref.h>

typedef struct po_obj         {
    struct kref          ref  ;
    po_mem              *mem  ;
    struct po_obj_trait *trait;
    void                *data ;
}   po_obj;

typedef struct po_obj_trait                    {
    bool_t (*on_new)  (po_obj*, u32_t, va_list);
    bool_t (*on_clone)(po_obj*, po_obj*)       ;
    bool_t (*on_ref)  (po_obj*)                ;
    void   (*on_del)  (po_obj*)                ;
    u64_t    size;
}   po_obj_trait;

#define as_new(par)   ((bool_t (*)(po_obj*, u32_t, va_list))(par))
#define as_clone(par) ((bool_t (*)(po_obj*, po_obj*))       (par))
#define as_ref(par)   ((bool_t (*)(po_obj*))                (par))
#define as_del(par)   ((void   (*)(po_obj*))                (par))

po_obj*       po_obj_new      (po_mem*, po_obj_trait*, u32_t, ...)    ;
po_obj*       po_obj_new_va   (po_mem*, po_obj_trait*, u32_t, va_list);

bool_t        po_obj_new_at   (po_obj*, po_obj_trait*, u32_t, ...)    ;
bool_t        po_obj_new_at_va(po_obj*, po_obj_trait*, u32_t, va_list);

po_obj*       po_obj_clone    (po_obj*)                               ;
bool_t        po_obj_clone_at (po_obj*, po_obj*)                      ;

po_obj*       po_obj_ref      (po_obj*)                               ;
u64_t         po_obj_del	  (po_obj*)                               ;

po_obj_trait* po_obj_get_trait(po_obj*)                               ;
u64_t         po_obj_use_count(po_obj*)                               ;

#ifndef __cplusplus
#define make(par_type)           po_obj_new      (0             , ((po_obj_trait*)par_type),
#define make_at(par, par_type)   po_obj_new_at   (((po_obj*)par), ((po_obj_trait*)par_type),
#define vmake(par_type)          po_obj_new_va   (0             , ((po_obj_trait*)par_type),
#define vmake_at(par, par_type)  po_obj_new_at_va(((po_obj*)par), ((po_obj_trait*)par_type),
#define from(...)                __VA_ARGS__)

#define clone(par)               po_obj_clone    (((po_obj*)par))
#define clone_at(par, par_clone) po_obj_clone_at (((po_obj*)par), ((po_obj*)par_clone))
#define ref(par)                 po_obj_ref      (((po_obj*)par))
#define del(par)                 po_obj_del      (((po_obj*)par))
#define use_count(par)           po_obj_use_count(((po_obj*)par))
#define trait_of(par)            po_obj_get_trait(((po_obj*)par))

#endif
#endif
