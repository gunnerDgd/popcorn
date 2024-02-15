#include "endian.h"
#include <linux/module.h>

#ifdef PRESET_ARCH_ENDIAN_LITTLE
u16_t
    po_be16(u16_t par)                                      {
        return ((par & 0xFF00) >> 8) | ((par & 0x00FF) << 8);
}

u32_t
    po_be32(u32_t par)                     {
        return ((par & 0xFF000000u) >> 24) |
               ((par & 0x00FF0000u) >> 8)  |
               ((par & 0x0000FF00u) << 8)  |
               ((par & 0x000000FFu) << 24);
}

u64_t
    po_be64(u64_t par)                               {
        return ((par & 0xFF00000000000000ull) >> 56) |
               ((par & 0x00FF000000000000ull) >> 40) |
               ((par & 0x0000FF0000000000ull) >> 24) |
               ((par & 0x000000FF00000000ull) >> 8)  |
               ((par & 0x00000000FF000000ull) << 8)  |
               ((par & 0x0000000000FF0000ull) << 24) |
               ((par & 0x000000000000FF00ull) << 40) |
               ((par & 0x00000000000000FFull) << 56);
}

u16_t po_le16(u16_t par) { return par; }
u32_t po_le32(u32_t par) { return par; }
u64_t po_le64(u64_t par) { return par; }

MODULE_LICENSE("GPL");
EXPORT_SYMBOL (po_be16);
EXPORT_SYMBOL (po_be32);
EXPORT_SYMBOL (po_be64);
EXPORT_SYMBOL (po_le16);
EXPORT_SYMBOL (po_le32);
EXPORT_SYMBOL (po_le64);
#endif