/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Authors: Simon Kuenzer <simon.kuenzer@neclab.eu>
 *          Fabrice Buoro <fabrice@tarides.com>
 *
 * Copyright (c) 2019, NEC Laboratories Europe GmbH, NEC Corporation.
 *               2024-2025, Tarides.
 *               All rights reserved.
*/

#include "netif.h"

// Size of the buffer area for uk_netbuf allocation
#define UKNETDEV_BUFLEN   2048


struct uk_netbuf *netdev_alloc_rx_netbuf(const struct netif *netif)
{
  struct uk_netbuf *netbuf = NULL;
  struct uk_alloc *alloc = netif->alloc;
  const size_t size = UKNETDEV_BUFLEN;
  const size_t align = netif->dev_info.ioalign;
  const size_t headroom = netif->dev_info.nb_encap_rx;
  const size_t priv_len = 0;

  netbuf = uk_netbuf_alloc_buf(alloc, size, align, headroom, priv_len, NULL);
  if (!netbuf) {
    return NULL;
  }
  netbuf->len = netbuf->buflen - headroom;
  return netbuf;
}

struct uk_netbuf *netdev_alloc_tx_netbuf(const struct netif *netif)
{
  struct uk_netbuf *netbuf = NULL;
  struct uk_alloc *alloc = netif->alloc;
  const size_t size = UKNETDEV_BUFLEN;
  const size_t align = netif->dev_info.ioalign;
  const size_t headroom = netif->dev_info.nb_encap_tx;
  const size_t priv_len = 0;

  netbuf = uk_netbuf_alloc_buf(alloc, size, align, headroom, priv_len, NULL);
  if (!netbuf) {
    return NULL;
  }
  return netbuf;
}
