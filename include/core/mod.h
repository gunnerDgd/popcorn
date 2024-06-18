#ifndef __MOD_H__
#define __MOD_H__

struct po_obj_trait;
struct po_obj      ;

struct po_mod                 {
    struct po_obj_trait *trait;
    struct po_obj       *mod  ;
};

bool_t po_mod_do_new(struct po_mod*);
void   po_mod_do_del(struct po_mod*);

#define po_dep(name) { (po_obj_trait*)name##_t, (po_obj*)&name },
#define po_use(...)               \
    bool_t po_mod_new()       {   \
        struct po_mod mod[] = {   \
            __VA_ARGS__           \
            { null_t, null_t }    \
        };                        \
        return po_mod_do_new(mod);\
    }                             \
                                  \
    void po_mod_del()           { \
        struct po_mod mod[] =   { \
            __VA_ARGS__           \
            { null_t, null_t }    \
        };                        \
        po_mod_do_del(mod);       \
    }

#endif
