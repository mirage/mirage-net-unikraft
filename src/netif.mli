(* SPDX-License-Identifier: BSD-3-Clause *)
(*
 * Copyright (c) 2011-2013 Anil Madhavapeddy <anil@recoil.org>
 * Copyright (c) 2024-2025 Fabrice Buoro <fabrice@tarides.com>
 *)

(** Unikraft interface for Ethernet I/O. *)

include Mirage_net.S

val connect : string -> t Lwt.t
