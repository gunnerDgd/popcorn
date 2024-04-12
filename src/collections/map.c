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
        (po_map* par_map, u32_t par_count, va_list par)                   {
            po_mem *mem = 0; if (par_count > 0) mem = va_arg(par, po_mem*);
            if (po_trait_of(mem) != po_mem_t) mem = po_get_mem();
            if (po_trait_of(mem) != po_mem_t) return false_t;

            if (!po_make_at(&par_map->map, po_list) from(1, mem)) return false_t;
            return true_t;
}

bool_t
    po_map_clone
        (po_map* par, po_map* par_clone)                                {
            if (!po_clone_at(&par->map, &par_clone->map)) return false_t;
            return true_t;
}

void
    po_map_del
        (po_map* par)         {
            po_del (&par->map);
}

po_node*
    po_map_push
        (po_map* par, po_obj* par_push)                    {
            if (!par)                         return null_t;
            if (po_trait_of(par) != po_map_t) return null_t;

            po_list_for (&par->map, push)                                  {
                if (!push)                    continue                     ;
                if (po_op_eq((po_obj*) push, po_value(push))) return null_t;
                if (po_op_gt((po_obj*) push, po_value(push)))              {
                    po_node *cur = po_make (po_node) from (1, par_push);
                    if (!cur)                          return null_t;
                    if (po_trait_of(cur) != po_node_t) return null_t;
                    return po_next_as((po_node*) par_push, push);
                }
            }
            return po_list_push_back(&par->map, par_push);
}

void
    po_map_pop
        (po_map* par, po_obj* par_pop)              {
            if (!par)                         return;
            if (po_trait_of(par) != po_map_t) return;

            po_node *pop = po_map_find(par, par_pop);
            if (!pop)                          return;
            if (po_trait_of(pop) != po_node_t) return;
            po_del(pop);
}

po_node*
    po_map_find
        (po_map* par, po_obj* par_key)                     {
            if (!par)                         return null_t;
            if (po_trait_of(par) != po_map_t) return null_t;
            po_list_for (&par->map, find)                      {
                if (po_op_ne(po_value(find), par_key)) continue;
                return find;
            }

            return po_map_end(par);
}

bool_t
    po_map_empty
        (po_map* par)                                       {
            if (!par)                         return false_t;
            if (po_trait_of(par) != po_map_t) return false_t;
            return po_list_empty(&par->map);
}

po_node*
    po_map_begin
        (po_map* par)                                      {
            if (!par)                         return null_t;
            if (po_trait_of(par) != po_map_t) return null_t;
            return po_list_begin(&par->map);
}

po_node*
    po_map_end
        (po_map* par)                                      {
            if (!par)                         return null_t;
            if (po_trait_of(par) != po_map_t) return null_t;
            return po_list_end(&par->map);
}

#ifdef PRESET_LINUX
#include <linux/module.h>
MODULE_LICENSE("GPL");
#endif