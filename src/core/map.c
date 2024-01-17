#include "map.h"

po_obj_trait po_map_trait            = {
    .on_new   = as_new  (&po_map_new)  ,
    .on_clone = as_clone(&po_map_clone),
    .on_ref   = 0                      ,
    .on_del   = as_del  (&po_map_del)  ,
    .size     = sizeof(po_map)
};

po_obj_trait* po_map_t = &po_map_trait;

bool_t    
    po_map_new
        (po_map* par_po_map, u32_t par_count, va_list par) {
            po_map_key *key = 0;
            po_mem     *res = 0;
            switch (par_count)                             {
                case 1 : key = va_arg    (par, po_map_key*);
                         res = po_get_mem()                ;
                         break;
                case 2 : key = va_arg (par, po_map_key*)   ;
                         res = va_arg (par, po_mem*)       ;
                         break;
                default: return false_t;
            }

            if (!res)                                               return false_t;
            if (!key)                                               return false_t;
            if (!key->eq)                                           return false_t;
            if (!key->lt)                                           return false_t;
            if (!key->gt)                                           return false_t;
            if (!make_at(&par_po_map->map, po_list_t) from(1, res)) return false_t;

            par_po_map->key = key;
            return true_t;
}

bool_t    
    po_map_clone
        (po_map* par, po_map* par_clone) {
            par->key = par_clone->key;

            if (par->key)                              return false_t;
            if (!clone_at(&par->map, &par_clone->map)) return false_t;

            return true_t;
}

void
    po_map_del
        (po_map* par)      {
            del (&par->map);
}

po_map_elem*
    po_map_push
        (po_map* par, po_obj* par_push)            {
            if (!par)                      return 0;
            if (trait_of(par) != po_map_t) return 0;

            po_list_for (&par->map, push_it)       {
                po_obj *push = po_list_get(push_it);
                if (!push)                        continue                                                       ;
                if (par->key->lt(push, par_push)) return po_list_push(&par->map, par_push, po_list_prev(push_it));
                if (par->key->eq(push, par_push)) return 0                                                       ;
            }

            return po_list_push_back(&par->map, par_push);
}

void      
    po_map_pop
        (po_map* par, po_map_elem* par_pop)      {
            if (!par)                      return;
            if (trait_of(par) != po_map_t) return;

            po_list_pop(&par->map, par_pop);
}

po_map_elem*
    po_map_find
        (po_map* par, po_obj* par_key)                {
            if (!par)                   return 0;
            if (trait_of(par) != po_map_t) return 0;

            po_list_for (&par->map, find_it)              {
                po_obj *find = po_list_get(find_it)       ;
                if (!find)                        continue;
                if (!par->key->eq(find, par_key)) continue;

                return find_it;
            }

            return po_map_end(par);
}

bool_t    
    po_map_empty
        (po_map* par)                                    {
            if (!par)                      return false_t;
            if (trait_of(par) != po_map_t) return false_t;

            return po_list_empty(&par->map);
}

po_map_elem* 
    po_map_begin
        (po_map* par)                              {
            if (!par)                      return 0;
            if (trait_of(par) != po_map_t) return 0;

            return po_list_begin(&par->map);
}

po_map_elem* 
    po_map_end
        (po_map* par)                              {
            if (!par)                      return 0;
            if (trait_of(par) != po_map_t) return 0;

            return po_list_end(&par->map);
}

po_map_elem*
    po_map_next
        (po_map_elem* par)                         {
            if (!par)                      return 0;
            if (trait_of(par) != po_map_t) return 0;

            return po_list_next(par);
}
po_map_elem*
    po_map_prev
        (po_map_elem* par)                         {
            if (!par)                      return 0;
            if (trait_of(par) != po_map_t) return 0;

            return po_list_prev(par);
}

po_obj*
    po_map_get
        (po_map_elem* par)         {
            return po_list_get(par);
}

#ifdef PO_PRESET_LINUX
#include <linux/module.h>

EXPORT_SYMBOL (po_map_push) ;
EXPORT_SYMBOL (po_map_pop)  ;
EXPORT_SYMBOL (po_map_find) ;

EXPORT_SYMBOL (po_map_empty);
EXPORT_SYMBOL (po_map_begin);
EXPORT_SYMBOL (po_map_end)  ;
EXPORT_SYMBOL (po_map_next) ;
EXPORT_SYMBOL (po_map_prev) ;

EXPORT_SYMBOL (po_map_get)  ;
EXPORT_SYMBOL (po_map_t)    ;
MODULE_LICENSE("GPL")       ;
#endif