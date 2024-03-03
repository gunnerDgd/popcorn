#include "class.h"
#include "com.h"

struct po_com*
    po_com_class_root
        (void)                                                                            {
            po_com *root = po_com_root(); if (po_trait_of(root) != po_com_t) return null_t;
            cstr_t  name = cstr("class");

            po_com *ret  = po_com_sub_cstr (root, name);
            if (po_trait_of(ret) != po_com_t)          {
                po_del (root);
                return null_t;
            }

            po_del(root);
            return   ret;
}

struct po_com*
    po_com_class_cstr
        (cstr_t par)                                                                           {
            po_com *dir = po_com_class_root (); if (po_trait_of(dir) != po_com_t) return null_t;
            if (!par.str) return null_t;
            if (!par.len) return null_t;

            po_com* ret = po_com_sub_cstr(dir, par);
            if (po_trait_of(ret) != po_com_t)      {
                po_del  (dir);
                return null_t;
            }

            po_del(dir);
            return ret ;
}

struct po_com*
    po_com_class
        (po_str* par)                         {
            po_com *dir = po_com_class_root ();
            if (po_trait_of(dir) != po_com_t) return null_t;
            if (po_trait_of(par) != po_str_t) return null_t;

            po_com* ret = po_com_sub(dir, par);
            if (po_trait_of(ret) != po_com_t) {
                po_del  (dir);
                return null_t;
            }

            po_del(dir);
            return ret ;
}

struct po_com*
    po_com_class_dev_cstr
        (cstr_t par, cstr_t par_dev)                                                             {
            po_com *dir = po_com_class_cstr(par); if (po_trait_of(dir) != po_com_t) return null_t;
            if (!par_dev.str) return null_t;
            if (!par_dev.len) return null_t;

            po_com* ret = po_com_sub_cstr(dir, par_dev);
            if (po_trait_of(ret) != po_com_t)          {
                po_del  (dir);
                return null_t;
            }

            po_del(dir);
            return ret ;
}

struct po_com*
    po_com_class_dev
        (po_str* par, po_str* par_dev)     {
            po_com *dir = po_com_class(par);
            if (po_trait_of(dir)     != po_com_t) return null_t;
            if (po_trait_of(par_dev) != po_str_t) return null_t;

            po_com* ret = po_com_sub(dir, par_dev);
            if (po_trait_of(ret) != po_com_t)     {
                po_del  (dir);
                return null_t;
            }

            po_del(dir);
            return ret ;
}