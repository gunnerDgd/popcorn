#ifndef __THIS_H__
#define __THIS_H__

#include "type.h"
#include "fut.h"

any_t po_await_until(po_fut*, u32_t);
any_t po_await      (po_fut*)       ;
void  po_yield      (void)          ;

#endif
