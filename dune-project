(lang dune 3.0)

(generate_opam_files)

(source (github fabbing/mirage-net-unikraft))
(license BSD-3)
(authors "Fabrice Buoro <fabrice@tarides.com>")
(maintainers "team@mirage.org")

(package
 (name mirage-net-unikraft)
 (synopsis "Unikraft implementation of MirageOS network interface")
 (description "This library implements the MirageOS network interface for Unikraft targets.")
 (depends
  (ocaml (>= "5.2.0"))
  (cstruct (>= "1.0.1"))
  (lwt (>= "2.4.3"))
  (mirage-net (>= "3.0.0"))
  (macaddr ( >= "4.0.0"))
  (mirage-unikraft (>= "1.0.0"))
  (logs (>= "0.6.0"))
  metrics
  (fmt (>= "0.8.7"))))
