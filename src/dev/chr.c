#include "chr.h"

po_str*
    po_chr_name
        (po_chr* par)                                 {
            if (!par)                      return NULL;
            if (trait_of(par) != po_chr_t) return NULL;
            return &par->name;
}