#include "scq.h"

static bool_t
    do_new
        (pp_scq* self, u32_t count, va_list arg)                         {
            pp_mem *mem = null_t; if (count > 0) mem = va_arg(arg, any_t);
            u32_t   num = 0;      if (count > 1) num = va_arg(arg, u32_t);

            if (pp_trait_of(mem) != pp_mem_t) mem = pp_get_mem();
            if (pp_trait_of(mem) != pp_mem_t) return false_t;
            if (num < 16)                     return false_t;
            u64_t len = sizeof (any_t) * num;

            self->scq = pp_mem_use (mem, null_t, len);
            self->mem = (pp_mem*) pp_ref(mem);
            self->num = num;
            self->sqe = 0;
            self->cqe = 0;

            if (!self->scq)   return false_t;
            pp_mem_set(self->scq, 0x00, len);
            return true_t;
}

static bool_t
    do_clone
        (pp_scq* self, pp_scq* clone) {
            return false_t;
}

static void
    do_del
        (pp_scq* self)                            {
            u64_t len = sizeof (any_t) * self->num;
            pp_mem_free                           (
                self->mem,
                self->scq,
                len
            );
}

static pp_obj_trait
    do_obj = pp_make_trait (
        do_new        ,
        do_clone      ,
        null_t        ,
        do_del        ,
        sizeof(pp_scq),
        null_t
);

pp_obj_trait *pp_scq_t = &do_obj;

bool_t
    pp_scq_empty
        (pp_scq* self)                                      {
            if (pp_trait_of(self) != pp_scq_t) return true_t;
            if (self->sqe == self->cqe)        return true_t;
            return false_t;
}

bool_t
    pp_enq_lock_try
        (pp_scq* self, pp_obj* enq)                          {
            if (pp_trait_of(self) != pp_scq_t) return false_t;
            if (pp_trait_of(enq)  == null_t)   return false_t;
            u64_t  pos = self->sqe            ;
            u64_t  sqe = (pos + 1) % self->num;
            enq = pp_ref(enq);

            if (sqe == self->cqe) goto err;
            if (!enq)             goto err;

            if    (pp_lock_cas(&self->sqe, pos, sqe) != pos)   goto   err;
            while (pp_lock_cas(&self->scq [pos], null_t, enq)) pp_yield();
            return true_t;
    err:    pp_del   (enq);
            pp_yield    ();
            return false_t;

}

bool_t
    pp_enq_lock
        (pp_scq* self, pp_obj* enq)                          {
            if (pp_trait_of(self) != pp_scq_t) return false_t;
            if (pp_trait_of(enq)  == null_t)   return false_t;

            for ( ; !pp_enq_lock_try(self, enq); pp_yield());
            return true_t;
}

bool_t
    pp_enq_try
        (pp_scq* self, pp_obj* enq)                          {
            if (pp_trait_of(self) != pp_scq_t) return false_t;
            if (pp_trait_of(enq)  == null_t)   return false_t;
            u64_t pos = self->sqe            ;
            u64_t sqe = (pos + 1) % self->num;
            enq = pp_ref(enq);

            if (sqe == self->cqe) goto err;
            if (!enq)             goto err;

            for ( ; self->scq[pos]; pp_yield());
            self->scq[pos] = enq;
            self->sqe      = pos;
            return true_t;
    err:    pp_del   (enq);
            pp_yield    ();
            return false_t;
}

bool_t
    pp_enq
        (pp_scq* self, pp_obj* enq)                          {
            if (pp_trait_of(self) != pp_scq_t) return false_t;
            if (pp_trait_of(enq)  == null_t)   return false_t;

            for ( ; !pp_enq_try(self, enq) ; pp_yield());
            return true_t;
}

pp_obj*
    pp_deq_lock_try
        (pp_scq* self)                                      {
            if (pp_trait_of(self) != pp_scq_t) return null_t;
            u64_t   pos = self->cqe            ;
            u64_t   cqe = (pos + 1) % self->num;
            pp_obj *deq = self->scq[pos]       ;

            if    (pos == self->sqe) goto err;
            if    (!deq)             goto err;

            if    (pp_lock_cas(&self->cqe, pos,  cqe) != pos) goto err;
            while (pp_lock_cas(&self->scq [pos], deq, null_t) != deq) {
                deq = self->scq[pos];
                pp_yield();
            }

            pp_del(deq);
            return deq;
    err:    pp_yield    ();
            return false_t;
}

pp_obj*
    pp_deq_lock
        (pp_scq* self)                                      {
            if (pp_trait_of(self) != pp_scq_t) return null_t;
            pp_obj*  ret;

            for ( ; !(ret = pp_deq_lock_try(self)) ; pp_yield());
            return ret;
}

pp_obj*
    pp_deq_try
        (pp_scq* self)                                      {
            if (pp_trait_of(self) != pp_scq_t) return null_t;
            u64_t   pos = self->cqe            ;
            u64_t   cqe = (pos + 1) % self->num;
            pp_obj *ret = self->scq[pos]       ;

            if (pos == self->sqe) return null_t;
            if (!ret)             return null_t;

            self->cqe = cqe;
            pp_del(ret);
            return ret ;
}

pp_obj*
    pp_deq
        (pp_scq* self)                                      {
            if (pp_trait_of(self) != pp_scq_t) return null_t;
            pp_obj*  ret;

            for ( ; !(ret = pp_deq_try(self)) ; pp_yield());
            return   ret;
}

#ifdef PRESET_LINUX
#include <linux/module.h>

EXPORT_SYMBOL(pp_scq_t);
EXPORT_SYMBOL(pp_scq_empty);

EXPORT_SYMBOL(pp_deq_lock_try);
EXPORT_SYMBOL(pp_deq_lock);

EXPORT_SYMBOL(pp_enq_lock_try);
EXPORT_SYMBOL(pp_enq_lock);

EXPORT_SYMBOL(pp_deq_try);
EXPORT_SYMBOL(pp_deq);

EXPORT_SYMBOL(pp_enq_try);
EXPORT_SYMBOL(pp_enq);

MODULE_LICENSE("GPL");
#endif