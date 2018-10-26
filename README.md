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
 - Concurrent Containers - (TODO)

## HTTP Connections
 - You create a socket using the `socket` function provided by glibc which takes a connection domain (e.g. ipv4, unix local socket..), a type (SOCK_STREAM, SOCK_DGRAM ..) and a protocol (this is usually defined by the type and is 0). This returns a filedescriptor. 
AF_INET has a value 2, SOCK_STREAM (1), SOCK_DGRAM (2),
In the struct filled by getifaddr, ai_addrlen is 16, ai_addr contains sa_family (protocol family) and sa_data. `sa_data` contains the port number in the first 2 bytes and the protocol family address in the remaining 4 bytes.
From the RFC:
```
     request-line   = method SP request-target SP HTTP-version CRLF
method = GET, PUT, POST ..
    request-target = origin-form (path)
                    / absolute-form (used for proxies - full url with the protocol)
                    / authority-form (...)
                    / asterisk-form (used for server wide requests such as OPTIONS)
```
A client MUST send a Host header field in all HTTP/1.1 request messages.
Headers are case-insensitive.
A client is expected to manage connections to the server and specifies the intended connection option (e.g. close) as the value for the `Connection` header.

Google sends its content in chunked encoding by default. If no `Connection` header is specified then Google expects a subsequent request and closes the connection with a 400 if nothing is provided. You keep getting a 0 when you read past the end.
you can shut down a closed fd and you can read from a shutdown fd but you can't read from a closed fd where you get a EBADF.
If I try and use `Connection:keep-alive` I get a 400 when trying to send multiple requests after the original request started, not sure why this is the case.
If I try sending the requests immediately it hangs on a receive evidently before the server has finished sending its response. Then the server just terminates the connection without finishing.


From the RFC:
```
HTTP/1.1 defaults to the use of "persistent connections", allowing
   multiple requests and responses to be carried over a single
   connection.
```

# Build intructions
`make lib` to build the static library. It places it in `out/libjc-$(VERSION).a` and the `.o` files in there as well. I run all my C-stuff inside docker so I copy it over to a mounted volume and mount that into `/usr/local/lib/jc`.