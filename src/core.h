#ifndef CORE_H
#define CORE_H

#include "core/atom.h"
#include "core/bit.h"
#include "core/box.h"
#include "core/endian.h"
#include "core/fut.h"
#include "core/mem.h"
#include "core/obj.h"
#include "core/ops.h"
#include "core/print.h"
#include "core/macro.h"
#include "core/task.h"
#include "core/type.h"
#include "core/this.h"

extern pp_obj_trait *pp_t;
struct               pp  {
    pp_obj head;
};

extern struct pp pp;

#endif