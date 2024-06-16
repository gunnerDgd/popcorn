#include <linux/string.h>
#include <linux/module.h>

#include "../mem.h"

void
    po_mem_set
        (void* des, u8_t set, u64_t len) {
            if (!len) return;
            if (!des) return;

            memset(des, set, len);
}

void
    po_mem_copy
        (void* des, void* src, u64_t len) {
            if (!des) return;
            if (!src) return;
            if (!len) return;

            memcpy(des, src, len);
}

void
    po_mem_move
        (void* des, void* src, u64_t len) {
            if (!des) return;
            if (!src) return;
            if (!len) return;

            memmove(des, src, len);
}

u64_t
    po_mem_find
        (void* des, void* src, u64_t dlen, u64_t slen) {
            if (dlen > slen) return -1;
            return (u64_t) strstr     (
                des,
                src
            );
}

po_ord_t
    po_mem_ord
        (void* des, void* ord, u64_t len) {
            if (!des) return po_ord_err;
            if (!ord) return po_ord_err;
            if (!len) return po_ord_err;

            int ret = memcmp (des, ord, len);
            if (ret < 0) return po_ord_lt;
            if (ret > 0) return po_ord_gt;
            return po_ord_eq;
}

bool_t po_mem_eq(void* des, void* ord, u64_t len) { return po_mem_ord(des, ord,len) == po_ord_eq; }
bool_t po_mem_gt(void* des, void* ord, u64_t len) { return po_mem_ord(des, ord,len) == po_ord_gt; }
bool_t po_mem_lt(void* des, void* ord, u64_t len) { return po_mem_ord(des, ord,len) == po_ord_lt; }

static po_mem *mem;

po_mem*
    po_get_mem()  {
        return mem;
}

po_mem*
    po_set_mem
        (po_mem* set)                                      {
            if (po_trait_of(set) != po_mem_t) return null_t;
            po_mem* ret = mem;
            mem   = set;
            return  ret;
}

EXPORT_SYMBOL(po_mem_eq);
EXPORT_SYMBOL(po_mem_gt);
EXPORT_SYMBOL(po_mem_lt);

EXPORT_SYMBOL(po_mem_set);
EXPORT_SYMBOL(po_mem_copy);
EXPORT_SYMBOL(po_mem_move);
EXPORT_SYMBOL(po_mem_find);

EXPORT_SYMBOL(po_get_mem);
EXPORT_SYMBOL(po_set_mem);