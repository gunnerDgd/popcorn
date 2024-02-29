#include <obj.h>
#include <str.h>
#include <print.h>

#include <dev/class.h>

#include <dev/chr/chr.h>
#include <dev/chr/dev.h>
#include <dev/chr/read.h>
#include <dev/chr/write.h>

typedef struct chr     {
    po_obj     head    ;
    po_str     name    ;
    po_str     cls_name;
    po_class   cls     ;
    po_chr_dev chr_dev ;
    po_chr     chr     ;
}   chr;

typedef struct chr_file {
    po_obj head;
    u64_t  file;
}   chr_file;

bool_t chr_new  (chr*, u32_t, va_list);
bool_t chr_clone(chr*, chr*)          ;
void   chr_del  (chr*)                ;

po_obj_trait chr_file_trait = po_make_trait (
        null_t          ,
        null_t          ,
        null_t          ,
        null_t          ,
        sizeof(chr_file),
        null_t
);

po_obj_trait chr_trait = po_make_trait (
        chr_new    ,
        chr_clone  ,
        null_t     ,
        chr_del    ,
        sizeof(chr),
        null_t
);

bool_t chr_read (chr_file* par, po_chr_read* par_read)  {
    po_chr_read_src(par_read, (u8_t*) "Hello World", 11);
    return true_t;
}

bool_t chr_write(chr_file* par, po_chr_write* par_write) {
    u8_t* dst = po_new(u8[64])             ;
    u64_t len = po_chr_write_len(par_write);

    po_chr_write_dest(par_write, dst, len);
    po_err           ((const char*) dst)  ;
    return true_t;
}

po_chr_ops chr_ops = po_make_chr_ops (
    chr_read ,
    chr_write,
    null_t   ,
    null_t
);

po_obj_trait *mod_t = &chr_trait;

bool_t
    chr_new
        (chr* par_chr, u32_t par_count, va_list par)                          {
            if(!po_make_at(&par_chr->name    , po_str) from(0)) return false_t;
            if(!po_make_at(&par_chr->cls_name, po_str) from(0)) return false_t;

            cstr_t name_class = cstr("hello_world")    ;
            cstr_t name       = cstr("hello_world_dev");
            po_str_push_back_cstr(&par_chr->cls_name, name_class);
            po_str_push_back_cstr(&par_chr->name    , name)      ;

            if (!po_make_at(&par_chr->chr, po_chr)   from (1, &par_chr->name)) {
                po_err("Failed To Create Character Device Region");
                goto new_err;
            }

            if (!po_make_at(&par_chr->cls, po_class) from (1, &par_chr->cls_name)) {
                po_err("Failed to Create Device Class");
                goto new_err;
            }

            bool_t res = po_make_at(&par_chr->chr_dev, po_chr_dev) from (
                6              ,
                &par_chr->name ,
                &par_chr->cls  ,
                &par_chr->chr  ,
                &chr_file_trait,
                &chr_ops       ,
                0ull
            );

            if (!res)                            {
                po_err("Failed to Create Device");
                goto new_err;
            }

            po_info("Hello Device !!");
            return true_t;
    new_err:
            po_del(&par_chr->cls_name);
            po_del(&par_chr->name)    ;
            po_del(&par_chr->cls)     ;
            po_del(&par_chr->chr_dev) ;
            po_del(&par_chr->chr)     ;
            return false_t;
}

bool_t
    chr_clone
        (chr* par, chr* par_clone) {
            return false_t;
}

void
    chr_del
        (chr* par)                {
            po_del(&par->chr_dev) ;
            po_del(&par->cls)     ;

            po_del(&par->cls_name);
            po_del(&par->name)    ;

            po_del(&par->chr)     ;
}

#ifdef PRESET_LINUX
#include <linux/module.h>
MODULE_LICENSE("GPL");
#endif