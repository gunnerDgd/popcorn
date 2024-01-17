#ifndef __PO_OBJ_H__
#define __PO_OBJ_H__

#include "mem.h"

typedef struct po_obj { u8_t obj[64]; } po_obj;
typedef struct po_obj_trait                   {
    bool_t (*on_new)  (po_obj*, u32_t, va_list);
    bool_t (*on_clone)(po_obj*, po_obj*)       ;
    bool_t (*on_ref)  (po_obj*)                ;
    void   (*on_del)  (po_obj*)                ;
    u64_t    size;
}   po_obj_trait;

po_obj*       po_obj_new      (po_mem*, po_obj_trait*, u32_t, ...)    ;
po_obj*       po_obj_new_va   (po_mem*, po_obj_trait*, u32_t, va_list);

bool_t        po_obj_new_at   (po_obj*, po_obj_trait*, u32_t, ...)    ;
bool_t        po_obj_new_at_va(po_obj*, po_obj_trait*, u32_t, va_list);

po_obj*       po_obj_clone    (po_obj*)         ;
bool_t        po_obj_clone_at (po_obj*, po_obj*);

po_obj*       po_obj_ref      (po_obj*)      ;
u64_t         po_obj_del	  (po_obj*)      ;

po_obj_trait* po_obj_get_trait(po_obj*);
u64_t         po_obj_use_count(po_obj*);

#ifndef __cplusplus
#define make(par_type)          obj_new      (0  , par_type,
#define make_at(par, par_type)  obj_new_at   (par, par_type,
#define vmake(par_type)         obj_new_va   (0  , par_type,
#define vmake_at(par, par_type) obj_new_at_va(par, par_type,
#define from(...)               __VA_ARGS__)

#define clone(par)               obj_clone    (par)
#define clone_at(par, par_clone) obj_clone_at (par, par_clone)
#define ref(par)                 obj_ref      (par)
#define del(par)                 obj_del      (par)
#define use_count(par)           obj_use_count(par)
#define trait_of(par)            obj_get_trait(par)

#endif
#endif
