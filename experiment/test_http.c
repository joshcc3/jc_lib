#include <time.h>
#include <assert.h>
#include <stdbool.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define BUF_LEN 4096


#define DEF_HEADER(var, hdr, val) char var[128];	\
  sprintf(var, "%s: %s", hdr, val);

char* err_table[200];



/*void  render_headers(char **headers, char **output);
{
  const int initial_size = 4 * (1 << 8);
  string_buffer buffer;
  buffer->init(&buffer);
  
  
  
  assert(buffer);
  *output = buffer->internal;
  buffer->deinit(&buffer);

  }*/

void init_err_table()
{
  err_table[11] = "EWOULDBLOCK";
  err_table[11] = "EAGAIN";
  err_table[9] = "EBADF";
  err_table[111] = "ECONNREFUSED";
  err_table[14] = "EFAULT";
  err_table[4] = "EINTR";
  err_table[22] = "EINVAL";
  err_table[12] = "ENOMEM";
  err_table[107] = "ENOTCONN";
}

bool double_carriage_return(char *buffer, int bytes)
{
  return buffer[bytes-2] == '\r' && buffer[bytes-1] == '\n';
}

void send_google_head_request(int fd, int try)
{
  char sbuffer[BUF_LEN];
  DEF_HEADER(host_header, "Host", "www.google.com");
  DEF_HEADER(conn_header, "Connection", "keep-alive");
  DEF_HEADER(contentlen_header, "Content-Length", "0");  
  
  sprintf(sbuffer, "GET /%s HTTP/1.1\r\n%s\r\n%s\r\n%s\r\n\r\n", try == 1? "": "device", host_header, conn_header, contentlen_header);
  //sprintf(sbuffer, "HEAD / HTTP/1.1\r\n%s\r\n\r\n", host_header);
  printf("Requesting:\n%s\n", sbuffer);
  send(fd, sbuffer, BUF_LEN, 0);

}
void main()
{
  init_err_table();

  int family = AF_INET;
  int sock_type = SOCK_STREAM;
  int sock_type2 = SOCK_DGRAM;
  
  int fd = socket(AF_INET, SOCK_STREAM, 0);
  if(fd < 0) assert(false);

  struct addrinfo *res;
  const char *addr = "www.google.com";
  const char *service = "http";
  
  if(getaddrinfo(addr, service, NULL, &res)) assert(false);

  int z = 10;
  
  if(connect(fd, res->ai_addr, res->ai_addrlen)) assert(false);
  //https://tools.ietf.org/html/rfc7230#section-3.3.1
  send_google_head_request(fd, 1);

  int head_count = 0;

  char rbuffer[BUF_LEN];
  int bytes_read = recv(fd, rbuffer, BUF_LEN, 0);
  int count =0;
  bool flag = false;
  while(bytes_read > 0 && head_count < 2)
    {
      if(bytes_read < BUF_LEN) rbuffer[bytes_read-1] = 0;
      printf("%s\n", rbuffer);
      bytes_read = recv(fd, rbuffer, BUF_LEN, 0);
      count++;
      if(!flag) { send_google_head_request(fd, 2); flag = true; }
  
    }
  printf("----\n\nEOM %d\n", bytes_read);
  assert(bytes_read == 0);

  close(fd);
  shutdown(fd, SHUT_RDWR);
  if(bytes_read == -1) printf("shutdown Errno %s\n", err_table[errno]);
  else printf("Successful read\n");

  bytes_read = recv(fd, rbuffer, BUF_LEN, 0);
  if(bytes_read == -1) printf("recv Errno %s\n", err_table[errno]);
  else printf("Successful read\n");
}
