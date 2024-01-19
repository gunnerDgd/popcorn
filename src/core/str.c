#include "str.h"

po_obj_trait po_str_trait            = {
    .on_new   = as_new  (&po_str_new)  ,
    .on_clone = as_clone(&po_str_clone),
    .on_ref   = 0                      ,
    .on_del   = as_del  (&po_str_del)  ,
    .size     = sizeof(po_str)
};

po_obj_trait* po_str_t = &po_str_trait;

bool_t
	po_str_new
		(po_str* par_str, u32_t par_count, va_list par)    {
            po_mem* res = 0;
            switch (par_count)                             {
                case 0 : res = po_get_mem()         ; break;
                case 1 : res = va_arg (par, po_mem*); break;
                default: return false_t;
            }

			if (!res)         return false_t;
            if (!res->on_new) return false_t;
            if (!res->on_del) return false_t;

            par_str->res = res             ;
            par_str->mem = po_mem_new(res, 16); if (!par_str->mem) return false_t;
		
			po_mem_set(par_str->mem, 0x00, 16);
            par_str->front = 0 ;
            par_str->back  = 0 ;
            par_str->size  = 16;
            par_str->len   = 0 ;

			return true_t;
}

bool_t
	po_str_clone
		(po_str* par, po_str* par_clone)		{
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
		(po_str* par)				       {
			po_mem_del(par->res, par->mem);
}

void 
    po_str_rsv_back 
        (po_str* par, u64_t par_size)            {
            if (!par)                      return;
            if (trait_of(par) != po_str_t) return;

            u64_t rsv_size = par->size << 1		           ; if (rsv_size < par_size) rsv_size = par_size + par->size;
			u8_t* rsv	   = po_mem_new(par->res, rsv_size);
			if  (!rsv) return;

			po_mem_set (rsv, 0x00, rsv_size)							   ;
			po_mem_copy(rsv + par->front, par->mem + par->front, par->len);
			po_mem_del								 (par->res  , par->mem);

			par->mem  = rsv		;
			par->size = rsv_size;
}

void 
    po_str_rsv_front
        (po_str* par, u64_t par_size)            {
            if (!par)                   return;
            if (trait_of(par) != po_str_t) return;

            u64_t rsv_size = par->size << 1			       ; if (rsv_size < par_size) rsv_size = par_size + par->size;
			u8_t *rsv	   = po_mem_new(par->res, rsv_size); 
            if  (!rsv) return;

			po_mem_copy(rsv + par->front + par_size, par->mem + par->front, par->len);
			po_mem_del										    (par->res  , par->mem);

			par->mem    = rsv	  ;
			par->size   = rsv_size;
			par->front += rsv_size;
			par->back  += rsv_size;
}

void 
    po_str_push_back	    
        (po_str* par, po_str* par_push)                  {
            if (!par_push)                   return;
            if (trait_of(par_push) != po_str_t) return;

            po_str_push_back_cstr              (
                par                            ,
                par_push->mem + par_push->front,
                par_push->len
            );
}

void 
    po_str_push_back_cstr
        (po_str* par, const char* par_push, u64_t par_len) {
            if (!par)                   return;
            if (trait_of(par) != po_str_t) return;
            
            if(par->size < (par->back + par_len + 1)) po_str_rsv_back(par, par_len + 1);
            if(par->size < (par->back + par_len + 1)) return;

			po_mem_copy(par->mem + par->back, par_push, par_len);
			par->back += par_len;
			par->len  += par_len;
}

void 
    po_str_push_front	    
        (po_str* par, po_str* par_push)                  {
            if (!par_push)                   return;
            if (trait_of(par_push) != po_str_t) return;

            po_str_push_front_cstr             (
                par                            ,
                par_push->mem + par_push->front,
                par_push->len
            ); 
}

void 
    po_str_push_front_cstr
        (po_str* par, const char* par_push, u64_t par_len) { 
            if (!par)                   return;
            if (trait_of(par) != po_str_t) return;

            if (par_len < par->front)   po_str_rsv_front(par, par_len);
            if (par_len < par->front)   return;

			par->front -= par_len;
			par->len   += par_len;
			po_mem_copy(par->mem + par->front, par_push, par_len);
}

void 
    po_str_push	
        (po_str* par, u64_t par_off, po_str* par_push)   {
            if (!par_push)                   return;
            if (trait_of(par_push) != po_str_t) return;

            po_str_push_cstr                   (
                par                            ,
                par_off                        ,
                par_push->mem + par_push->front,
                par_push->len
            );
}

void 
    po_str_push_cstr
        (po_str* par, u64_t par_off, const char* par_push, u64_t par_len) { 
            if (!par)                   return;
            if (trait_of(par) != po_str_t) return;
            
            if (par_off > par->len)     return po_str_push_back_cstr (par, par_push, par_len);
			if (par_off == 0)           return po_str_push_front_cstr(par, par_push, par_len);

			u64_t ret_off = par->front;
			u8_t *ret	  = po_mem_new(par->res, par_len + par->size + 1); 
            if  (!ret) return;

			par->size = par_len + par->size + 1;
			po_mem_set (ret		  , 0x00						      , par->size)			  ;
			po_mem_copy(ret + ret_off, par->mem + ret_off			  , par_off)			  ; ret_off += par_off;
			po_mem_copy(ret + ret_off, par_push					      , par_len)			  ; ret_off += par_len;
			po_mem_copy(ret + ret_off, par->mem + par->front + par_off, (par->back - par_off));

			par->back += par_len;
			par->len  += par_len; po_mem_del(par->res, par->mem);
			par->mem   = ret	;
}

void 
    po_str_pop_front
        (po_str* par, u64_t par_len)             { 
            if (!par)                      return;
            if (trait_of(par) != po_str_t) return;

            u64_t pop_len = (par->back > (par->front + par_len)) ? par_len : par->len;
            u64_t pop     = par->front + pop_len;

            par->len  -= pop_len;
            par->front = pop    ;
            			
            po_mem_set(par->mem + pop, 0x00, pop_len);
}

void 
    po_str_pop_back 
        (po_str* par, u64_t par_len)             {
            if (!par)                      return;
            if (trait_of(par) != po_str_t) return;

            u64_t pop_len = (par_len < par->len) ? par_len : par->len;
            u64_t pop     =  par->back - pop_len;

            par->len -= pop_len;
            par->back = pop    ;

            po_mem_set(par->mem + pop, 0x00, pop_len);
}

void 
    po_str_pop
        (po_str* par, u64_t par_off, u64_t par_len)   {
            if (!par)                           return;
            if (trait_of(par) != po_str_t)      return;
            
            if (par_off > par->len)	            return po_str_pop_back (par, par_len);
			if (par_off == 0)                   return po_str_pop_front(par, par_len);
			if ((par_off + par_len) > par->len) return;

			po_mem_copy									 (
				par->mem + par->front + par_off			 , 
				par->mem + par->front + par_off + par_len,
				par->len - par_off - par_len
			);

			par->len  -= par_len;
			par->back -= par_len;
			po_mem_set(par->mem + par->back, 0x00, par->len - par->back);
}

u64_t
    po_str_find
        (po_str* par, u64_t par_off, po_str* par_find)           {
            if (!par_find)                   return false_t;
            if (trait_of(par_find) != po_str_t) return false_t;

            return po_str_find_cstr            (
                par                            ,
                par_off                        ,
                par_find->mem + par_find->front,
                par_find->len
            );
}

u64_t
    po_str_find_cstr
        (po_str* par, u64_t par_off, const char* par_find, u64_t par_len) { 
            if (!par)                                         return -1;
            if (trait_of(par) != po_str_t)                    return -1;
            if (par->back < (par->front + par_off))           return -1;
            if (par->back < (par->front + par_off + par_len)) return -1;

            u64_t find     = par->mem + par->front + par_off               ;
            u64_t find_len = par->len - par_off                            ;
            u64_t ret      = po_mem_find(find, par_find, find_len, par_len); if (ret == -1) return -1;
            			
			return par_off + ret;
}

bool_t 
    po_str_eq
        (po_str* par, po_str* par_cmp)                       {
            if (!par_cmp)                      return false_t;
            if (trait_of(par_cmp) != po_str_t) return false_t;

            return po_str_eq_cstr            (
                par                          ,
                par_cmp->mem + par_cmp->front,
                par_cmp->len
            );
}

bool_t 
    po_str_eq_cstr
        (po_str* par, const char* par_cmp, u64_t par_len)         {
            if (!par)                               return false_t;
            if (trait_of(par) != po_str_t)          return false_t;
            if (par->back < (par->front + par_len)) return false_t;

            return po_mem_eq         (
                par->mem + par->front,
                par_cmp              ,
                par_len
            );
}

bool_t
    po_str_gt
        (po_str* par, po_str* par_cmp)                       {
            if (!par_cmp)                      return false_t;
            if (trait_of(par_cmp) != po_str_t) return false_t;

            return po_str_gt_cstr            (
                par                          ,
                par_cmp->mem + par_cmp->front,
                par_cmp->len
            );
}

bool_t 
    po_str_gt_cstr
        (po_str* par, const char* par_cmp, u64_t par_len)         {
            if (!par)                               return false_t;
            if (trait_of(par) != po_str_t)          return false_t;
            if (par->back < (par->front + par_len)) return false_t;

            return po_mem_gt		 (
				par->mem + par->front, 
				par_cmp              ,
				par_len
			); 
}

bool_t 
    po_str_lt
        (po_str* par, po_str* par_cmp)                       {
            if (!par_cmp)                      return false_t;
            if (trait_of(par_cmp) != po_str_t) return false_t;

            return po_str_lt_cstr            (
                par                          ,
                par_cmp->mem + par_cmp->front,
                par_cmp->len
            );
}

bool_t 
    po_str_lt_cstr
        (po_str* par, const char* par_cmp, u64_t par_len) { 
            if (!par)                      return false_t;
            if (trait_of(par) != po_str_t) return false_t;

            return po_mem_lt		 (
				par->mem + par->front,
				par_cmp				 , 
				par_len
			); 
}

bool_t 
    po_str_starts
        (po_str* par, po_str* par_cmp)                       {
            if (!par_cmp)                      return false_t;
            if (trait_of(par_cmp) != po_str_t) return false_t;

            return po_str_starts_cstr        (
                par                          ,
                par_cmp->mem + par_cmp->front,
                par_cmp->len
            );
}

bool_t 
    po_str_starts_cstr
        (po_str* par, const char* par_cmp, u64_t par_len) { 
            if (!par)                      return false_t;
            if (trait_of(par) != po_str_t) return false_t;
            if (par_len > par->len)        return false_t;

			return po_mem_eq			 (
				par->mem + par->front, 
				par_cmp				 ,
				par_len
			);
}

bool_t 
    po_str_ends
        (po_str* par, po_str* par_cmp)                       {
            if (!par_cmp)                      return false_t;
            if (trait_of(par_cmp) != po_str_t) return false_t;

            return po_str_ends_cstr          (
                par                          ,
                par_cmp->mem + par_cmp->front,
                par_cmp->len
            );
}

bool_t 
    po_str_ends_cstr
        (po_str* par, const char* par_cmp, u64_t par_len) {
            if (!par)                      return false_t;
            if (trait_of(par) != po_str_t) return false_t;
            if (par_len > par->len)        return false_t;

			return po_mem_eq					  (
				par->mem + par->back - par_len, 
				par_cmp						  ,
				par_len
			);
}

bool_t
    po_str_empty
        (po_str* par)                                   {
            if (!par)                      return true_t;
            if (trait_of(par) != po_str_t) return true_t;

            return par->front == par->back; 
}

u64_t  
    po_str_len	
        (po_str* par)                              { 
            if (!par)                      return 0;
            if (trait_of(par) != po_str_t) return 0;

            return par->back - par->front;
}

const char*
    po_str_ptr	
        (po_str* par)                              {
            if (!par)                   return 0;
            if (trait_of(par) != po_str_t) return 0;

            return par->mem + par->front;
}

#ifdef PO_PRESET_LINUX
#include <linux/module.h>

MODULE_LICENSE("GPL");
#endif