#ifndef CORE_OBJ_H
#define CORE_OBJ_H

#include "type.h"
#include "ops.h"

struct pp_mem;
struct pp_obj;
typedef struct pp_obj_trait                              {
    bool_t    (*on_new)  (struct pp_obj*, u32_t, va_list);
    bool_t    (*on_clone)(struct pp_obj*, struct pp_obj*);
    bool_t    (*on_ref)  (struct pp_obj*)                ;
    void      (*on_del)  (struct pp_obj*)                ;
    u64_t       size;
    pp_obj_ops *ops ;
}   pp_obj_trait;

#define pp_make_trait(par_new, par_clone, par_ref, par_del, par_size, par_ops) {\
    .on_new   = ((bool_t (*)(pp_obj*, u32_t, va_list))(par_new))  ,             \
    .on_clone = ((bool_t (*)(pp_obj*, pp_obj*))       (par_clone)),             \
    .on_ref   = ((bool_t (*)(pp_obj*))(par_ref))                  ,             \
    .on_del   = ((void   (*)(pp_obj*))(par_del))                  ,             \
    .size     = ((u64_t)(par_size))                               ,             \
    .ops      = ((pp_obj_ops*)(par_ops))                          ,             \
}

typedef struct pp_obj { u8_t pp_obj[64]; } pp_obj;

extern pp_obj* pp_obj_new      (struct pp_mem*, pp_obj_trait*, u32_t, ...)    ;
extern pp_obj* pp_obj_new_va   (struct pp_mem*, pp_obj_trait*, u32_t, va_list);

extern bool_t  pp_obj_new_at   (pp_obj*, pp_obj_trait*, u32_t, ...)    ;
extern bool_t  pp_obj_new_at_va(pp_obj*, pp_obj_trait*, u32_t, va_list);

extern pp_obj* pp_obj_clone    (pp_obj*)         ;
extern bool_t  pp_obj_clone_at (pp_obj*, pp_obj*);

extern pp_obj* pp_obj_ref      (pp_obj*);
extern u64_t   pp_obj_del		(pp_obj*);

extern pp_obj_trait* pp_obj_get_trait(pp_obj*);
extern u64_t         pp_obj_use_count(pp_obj*);

#ifndef __cplusplus
#define pp_make(par_type)           (par_type*)pp_obj_new      (null_t          , ((pp_obj_trait*)(par_type##_t)),
#define pp_vmake(par_type)          (par_type*)pp_obj_new_va   (null_t          , ((pp_obj_trait*)(par_type##_t)),
#define pp_make_at(par, par_type)              pp_obj_new_at   (((pp_obj*)(par)), ((pp_obj_trait*)(par_type##_t)),
#define pp_vmake_at(par, par_type)             pp_obj_new_at_va(((pp_obj*)(par)), ((pp_obj_trait*)(par_type##_t)),
#define from(...)                __VA_ARGS__)

#define pp_clone(par)               pp_obj_clone    (((pp_obj*)par))
#define pp_clone_at(par, par_clone) pp_obj_clone_at (((pp_obj*)par), ((pp_obj*)par_clone))
#define pp_ref(par)                 pp_obj_ref      (((pp_obj*)par))
#define pp_del(par)                 pp_obj_del      (((pp_obj*)par))
#define pp_use_count(par)           pp_obj_use_count(((pp_obj*)par))
#define pp_trait_of(par)            pp_obj_get_trait(((pp_obj*)par))

#endif
#endif