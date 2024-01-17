#include "list.h"

po_obj_trait po_list_trait            = {
    .on_new   = as_new  (&po_list_new)  ,
    .on_clone = as_clone(&po_list_clone),
    .on_ref   = 0                       ,
    .on_del   = as_del   (&po_list_del) ,
    .size     = sizeof(po_list)
};

po_obj_trait* po_list_t = &po_list_trait;

bool_t
    po_list_new
        (po_list* par_po_list, u32_t par_count, va_list par)  {
            po_mem* res = 0;
            switch (par_count)                                {
                case 0 : res = po_get_mem()            ; break;
                case 1 : res = va_arg    (par, po_mem*); break;
                default: return false_t                ;
            }

            if (!res)         return false_t;
            if (!res->on_new) return false_t;
            if (!res->on_del) return false_t;

            par_po_list->res        = res              ;
            par_po_list->begin.next = &par_po_list->end;
            par_po_list->begin.prev =                 0;
            par_po_list->begin.elem =                 0;

            par_po_list->end.prev   = &par_po_list->begin;
            par_po_list->end.next   = 0                  ;
            par_po_list->end.elem   = 0                  ;

            po_mem_set(&par_po_list->begin.head, 0x00, sizeof(po_obj));
            po_mem_set(&par_po_list->end  .head, 0x00, sizeof(po_obj));
            return true_t;
}

bool_t
    po_list_clone
        (po_list* par, po_list* par_clone)     {
            if (!par)            return false_t;
            if (!par_clone)      return false_t;
            if (!par_clone->res) return false_t;

            par->begin.next = &par->end;
            par->begin.prev = 0        ;

            par->end.prev   = &par->begin   ;
            par->end.next   = 0             ;
            par->res        = par_clone->res;

            po_list_elem *push = par_clone->begin.next;
            while     (push != &par_clone->end) po_list_push_back(par, push->elem);

            po_mem_set(&par->begin.head, 0x00, sizeof(po_obj));
            po_mem_set(&par->end  .head, 0x00, sizeof(po_obj));
            return true_t;
}

void
    po_list_del
        (po_list* par)                          {
            while (par->begin.next != &par->end)
                po_list_pop_front(par);
}

po_list_elem*
    po_list_push_back
        (po_list* par, po_obj* par_push)            {
            if (!par)                       return 0;
            if (!par_push)                  return 0;
            if (!trait_of(par_push))        return 0;
            if (trait_of(par) != po_list_t) return 0;
            

            if (!par->res) return 0; po_list_elem* ret = po_mem_new(par->res, sizeof(po_list_elem));
            if (!ret)      return 0;

            po_mem_set(&ret->head, 0x00, sizeof(po_obj));
            ret->elem = ref(par_push);
            ret->list = par          ;

            ret->next = &par->end     ;
            ret->prev =  par->end.prev;

            par->end.prev->next = ret;
            par->end.prev       = ret;

            return ret;
}

po_list_elem*
    po_list_push_front
        (po_list* par, po_obj* par_push)            {
            if (!par)                       return 0;
            if (!par_push)                  return 0;
            if (!trait_of(par_push))        return 0;
            if (trait_of(par) != po_list_t) return 0;
            
            if (!par->res) return 0; po_list_elem *ret = po_mem_new(par->res, sizeof(po_list_elem));
            if (!ret)      return 0;

            po_mem_set(&ret->head, 0x00, sizeof(po_obj));
            ret->elem = ref(par_push);
            ret->list = par          ;

            ret->next =  par->begin.next;
            ret->prev = &par->begin     ;
            
            par->begin.next->prev = ret;
            par->begin.next       = ret;

            return ret;
}

po_list_elem*
    po_list_push
        (po_list* par, po_obj* par_push, po_list_elem* par_at) {
            if (!par)                       return 0;
            if (!par_at)                    return 0;
            if (!par_push)                  return 0;
            if (trait_of(par_push) == NULL) return 0;
            if (trait_of(par) != po_list_t) return 0;

            if (!par->res)                  return 0;
            if (par_at->list != par)        return 0;
            if (par_at == &par->end)        return po_list_push_back (par, par_push);
            if (par_at == &par->begin)      return po_list_push_front(par, par_push);

            po_list_elem* ret = po_mem_new(par->res, sizeof(po_list_elem));
            if (!ret) return 0;

            po_mem_set(&ret->head, 0x00, sizeof(po_obj));
            ret->prev = par_at      ;
            ret->next = par_at->next;

            ret->elem = ref(par_push);
            ret->list = par          ; par_at->next = ret;

            return ret;
}

