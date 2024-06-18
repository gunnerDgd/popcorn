#include <core.h>
#include <collections.h>
#include <thread.h>

#include <linux/module.h>

static any_t
    do_run(any_t arg)      {
        po_info("Thread\n");
        return null_t;
}

po_str name;

static int
    mod_init (void)                {
        po_info("Hello Popcorn !!");

        po_task *task = po_make (po_task) from (1, do_run);
        po_thd  *thd  = po_make (po_thd)  from (
            2    ,
            "thd",
            task
        );

        po_await(po_thd_fut(thd));
        po_del(&name);
        po_del(task);
        po_del(thd);
        return 0;
}

static void
    mod_exit (void)                   {
        po_info ("Goodbye Popcorn !!");
}

module_init(mod_init)
module_exit(mod_exit)

MODULE_LICENSE("GPL");