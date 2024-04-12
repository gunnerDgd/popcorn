#ifndef __PO_CORE_MEM_H__
#define __PO_CORE_MEM_H__

#include "type.h"
#include "obj.h"

typedef struct po_mem_ops               {
    void* (*on_acq)(any_t, void*, u64_t);
    void  (*on_rel)(any_t, void*, u64_t);
    any_t (*on_new)(u32_t, va_list);
    void  (*on_del)(any_t);
}   po_mem_ops;

#define po_make_mem_ops(par_acq, par_rel, par_new, par_del) {\
    .on_acq = ((void* (*)(any_t, void*, u64_t))(par_acq)),\
    .on_rel = ((void  (*)(any_t, void*, u64_t))(par_rel)),\
    .on_new = ((any_t (*)(u32_t, va_list))     (par_new)),\
    .on_del = ((void  (*)(any_t))              (par_del)),\
}

extern po_obj_trait *po_mem_t;
typedef struct       po_mem  {
    po_obj      head;
    po_mem_ops *ops;
    any_t       mem;
}   po_mem;

bool_t  po_mem_new  (po_mem*, u32_t, va_list);
bool_t  po_mem_clone(po_mem*, po_mem*)       ;
void    po_mem_del  (po_mem*)                ;

po_mem* po_get_mem  (void);
po_mem* po_set_mem  (po_mem*);

void*   po_mem_acq  (po_mem*, void*, u64_t);
void    po_mem_rel  (po_mem*, void*, u64_t);

void    po_mem_set  (void*, u8_t , u64_t)       ;
void    po_mem_copy (void*, void*, u64_t)       ;
void    po_mem_move (void*, void*, u64_t)       ;
u64_t   po_mem_find (void*, void*, u64_t, u64_t);

bool_t  po_mem_eq   (void*, void*, u64_t, u64_t);
bool_t  po_mem_gt   (void*, void*, u64_t, u64_t);
bool_t  po_mem_lt   (void*, void*, u64_t, u64_t);

#define KB *(1ull << 10ull)
#define MB *(1ull << 20ull)
#define GB *(1ull << 30ull)

#ifndef __cplusplus
#define po_new(par)  po_mem_acq(po_get_mem(), null_t, sizeof(par))
#define po_drop(par) po_mem_rel(po_get_mem(), par, 0)
#endif

#endif