po_obj*
    po_list_pop_front
        (po_list* par)                              {
            if (!par)                       return 0;
            if (trait_of(par) != po_list_t) return 0;

            po_list_elem *pop = par->begin.next;
            if (pop == &par->end)      return 0;
            if (pop == &par->begin)    return 0;
            if (pop->list != par)      return 0;

            pop->prev->next = pop->next;
            pop->next->prev = pop->prev;

            po_obj* ret = (del(pop->elem)) ? pop->elem : 0; po_mem_del(par->res, pop);
            return  ret;
}

po_obj*
    po_list_pop_back
        (po_list* par)                              {
            if (!par)                       return 0;
            if (trait_of(par) != po_list_t) return 0; po_list_elem *pop = par->end.prev;

            if (pop == &par->begin)         return 0;
            if (pop == &par->end)           return 0;
            if (pop->list != par)           return 0;
                        
            pop->prev->next = pop->next;
            pop->next->prev = pop->prev;

            po_obj*   ret = (del(pop->elem)) ? pop->elem : 0; po_mem_del(par->res, pop);
            return ret;
}

po_obj*
    po_list_pop
        (po_list* par, po_list_elem* par_at)        {
            if (!par)                       return 0;
            if (trait_of(par) != po_list_t) return 0;
            if (!par_at)                    return 0;

            if (par_at == &par->begin)      return po_list_pop_front(par);
            if (par_at == &par->end)        return po_list_pop_back (par);
            if (par_at->list != par)        return 0;

            par_at->prev->next = par_at->next;
            par_at->next->prev = par_at->prev;

            po_obj*   ret = (del(par_at->elem)) ? par_at->elem : 0; po_mem_del(par->res, par_at);
            return ret;
}


bool_t
    po_list_empty
        (po_list* par)                                   {
            if (!par)                       return true_t;
            if (trait_of(par) != po_list_t) return true_t;

            return par->begin.next == &par->end;
}

po_list_elem*
    po_list_begin
        (po_list* par)                              {
            if (!par)                       return 0;
            if (trait_of(par) != po_list_t) return 0;

            return par->begin.next;
}

po_list_elem*
    po_list_end
        (po_list* par)                              {
            if (!par)                       return 0;
            if (trait_of(par) != po_list_t) return 0;

            return &par->end;
}

po_list_elem*
    po_list_next
        (po_list_elem* par)                                   {
            if (!par)                   return 0              ;
            if (!par->list)             return 0              ;
            if (par == &par->list->end) return &par->list->end;

            return par->next;
}

po_list_elem*
    po_list_prev
        (po_list_elem* par)                                 {
            if (!par)                             return   0;
            if (!par->list)                       return   0;
            if (trait_of(par->list) != po_list_t) return   0;
            if (par->prev == &par->list->begin)   return par;

            return par->prev;
}

po_obj*
    po_list_get
        (po_list_elem* par)                               {
            if (!par)                             return 0;
            if (!par->list)                       return 0;
            if (trait_of(par->list) != po_list_t) return 0;

            if (par == &par->list->begin)         return 0;
            if (par == &par->list->end)           return 0;

            return par->elem;
}

po_obj*
    po_list_set
        (po_list_elem* par, po_obj* par_set)              {
            po_obj *ret = (del(par->elem)) ? par->elem : 0;

            if (!par)                             return 0;
            if (!par->list)                       return 0;
            if (trait_of(par->list) != po_list_t) return 0;
            if (!par_set)                         return 0;

            if (par == &par->list->begin)         return 0;
            if (par == &par->list->end)           return 0;

            par->elem = ref(par_set);
            return ret;
}

#ifdef PO_PRESET_LINUX
#include <linux/module.h>

EXPORT_SYMBOL (po_list_push_back) ;
EXPORT_SYMBOL (po_list_push_front);
EXPORT_SYMBOL (po_list_push)      ;

EXPORT_SYMBOL (po_list_pop_back)  ;
EXPORT_SYMBOL (po_list_pop_front) ;
EXPORT_SYMBOL (po_list_pop)       ;

EXPORT_SYMBOL (po_list_empty)     ;
EXPORT_SYMBOL (po_list_begin)     ;
EXPORT_SYMBOL (po_list_end)       ;
EXPORT_SYMBOL (po_list_next)      ;
EXPORT_SYMBOL (po_list_prev)      ;

EXPORT_SYMBOL (po_list_get)       ;
EXPORT_SYMBOL (po_list_set)       ;

EXPORT_SYMBOL (po_list_t)         ;
MODULE_LICENSE("GPL")             ;
#endif