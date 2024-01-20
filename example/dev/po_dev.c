#include <linux/module.h>

#include <popcorn/core.h>
#include <popcorn/dev.h>

bool_t mod_do_new    (po_obj* par) { printk("New Module !!\n")        ; return true_t; }
bool_t mod_do_open   (po_obj* par) { printk("Opened Module !!\n")     ; return true_t; }
void   mod_do_close  (po_obj* par) { printk("Closed Module !!\n")     ; }
void   mod_do_del    (po_obj* par) { printk("Goodbye Module !!\n")    ; }

i64_t  mod_do_read   (po_obj* par, po_ubuf par_buf)                { printk("Read\n")  ; return po_ubuf_size(par_buf); }
i64_t  mod_do_write  (po_obj* par, po_ubuf par_buf)                { printk("Write\n") ; return po_ubuf_size(par_buf); }
i64_t  mod_do_control(po_obj* par, u32_t  par_code, void* par_arg) { printk("Control\n"); return 0                   ; }

po_dev_ops ops  =               {
    .on_new     = mod_do_new    ,
    .on_open    = mod_do_open   ,
    .on_close   = mod_do_close  ,
    .on_del     = mod_do_del    ,

    .on_read    = mod_do_read   ,
    .on_write   = mod_do_write  ,
    .on_control = mod_do_control
};

po_chr     dev_type;
po_ns      dev_ns  ;
po_chr_dev dev     ;

int
    po_start(void)                                                             {
        dev_ns   = make (po_ns_t)      from (1, "TestClass")                   ;
        dev_type = make (po_chr_t)     from (1, "TestDevice")                  ;
        dev      = make (po_chr_dev_t) from (4, "Test", dev_ns, dev_type, &ops);

        printk("Hello Module!!\n")           ;
        printk("dev_type : %08x\n", dev_type);
        printk("dev_ns : %08x\n"  , dev_ns)  ;
        printk("dev : %08x\n"     , dev)     ;

        return 0;
}

void
    po_end(void)                    {
        printk("Goodbye Module!!\n");
        del(dev)     ;
        del(dev_type);
        del(dev_ns)  ;
}