#ifndef CORE_THIS_H
#define CORE_THIS_H

#include "type.h"
#include "fut.h"

extern any_t pp_await_until(pp_fut*, u32_t);
extern any_t pp_await      (pp_fut*)       ;
extern void  pp_yield      (void)          ;

#endif
