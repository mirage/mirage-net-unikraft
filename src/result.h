/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Authors: Fabrice Buoro <fabrice@tarides.com>
 *
 * Copyright (c) 2024-2025, Tarides.
 *               All rights reserved.
*/

#ifndef RESULT_H
#define RESULT_H

#define CAML_NAME_SPACE
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/alloc.h>

CAMLprim value alloc_result_ok(value v);
CAMLprim value alloc_result_error(const char *msg);

#endif /* !RESULT_H */
