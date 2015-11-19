/*
  Copyright (C) 2015  ABRT team

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/
#ifndef ABRT_PROBLEMS2_ENTRY_NODE_H
#define ABRT_PROBLEMS2_ENTRY_NODE_H

#include "libabrt.h"

#include <gio/gio.h>

struct p2e_node;

struct p2e_node *abrt_problems2_entry_node_new(char *dirname);
int  abrt_problems2_entry_node_remove(struct p2e_node *entry, uid_t caller_uid, GError **error);
void abrt_problems2_entry_node_free(struct p2e_node *entry);
int abrt_problems2_entry_node_accessible_by_uid(struct p2e_node *entry, uid_t uid, struct dump_dir **dd);
problem_data_t *abrt_problems2_entry_node_problem_data(struct p2e_node *node, uid_t caller_uid, GError **error);

GDBusInterfaceVTable *abrt_problems2_entry_node_vtable(void);


/*
 * Utility functions
 */
enum p2e_save_elements_flags
{
    P2E_IO_ERROR_FATAL             = (1 << 0),
    P2E_UNSUPPORTED_ERROR_FATAL    = (1 << 1),
    P2E_ELEMENTS_COUNT_LIMIT_FATAL = (1 << 2),
    P2E_DATA_SIZE_LIMIT_FATAL      = (1 << 3),

    P2E_ALL_FATAL =(  P2E_IO_ERROR_FATAL
                    | P2E_UNSUPPORTED_ERROR_FATAL
                    | P2E_ELEMENTS_COUNT_LIMIT_FATAL
                    | P2E_DATA_SIZE_LIMIT_FATAL),
};

int abrt_problems2_entry_save_elements(struct dump_dir *dd, gint32 flags,
        GVariant *elements, GUnixFDList *fd_list, uid_t caller_uid, GError **error);

enum p2e_read_elements_flags
{
    P2E_READ_ALL_FD             = 0x01,
    P2E_READ_ALL_TYPES          = 0x02,
    P2E_READ_ONLY_TEXT          = 0x04,
    P2E_READ_ONLY_BIG_TEXT      = 0x08,
    P2E_READ_ONLY_BINARY        = 0x10,
    P2E_READ_ALL_NO_FD          = 0x20,
};

#endif/*ABRT_PROBLEMS2_ENTRY_NODE_H*/
