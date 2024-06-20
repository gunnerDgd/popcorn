#include <core.h>
#include <collections.h>
#include <thread.h>

#include <linux/module.h>

typedef struct num {
    po_obj head;
    int    num;
}   num;

bool_t num_new	(num* self, u32_t count, va_list arg) { self->num = va_arg(arg, u64_t); return true_t; }
bool_t num_clone(num* self, num*  clone)              { return true_t; }
bool_t num_ref  (num* self)                           { return true_t; }
void   num_del  (num* self)                           {                }

po_obj_trait num_trait = po_make_trait (
    num_new    ,
    num_clone  ,
    num_ref    ,
    num_del    ,
	sizeof(num),
	null_t
);

po_obj_trait *num_t = &num_trait;

u64_t sum = 0;

static void
    do_enq
        (po_scq* scq)                         {
            printk ("do_enq started\n");
            if (po_trait_of(scq) != po_scq_t) {
                printk ("WRONG SCQ\n");
                return;
            }

            for (u64_t i = 1 ; i <= 1000 ; ++i)      {
                num* enq = po_make (num) from (1, i);
                if (po_trait_of(enq) != num_t)      {
                    printk("Failed to Create num\n");
                    return;
                }

                po_enq(scq, (po_obj*) enq);
            }
}

static void
    do_enq_lock
        (po_scq* scq)                         {
            if (po_trait_of(scq) != po_scq_t) {
                printk ("WRONG SCQ\n");
                return;
            }

            printk ("do_enq started\n");
            for (u64_t i = 1 ; i <= 1000 ; ++i)      {
                num* enq = po_make (num) from (1, i);
                if (po_trait_of(enq) != num_t)      {
                    printk("Failed to Create num\n");
                    return;
                }

                po_enq_lock(scq, (po_obj*) enq);
            }
}

static void
    do_deq
        (po_scq* scq)                  {
            printk ("do_deq started\n");
            for (u64_t i = 1 ; i <= 1000 ; ++i) {
                num* enq = (num*) po_deq (scq);
                po_lock_add64(&sum, enq->num);
                po_del(enq);
            }
}

static void
    do_deq_lock
        (po_scq* scq)                  {
            printk ("do_deq started\n");
            for (u64_t i = 1 ; i <= 1000 ; ++i) {
                num* enq = (num*) po_deq_lock(scq);
                po_lock_add64(&sum, enq->num);
                po_del(enq);
            }
}

static int
    mod_init (void)                                         {
        po_scq *scq = po_make (po_scq) from (2, null_t, 256);
        po_task enq;
        po_task deq;
        po_thd  tenq[4];
        po_thd  tdeq[4];

        po_make_at(&enq, po_task) from (2, do_enq_lock, scq);
        po_make_at(&deq, po_task) from (2, do_deq_lock, scq);

        po_make_at (&tdeq[0], po_thd) from (2, "deq1", &deq);
        po_make_at (&tdeq[1], po_thd) from (2, "deq2", &deq);
        po_make_at (&tdeq[2], po_thd) from (2, "deq3", &deq);
        po_make_at (&tdeq[3], po_thd) from (2, "deq4", &deq);

        po_make_at (&tenq[0], po_thd) from (2, "enq1", &enq);
        po_make_at (&tenq[1], po_thd) from (2, "enq2", &enq);
        po_make_at (&tenq[2], po_thd) from (2, "enq3", &enq);
        po_make_at (&tenq[3], po_thd) from (2, "enq4", &enq);

        for (u64_t i = 0 ; i < 4 ; ++i) {
            po_del (&tenq[i]);
            po_del (&tdeq[i]);
        }

        printk ("SUM : %d\n", sum);
        return 0;
}

static void
    mod_exit (void)                   {
        po_info ("Goodbye Popcorn !!");
}

module_init(mod_init);
module_exit(mod_exit);

MODULE_LICENSE("GPL");