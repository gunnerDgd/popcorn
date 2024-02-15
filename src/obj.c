#include "obj.h"
#include "atom.h"

po_obj*
    po_obj_new
		(po_mem* par_mem, po_obj_trait* par_trait, u32_t par_count, ...) {
    		va_list  par;
			va_start(par, par_count); po_obj* ret = po_obj_new_va(par_mem, par_trait, par_count, par);
			va_end  (par);
			return   ret ;
}

po_obj*
    po_obj_new_va
		(po_mem* par_mem, po_obj_trait* par_trait, u32_t par_count, va_list par) 		     {
			po_obj_trait *trait = par_trait; if (!trait)					    return null_t;
			po_mem       *mem   = par_mem  ; if (trait->size <= sizeof(po_obj)) return null_t;
			if (!mem) mem = po_get_mem();
			if (!mem) return   null_t;
			
			po_obj    *ret = po_mem_new(mem, trait->size); if (!ret) return null_t;
			po_mem_set(ret, 0x00, trait->size);
			ret->trait = trait;
			ret->mem   = mem  ;
			ret->ref   = 1	  ;

			if (!trait->on_new)			   return ret;
			if (!trait->on_new(ret, par_count, par)) {
				po_mem_del(mem, ret);
				return null_t;
			}

			return ret;
}

bool_t
	po_obj_new_at
		(po_obj* par_po_obj, po_obj_trait* par_trait, u32_t par_count, ...) {
			va_list  par;
			va_start(par, par_count); 
			bool_t ret = po_obj_new_at_va (
				par_po_obj  , 
				par_trait,
				par_count,
				par
			);
			
			va_end (par);
			return  ret ;
}

bool_t 
	po_obj_new_at_va
		(po_obj* par_po_obj, po_obj_trait* par_trait, u32_t par_count, va_list par) {
			po_obj		 *ret   = par_po_obj; if (!ret)   return false_t;
			po_obj_trait *trait = par_trait ; if (!trait) return false_t;
			if (trait->size <= sizeof(po_obj)) return false_t;

			po_mem_set(ret, 0x00, trait->size);
			ret->trait = par_trait;
			ret->mem   = 0		  ;
			ret->ref   = 1		  ;

			if (!trait->on_new)			return true_t;
			if (!trait->on_new(ret, par_count, par)) {
				po_mem_set(ret, 0x00, trait->size);
				return false_t;
			}

			return true_t;
}

po_obj*	   
	po_obj_clone   
		(po_obj* par)										           {
			po_obj		  *arg  = par		 ; if (!arg)  return null_t;
			po_obj_trait *trait = arg->trait; if (!trait) return null_t;
			po_mem		  *mem  = par->mem  ;
			if (!mem)					   	   mem = po_get_mem();
			if (!mem)						   return null_t;
			if (trait->size <= sizeof(po_obj)) return null_t;
			if (!arg->ref)					   return null_t;

			po_obj *ret = po_mem_new(par->mem, par->trait->size); if (!ret) return null_t;
			ret->trait = trait;
			ret->mem   = mem  ;
			ret->ref   = 1	  ;

			if (!trait->on_clone)			      {
				po_mem_copy(ret, arg, trait->size);
				return   ret;
			}

			if (!trait->on_clone(ret, arg)) goto clone_failed;
			return ret;
	clone_failed:
			po_mem_del(mem, ret);
			return null_t;
}

bool_t     
	po_obj_clone_at
		(po_obj* par, po_obj* par_clone)								{
			po_obj		  *arg  = par_clone ; if (!arg)   return false_t;
			po_obj		  *ret  = par	    ; if (!ret)   return false_t;
			po_obj_trait *trait = arg->trait; if (!trait) return false_t;
			if (po_trait_of(ret)) return false_t;
			if (!arg->ref)	      return false_t;

			par->trait = trait;
			par->mem   = 0	  ;
			par->ref   = 1	  ;

			if (!par_clone->trait->on_clone)      {
				po_mem_copy(ret, arg, trait->size);
				return true_t;
			}

			if(!trait->on_clone(ret, arg)) goto clone_failed;
			return true_t;
	clone_failed:
			po_mem_set(ret, 0x00, trait->size);
			return false_t;
}

po_obj*
	po_obj_ref
		(po_obj* par)                {
			if (!par)		 return 0;
			if (!par->trait) return 0;
			if (!par->ref)	 return 0;

			if (!par->trait->on_ref)      {
				po_lock_inc_ptr(&par->ref);
				return par;
			}
			
			if   (!par->trait->on_ref(par)) return 0; po_lock_inc_ptr(&par->ref);
			return par;
}

u64_t
	po_obj_del
		(po_obj* par)			           {
			if(!par)		   return 0;
			if(!par->trait)    return 0;
			if (par->ref == 0) return 0;

			u64_t ref = po_lock_cas_dec_ptr(&par->ref);
			if (ref) return ref;
			if (par->trait->on_del) par->trait->on_del(par);
			if (!par->mem)						       {
				po_mem_set(par, 0x00, par->trait->size);
				return 0;
			}

			po_mem_del(par->mem, par);
			return 0;
}

po_obj_trait* 
	po_obj_get_trait
		(po_obj* par)		      {
			if (!par) return 0;
			return par->trait;
}

u64_t 
	po_obj_use_count
		(po_obj* par)					 {
			if (!par)		 return 0;
			if (!par->trait) return 0;

			return par->ref;
}

#ifdef PRESET_LINUX
#include <linux/module.h>
MODULE_LICENSE("GPL");
#endif