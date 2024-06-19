#include "map.h"

po_obj_trait po_map_trait = po_make_trait (
    po_map_new    ,
    po_map_clone  ,
    null_t        ,
    po_map_del    ,
    sizeof(po_map),
    null_t
);

po_obj_trait* po_map_t = &po_map_trait;

bool_t
    po_map_new
        (po_map* self, u32_t count, va_list arg)                      {
            po_mem *mem = 0; if (count > 0) mem = va_arg(arg, po_mem*);
            if (po_trait_of(mem) != po_mem_t) mem = po_get_mem();
            if (po_trait_of(mem) != po_mem_t) return false_t;

            if (!po_make_at(&self->map, po_list) from(1, mem)) return false_t;
            return true_t;
}

bool_t
    po_map_clone
        (po_map* self, po_map* clone)                                {
            if (!po_clone_at(&self->map, &clone->map)) return false_t;
            return true_t;
}

void
    po_map_del
        (po_map* self)         {
            po_del (&self->map);
}

po_node*
    po_map_push
        (po_map* self, po_obj* push)                        {
            if (po_trait_of(self) != po_map_t) return null_t;

            po_list_for (&self->map, pos)                       {
                if (po_op_eq(push, po_value(pos))) return null_t;
                if (po_op_gt(push, po_value(pos))) continue;
                po_node *cur = po_make (po_node) from (1, push);

                if (po_trait_of(cur) != po_node_t) return null_t;
                return po_next_as(cur, pos);
            }

            return po_list_push_back(&self->map, push);
}

po_node*
    po_map_move
        (po_map *self, po_obj* push)                        {
            if (po_trait_of(self) != po_map_t) return null_t;
            po_node *ret = po_map_push(self, push);

            if (po_trait_of(ret) != po_node_t) return null_t;
            po_del (push);
            return  ret  ;
}

void
    po_map_pop
        (po_map* self, any_t key)                    {
            if (po_trait_of(self) != po_map_t) return;
            po_node *pop = po_map_find(self, key);

            if (po_trait_of(pop) != po_node_t) return;
            po_del(pop);
}

po_node*
    po_map_find
        (po_map* self, any_t key)                           {
            if (po_trait_of(self) != po_map_t) return null_t;

            po_list_for (&self->map, pos)                     {
                if (po_op_ne_arg(po_value(pos), key)) continue;
                return pos;
            }

            return po_map_end(self);
}

bool_t
    po_map_empty
        (po_map* par)                                       {
            if (po_trait_of(par) != po_map_t) return false_t;
            return po_list_empty(&par->map);
}

po_node*
    po_map_begin
        (po_map* par)                                      {
            if (po_trait_of(par) != po_map_t) return null_t;
            return po_list_begin(&par->map);
}

po_node*
    po_map_end
        (po_map* par)                                      {
            if (po_trait_of(par) != po_map_t) return null_t;
            return po_list_end(&par->map);
}

#ifdef PRESET_LINUX
#include <linux/module.h>
MODULE_LICENSE("GPL");
EXPORT_SYMBOL(po_map_begin);
EXPORT_SYMBOL(po_map_end);
EXPORT_SYMBOL(po_map_empty);
EXPORT_SYMBOL(po_map_find);
EXPORT_SYMBOL(po_map_move);
EXPORT_SYMBOL(po_map_push);
EXPORT_SYMBOL(po_map_pop);
EXPORT_SYMBOL(po_map_t);
#endif