/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Authors: Fabrice Buoro <fabrice@tarides.com>
 *
 * Copyright (c) 2024-2025, Tarides.
 *               All rights reserved.
*/

#include "result.h"

CAMLprim value alloc_result_ok(value v)
{
  CAMLparam1(v);
  CAMLlocal1(v_result);

  v_result = caml_alloc(1, 0);
  Store_field(v_result, 0, v);
  CAMLreturn(v_result);
}

CAMLprim value alloc_result_error(const char *msg)
{
  CAMLparam0();
  CAMLlocal2(v_result, v_error);

  v_error = caml_copy_string(msg);
  v_result = caml_alloc_1(1, v_error);
  CAMLreturn(v_result);
};
