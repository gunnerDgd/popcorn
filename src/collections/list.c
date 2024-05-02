#include "list.h"

po_obj_trait po_list_trait = po_make_trait (
    po_list_new    ,
    po_list_clone  ,
    null_t         ,
    po_list_del    ,
    sizeof(po_list),
    null_t
);

po_obj_trait* po_list_t = &po_list_trait;

bool_t
    po_list_new
        (po_list* par_list, u32_t par_count, va_list par)                    {
            po_mem* mem = null_t; if (par_count > 0) mem = va_arg(par, void*);
            if (po_trait_of(mem) != po_mem_t) mem = po_get_mem();
            if (po_trait_of(mem) != po_mem_t) return false_t    ;

            if (!po_make_at(&par_list->begin, po_node) from(0)) goto new_err;
            if (!po_make_at(&par_list->end  , po_node) from(0)) goto new_err;
            if (!po_next_as(&par_list->begin, &par_list->end))  goto new_err;
            par_list->mem = (po_mem*) po_ref(mem);
            return true_t;
    new_err:
            po_del(&par_list->begin);
            po_del(&par_list->end)  ;
            return false_t;
}

bool_t
    po_list_clone
        (po_list* par, po_list* par_clone)                                 {
            if (!po_make_at(&par->begin, po_node) from(0))   return false_t;
            if (!po_make_at(&par->end  , po_node) from(0))   return false_t;

            if (!po_next_as(&par->begin, &par_clone->end))   return false_t;
            if (!po_prev_as(&par->end  , &par_clone->begin)) return false_t;

            par->mem = par_clone->mem;
            po_list_for(par_clone, push)                                 {
                po_node* ret = po_make (po_node) from (1, po_value(push));
                po_list_push_back(par, (po_obj*) ret);
            }

            return true_t;
}

void
    po_list_del
        (po_list* par)                               {
            while(po_next(&par->begin) != &par->end) {
                po_list_pop_back(par);
            }
}

po_node*
    po_list_push_back
        (po_list* par, po_obj* par_push)                    {
            if (!par_push)                     return null_t;
            if (!par)                          return null_t;
            if (po_trait_of(par) != po_list_t) return null_t;
            po_node *ret = (po_node*) po_obj_new            (
                par->mem,
                po_node_t,
                1        ,
                par_push
            );

            if (po_trait_of(ret) != po_node_t) return null_t;
            po_prev_as(ret, po_prev(&par->end));
            po_prev_as(&par->end, ret)         ;
            return  ret;
}

po_node*
    po_list_push_front
        (po_list* par, po_obj* par_push)                    {
            if (!par_push)                     return null_t;
            if (!par)                          return null_t;
            if (po_trait_of(par) != po_list_t) return null_t;
            po_node *ret = (po_node*) po_obj_new            (
                par->mem ,
                po_node_t,
                1        ,
                par_push
            );

            if (po_trait_of(ret) != po_node_t) return null_t;
            po_next_as(ret, po_next(&par->begin));
            po_next_as(&par->begin, ret)         ;
            return  ret;
}

po_node*
    po_list_move_back
        (po_list* par, po_obj* par_push)                    {
            if (!par_push)                     return null_t;
            if (!par)                          return null_t;
            if (po_trait_of(par) != po_list_t) return null_t;
            po_node *ret = (po_node*) po_obj_new            (
                par->mem,
                po_node_t,
                1        ,
                par_push
            );

            if (po_trait_of(ret) != po_node_t) return null_t;
            po_del (par_push);

            po_prev_as(ret, po_prev(&par->end));
            po_prev_as(&par->end, ret)         ;
            return  ret;
}

po_node*
    po_list_move_front
        (po_list* par, po_obj* par_push)                    {
            if (!par_push)                     return null_t;
            if (!par)                          return null_t;
            if (po_trait_of(par) != po_list_t) return null_t;
            po_node *ret = (po_node*) po_obj_new            (
                par->mem ,
                po_node_t,
                1        ,
                par_push
            );

            if (po_trait_of(ret) != po_node_t) return null_t;
            po_del (par_push);

            po_next_as(ret, po_next(&par->begin));
            po_next_as(&par->begin, ret)         ;
            return  ret;
}

po_obj*
    po_list_pop_front
        (po_list* par)                                      {
            if (!par)                          return null_t;
            if (po_trait_of(par) != po_list_t) return null_t;
            if (po_list_empty(par))            return null_t;

            po_node *ret_cur = po_next (&par->begin);
            po_obj  *ret     = po_value(ret_cur)    ;
            if (po_use_count(ret) == 1)             {
                po_del(ret_cur);
                return 0;
            }

            po_del(ret_cur);
            return ret     ;
}

po_obj*
    po_list_pop_back
        (po_list* par)                                      {
            if (!par)                          return null_t;
            if (po_trait_of(par) != po_list_t) return null_t;
            if (po_list_empty(par))            return null_t;

            po_node *ret_cur = po_prev (&par->end);
            po_obj  *ret     = po_value(ret_cur)  ;
            if (po_use_count(ret) == 1)           {
                po_del (ret_cur);
                return null_t;
            }

            po_del(ret_cur);
            return ret     ;
}

bool_t
    po_list_empty
        (po_list* par)                                      {
            if (!par)                          return true_t;
            if (po_trait_of(par) != po_list_t) return true_t;
            return po_next(&par->begin) == &par->end;
}

po_node*
    po_list_begin
        (po_list* par)                                      {
            if (!par)                          return null_t;
            if (po_trait_of(par) != po_list_t) return null_t;
            return par->begin.next;
}

po_node*
    po_list_end
        (po_list* par)                                      {
            if (!par)                          return null_t;
            if (po_trait_of(par) != po_list_t) return null_t;
            return &par->end;
}

#ifdef PRESET_LINUX
#include <linux/module.h>
MODULE_LICENSE("GPL");

EXPORT_SYMBOL(po_list_empty);
EXPORT_SYMBOL(po_list_push_front);
EXPORT_SYMBOL(po_list_push_back);
EXPORT_SYMBOL(po_list_pop_front);
EXPORT_SYMBOL(po_list_pop_back);
EXPORT_SYMBOL(po_list_begin);
EXPORT_SYMBOL(po_list_end);
EXPORT_SYMBOL(po_list_t);
#endif