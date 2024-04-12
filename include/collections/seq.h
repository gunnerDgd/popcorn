#ifndef __PO_COLLECTIONS_SEQ_H__
#define __PO_COLLECTIONS_SEQ_H__

#include "../core.h"

extern po_obj_trait *po_seq_t;
typedef struct       po_seq  { u8_t po_seq[128]; } po_seq;

void   po_seq_prep_front(po_seq*, u64_t)       ;
void   po_seq_prep_back (po_seq*, u64_t)       ;
void   po_seq_prep      (po_seq*, u64_t, u64_t);

u64_t  po_seq_free_front(po_seq*);
u64_t  po_seq_free_back (po_seq*);
bool_t po_seq_empty     (po_seq*);
u64_t  po_seq_len       (po_seq*);
void*  po_seq_ptr       (po_seq*);

void   po_seq_push_front(po_seq*, void*, u64_t)       ;
void   po_seq_push_back (po_seq*, void*, u64_t)       ;
void   po_seq_push      (po_seq*, void*, u64_t, u64_t);

void   po_seq_pop_front (po_seq*, u64_t)       ;
void   po_seq_pop_back  (po_seq*, u64_t)       ;
void   po_seq_pop       (po_seq*, u64_t, u64_t);

#endif
