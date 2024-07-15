#ifndef CORE_MEM_H
#define CORE_MEM_H

#include "type.h"
#include "obj.h"

extern pp_obj_trait *pp_mem_t;
typedef struct pp_mem { u8_t pp_mem[64]; } pp_mem;

typedef struct pp_mem_ops                {
    void* (*on_use) (any_t, void*, u64_t);
    void  (*on_free)(any_t, void*, u64_t);
    any_t (*on_new) (u32_t, va_list);
    void  (*on_del) (any_t);
}   pp_mem_ops;

#define pp_make_mem_ops(do_use, do_free, do_new, do_del)  {\
    .on_use  = ((void* (*)(any_t, void*, u64_t))(do_use)) ,\
    .on_free = ((void  (*)(any_t, void*, u64_t))(do_free)),\
    .on_new  = ((any_t (*)(u32_t, va_list))     (do_new)) ,\
    .on_del  = ((void  (*)(any_t))              (do_del)) ,\
}

extern pp_mem*  pp_get_mem  (void);
extern pp_mem*  pp_set_mem  (pp_mem*);

void            pp_mem_free (pp_mem*, void*, u64_t);
void*           pp_mem_use  (pp_mem*, void*, u64_t);

extern u64_t    pp_mem_find (void*, void*, u64_t, u64_t);
extern void     pp_mem_set  (void*, u8_t , u64_t);
extern void     pp_mem_copy (void*, void*, u64_t);
extern void     pp_mem_move (void*, void*, u64_t);

extern pp_ord_t pp_mem_ord  (void*, void*, u64_t);
extern bool_t   pp_mem_eq   (void*, void*, u64_t);
extern bool_t   pp_mem_gt   (void*, void*, u64_t);
extern bool_t   pp_mem_lt   (void*, void*, u64_t);

#ifdef PRESET_LINUX
extern pp_mem *pp_heap     ;
extern pp_mem *pp_heap_atom;
extern pp_mem *pp_page     ;
#endif

#define KB *(1ull << 10ull)
#define MB *(1ull << 20ull)
#define GB *(1ull << 30ull)

#ifndef __cplusplus
#define pp_new(par)  pp_mem_use (null_t, null_t, sizeof(par))
#define pp_drop(par) pp_mem_free(null_t, par   , 0)
#endif

#endif
