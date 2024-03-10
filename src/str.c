#include "str.h"

po_obj_trait po_str_trait = po_make_trait (
    po_str_new    ,
    po_str_clone  ,
    null_t        ,
    po_str_del    ,
    sizeof(po_str),
    null_t
);

po_obj_trait* po_str_t = &po_str_trait;

bool_t
    po_str_new
		(po_str* par_str, u32_t par_count, va_list par)                   {
            po_mem *res = 0; if (par_count > 0) res = va_arg(par, po_mem*);
			if (!res)         res = po_get_mem();
			if (!res)         return false_t;
            if (!res->on_new) return false_t;
            if (!res->on_del) return false_t;

			par_str->mem = po_mem_new(res, 16); if (!par_str->mem) return false_t;
            po_mem_set(par_str->mem, 0x00, 16);
            par_str->res   = res;
			par_str->front = 0 ;
			par_str->back  = 0 ;
			par_str->size  = 16;
			par_str->len   = 0 ;

			return true_t;
}

bool_t
	po_str_clone
		(po_str* par, po_str* par_clone)        {
			if (!par_clone->res)  return false_t;
			if (!par_clone->mem)  return false_t;
			if (!par_clone->size) return false_t;

			par->res  = par_clone->res ;
			par->size = par_clone->size;

			par->mem  = po_mem_new(par->res, par->size);
            if (!par->mem)
                return false_t;

            po_mem_copy(par->mem, par_clone->mem, par->size);
			par->len   = par_clone->len  ;
			par->front = par_clone->front;
			par->back  = par_clone->back ;

			return true_t;
}

void
    po_str_del
		(po_str* par)				      {
            po_mem_del(par->res, par->mem);
}

void
    po_str_rsv_back
        (po_str* par, u64_t par_size)                                     {
            if (po_trait_of(par) != po_str_t) return; u64_t len = par_size;
            if (!len) len = par->size;

            if (par_size > shl(len, 1)) len += par_size;

			u8_t* rsv = po_mem_new(par->res, len);
			if  (!rsv) return;

            po_mem_set (rsv, 0x00, len)							          ;
            po_mem_copy(rsv + par->front, par->mem + par->front, par->len);
            po_mem_del (par->res  , par->mem);

            par->mem  = rsv;
			par->size = len;
}

void
    po_str_rsv_front
        (po_str* par, u64_t par_size)               {
            if (!par)                         return;
            if (po_trait_of(par) != po_str_t) return;

            u64_t rsv_size = shl(par->size, 1)             ; if (rsv_size < par_size) rsv_size = par_size + par->size;
			u8_t *rsv	   = po_mem_new(par->res, rsv_size);
            if  (!rsv) return;

            po_mem_copy(rsv + par->front + par_size, par->mem + par->front, par->len);
            po_mem_del (par->res  , par->mem);
			par->mem    = rsv	  ;
			par->size   = rsv_size;
			par->front += rsv_size;
			par->back  += rsv_size;
}

void
    po_str_push_back
        (po_str* par, po_str* par_push)                  {
            if (!par_push)                         return;
            if (po_trait_of(par_push) != po_str_t) return;
            po_str_push_back_raw                         (
                par                    ,
                po_str_as_raw(par_push),
                po_str_len   (par_push)
            );
}

void
    po_str_push_back_cstr
        (po_str* par, cstr_t par_cstr)                                              {
            if (!par_cstr.len)                return; u64_t       len = par_cstr.len;
            if (!par_cstr.str)                return; const char *str = par_cstr.str;
            if (po_trait_of(par) != po_str_t) return;

            if(par->size < (par->back + len + 1)) po_str_rsv_back(par, len + 1);
            if(par->size < (par->back + len + 1)) return;

            po_mem_copy(par->mem + par->back, str, len);
			par->back += len;
			par->len  += len;
}

