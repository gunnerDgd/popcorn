#ifndef __MOD_H__
#define __MOD_H__

#include "type.h"

struct po_obj_trait;
struct po_obj;

struct po_mod                 {
    struct po_obj_trait *trait;
    struct po_obj       *mod;
};

bool_t po_mod_new();
bool_t po_mod_del();

#endif
