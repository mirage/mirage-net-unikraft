/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Authors: Simon Kuenzer <simon.kuenzer@neclab.eu>
 *          Fabrice Buoro <fabrice@tarides.com>
 *
 * Copyright (c) 2019, NEC Laboratories Europe GmbH, NEC Corporation.
 *               2024-2025, Tarides.
 *               All rights reserved.
*/

#ifndef NETIF_H
#define NETIF_H

#include <uk/netdev.h>
#include <uk/assert.h>
#include <uk/print.h>


struct netif {
  struct uk_netdev      *dev;
  struct uk_alloc       *alloc;
  struct uk_netdev_info dev_info;
  unsigned              id;
};

/* netbuf.c */
struct uk_netbuf *netdev_alloc_rx_netbuf(const struct netif *netif);
struct uk_netbuf *netdev_alloc_tx_netbuf(const struct netif *netif);

/* rx.c */
uint16_t netdev_alloc_rxpkts(void *argp, struct uk_netbuf *nb[],
        uint16_t count);

#endif /* !NETIF_H */