void
    po_str_push_back_raw
        (po_str* par, const char* par_str, u64_t par_len) {
            if (po_trait_of(par) != po_str_t) return;
            if (!par_str)                     return;
            if (!par_len)                     return;

            if(par->size < (par->back + par_len + 1)) po_str_rsv_back(par, par_len + 1);
            if(par->size < (par->back + par_len + 1)) return;

            po_mem_copy(par->mem + par->back, par_str, par_len);
            par->back += par_len;
            par->len  += par_len;
}




void
    po_str_push_front
        (po_str* par, po_str* par_push)                  {
            if (po_trait_of(par_push) != po_str_t) return;
            if (po_trait_of(par)      != po_str_t) return;
            po_str_push_front_raw                        (
                par                    ,
                po_str_as_raw(par_push),
                po_str_len   (par_push)
            );
}

void
    po_str_push_front_cstr
        (po_str* par, cstr_t par_cstr)                                              {
            if (!par_cstr.len)                return; u64_t       len = par_cstr.len;
            if (!par_cstr.str)                return; const char *str = par_cstr.str;
            if (po_trait_of(par) != po_str_t) return;
            po_str_push_front_raw(par, str, len);
}

void
    po_str_push_front_raw
        (po_str* par, const char* par_str, u64_t par_len) {
            if (po_trait_of(par) != po_str_t) return;
            if (!par_str)                     return;
            if (!par_len)                     return;

            if (par_len < par->front) po_str_rsv_front(par, par_len);
            if (par_len < par->front) return;

            par->front -= par_len;
            par->len   += par_len;
            po_mem_copy              (
                par->mem + par->front,
                par_str              ,
                par_len
            );

}

void
    po_str_push
        (po_str* par, u64_t par_off, po_str* par_push)   {
            if (!par_push)                         return;
            if (po_trait_of(par_push) != po_str_t) return;
            po_str_push_raw                              (
                par                    ,
                par_off                ,
                po_str_as_raw(par_push),
                po_str_len   (par_push)
            );
}

void
    po_str_push_cstr
        (po_str* par, u64_t par_off, cstr_t par_cstr)                               {
            if (!par_cstr.len)                return; u64_t       len = par_cstr.len;
            if (!par_cstr.str)                return; const char *str = par_cstr.str;
            if (po_trait_of(par) != po_str_t) return; u64_t       off = par->front  ;
            po_str_push_raw(par, off, str, len);
}

void
    po_str_push_raw
        (po_str* par, u64_t par_off, const char* par_str, u64_t par_len)            {
            if (po_trait_of(par) != po_str_t) return;
            if (!par_str)                     return;
            if (!par_len)                     return;

            if (par_off > par->len) return po_str_push_back_raw (par, par_str, par_len);
            if (par_off == 0)       return po_str_push_front_raw(par, par_str, par_len);
            u8_t *ret = po_mem_new(par->res, par_len + par->size + 1);
            u8_t *old = par->mem;
            if  (!ret) return;

            par->size = par_len + par->size + 1;
            par->mem  = ret                         ;

            po_mem_set (ret, 0x00         , par->size)         ;
            po_mem_copy(ret, old + par_off, par_off)           ; ret += par_off; par_off += par_off   ;
            po_mem_copy(ret, par_str      , par_len)           ; ret += par_len; par_off += par->front;
            po_mem_copy(ret, old + par_off, par->len - par_off);

            po_mem_del (par->res, old);
            par->len  += par_len;
            par->front =       0;
            par->back  = par_len;
}

void
    po_str_pop_front
        (po_str* par, u64_t par_len)                {
            if (po_trait_of(par) != po_str_t) return;
            if (!par_len)                     return;
            u64_t len = 0;

            if (par_len > par->len) len = par->len;
            if (!len)               len = par_len ;
            if (!len)               return;

            po_mem_set(par->mem + par->front, 0x00, len);
            par->len   -= len;
            par->front += len;
}

void
    po_str_pop_back
        (po_str* par, u64_t par_len)                {
            if (po_trait_of(par) != po_str_t) return;
            if (!par_len)                     return;
            u64_t len = 0;

            if (par_len > par->len) len = par->len;
            if (!len)               len = par_len ;
            if (!len)               return;
            par->len  -= len;
            par->back -= len;

            po_mem_set              (
                par->mem + par->back,
                0x00                ,
                len
            );
            
}

