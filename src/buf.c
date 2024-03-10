#include "buf.h"
#include <linux/uaccess.h>

po_buf_vec*
    po_buf_vec_from_user
        (u8_t* par, u64_t par_len, po_mem* par_mem) {
            if (!par_mem) par_mem = po_get_mem();
            if (!par_mem) return null_t;
            if (!par_len) return null_t;
            if (!par)     return null_t;

            po_buf_vec* ret = po_new(po_buf_vec); if (!ret) return null_t;
            ret->head.trait = po_buf_vec_t;
            ret->head.mem   = po_get_mem();
            ret->head.ref   = 1           ;

            ret->mem = par_mem;
            ret->off = 0      ;

            ret->buf = po_mem_new(par_mem, par_len)                    ; if (ret->buf == 0)       goto new_err;
            ret->len = par_len - copy_from_user(ret->buf, par, par_len); if (ret->len != par_len) goto new_err;
            return ret;
    new_err:
            po_drop(ret->buf);
            po_drop(ret)     ;
            return null_t;
}

po_buf_vec*
    po_buf_vec_from
        (u8_t* par, u64_t par_len)     {
            if (!par_len) return null_t;
            if (!par)     return null_t;

            po_buf_vec* ret = po_new(po_buf_vec); if (!ret) return null_t;
            ret->head.trait = po_buf_vec_t;
            ret->head.mem   = po_get_mem();
            ret->head.ref   = 1           ;

            ret->len = par_len;
            ret->buf = par    ;

            ret->mem = null_t;
            ret->off = 0     ;
            return ret;

}

bool_t po_buf_vec_new  (po_buf_vec* par_buf, u32_t par_count, va_list par) { return false_t; }
bool_t po_buf_vec_clone(po_buf_vec* par, po_buf_vec* par_clone)            { return false_t; }

void
    po_buf_vec_del
        (po_buf_vec* par)                               {
            if (par->mem) po_mem_del(par->mem, par->buf);
}

u64_t
    po_buf_vec_copy_user
        (po_buf_vec* par, u8_t* par_buf, u64_t par_len)   {
            if (po_trait_of(par) != po_buf_vec_t) return 0;
            if (!par_buf)                         return 0;
            if (!par_len)                         return 0;
            u64_t off = par->off      ;
            u64_t len = par->len - off;
            u8_t* buf = par->buf + off;

            if (par_len > len) par_len = len;
            u64_t ret = copy_to_user        (
                par_buf,
                buf    ,
                par_len
            );

            par->off += (len - ret);
            return      (len - ret);
}

u64_t
    po_buf_vec_copy
        (po_buf_vec* par, u8_t* par_buf, u64_t par_len)   {
            if (po_trait_of(par) != po_buf_vec_t) return 0;
            if (!par_buf)                         return 0;
            if (!par_len)                         return 0;
            u64_t off = par->off      ;
            u64_t len = par->len - off;
            u8_t* buf = par->buf + off;

            if (par_len > len) par_len = len;
            po_mem_copy                     (
                par_buf,
                buf    ,
                par_len
            );

            par->off += par_len;
            return      par_len;
}

bool_t
    po_buf_vec_empty
        (po_buf_vec* par)                                      {
            if (po_trait_of(par) != po_buf_vec_t) return true_t;
            return par->off == par->len;
}

u64_t
    po_buf_vec_len
        (po_buf_vec* par)                                      {
            if (po_trait_of(par) != po_buf_vec_t) return true_t;
            return par->len - par->off;
}

po_obj_trait po_buf_vec_trait = po_make_trait (
    po_buf_vec_new    ,
    po_buf_vec_clone  ,
    null_t            ,
    po_buf_vec_del    ,
    sizeof(po_buf_vec),
    null_t
);

po_obj_trait *po_buf_vec_t = &po_buf_vec_trait;


bool_t po_buf_new  (po_buf* par_buf, u32_t par_count, va_list par) { return po_make_at(&par_buf->buf, po_list) from (0); }
bool_t po_buf_clone(po_buf* par, po_buf* par_clone)                { return false_t; }
void   po_buf_del  (po_buf* par)                                   { po_del(&par->buf); }

u64_t
    po_buf_copy_user
        (po_buf* par, u8_t* par_buf, u64_t par_len)   {
            if (po_trait_of(par) != po_buf_t) return 0;
            if (!par_buf)                     return 0;
            if (!par_len)                     return 0;
            u64_t off = 0;

            po_list_while(&par->buf, node)                              {
                po_node    *buf_node = node                             ;
                po_buf_vec *buf      = (po_buf_vec*) po_node_value(node);
                if (po_trait_of(buf_node) != po_node_t)    continue;
                if (po_trait_of(buf)      != po_buf_vec_t) continue;
                off += po_buf_vec_copy_user                        (
                    buf          ,
                    par_buf + off,
                    par_len - off
                );


                if (off == par_len)            return off;
                if (po_buf_vec_empty(buf))               {
                    node = po_node_next(buf_node, null_t);
                    po_del(buf_node);
                }
            }

            return off;
}

u64_t
    po_buf_copy
        (po_buf* par, u8_t* par_buf, u64_t par_len)   {
            if (po_trait_of(par) != po_buf_t) return 0;
            if (!par_buf)                     return 0;
            if (!par_len)                     return 0;
            u64_t off = 0;

            po_list_while(&par->buf, node)                              {
                po_node    *buf_node = node                             ;
                po_buf_vec *buf      = (po_buf_vec*) po_node_value(node);
                if (po_trait_of(buf_node) != po_node_t)    continue;
                if (po_trait_of(buf)      != po_buf_vec_t) continue;
                off += po_buf_vec_copy                             (
                    buf          ,
                    par_buf + off,
                    par_len - off
                );


                if (off == par_len)            return off;
                if (po_buf_vec_empty(buf))               {
                    node = po_node_next(buf_node, null_t);
                    po_del(buf_node);
                }
            }

            return off;
}

void
    po_buf_push
        (po_buf* par, po_buf_vec* par_vec)                  {
            if (po_trait_of(par_vec) != po_buf_vec_t) return;
            if (po_trait_of(par)     != po_buf_t)     return;
            po_list_push_back(&par->buf, (po_obj*) par_vec);
}

po_buf_vec*
    po_buf_pop
        (po_buf* par)                                      {
            if (po_trait_of(par) != po_buf_t) return null_t;
            if (po_list_empty(&par->buf))     return null_t;

            po_buf_vec* ret = (po_buf_vec*) po_list_pop_front(&par->buf);
            if (po_trait_of(ret) != po_buf_vec_t) return null_t;
            return ret;
}

po_obj_trait po_buf_trait = po_make_trait (
    po_buf_new    ,
    po_buf_clone  ,
    null_t        ,
    po_buf_del    ,
    sizeof(po_buf),
    null_t
);

po_obj_trait *po_buf_t = &po_buf_trait;