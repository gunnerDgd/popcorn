#include "chr.h"
#include "../dev/dev.h"

po_chr*
    po_chr_from_dev
        (struct po_dev* par)                               {
            if (po_trait_of(par) != po_dev_t) return null_t;
            if (!par->dev)                    return null_t;
            if (!par->dev->driver_data)       return null_t;

            po_chr* ret = dev_get_drvdata(par->dev);
            if (po_trait_of(ret) != po_chr_t) return null_t;
            return ret;
}