void
    po_str_pop
        (po_str* par, u64_t par_off, u64_t par_len)                      {
            if (po_trait_of(par) != po_str_t) return; u64_t off = par_off;
            if (!par_len)                     return; u64_t len = par_len;
            if ((off + len) > par->len)       return;

            if (off > par->len) return po_str_pop_back (par, len);
			if (off == 0)       return po_str_pop_front(par, len);
            po_mem_copy                                          (
				par->mem + par->front + off      ,
				par->mem + par->front + off + len,
				par->len - off - len
			);

			par->len          -= len;
			par->back         -= len;
            po_mem_set              (
                par->mem + par->back,
                0x00                ,
                len
            );
}

u64_t
    po_str_find
        (po_str* par, u64_t par_off, po_str* par_find)           {
            if (!par_find)                         return false_t;
            if (po_trait_of(par_find) != po_str_t) return false_t;
            return po_str_find_cstr                              (
                par                    ,
                par_off                ,
                po_str_as_cstr(par_find)
            );
}

u64_t
    po_str_find_cstr
        (po_str* par, u64_t par_off, cstr_t par_cstr)                                  {
            if (!par_cstr.str)                return -1; const char *str = par_cstr.str;
            if (!par_cstr.len)                return -1; u64_t       len = par_cstr.len;
            if (po_trait_of(par) != po_str_t) return -1; u64_t       off = par_off     ;
            return po_str_find_raw(par, off, str, len);
}

u64_t
    po_str_find_raw
        (po_str* par, u64_t par_off, const char* par_str, u64_t par_len) {
            if (po_trait_of(par) != po_str_t) return -1;
            if (!par_str)                     return -1;
            if (!par_len)                     return -1;

            if (par->len <  par_off)            return -1;
            if (par->len < (par_off + par_len)) return -1;

            u8_t* find = par->mem + par->front + par_off                 ;
            u64_t ran  = par->len - par_off                              ;
            u64_t ret  = po_mem_find(find, (void*) par_str, ran, par_len);
            if (ret == -1) return -1;
            return par_off + ret;
}

bool_t
    po_str_eq
        (po_str* par, po_str* par_cmp)                          {
            if (po_trait_of(par_cmp) != po_str_t) return false_t;
            if (po_trait_of(par)     != po_str_t) return false_t;
            return po_str_eq_cstr(par, po_str_as_cstr(par_cmp));
}

bool_t
    po_str_eq_cstr
        (po_str* par, cstr_t par_cstr)                                                        {
            if (!par_cstr.str)                  return false_t; const char *str = par_cstr.str;
            if (!par_cstr.len)                  return false_t; u64_t       len = par_cstr.len;
            if (po_trait_of(par) != po_str_t)   return false_t;
            if (par->back < (par->front + len)) return false_t;
            return po_mem_eq                                  (
                par->mem + par->front,
                str                  ,
                len
            );
}

bool_t
    po_str_gt
        (po_str* par, po_str* par_cmp)                          {
            if (po_trait_of(par_cmp) != po_str_t) return false_t;
            if (po_trait_of(par)     != po_str_t) return false_t;
            return po_str_gt_cstr(par, po_str_as_cstr(par_cmp));
}

bool_t
    po_str_gt_cstr
        (po_str* par, cstr_t par_cstr)                                                        {
            if (!par_cstr.str)                  return false_t; const char *str = par_cstr.str;
            if (!par_cstr.len)                  return false_t; u64_t       len = par_cstr.len;
            if (po_trait_of(par) != po_str_t)   return false_t;
            if (par->back < (par->front + len)) return false_t;
            return po_mem_gt			                      (
				par->mem + par->front, 
                str                  ,
                len
			); 
}

