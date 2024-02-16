#include "chr.h"
#include "dev.h"

#include "bit.h"

#include <linux/vmalloc.h>

static int
    po_chr_dev_do_open
        (struct inode* par, struct file* par_file)                      {
            po_chr_dev *dev = container_of(par->i_cdev, po_chr_dev, chr);
            po_chr     *chr = container_of(par->i_fop , po_chr    , ops);
            if (po_trait_of(dev) != po_chr_dev_t) return -EINVAL;
            if (po_trait_of(chr) != po_chr_t)     return -EINVAL;
            par_file->private_data = po_obj_new                 (
                null_t    ,
                dev->trait,
                2         ,
                chr       ,
                dev
            );

            if (!par_file->private_data) return -EINVAL;
            po_ref(dev);
            po_ref(chr);
            return 0;
}

static int
    po_chr_dev_do_close
        (struct inode* par, struct file* par_file)                      {
            po_chr_dev *dev = container_of(par->i_cdev, po_chr_dev, chr);
            po_chr     *chr = container_of(par->i_fop , po_chr    , ops);
            if (po_trait_of(dev) != po_chr_dev_t) return -EINVAL;
            if (po_trait_of(chr) != po_chr_t)     return -EINVAL;
            po_del(par_file->private_data);
            po_del(dev);
            po_del(chr);
            return 0;
}

static ssize_t
    po_chr_dev_do_read
        (struct file* par, __user char* par_buf, size_t par_len, loff_t* par_off) {

}

static ssize_t
    po_chr_dev_do_write
        (struct file* par, __user const char* par_buf, size_t par_len, loff_t* par_off) {

}

po_obj_trait po_chr_trait = po_make_trait (
    po_chr_new    ,
    po_chr_clone  ,
    null_t        ,
    po_chr_del    ,
    sizeof(po_chr),
    null_t
);

po_obj_trait *po_chr_t = &po_chr_trait;

bool_t
    po_chr_new
        (po_chr* par_chr, u32_t par_count, va_list par)                              {
            po_str* name = null_t    ; if (par_count > 0) name = va_arg(par, po_str*);
            u64_t   maj  = 0         ; if (par_count > 1) maj  = va_arg(par, u64_t)  ;
            u64_t   min  = shl(1, 19); if (par_count > 2) min  = va_arg(par, u64_t)  ;
            if (po_trait_of(name) != po_str_t)                                         goto new_err;
            if (!po_make_at(&par_chr->name, po_str) from (0))                          goto new_err;
            if (!po_make_at(&par_chr->dev , po_set) from (0))                          goto new_err;
            if (alloc_chrdev_region(&par_chr->maj, maj, min, po_str_as_raw(name)) < 0) goto new_err;
            par_chr->ops.open    = po_chr_dev_do_open ;
            par_chr->ops.release = po_chr_dev_do_close;
            par_chr->ops.read    = po_chr_dev_do_read ;
            par_chr->ops.write   = po_chr_dev_do_write;
            po_str_push_back(&par_chr->name, name);
            par_chr->num = 0;
            return true_t   ;
    new_err:
            po_del(&par_chr->name);
            po_del(&par_chr->dev) ;
            return false_t;
}

bool_t
    po_chr_clone
        (po_chr* par, po_chr* par_clone)  {
            return false_t;
}

void
    po_chr_del
        (po_chr* par)                                      {
            unregister_chrdev_region(par->maj, shl (1, 19));
            po_del(&par->name);
            po_del(&par->dev) ;
}

MODULE_LICENSE("GPL");