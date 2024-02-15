#ifndef __OBJ_H__
#define __OBJ_H__

#include "mem.h"

#include "type.h"
#include "ops.h"

struct po_obj;
typedef struct po_obj_trait                              {
    bool_t    (*on_new)  (struct po_obj*, u32_t, va_list);
    bool_t    (*on_clone)(struct po_obj*, struct po_obj*);
    bool_t    (*on_ref)  (struct po_obj*)                ;
    void      (*on_del)  (struct po_obj*)                ;
    u64_t       size;
    po_obj_ops *ops ;
}   po_obj_trait;

typedef struct po_obj  {
    po_obj_trait *trait;
    reg_t         ref  ;
    po_mem       *mem  ;
    void         *data ;
}   po_obj;

po_obj* po_obj_new      (po_mem*, po_obj_trait*, u32_t, ...)    ;
po_obj* po_obj_new_va   (po_mem*, po_obj_trait*, u32_t, va_list);

bool_t  po_obj_new_at   (po_obj*, po_obj_trait*, u32_t, ...)    ;
bool_t  po_obj_new_at_va(po_obj*, po_obj_trait*, u32_t, va_list);

po_obj* po_obj_clone    (po_obj*)         ;
bool_t  po_obj_clone_at (po_obj*, po_obj*);

po_obj* po_obj_ref      (po_obj*);
u64_t   po_obj_del		(po_obj*);

po_obj_trait* po_obj_get_trait(po_obj*);
u64_t         po_obj_use_count(po_obj*);

#ifndef __cplusplus
#define po_make(par_type)           (par_type*)po_obj_new      (null_t          , ((po_obj_trait*)(par_type##_t)),
#define po_vmake(par_type)          (par_type*)po_obj_new_va   (null_t          , ((po_obj_trait*)(par_type##_t)),
#define po_make_at(par, par_type)              po_obj_new_at   (((po_obj*)(par)), ((po_obj_trait*)(par_type##_t)),
#define po_vmake_at(par, par_type)             po_obj_new_at_va(((po_obj*)(par)), ((po_obj_trait*)(par_type##_t)),
#define from(...)                __VA_ARGS__)

#define po_clone(par)               po_obj_clone    (((po_obj*)par))
#define po_clone_at(par, par_clone) po_obj_clone_at (((po_obj*)par), ((po_obj*)par_clone))
#define po_ref(par)                 po_obj_ref      (((po_obj*)par))
#define po_del(par)                 po_obj_del      (((po_obj*)par))
#define po_use_count(par)           po_obj_use_count(((po_obj*)par))
#define po_trait_of(par)            po_obj_get_trait(((po_obj*)par))

#define po_make_trait(par_new, par_clone, par_ref, par_del, par_size, par_ops) {\
    .on_new   = ((bool_t (*)(po_obj*, u32_t, va_list))(par_new))  ,                \
    .on_clone = ((bool_t (*)(po_obj*, po_obj*))       (par_clone)),                \
    .on_ref   = ((bool_t (*)(po_obj*))(par_ref))                  ,                \
    .on_del   = ((void   (*)(po_obj*))(par_del))                  ,                \
    .size     = ((u64_t)(par_size))                               ,                \
    .ops      = ((po_obj_ops*)(par_ops))                          ,                \
}

#endif
#endif