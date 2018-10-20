# libjc

Std lib for shitty stuff that I build and come to depend on.

## Containers
 - arraylists
 - hashmaps/sets
 - trees

## Logging
  - log to file, stdout, http (TODO)
  - log line formatting

## Time utils
  - Time deltas
  - Calendar API - todo

## Concurrent stuff
 - Atomic operations on 128 bit ints

# Build intructions
`make lib` to build the static library. It places it in `out/libjc-$(VERSION).a` and the `.o` files in there as well. I run all my C-stuff inside docker so I copy it over to a mounted volume and mount that into `/usr/local/lib/jc`.