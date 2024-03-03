#include "bus.h"
#include "com.h"

po_com*
    po_com_bus_root(void)                                                             {
        po_com *root = po_com_root(); if (po_trait_of(root) != po_com_t) return null_t;
        cstr_t  name = cstr("bus");

        po_com *ret  = po_com_sub_cstr (root, name);
        if (po_trait_of(ret) != po_com_t)          {
            po_del (root);
            return null_t;
        }

        po_del(root);
        return   ret;
}

po_com*
    po_com_bus_cstr
        (cstr_t par)                                                                        {
            po_com *dir = po_com_bus_root(); if (po_trait_of(dir) != po_com_t) return null_t;
            if (!par.str) return null_t;
            if (!par.len) return null_t;

            po_com *ret = po_com_sub_cstr(dir, par);
            if (po_trait_of(ret) != po_com_t)      {
                po_del  (dir);
                return null_t;
            }

            po_del(dir);
            return ret ;
}

po_com*
    po_com_bus
        (po_str* par)                      {
            po_com *dir = po_com_bus_root();
            if (po_trait_of(dir) != po_com_t) return null_t;
            if (po_trait_of(par) != po_str_t) return null_t;

            po_com *ret = po_com_sub(dir, par);
            if (po_trait_of(ret) != po_com_t) {
                po_del  (dir);
                return null_t;
            }

            po_del(dir);
            return ret ;
}

po_com*
    po_com_bus_dev_cstr
        (cstr_t par)                                                                            {
            po_com *dir  = po_com_bus_cstr(par); if (po_trait_of(dir) != po_com_t) return null_t;
            cstr_t  name = cstr("devices")     ;

            po_com *ret = po_com_sub_cstr(dir, name);
            if (po_trait_of(ret) != po_com_t)       {
                po_del  (dir);
                return null_t;
            }

            po_del(dir);
            return ret ;
}

po_com*
    po_com_bus_dev
        (po_str* par)                                                                      {
            po_com *dir  = po_com_bus(par); if (po_trait_of(dir) != po_com_t) return null_t;
            cstr_t  name = cstr("devices");

            po_com *ret = po_com_sub_cstr(dir, name);
            if (po_trait_of(ret) != po_com_t)       {
                po_del  (dir);
                return null_t;
            }

            po_del(dir);
            return ret ;
}

po_com*
    po_com_bus_drv_cstr
        (cstr_t par)                                                                            {
            po_com *dir  = po_com_bus_cstr(par); if (po_trait_of(dir) != po_com_t) return null_t;
            cstr_t  name = cstr("drivers")     ;

            po_com *ret = po_com_sub_cstr(dir, name);
            if (po_trait_of(ret) != po_com_t)       {
                po_del  (dir);
                return null_t;
            }

            po_del(dir);
            return ret ;
}

po_com*
    po_com_bus_drv
        (po_str* par)                                                                      {
            po_com *dir  = po_com_bus(par); if (po_trait_of(dir) != po_com_t) return null_t;
            cstr_t  name = cstr("drivers");

            po_com *ret = po_com_sub_cstr(dir, name);
            if (po_trait_of(ret) != po_com_t)       {
                po_del  (dir);
                return null_t;
            }

            po_del(dir);
            return ret ;
}