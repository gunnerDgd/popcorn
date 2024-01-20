#include <linux/module.h>

#include <popcorn/core.h>
#include <popcorn/dev.h>

#include <linux/slab.h>

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

void* po_heap_new(po_mem* par, u64_t par_size) { return kmalloc(par_size, GFP_KERNEL); }
void  po_heap_del(po_mem* par, void* par_mem)  { kfree(par_mem); }

po_mem po_heap =            {
    .on_new    = po_heap_new,
    .on_del    = po_heap_del
};

po_chr     dev_type;
po_ns      dev_ns  ;
po_chr_dev dev     ;

static int
    __init mod_new(void)                                 {
        po_set_mem(&po_heap)                             ;
        dev_type = make (po_chr_t) from (1, "TestDevice");
        dev_ns   = make (po_ns_t)  from (1, "TestClass") ;
        dev      = po_chr_dev_new("Test", dev_ns, dev_type, &ops, NULL);

        printk("Hello Module!!\n")           ;
        printk("dev_type : %08x\n", dev_type);
        printk("dev_ns : %08x\n"  , dev_ns)  ;
        printk("dev : %08x\n"     , dev)     ;

        return 0;
}

static void
    __exit mod_del(void)            {
        printk("Goodbye Module!!\n");
        po_chr_dev_del(dev);
        del(dev_type);
        del(dev_ns)  ;
}

module_init   (mod_new);
module_exit   (mod_del);
MODULE_LICENSE("GPL");