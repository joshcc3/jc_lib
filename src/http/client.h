#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include "err_t.h"
#include "containers/hash_map.h"
#include "data/string_.h"

typedef struct http_request {
  string_ url;
  hash_map headers;
};

typedef struct http_client {
  err_t get(http_request *, http_response *);
  err_t post(http_request *, http_response *);
} http_client;

void new_simple_http_client(http_client*);

#endif
