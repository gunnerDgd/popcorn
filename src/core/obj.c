#include "obj.h"
#include "mem.h"
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
		(po_mem* mem, po_obj_trait* trait, u32_t count, va_list arg) {
			if (!trait)				          return null_t;
			if (trait->size < sizeof(po_obj)) return null_t;
			if (!mem) mem = po_get_mem();
			if (!mem) return null_t;
			
			po_obj    *ret = po_mem_use(mem, null_t, trait->size); if (!ret) return null_t;
			po_mem_set(ret, 0x00, trait->size);
			ret->trait = trait;
			ret->mem   = mem  ;
			ret->ref   = 1	  ;

			if (!trait->on_new)         return ret;
			if (!trait->on_new(ret, count, arg))  {
				po_mem_free(mem, ret, trait->size);
				return null_t;
			}

			return ret;
}

bool_t
	po_obj_new_at
		(po_obj* at, po_obj_trait* trait, u32_t count, ...) {
			va_list  arg;
			va_start(arg, count);
			bool_t ret = po_obj_new_at_va (
			    at   ,
				trait,
				count,
				arg
			);
			
			va_end (arg);
			return  ret ;
}

bool_t 
	po_obj_new_at_va
		(po_obj* at, po_obj_trait* trait, u32_t count, va_list arg) {
		    if (!trait) return false_t;
		    if (!at)    return false_t;

			if (trait->size < sizeof(po_obj)) return false_t;
			po_mem_set(at, 0x00, trait->size);
            at->trait = trait;
            at->mem   = 0;
            at->ref   = 1;

			if (!trait->on_new)     return true_t;
			if (!trait->on_new(at, count, arg))  {
				po_mem_set(at, 0x00, trait->size);
				return false_t;
			}

			return true_t;
}

po_obj*	   
	po_obj_clone   
		(po_obj* self)									               {
			po_obj		 *arg   = self      ; if (!arg)   return null_t;
			po_obj_trait *trait = arg->trait; if (!trait) return null_t;
			po_mem		 *mem   = self->mem ;
			if (po_trait_of(mem) != po_mem_t) mem = po_get_mem();
			if (po_trait_of(mem) != po_mem_t) return null_t;
			if (trait->size < sizeof(po_obj)) return null_t;
			if (!arg->ref)					  return null_t;

			po_obj *ret = po_mem_use(self->mem, null_t, self->trait->size); if (!ret) return null_t;
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
			po_mem_free(mem, ret, trait->size);
			return null_t;
}

bool_t     
	po_obj_clone_at
		(po_obj* self, po_obj* clone)               {
		    if (!po_trait_of (clone)) return false_t;
		    if (!po_use_count(clone)) return false_t;
		    if (!clone)               return false_t;
		    if (!self)                return false_t;

			po_obj_trait *trait = clone->trait;
            self->trait = trait ;
            self->mem   = null_t;
            self->ref   = 1;

			if (!self->trait->on_clone)              {
				po_mem_copy(self, clone, trait->size);
				return true_t;
			}

			if(!trait->on_clone(self, clone)) goto err;
			return true_t;
	err:    po_mem_set(self, 0x00, trait->size);
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

			po_mem_free(par->mem, par, par->trait->size);
			return 0;
}

po_obj_trait* 
	po_obj_get_trait
		(po_obj* self)              {
			if (!self) return null_t;
			return self->trait;
}

u64_t 
	po_obj_use_count
		(po_obj* self)                      {
		    if (!po_trait_of(self)) return 0;
			return self->ref;
}

#ifdef PRESET_LINUX
#include <linux/module.h>
MODULE_LICENSE("GPL");

EXPORT_SYMBOL(po_obj_new);
EXPORT_SYMBOL(po_obj_new_va);

EXPORT_SYMBOL(po_obj_new_at);
EXPORT_SYMBOL(po_obj_new_at_va);

EXPORT_SYMBOL(po_obj_clone);
EXPORT_SYMBOL(po_obj_clone_at);

EXPORT_SYMBOL(po_obj_ref);
EXPORT_SYMBOL(po_obj_del);

EXPORT_SYMBOL(po_obj_get_trait);
EXPORT_SYMBOL(po_obj_use_count);
#endif