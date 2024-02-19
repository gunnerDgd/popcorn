#ifndef __PRINT_H__
#define __PRINT_H__

#include "obj.h"

void po_info_va(const char*, va_list);
void po_info   (const char*, ...)    ;

void po_crit_va(const char*, va_list);
void po_crit   (const char*, ...)    ;

void po_err_va (const char*, va_list);
void po_err    (const char*, ...)    ;

#endif