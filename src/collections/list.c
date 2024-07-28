#include "list.h"

static bool_t
    do_new
        (pp_list* self, u32_t count, va_list arg)                        {
            pp_mem* mem = null_t; if (count > 0) mem = va_arg(arg, void*);
            if (pp_trait_of(mem) != pp_mem_t) mem = pp_get_mem();
            if (pp_trait_of(mem) != pp_mem_t) return false_t;

            if (!pp_make_at(&self->begin, pp_pos) from(0)) goto err;
            if (!pp_make_at(&self->end  , pp_pos) from(0)) goto err;
            if (!pp_next_as(&self->begin, &self->end))     goto err;
            self->mem = (pp_mem*) pp_ref(mem);
            return true_t;
    err:    pp_del(&self->begin);
            pp_del(&self->end)  ;
            return false_t;
}

static bool_t
    do_clone
        (pp_list* self, pp_list* clone)                                  {
            if (!pp_make_at(&self->begin, pp_pos) from(0)) return false_t;
            if (!pp_make_at(&self->end  , pp_pos) from(0)) return false_t;

            if (!pp_next_as(&self->begin, &clone->end))   return false_t;
            if (!pp_prev_as(&self->end  , &clone->begin)) return false_t;
            self->mem = clone->mem;

            pp_list_for(clone, push) pp_list_push_back(self, pp_as_any((pp_obj*) push));
            return true_t;
}

static void
    do_del
        (pp_list* self)                                      {
            if (pp_trait_of(&self->begin) != pp_pos_t) return;
            if (pp_trait_of(&self->end)   != pp_pos_t) return;
            for( ; !pp_list_empty(self) ; pp_list_pop_back(self));
}

static pp_obj_trait
    do_obj = pp_make_trait (
        do_new         ,
        do_clone       ,
        null_t         ,
        do_del         ,
        sizeof(pp_list),
        null_t
);

pp_obj_trait* pp_list_t = &do_obj;

pp_pos*
    pp_list_push_back
        (pp_list* self, any_t push)                          {
            if (pp_trait_of(self) != pp_list_t) return null_t;
            pp_pos *ret = (pp_pos*) pp_obj_new (
                self->mem,
                pp_pos_t ,
                1        ,
                push
            );

            if (pp_trait_of(ret) != pp_pos_t) return null_t;
            pp_prev_as(ret, pp_prev(&self->end));
            pp_prev_as(&self->end, ret);
            return ret;
}

pp_pos*
    pp_list_push_front
        (pp_list* self, any_t push)                          {
            if (pp_trait_of(self) != pp_list_t) return null_t;
            pp_pos *ret = (pp_pos*) pp_obj_new (
                self->mem,
                pp_pos_t ,
                1        ,
                push
            );

            if (pp_trait_of(ret) != pp_pos_t) return null_t;
            pp_next_as(ret, pp_next(&self->begin));
            pp_next_as(&self->begin, ret);
            return ret;
}

pp_pos*
    pp_list_move_back
        (pp_list* self, any_t* push)                    {
            pp_pos* ret = pp_list_push_back(self, *push);

            if (pp_trait_of(ret) != pp_pos_t) return null_t;
            *push = null_t;
            return ret;
}

pp_pos*
    pp_list_move_front
        (pp_list* self, any_t* push)                     {
            pp_pos* ret = pp_list_push_front(self, *push);

            if (pp_trait_of(ret) != pp_pos_t) return null_t;
            *push = null_t;
            return ret;
}

any_t
    pp_list_pop_front
        (pp_list* self)                                        {
            if (pp_trait_of  (self) != pp_list_t) return null_t;
            if (pp_list_empty(self))              return null_t;

            pp_pos *pos = pp_next  (&self->begin);
            any_t   ret = pp_as_any((pp_obj*)pos);

            if (pos == &self->end) return null_t;
            pp_del(pos);
            return ret;
}

any_t
    pp_list_pop_back
        (pp_list* self)                                        {
            if (pp_trait_of  (self) != pp_list_t) return null_t;
            if (pp_list_empty(self))              return null_t;

            pp_pos *pos = pp_prev  (&self->end);
            pp_obj *ret = pp_as_any((pp_obj*)pos);

            if (pos == &self->begin) return null_t;
            pp_del(pos);
            return ret;
}

bool_t
    pp_list_empty
        (pp_list* self)                                      {
            if (pp_trait_of(self) != pp_list_t) return true_t;
            return pp_next(&self->begin) == &self->end;
}

pp_pos*
    pp_list_begin
        (pp_list* self)                                      {
            if (pp_trait_of(self) != pp_list_t) return null_t;
            return pp_next(&self->begin);
}

pp_pos*
    pp_list_end
        (pp_list* self)                                      {
            if (pp_trait_of(self) != pp_list_t) return null_t;
            return &self->end;
}

#ifdef PRESET_LINUX
#include <linux/module.h>
MODULE_LICENSE("GPL");

EXPORT_SYMBOL(pp_list_empty);
EXPORT_SYMBOL(pp_list_push_front);
EXPORT_SYMBOL(pp_list_push_back);
EXPORT_SYMBOL(pp_list_move_front);
EXPORT_SYMBOL(pp_list_move_back);
EXPORT_SYMBOL(pp_list_pop_front);
EXPORT_SYMBOL(pp_list_pop_back);
EXPORT_SYMBOL(pp_list_begin);
EXPORT_SYMBOL(pp_list_end);
EXPORT_SYMBOL(pp_list_t);
#endif