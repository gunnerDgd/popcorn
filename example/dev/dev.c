#include <linux/module.h>

#include <popcorn/core.h>
#include <popcorn/dev.h>

bool_t mod_do_new    (po_obj* par) { printk("New Module !!\n")        ; return true_t; }
bool_t mod_do_ref    (po_obj* par) { printk("Module Have Friend !!\n"); return true_t; }
void   mod_do_del    (po_obj* par) { printk("Goodbye Module !!\n")    ; }

i64_t  mod_do_read   (po_obj* par, po_buf par_buf)                 { printk("Read\n")   ; return po_buf_size(par_buf); }
i64_t  mod_do_write  (po_obj* par, po_buf par_buf)                 { printk("Write\n")  ; return po_buf_size(par_buf); }
i64_t  mod_do_control(po_obj* par, u32_t  par_code, void* par_arg) { printk("Control\n"); return 0                   ; }

po_dev_ops ops  =               {
    .on_new     = mod_do_new    ,
    .on_ref     = mod_do_ref    ,
    .on_del     = mod_do_del    ,

    .on_read    = mod_do_read   ,
    .on_write   = mod_do_write  ,
    .on_control = mod_do_control
};

po_dev_type dev_type;
po_dev      dev     ;

static int
    __init init_module() {
        dev_type = make (po_dev_type_t) from (1, "TestDevice");
        dev      = po_new_dev("Test", dev_type, &ops, 0);
        printk("Hello Module!!\n");
}

static int
    __exit exit_module()    {
        po_del_dev(dev)     ;
        del       (dev_type);
}