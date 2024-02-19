#include "../print.h"
#include <linux/printk.h>

void po_info_va(const char* par, va_list par_arg) { vprintk(KERN_INFO par, par_arg); }
void po_crit_va(const char* par, va_list par_arg) { vprintk(KERN_CRIT par, par_arg); }
void po_err_va (const char* par, va_list par_arg) { vprintk(KERN_ERR  par, par_arg); }

void po_crit   (const char* par, ...) { va_list par_arg; va_start(par_arg, par); po_crit_va(par, par_arg); va_end(par_arg); }
void po_info   (const char* par, ...) { va_list par_arg; va_start(par_arg, par); po_info_va(par, par_arg); va_end(par_arg); }
void po_err    (const char* par, ...) { va_list par_arg; va_start(par_arg, par); po_err_va (par, par_arg); va_end(par_arg); }