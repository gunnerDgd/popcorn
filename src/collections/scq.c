#include "scq.h"

static bool_t
    do_new
        (po_scq* self, u32_t count, va_list arg)                         {
            po_mem *mem = null_t; if (count > 0) mem = va_arg(arg, any_t);
            u32_t   num = 0;      if (count > 1) num = va_arg(arg, u32_t);

            if (po_trait_of(mem) != po_mem_t) mem = po_get_mem();
            if (po_trait_of(mem) != po_mem_t) return false_t;
            if (!num)                         return false_t;
            u64_t len = sizeof (any_t) * num;

            self->scq = po_mem_use (mem, null_t, len);
            self->mem = (po_mem*) po_ref(mem);
            self->num = num;
            self->sqe = 0;
            self->cqe = 0;

            if (!self->scq)   return false_t;
            po_mem_set(self->scq, 0x00, len);
            return true_t;
}

static bool_t
    do_clone
        (po_scq* self, po_scq* clone) {
            return false_t;
}

static void
    do_del
        (po_scq* self)                            {
            u64_t len = sizeof (any_t) * self->num;
            po_mem_free                           (
                self->mem,
                self->scq,
                len
            );
}

static po_obj_trait
    do_obj = po_make_trait (
        do_new        ,
        do_clone      ,
        null_t        ,
        do_del        ,
        sizeof(po_scq),
        null_t
);

po_obj_trait *po_scq_t = &do_obj;

bool_t
    po_enq_lock_try
        (po_scq* self, po_obj* enq)                          {
            if (po_trait_of(self) != po_scq_t) return false_t;
            if (po_trait_of(enq)  == null_t)   return false_t;
            u64_t  pos = self->sqe            ;
            u64_t  sqe = (pos + 1) % self->num;
            enq = po_ref(enq);

            if (sqe == self->cqe) goto err;
            if (!enq)             goto err;

            if    (po_lock_cas_ptr(&self->sqe, pos, sqe) != pos)   goto   err;
            while (po_lock_cas_ptr(&self->scq [pos], null_t, enq)) po_yield();
            return true_t;
    err:    po_del   (enq);
            po_yield    ();
            return false_t;

}

bool_t
    po_enq_lock
        (po_scq* self, po_obj* enq)                          {
            if (po_trait_of(self) != po_scq_t) return false_t;
            if (po_trait_of(enq)  == null_t)   return false_t;

            for ( ; !po_enq_lock_try(self, enq); po_yield());
            return true_t;
}

bool_t
    po_enq_try
        (po_scq* self, po_obj* enq)                          {
            if (po_trait_of(self) != po_scq_t) return false_t;
            if (po_trait_of(enq)  == null_t)   return false_t;
            u64_t pos = self->sqe            ;
            u64_t sqe = (pos + 1) % self->num;
            enq = po_ref(enq);

            if (sqe == self->cqe) goto err;
            if (!enq)             goto err;

            for ( ; self->scq[pos]; po_yield());
            self->scq[pos] = enq;
            self->sqe      = pos;
            return true_t;
    err:    po_del   (enq);
            po_yield    ();
            return false_t;
}

bool_t
    po_enq
        (po_scq* self, po_obj* enq)                          {
            if (po_trait_of(self) != po_scq_t) return false_t;
            if (po_trait_of(enq)  == null_t)   return false_t;

            for ( ; !po_enq_try(self, enq) ; po_yield());
            return true_t;
}

po_obj*
    po_deq_lock_try
        (po_scq* self)                                      {
            if (po_trait_of(self) != po_scq_t) return null_t;
            u64_t   pos = self->cqe            ;
            u64_t   cqe = (pos + 1) % self->num;
            po_obj *deq = self->scq[pos]       ;

            if    (pos == self->sqe) goto err;
            if    (!deq)             goto err;

            if    (po_lock_cas_ptr(&self->cqe, pos,  cqe) != pos) goto err;
            while (po_lock_cas_ptr(&self->scq [pos], deq, null_t) != deq) {
                deq = self->scq[pos];
                po_yield();
            }

            po_del(deq);
            return deq;
    err:    po_yield    ();
            return false_t;
}

po_obj*
    po_deq_lock
        (po_scq* self)                                      {
            if (po_trait_of(self) != po_scq_t) return null_t;
            po_obj*  ret;

            for ( ; !(ret = po_deq_lock_try(self)) ; po_yield());
            return ret;
}

po_obj*
    po_deq_try
        (po_scq* self)                                      {
            if (po_trait_of(self) != po_scq_t) return null_t;
            u64_t   pos = self->cqe            ;
            u64_t   cqe = (pos + 1) % self->num;
            po_obj *ret = self->scq[pos]       ;

            if (pos == self->sqe) return null_t;
            if (!ret)             return null_t;

            self->cqe = cqe;
            po_del(ret);
            return ret ;
}

po_obj*
    po_deq
        (po_scq* self)                                      {
            if (po_trait_of(self) != po_scq_t) return null_t;
            po_obj*  ret;

            for ( ; !(ret = po_deq_try(self)) ; po_yield());
            return   ret;
}

#ifdef PRESET_LINUX
#include <linux/module.h>

EXPORT_SYMBOL(po_scq_t);
EXPORT_SYMBOL(po_scq_empty);

EXPORT_SYMBOL(po_deq_lock_try);
EXPORT_SYMBOL(po_deq_lock);

EXPORT_SYMBOL(po_enq_lock_try);
EXPORT_SYMBOL(po_enq_lock);

EXPORT_SYMBOL(po_deq_try);
EXPORT_SYMBOL(po_deq);

EXPORT_SYMBOL(po_enq_try);
EXPORT_SYMBOL(po_enq);

MODULE_LICENSE("GPL");
#endif