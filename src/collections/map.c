#include "map.h"

static bool_t
    do_new
        (pp_map* self, u32_t count, va_list arg)                         {
            pp_cmp *cmp = null_t; if (count > 0) cmp = va_arg(arg, any_t);
            pp_mem *mem = null_t; if (count > 1) mem = va_arg(arg, any_t);
            if (pp_trait_of(mem) != pp_mem_t) mem = pp_get_mem();
            if (pp_trait_of(mem) != pp_mem_t) return false_t;
            if (!cmp)                         return false_t;

            if (!pp_make_at(&self->map, pp_list) from(1, mem)) goto err;
            if (!cmp->ord)                                     goto err;
            self->mem = (pp_obj*) pp_ref(mem);
            self->cmp = cmp;

            return true_t;
    err:    pp_del (&self->map);
            return false_t;
}

static bool_t
    do_clone
        (pp_map* self, pp_map* clone)                                {
            if (!pp_clone_at(&self->map, &clone->map)) return false_t;
            return true_t;
}

static void
    do_del
        (pp_map* self)         {
            pp_del (&self->map);
}

static pp_obj_trait
    do_obj = pp_make_trait (
        do_new        ,
        do_clone      ,
        null_t        ,
        do_del        ,
        sizeof(pp_map),
        null_t
);

pp_obj_trait* pp_map_t = &do_obj;

pp_pos*
    pp_map_push
        (pp_map* self, any_t push)                          {
            if (pp_trait_of(self) != pp_map_t) return null_t;

            pp_list_for (&self->map, pos)                                    {
                pp_ord_t ord = self->cmp->ord(push, pp_as_any((pp_obj*) pos));
                if (ord == pp_ord_err) return null_t;
                if (ord == pp_ord_eq)  return null_t;
                if (ord == pp_ord_gt)  continue;
                pp_pos *cur = pp_obj_new      (
                    self->mem,
                    pp_pos_t ,
                    1        ,
                    push
                );

                if (pp_trait_of(cur) != pp_pos_t) return null_t;
                return pp_next_as(cur, pos);
            }

            return pp_list_push_back(&self->map, push);
}

pp_pos*
    pp_map_move
        (pp_map *self, any_t* push)                         {
            if (pp_trait_of(self) != pp_map_t) return null_t;
            pp_pos *ret = pp_map_push(self, *push);

            if (pp_trait_of(ret) != pp_pos_t) return null_t;
            *push = null_t;
            return ret;
}

void
    pp_map_pop
        (pp_map* self, any_t key)                    {
            if (pp_trait_of(self) != pp_map_t) return;
            pp_pos *pop = pp_map_find(self, key);

            if (pp_trait_of(pop) != pp_pos_t) return;
            pp_del(pop);
}

pp_pos*
    pp_map_find
        (pp_map* self, any_t key)                           {
            if (pp_trait_of(self) != pp_map_t) return null_t;

            pp_list_for (&self->map, pos)                                   {
                pp_ord_t ord = self->cmp->ord(pp_as_any((pp_obj*) pos), key);
                if (ord != pp_ord_eq) continue;
                return pos;
            }

            return pp_map_end(self);
}

bool_t  pp_map_empty(pp_map* self) { if (pp_trait_of(self) != pp_map_t) return false_t; return pp_list_empty(&self->map); }
pp_pos* pp_map_begin(pp_map* self) { if (pp_trait_of(self) != pp_map_t) return null_t;  return pp_list_begin(&self->map); }
pp_pos* pp_map_end  (pp_map* self) { if (pp_trait_of(self) != pp_map_t) return null_t;  return pp_list_end  (&self->map); }

#ifdef PRESET_LINUX
#include <linux/module.h>
MODULE_LICENSE("GPL");
EXPORT_SYMBOL(pp_map_begin);
EXPORT_SYMBOL(pp_map_end);
EXPORT_SYMBOL(pp_map_empty);
EXPORT_SYMBOL(pp_map_find);
EXPORT_SYMBOL(pp_map_move);
EXPORT_SYMBOL(pp_map_push);
EXPORT_SYMBOL(pp_map_pop);
EXPORT_SYMBOL(pp_map_t);
#endif