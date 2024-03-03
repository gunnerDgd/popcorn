#include "com.h"

po_obj_trait po_com_trait = po_make_trait (
    po_com_new    ,
    po_com_clone  ,
    null_t        ,
    po_com_del    ,
    sizeof(po_com),
    null_t
);

po_obj_trait* po_com_t = &po_com_trait;

bool_t
    po_com_new
        (po_com* par_com, u32_t par_count, va_list par)                          {
            po_str *name = null_t; if (par_count > 0) name = va_arg(par, po_str*);
            po_com *sup  = null_t; if (par_count > 2) sup  = va_arg(par, po_com*);
            if (po_trait_of(name) != po_str_t) return false_t;
            if (po_trait_of(sup)  != po_com_t)                                         {
                par_com->com = kobject_create_and_add(po_str_as_raw(name), kernel_kobj);
                if (!par_com->com) return false_t;

                par_com->dir = par_com->com->sd;
                par_com->sup = null_t          ;
                return true_t;
            }

            par_com->com = kobject_create_and_add(po_str_as_raw(name), sup->com);
            if (!par_com->com) return false_t;

            par_com->sup = (po_com*) po_ref(sup);
            par_com->dir = par_com->com->sd;
            return true_t;
}

bool_t
    po_com_clone
        (po_com* par, po_com* par_clone) {
            return false_t;
}

void
    po_com_del
        (po_com* par)            {
            kobject_put(par->com);
            po_del     (par->sup);
}

po_com*
    po_com_root(void)                                        {
        po_com* ret = po_new(po_com); if (!ret) return null_t;
        ret->head.trait = po_com_t    ;
        ret->head.mem   = po_get_mem();
        ret->head.ref   = 1           ;

        ret->dir = kernel_kobj->sd->parent;
        ret->sup = null_t                 ;
        ret->com = null_t                 ;

        if (!ret->com && !ret->dir) {
            po_drop (ret);
            return null_t;
        }

        return ret;
}

struct po_com*
    po_com_sub_cstr
        (po_com* par, cstr_t par_name)                     {
            if (po_trait_of(par) != po_com_t) return null_t;
            if (!par_name.str)                return null_t;
            if (!par_name.len)                return null_t;

            struct kernfs_node *dir = kernfs_find_and_get(par->dir, par_name.str); if (!dir) return null_t;
            po_com             *ret = po_new(po_com)                             ; if (!ret) return null_t;
            ret->head.trait = po_com_t    ;
            ret->head.ref   = 1           ;
            ret->head.mem   = po_get_mem();

            ret->sup = null_t   ;
            ret->dir = dir      ;
            ret->com = dir->priv;
            return ret;
}

po_com*
    po_com_sub
        (po_com* par, po_str* par_name)                         {
            if (po_trait_of(par)      != po_com_t) return null_t;
            if (po_trait_of(par_name) != po_str_t) return null_t;

            cstr_t name          = { .str = po_str_as_raw(par_name), .len = po_str_len(par_name) };
            return po_com_sub_cstr (
                par,
                name
            );
}

po_com*
    po_com_sup
        (po_com* par)                                      {
            if (po_trait_of(par) != po_com_t) return null_t;

            po_com* ret = po_new(po_com)  ; if (!ret) return null_t;
            ret->head.trait = po_com_t    ;
            ret->head.mem   = po_get_mem();
            ret->head.ref   = 1           ;

            if (!par->sup)                              {
                ret->com = kobject_get(par->com->parent);
                if (!ret->com) return null_t;

                ret->dir = ret->com->sd;
                return ret;
            }

            ret->com = kobject_get(par->sup->com);
            ret->dir = ret->com->sd;
            ret->sup = null_t      ;
            return ret;
}