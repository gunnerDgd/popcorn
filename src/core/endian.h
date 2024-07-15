#ifndef CORE_ENDIAN_H
#define CORE_ENDIAN_H

#include "type.h"

u16_t pp_be16(u16_t);
u32_t pp_be32(u32_t);
u64_t pp_be64(u64_t);

u16_t pp_le16(u16_t);
u32_t pp_le32(u32_t);
u64_t pp_le64(u64_t);

#endif