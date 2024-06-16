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
        (po_list* self, u32_t count, va_list arg)                        {
            po_mem* mem = null_t; if (count > 0) mem = va_arg(arg, void*);
            if (po_trait_of(mem) != po_mem_t) mem = po_get_mem();
            if (po_trait_of(mem) != po_mem_t) return false_t    ;

            if (!po_make_at(&self->begin, po_node) from(0)) goto err;
            if (!po_make_at(&self->end  , po_node) from(0)) goto err;
            if (!po_next_as(&self->begin, &self->end))      goto err;
            self->mem = (po_mem*) po_ref(mem);
            return true_t;
    err:    po_del(&self->begin);
            po_del(&self->end)  ;
            return false_t;
}

bool_t
    po_list_clone
        (po_list* self, po_list* clone)                                     {
            if (!po_make_at(&self->begin, po_node) from(0))   return false_t;
            if (!po_make_at(&self->end  , po_node) from(0))   return false_t;

            if (!po_next_as(&self->begin, &clone->end))   return false_t;
            if (!po_prev_as(&self->end  , &clone->begin)) return false_t;
            self->mem = clone->mem;

            po_list_for(clone, push) po_list_push_back(self, po_value(push));
            return true_t;
}

void
    po_list_del
        (po_list* self)                                           {
            for ( ; !po_list_empty(self) ; po_list_pop_back(self));
}

po_node*
    po_list_push_back
        (po_list* self, po_obj* push)                        {
            if (po_trait_of(self) != po_list_t) return null_t;
            if (po_trait_of(push) == null_t)    return null_t;
            po_node *ret = (po_node*) po_obj_new             (
                self->mem,
                po_node_t,
                1        ,
                push
            );

            if (po_trait_of(ret) != po_node_t) return null_t;
            po_prev_as(ret, po_prev(&self->end));
            po_prev_as(&self->end, ret)         ;
            return  ret;
}

po_node*
    po_list_push_front
        (po_list* self, po_obj* push)                        {
            if (po_trait_of(self) != po_list_t) return null_t;
            if (po_trait_of(push) == null_t)    return null_t;
            po_node *ret = (po_node*) po_obj_new            (
                self->mem,
                po_node_t,
                1        ,
                push
            );

            if (po_trait_of(ret) != po_node_t) return null_t;
            po_next_as(ret, po_next(&self->begin));
            po_next_as(&self->begin, ret)         ;
            return  ret;
}

po_node*
    po_list_move_back
        (po_list* self, po_obj* push)                   {
            po_node* ret = po_list_push_back(self, push);

            if (po_trait_of(ret) != po_node_t) return null_t;
            po_del(push);
            return  ret ;
}

po_node*
    po_list_move_front
        (po_list* self, po_obj* push)                    {
            po_node* ret = po_list_push_front(self, push);

            if (po_trait_of(ret) != po_node_t) return null_t;
            po_del(push);
            return  ret ;
}

po_obj*
    po_list_pop_front
        (po_list* self)                                        {
            if (po_trait_of  (self) != po_list_t) return null_t;
            if (po_list_empty(self))              return null_t;

            po_node *ret_cur = po_next (&self->begin);
            po_obj  *ret     = po_value(ret_cur)     ;
            if (po_use_count(ret) == 1)              {
                po_del(ret_cur);
                return 0;
            }

            po_del(ret_cur);
            return ret     ;
}

po_obj*
    po_list_pop_back
        (po_list* self)                                        {
            if (po_trait_of  (self) != po_list_t) return null_t;
            if (po_list_empty(self))              return null_t;

            po_node *ret_cur = po_prev (&self->end);
            po_obj  *ret     = po_value(ret_cur)   ;
            if (po_use_count(ret) == 1)            {
                po_del (ret_cur);
                return null_t;
            }

            po_del(ret_cur);
            return ret     ;
}

bool_t
    po_list_empty
        (po_list* self)                                      {
            if (po_trait_of(self) != po_list_t) return true_t;
            return po_next(&self->begin) == &self->end;
}

po_node*
    po_list_begin
        (po_list* self)                                      {
            if (po_trait_of(self) != po_list_t) return null_t;
            return self->begin.next;
}

po_node*
    po_list_end
        (po_list* self)                                      {
            if (po_trait_of(self) != po_list_t) return null_t;
            return &self->end;
}

#ifdef PRESET_LINUX
#include <linux/module.h>
MODULE_LICENSE("GPL");

EXPORT_SYMBOL(po_list_empty);
EXPORT_SYMBOL(po_list_push_front);
EXPORT_SYMBOL(po_list_push_back);
EXPORT_SYMBOL(po_list_move_front);
EXPORT_SYMBOL(po_list_move_back);
EXPORT_SYMBOL(po_list_pop_front);
EXPORT_SYMBOL(po_list_pop_back);
EXPORT_SYMBOL(po_list_begin);
EXPORT_SYMBOL(po_list_end);
EXPORT_SYMBOL(po_list_t);
#endif