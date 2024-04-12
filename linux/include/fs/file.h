#ifndef __PO_FS_FILE_H__
#define __PO_FS_FILE_H__

#include <core.h>

struct po_file_type;

extern po_obj_trait *po_file_t;
typedef struct       po_file  { u8_t po_file[64]; } po_file;

#endif