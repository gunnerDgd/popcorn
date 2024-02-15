#ifndef __ENDIAN_H__
#define __ENDIAN_H__

#include "type.h"

u16_t po_be16(u16_t);
u32_t po_be32(u32_t);
u64_t po_be64(u64_t);

u16_t po_le16(u16_t);
u32_t po_le32(u32_t);
u64_t po_le64(u64_t);

#endif