bool_t
    po_str_lt
        (po_str* par, po_str* par_cmp)                          {
            if (po_trait_of(par_cmp) != po_str_t) return false_t;
            if (po_trait_of(par)     != po_str_t) return false_t;
            return po_str_lt_cstr(par, po_str_as_cstr(par_cmp));
}

bool_t
    po_str_lt_cstr
        (po_str* par, cstr_t par_cstr)                                                      {
            if (!par_cstr.str)                return false_t; const char *str = par_cstr.str;
            if (!par_cstr.len)                return false_t; u64_t       len = par_cstr.len;
            if (po_trait_of(par) != po_str_t) return false_t;
            return po_mem_lt			                    (
				par->mem + par->front,
                str                  ,
                len
			); 
}

bool_t
    po_str_starts
        (po_str* par, po_str* par_cmp)                          {
            if (po_trait_of(par_cmp) != po_str_t) return false_t;
            if (po_trait_of(par)     != po_str_t) return false_t;
            return po_str_starts_raw                            (
                par                   ,
                po_str_as_raw(par_cmp),
                po_str_len   (par_cmp)
            );
}

bool_t
    po_str_starts_cstr
        (po_str* par, cstr_t par_cstr)                                                      {
            if (!par_cstr.str)                return false_t; const char* str = par_cstr.str;
            if (!par_cstr.len)                return false_t; u64_t       len = par_cstr.len;
            if (po_trait_of(par) != po_str_t) return false_t;
            return po_str_starts_raw                        (
                par,
                str,
                len
            );
}

bool_t
    po_str_starts_raw
        (po_str* par, const char* par_str, u64_t par_len)   {
            if (po_trait_of(par) != po_str_t) return false_t;
            if (!par_str)                     return false_t;
            if (!par_len)                     return false_t;
            if (par_len > po_str_len(par))    return false_t;
            return po_mem_eq			                    (
                    par->mem + par->front,
                    par_str				 ,
                    par_len
           );
}

bool_t
    po_str_ends
        (po_str* par, po_str* par_cmp)                          {
            if (po_trait_of(par_cmp) != po_str_t) return false_t;
            if (po_trait_of(par)     != po_str_t) return false_t;
            return po_str_ends_raw                              (
                par                   ,
                po_str_as_raw(par_cmp),
                po_str_len   (par_cmp)
                );
}

bool_t
    po_str_ends_cstr
        (po_str* par, cstr_t par_cstr)                                                      {
            if (!par_cstr.str)                return false_t; const char* str = par_cstr.str;
            if (!par_cstr.len)                return false_t; u64_t       len = par_cstr.len;
            if (po_trait_of(par) != po_str_t) return false_t;
            return po_str_ends_raw                          (
                par,
                str,
                len
            );
}

bool_t
    po_str_ends_raw
        (po_str* par, const char* par_str, u64_t par_len)   {
            if (po_trait_of(par) != po_str_t) return false_t;
            if (!par_str)                     return false_t;
            if (!par_len)                     return false_t;
            if (par_len > par->len)           return false_t;
            return po_mem_eq					            (
                    par->mem + par->back - par_len,
                    par_str                       ,
                    par_len
            );
}

bool_t
    po_str_empty
        (po_str* par)                                      {
            if (po_trait_of(par) != po_str_t) return true_t;
            return par->len == 0; 
}

u64_t
    po_str_len
        (po_str* par)                                 {
            if (po_trait_of(par) != po_str_t) return 0;
            return par->len;
}

const char*
    po_str_as_raw
        (po_str* par)                                 {
            if (po_trait_of(par) != po_str_t) return 0;
            return par->mem + par->front;
}

cstr_t
    po_str_as_cstr
        (po_str* par)    {
            cstr_t ret = {
                .str = 0,
                .len = 0
            };

            if (po_trait_of(par) != po_str_t) return ret;
            ret.str = po_str_as_raw(par);
            ret.len = po_str_len   (par);
            return ret;
}

#ifdef PRESET_LINUX
#include <linux/module.h>
MODULE_LICENSE("GPL");
#endif