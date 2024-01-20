#include "obj.h"

po_obj*
    po_obj_new
		(po_mem* par_res, po_obj_trait* par_trait, u32_t par_count, ...) {
    		va_list  par;
			va_start(par, par_count); po_obj* ret = po_obj_new_va(par_res, par_trait, par_count, par);
			va_end  (par);
			return   ret ;
}

po_obj*
    po_obj_new_va
		(po_mem* par_res, po_obj_trait* par_trait, u32_t par_count, va_list par) {
			if (!par_res)						   par_res = po_get_mem();
			if (!par_res)						   return 0;
			if (par_trait->size <= sizeof(po_obj)) return 0;

			po_obj *ret = po_mem_new(par_res, par_trait->size);
			if (!ret) return 0;

            po_mem_set(ret, 0x00, par_trait->size);
			ret->trait = par_trait;
			ret->mem   = par_res  ;

			if (!ret->trait->on_new)			return ret;
			if (!ret->trait->on_new(ret, par_count, par)) {
                po_mem_del(par_res, ret);
				return 0;
			}

            kref_init(&ret->ref);
			return ret;
}

bool_t
	po_obj_new_at
		(po_obj* par_obj, po_obj_trait* par_trait, u32_t par_count, ...) {
			va_list  par;
			va_start(par, par_count); bool_t ret = po_obj_new_at_va(par_obj, par_trait, par_count, par);
			va_end  (par);

			return ret;
}

bool_t 
	po_obj_new_at_va
		(po_obj* par_obj, po_obj_trait* par_trait, u32_t par_count, va_list par) {
			if (!par_obj)					       return false_t;
			if (!par_trait)						   return false_t;
			if (par_trait->size <= sizeof(po_obj)) return false_t;

            po_mem_set(par_obj, 0x00, par_trait->size);
            par_obj->trait = par_trait;
            par_obj->mem   = 0		  ;

            if (!par_obj->trait->on_new) {
                kref_init(&par_obj->ref);
                return true_t;
            }

			if (!par_obj->trait->on_new(par_obj, par_count, par)) {
                po_mem_set(par_obj, 0x00, par_trait->size);
				return false_t;
			}

            kref_init(&par_obj->ref);
			return true_t;
}

po_obj*	   
	po_obj_clone   
		(po_obj* par)                                             {
			if (!par)   return 0; po_obj_trait *trait = par->trait;
            if (!trait) return 0; po_mem       *mem   = par->mem  ;
			if (!mem)   return 0; po_obj       *ret   = NULL      ;

			if (trait->size <= sizeof(po_obj)) return 0; ret = po_mem_new(par->mem, par->trait->size);
			if (!ret)                          return 0;

			ret->trait = trait;
			ret->mem   = mem  ;

			if (!par->trait->on_clone)				    {
                po_mem_copy(ret, par, par->trait->size);
				kref_init(&par->ref);
				return ret;
			}

			if(!par->trait->on_clone(ret, par)) {
                po_mem_del(mem, ret);
				return 0;
			}

			kref_init(&par->ref);
			return ret;
}

bool_t     
	po_obj_clone_at
		(po_obj* par, po_obj* par_clone)                                                       {
            if (!par_clone)                    return 0; po_obj_trait *trait = par_clone->trait;
			if (!par)                          return 0;

            if (!trait)	                       return 0;
			if (trait->size <= sizeof(po_obj)) return 0;
            par->trait = trait;
            par->mem   = 0;

			if (!par_clone->trait->on_clone)		    {
                po_mem_copy(par, par_clone, trait->size);
                kref_init  (&par->ref);
				return true_t;
			}

			if(!par->trait->on_clone(par, par_clone))        {
                po_mem_set(par, 0x00, par_clone->trait->size);
				return false_t;
			}

			return true_t;
}

po_obj*
	po_obj_ref
		(po_obj* par)				                              {
			if (!par)	return 0; po_obj_trait* trait = par->trait;
			if (!trait) return 0;
			if (trait->on_ref)                      {
			    if (!trait->on_ref(par)) return NULL;
			}
			
			kref_get(&par->ref);
			return par;
}

void
    po_obj_do_del
        (struct kref* par)                                 {
            po_obj* obj = (po_obj*)par                     ;
            if (obj->trait->on_del) obj->trait->on_del(obj);
            if (!obj->mem)						      {
                po_mem_set(par, 0x00, obj->trait->size);
                return;
            }

            po_mem_del(obj->mem, obj);
}

u64_t	   
	po_obj_del
		(po_obj* par)			                              {
			if(!par)		                          return 0;
			if(!par->trait)                           return 0;

            if (!kref_read(&par->ref))                return 0;
            if (!kref_put (&par->ref, po_obj_do_del)) return kref_read(&par->ref);
            return 0;
}

po_obj_trait* 
	po_obj_get_trait
		(po_obj* par)		  {
			if (!par) return 0;
			return par->trait;
}

u64_t 
	po_obj_use_count
		(po_obj* par)				   {
			if (!par)		   return 0;
			if (!par->trait)   return 0;

			return kref_read(&par->ref);
}

#ifdef PO_PRESET_LINUX
#include <linux/module.h>

MODULE_LICENSE("GPL");
#endif