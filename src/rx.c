/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Authors: Simon Kuenzer <simon.kuenzer@neclab.eu>
 *          Fabrice Buoro <fabrice@tarides.com>
 *
 * Copyright (c) 2019, NEC Laboratories Europe GmbH, NEC Corporation.
 *               2024-2025, Tarides.
 *               All rights reserved.
*/

#ifdef __Unikraft__

#include "netif.h"
#include "result.h"

#include <string.h>
#include <caml/bigarray.h>

#include <yield.h> /* provided by mirage-unikraft */

uint16_t netdev_alloc_rxpkts(void *argp, struct uk_netbuf *nb[], uint16_t count)
{
  struct netif *netif = (struct netif*)argp;
  uint16_t i;

  for (i = 0; i < count; ++i) {
    nb[i] = netdev_alloc_rx_netbuf(netif);
    if (!nb[i]) {
      /* we run out of memory */
      break;
    }
  }
  return i;
}

/* Returns
* -1 on error
*  0 on success
*  1 on success and more to process
*/
static int netdev_rx(struct netif* netif, uint8_t *buf, unsigned *size,
        const char **err)
{
  struct uk_netdev *dev = netif->dev;
  struct uk_netbuf *nb;
  unsigned bufsize = *size;

  *size = 0;

  const int rc = uk_netdev_rx_one(dev, 0, &nb);
  if (rc < 0) {
    *err = "Failed to receive a packet";
    return -1;
  }

  if (!uk_netdev_status_successful(rc)) {
    *err = "No packet received";
    return 0;
  }

  const bool more = uk_netdev_status_more(rc);

  /* If bufsize < nb->len, simply drop the extra trailing bytes, as they cannot
   * be part of the packet payload or it would exceed MTU; so define len, the
   * number of bytes to copy, to be the minimum of bufsize and nb->len */
  const unsigned len = (bufsize < nb->len) ? bufsize : nb->len;
  memcpy(buf, nb->data, len);
  *size = len;
  uk_netbuf_free_single(nb);

  return (more ? 1 : 0);
}

CAMLprim value uk_netdev_rx(value v_netif, value v_buf, value v_size)
{
  CAMLparam3(v_netif, v_buf, v_size);
  CAMLlocal1(v_result);

  struct netif *netif = (struct netif*)Ptr_val(v_netif);
  uint8_t *buf = (uint8_t *)Caml_ba_data_val(v_buf);
  unsigned size = Int_val(v_size);
  const char *err = NULL;

  const int rc = netdev_rx(netif, buf, &size, &err);
  if (rc < 0) {
    v_result = alloc_result_error(err);
    CAMLreturn(v_result);
  }

  if (rc > 0) {
    /* No-op: there is more to dequeue, keep the ready flag up */
  }
  else {
    set_netdev_queue_empty(netif->id);
  }

  v_result = alloc_result_ok(Val_int(size));
  CAMLreturn(v_result);
}

#endif /* __Unikraft__ */
