#ifndef __PO_CORE_MEM_H__
#define __PO_CORE_MEM_H__

#include "type.h"
#include "../mod.h"

typedef struct po_mem                      {
    void* (*on_new) (struct po_mem*, u64_t);
    void  (*on_del) (struct po_mem*, void*);
}   po_mem;

po_mod po_mem*  po_get_mem (void)                      ;
po_mod po_mem*  po_set_mem (po_mem*)                   ;
po_mod void*    po_mem_new (po_mem*, u64_t)            ;
po_mod void     po_mem_del (po_mem*, void*)            ;

po_mod void     po_mem_set (void*, u8_t , u64_t)       ;
po_mod void     po_mem_copy(void*, void*, u64_t)       ;
po_mod void     po_mem_move(void*, void*, u64_t)       ;
po_mod u64_t    po_mem_find(void*, void*, u64_t, u64_t);
po_mod bool_t   po_mem_eq  (void*, void*, u64_t)       ;
po_mod bool_t   po_mem_gt  (void*, void*, u64_t)       ;
po_mod bool_t   po_mem_lt  (void*, void*, u64_t)       ;

#define KB *(1ull << 10ull)
#define MB *(1ull << 20ull)
#define GB *(1ull << 30ull)

#endif
