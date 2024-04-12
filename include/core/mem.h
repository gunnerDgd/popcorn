#ifndef __MEM_H__
#define __MEM_H__

#include "type.h"
#include "obj.h"

extern po_obj_trait *po_mem_t;
typedef struct po_mem { u8_t po_mem[64]; } po_mem;

po_mem*   po_get_mem  (void);
po_mem*   po_set_mem  (po_mem*);

bool_t po_mem_new  (po_mem*, u32_t, va_list);
bool_t po_mem_clone(po_mem*, po_mem*)       ;
void   po_mem_del  (po_mem*)                ;

void*  po_mem_acq  (po_mem*, void*, u64_t);
void   po_mem_rel  (po_mem*, void*, u64_t);

void   po_mem_set  (void*, u8_t , u64_t)       ;
void   po_mem_copy (void*, void*, u64_t)       ;
void   po_mem_move (void*, void*, u64_t)       ;
u64_t  po_mem_find (void*, void*, u64_t, u64_t);
bool_t po_mem_eq   (void*, void*, u64_t, u64_t);
bool_t po_mem_gt   (void*, void*, u64_t, u64_t);
bool_t po_mem_lt   (void*, void*, u64_t, u64_t);

#ifdef PRESET_LINUX
extern po_mem po_heap     ;
extern po_mem po_heap_atom;
extern po_mem po_page     ;
#endif

#define KB *(1ull << 10ull)
#define MB *(1ull << 20ull)
#define GB *(1ull << 30ull)

#ifndef __cplusplus
#define po_new(par)  po_mem_acq(po_get_mem(), null_t, sizeof(par))
#define po_drop(par) po_mem_rel(po_get_mem(), par   , 0)
#endif

#endif
