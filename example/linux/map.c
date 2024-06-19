#include <core.h>
#include <collections.h>
#include <thread.h>

#include <linux/module.h>

typedef struct foo {
    po_obj head;
    int    num;
}   foo;

bool_t foo_new	(foo* self, u32_t count, va_list arg) { po_info("Object Created")         ; self->num = va_arg(arg, u64_t); return true_t; }
bool_t foo_clone(foo* self, foo*  clone)              { po_info("Object Created As Clone"); return true_t; }
bool_t foo_ref  (foo* self)                           { po_info("Object Referenced")      ; return true_t; }
void   foo_del  (foo* self)                           { po_info("Object Destroyed")       ; }

po_ord_t
    foo_ord_arg
        (foo* self, u64_t ops)                    {
	        if (self->num == ops) return po_ord_eq;
	        if (self->num <  ops) return po_ord_lt;
	        if (self->num >  ops) return po_ord_gt;
	        return po_ord_err;
}

po_ord_t
    foo_ord
        (foo* self, foo* ops)		                   {
	        if (self->num == ops->num) return po_ord_eq;
	        if (self->num <  ops->num) return po_ord_lt;
	        if (self->num >  ops->num) return po_ord_gt;
	        return po_ord_err;
}


po_ops_cmp foo_cmp = po_make_cmp_ops(foo_ord, foo_ord_arg);
po_obj_ops foo_ops = {
    .cmp = &foo_cmp
};

po_obj_trait foo_trait = po_make_trait (
    foo_new    ,
    foo_clone  ,
    foo_ref    ,
    foo_del    ,
	sizeof(foo),
	&foo_ops
);

po_obj_trait *foo_t = &foo_trait;

static int
    mod_init (void)                                          {
        po_map* fma  = (po_map*) po_make (po_map) from (0)   ;
    	foo   * foo1 = (foo*)    po_make (foo)    from (1, 0);
    	foo   * foo2 = (foo*)    po_make (foo)    from (1, 1);

        po_node* fno1 = po_map_move(fma, (po_obj*) foo1);
        po_node* fno2 = po_map_move(fma, (po_obj*) foo2);

    	foo* val1 = po_value_as(po_map_find(fma, (any_t) 0), foo*);
    	foo* val2 = po_value_as(po_map_find(fma, (any_t) 1), foo*);

    	printk("VAL1 : %d\n", (po_trait_of(val1) == foo_t) ? val1->num : -1);
    	printk("VAL2 : %d\n", (po_trait_of(val2) == foo_t) ? val2->num : -1);

    	po_del (fma);
        return 0;
}

static void
    mod_exit (void)                   {
        po_info ("Goodbye Popcorn !!");
}

module_init(mod_init)
module_exit(mod_exit)

MODULE_LICENSE("GPL");