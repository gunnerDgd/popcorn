#include <obj.h>
#include <str.h>
#include <print.h>

#include <dev/class.h>
#include <dev/dev.h>

#include <fs/chr/chr_type.h>
#include <fs/chr/chr.h>

#include <fs/file_type.h>
#include <fs/file.h>
#include <fs/write.h>
#include <fs/read.h>

typedef struct chr        {
    po_obj       head     ;
    po_class     cls      ;
    po_file_type file_type;
    po_chr_type  chr_type ;
    po_chr       chr      ;
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

bool_t
    chr_read
        (chr_file* par, po_read* par_read)                  {
            po_read_from(par_read, (u8_t*) "Hello World", 11);
            return true_t;
}

bool_t
    chr_write
        (chr_file* par, po_write* par_write)   {
            u8_t* dst = po_new(u8[64])         ;
            u64_t len = po_write_len(par_write);

            po_write_to (par_write, dst, len);
            po_err      ((const char*) dst)  ;
            return true_t;
}

po_file_ops chr_ops = po_make_file_ops (
    null_t   ,
    null_t   ,
    chr_read ,
    null_t   ,
    chr_write,
    null_t   ,
    null_t   ,
    null_t
);

po_obj_trait *mod_t = &chr_trait;

bool_t
    chr_new
        (chr* par_chr, u32_t par_count, va_list par)   {
            cstr_t name_class = cstr("hello_world")    ;
            cstr_t name       = cstr("hello_world_dev");

            if (!po_make_at(&par_chr->file_type, po_file_type) from (2, &chr_ops, &chr_file_trait))             goto new_err;
            if (!po_make_at(&par_chr->chr_type , po_chr_type)  from (3, cstr_as_va(name), &par_chr->file_type)) goto new_err;
            if (!po_make_at(&par_chr->cls      , po_class)     from (2, cstr_as_va(name_class)))                goto new_err;
            bool_t res = po_make_at(&par_chr->chr, po_chr)     from (
                4                 ,
                cstr_as_va(name)  ,
                &par_chr->cls     ,
                &par_chr->chr_type
            );

            if (!res) goto new_err;
            return true_t;
    new_err:
            po_del(&par_chr->cls)      ;
            po_del(&par_chr->file_type);
            po_del(&par_chr->chr_type) ;
            po_del(&par_chr->chr)      ;
            return false_t;
}

bool_t
    chr_clone
        (chr* par, chr* par_clone) {
            return false_t;
}

void
    chr_del
        (chr* par)                 {
            po_del(&par->cls)      ;
            po_del(&par->file_type);
            po_del(&par->chr_type) ;
            po_del(&par->chr)      ;
}

#ifdef PRESET_LINUX
#include <linux/module.h>
MODULE_LICENSE("GPL");
#endif