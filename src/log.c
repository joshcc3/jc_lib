#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include "time/pprint.h"
#include "log.h"
#include <assert.h>
#include <sys/syscall.h>

#define gettid() syscall(SYS_gettid)

const struct log_context std_log_context = (struct log_context){ .formatter = std_format_fn, .message_handler = stdout_handler };

string_ std_format_fn(string_ message)
{
  string_ run_name = new_string(getenv("RUN_NAME"));
  int estimated_len = message.length + run_name.length + 256;
  
  char* buffer = (char*)calloc(sizeof(char), estimated_len + 1);
  sprintf(buffer, "%s %llu Thread-%ld: %s\0", run_name.char_arr, now(), gettid(), message.char_arr);
  return new_string(buffer);
}

void stdout_handler(string_ str) { printf("%s\n", str.char_arr); }

struct log_context current_context = (struct log_context){ .formatter = std_format_fn, .message_handler = stdout_handler };

void log_info_(string_ message)
{
  current_context.message_handler(current_context.formatter(message));
}

void log_info(char* message, ...)
{
  char buffer[4096];
  memset(buffer, 0, 4096);
  va_list args;
  va_start(args, message);
  vsprintf(buffer, message, args);
  va_end(args);
  string_ tmp = new_string(buffer);
  if(tmp.length >= 2048) { perror(tmp.char_arr); assert(false); }
  log_info_(tmp);
}
void log_err(char* message, ...)
{
  assert(false);
}
void log_err_(string_ message)
{
  current_context.message_handler(current_context.formatter(message));
}
