#ifndef __PO_CORE_MEM_H__
#define __PO_CORE_MEM_H__

#include "type.h"
#include "obj.h"

typedef struct po_mem_ops                {
    void* (*on_use) (any_t, void*, u64_t);
    void  (*on_free)(any_t, void*, u64_t);
    any_t (*on_new) (u32_t, va_list);
    void  (*on_del) (any_t);
}   po_mem_ops;

#define po_make_mem_ops(do_use, do_free, do_new, do_del)  {\
    .on_use  = ((void* (*)(any_t, void*, u64_t))(do_use)) ,\
    .on_free = ((void  (*)(any_t, void*, u64_t))(do_free)),\
    .on_new  = ((any_t (*)(u32_t, va_list))     (do_new)) ,\
    .on_del  = ((void  (*)(any_t))              (do_del)) ,\
}

extern po_obj_trait *po_mem_t;
typedef struct       po_mem  {
    po_obj      head;
    po_mem_ops *ops;
    any_t       mem;
}   po_mem;

bool_t   po_mem_new  (po_mem*, u32_t, va_list);
bool_t   po_mem_clone(po_mem*, po_mem*)       ;
void     po_mem_del  (po_mem*)                ;

po_mem*  po_get_mem  (void);
po_mem*  po_set_mem  (po_mem*);

void     po_mem_free (po_mem*, void*, u64_t);
void*    po_mem_use  (po_mem*, void*, u64_t);

void     po_mem_set  (void*, u8_t , u64_t)       ;
void     po_mem_copy (void*, void*, u64_t)       ;
void     po_mem_move (void*, void*, u64_t)       ;
u64_t    po_mem_find (void*, void*, u64_t, u64_t);

po_ord_t po_mem_ord  (void*, void*, u64_t);
bool_t   po_mem_eq   (void*, void*, u64_t);
bool_t   po_mem_gt   (void*, void*, u64_t);
bool_t   po_mem_lt   (void*, void*, u64_t);

#define KB *(1ull << 10ull)
#define MB *(1ull << 20ull)
#define GB *(1ull << 30ull)

#ifndef __cplusplus
#define po_new(par)  po_mem_use (null_t, null_t, sizeof(par))
#define po_drop(par) po_mem_free(null_t, par, 0)
#endif

#endif
