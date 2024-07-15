#include "obj.h"
#include "mem.h"
#include "atom.h"

pp_obj*
    pp_obj_new
		(pp_mem* par_mem, pp_obj_trait* par_trait, u32_t par_count, ...) {
    		va_list  par;
			va_start(par, par_count); pp_obj* ret = pp_obj_new_va(par_mem, par_trait, par_count, par);
			va_end  (par);
			return   ret ;
}

pp_obj*
    pp_obj_new_va
		(pp_mem* mem, pp_obj_trait* trait, u32_t count, va_list arg) {
			if (!trait)				          return null_t;
			if (trait->size < sizeof(pp_obj)) return null_t;
			if (!mem) mem = pp_get_mem();
			if (!mem) return null_t;
			
			pp_obj    *ret = pp_mem_use(mem, null_t, trait->size); if (!ret) return null_t;
			pp_mem_set(ret, 0x00, trait->size);
			ret->trait = trait;
			ret->mem   = mem  ;
			ret->ref   = 1	  ;

			if (!trait->on_new)         return ret;
			if (!trait->on_new(ret, count, arg))  {
				pp_mem_free(mem, ret, trait->size);
				return null_t;
			}

			return ret;
}

bool_t
	pp_obj_new_at
		(pp_obj* at, pp_obj_trait* trait, u32_t count, ...) {
			va_list  arg;
			va_start(arg, count);
			bool_t ret = pp_obj_new_at_va (
			    at   ,
				trait,
				count,
				arg
			);
			
			va_end (arg);
			return  ret ;
}

bool_t 
	pp_obj_new_at_va
		(pp_obj* at, pp_obj_trait* trait, u32_t count, va_list arg) {
		    if (!trait) return false_t;
		    if (!at)    return false_t;

			if (trait->size < sizeof(pp_obj)) return false_t;
			pp_mem_set(at, 0x00, trait->size);
            at->trait = trait;
            at->mem   = 0;
            at->ref   = 1;

			if (!trait->on_new)     return true_t;
			if (!trait->on_new(at, count, arg))  {
				pp_mem_set(at, 0x00, trait->size);
				return false_t;
			}

			return true_t;
}

pp_obj*	   
	pp_obj_clone   
		(pp_obj* self)									               {
			pp_obj		 *arg   = self      ; if (!arg)   return null_t;
			pp_obj_trait *trait = arg->trait; if (!trait) return null_t;
			pp_mem		 *mem   = self->mem ;
			if (pp_trait_of(mem) != pp_mem_t) mem = pp_get_mem();
			if (pp_trait_of(mem) != pp_mem_t) return null_t;
			if (trait->size < sizeof(pp_obj)) return null_t;
			if (!arg->ref)					  return null_t;

			pp_obj *ret = pp_mem_use(self->mem, null_t, self->trait->size); if (!ret) return null_t;
			ret->trait = trait;
			ret->mem   = mem  ;
			ret->ref   = 1	  ;

			if (!trait->on_clone)			      {
				pp_mem_copy(ret, arg, trait->size);
				return   ret;
			}

			if (!trait->on_clone(ret, arg)) goto clone_failed;
			return ret;
	clone_failed:
			pp_mem_free(mem, ret, trait->size);
			return null_t;
}

bool_t     
	pp_obj_clone_at
		(pp_obj* self, pp_obj* clone)               {
		    if (!pp_trait_of (clone)) return false_t;
		    if (!pp_use_count(clone)) return false_t;
		    if (!clone)               return false_t;
		    if (!self)                return false_t;

			pp_obj_trait *trait = clone->trait;
            self->trait = trait ;
            self->mem   = null_t;
            self->ref   = 1;

			if (!self->trait->on_clone)              {
				pp_mem_copy(self, clone, trait->size);
				return true_t;
			}

			if(!trait->on_clone(self, clone)) goto err;
			return true_t;
	err:    pp_mem_set(self, 0x00, trait->size);
			return false_t;
}

pp_obj*
	pp_obj_ref
		(pp_obj* par)                {
			if (!par)		 return 0;
			if (!par->trait) return 0;
			if (!par->ref)	 return 0;

			if (!par->trait->on_ref)      {
				pp_lock_inc_ptr(&par->ref);
				return par;
			}
			
			if   (!par->trait->on_ref(par)) return 0; pp_lock_inc_ptr(&par->ref);
			return par;
}

u64_t
	pp_obj_del
		(pp_obj* par)			           {
			if(!par)		   return 0;
			if(!par->trait)    return 0;
			if (par->ref == 0) return 0;

			u64_t ref = pp_lock_cas_dec_ptr(&par->ref);
			if (ref) return ref;
			if (par->trait->on_del) par->trait->on_del(par);
			if (!par->mem)						       {
				pp_mem_set(par, 0x00, par->trait->size);
				return 0;
			}

			pp_mem_free(par->mem, par, par->trait->size);
			return 0;
}

pp_obj_trait* 
	pp_obj_get_trait
		(pp_obj* self)              {
			if (!self) return null_t;
			return self->trait;
}

u64_t 
	pp_obj_use_count
		(pp_obj* self)                      {
		    if (!pp_trait_of(self)) return 0;
			return self->ref;
}

#ifdef PRESET_LINUX
#include <linux/module.h>
MODULE_LICENSE("GPL");

EXPORT_SYMBOL(pp_obj_new);
EXPORT_SYMBOL(pp_obj_new_va);

EXPORT_SYMBOL(pp_obj_new_at);
EXPORT_SYMBOL(pp_obj_new_at_va);

EXPORT_SYMBOL(pp_obj_clone);
EXPORT_SYMBOL(pp_obj_clone_at);

EXPORT_SYMBOL(pp_obj_ref);
EXPORT_SYMBOL(pp_obj_del);

EXPORT_SYMBOL(pp_obj_get_trait);
EXPORT_SYMBOL(pp_obj_use_count);
#endif