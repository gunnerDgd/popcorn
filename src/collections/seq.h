#ifndef COLLECTIONS_SEQ_H
#define COLLECTIONS_SEQ_H

#include "../core.h"

extern pp_obj_trait *pp_seq_t;
typedef struct       pp_seq  {
    pp_obj  head;
    u64_t   begin, end;
    pp_mem *mem;
    u8_t   *ptr;
    u64_t   len;
}   pp_seq;

void   pp_seq_prep_front(pp_seq*, u64_t)       ;
void   pp_seq_prep_back (pp_seq*, u64_t)       ;
void   pp_seq_prep      (pp_seq*, u64_t, u64_t);

u64_t  pp_seq_free_front(pp_seq*);
u64_t  pp_seq_free_back (pp_seq*);
bool_t pp_seq_empty     (pp_seq*);
u64_t  pp_seq_len       (pp_seq*);
void*  pp_seq_ptr       (pp_seq*);

void   pp_seq_push_front(pp_seq*, void*, u64_t)       ;
void   pp_seq_push_back (pp_seq*, void*, u64_t)       ;
void   pp_seq_push      (pp_seq*, void*, u64_t, u64_t);

void   pp_seq_pop_front (pp_seq*, u64_t)       ;
void   pp_seq_pop_back  (pp_seq*, u64_t)       ;
void   pp_seq_pop       (pp_seq*, u64_t, u64_t);

#endif