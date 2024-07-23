#ifndef COLLECTIONS_STR_H
#define COLLECTIONS_STR_H

#include "../core.h"

extern struct pp_obj_trait* pp_str_t;
typedef struct	            pp_str  { u8_t pp_str[128]; } pp_str;

void pp_str_prep_front(pp_str*, u64_t);
void pp_str_prep_back (pp_str*, u64_t);

void pp_str_push_front(pp_str*, const char*, u64_t);
void pp_str_push_back (pp_str*, const char*, u64_t);
void pp_str_push      (pp_str*, const char*, u64_t, u64_t);

void pp_str_pop_front(pp_str*, u64_t);
void pp_str_pop_back (pp_str*, u64_t);
void pp_str_pop	     (pp_str*, u64_t, u64_t);

pp_ord_t pp_str_ord  (pp_str*, const char*, u64_t);
bool_t   pp_str_gt_eq(pp_str*, const char*, u64_t);
bool_t   pp_str_lt_eq(pp_str*, const char*, u64_t);
bool_t   pp_str_gt   (pp_str*, const char*, u64_t);
bool_t   pp_str_lt   (pp_str*, const char*, u64_t);
bool_t   pp_str_eq   (pp_str*, const char*, u64_t);
bool_t   pp_str_ne   (pp_str*, const char*, u64_t);

u64_t       pp_str_find (pp_str*, u64_t, const char*, u64_t);
bool_t      pp_str_begin(pp_str*, const char*, u64_t);
bool_t	    pp_str_end  (pp_str*, const char*, u64_t);

bool_t      pp_str_empty(pp_str*);
u64_t       pp_str_len  (pp_str*);
const char* pp_str_ptr  (pp_str*);

#endif