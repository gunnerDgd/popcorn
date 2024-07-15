#include "map.h"

static bool_t
    do_new
        (pp_map* self, u32_t count, va_list arg)                      {
            pp_mem *mem = 0; if (count > 0) mem = va_arg(arg, pp_mem*);
            if (pp_trait_of(mem) != pp_mem_t) mem = pp_get_mem();
            if (pp_trait_of(mem) != pp_mem_t) return false_t;

            if (!pp_make_at(&self->map, pp_list) from(1, mem)) return false_t;
            return true_t;
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
        (pp_map* self, pp_obj* push)                        {
            if (pp_trait_of(self) != pp_map_t) return null_t;

            pp_list_for (&self->map, pos)                     {
                if (pp_eq_arg(push, pp_as_any(pos))) return null_t;
                if (pp_gt_arg(push, pp_as_any(pos))) continue;
                pp_pos *cur = pp_make (pp_pos) from (1, push);

                if (pp_trait_of(cur) != pp_pos_t) return null_t;
                return pp_next_as(cur, pos);
            }

            return pp_list_push_back(&self->map, push);
}

pp_pos*
    pp_map_move
        (pp_map *self, pp_obj* push)                        {
            if (pp_trait_of(self) != pp_map_t) return null_t;
            pp_pos *ret = pp_map_push(self, push);

            if (pp_trait_of(ret) != pp_pos_t) return null_t;
            pp_del (push);
            return  ret  ;
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

            pp_list_for (&self->map, pos)                   {
                if (pp_ne_arg(pp_as_any(pos), key)) continue;
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