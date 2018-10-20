#include <stdlib.h>
#include <stdio.h>
#include "time/pprint.h"
#include "log.h"

string_ std_format_fn(string_ message)
{
  int estimated_len = message.length + 25;
  char* buffer = (char*)calloc(sizeof(char), estimated_len + 1);
  sprintf(buffer, "%llu: %s\n", now(), message.char_arr);
  return new_string(buffer);
}

void stdout_handler(string_ str)
{
  printf("%s\n", str.char_arr);
}

struct log_context current_context = (struct log_context){ .formatter = std_format_fn, .message_handler = stdout_handler };

void log_info_(string_ message)
{
  current_context.message_handler(current_context.formatter(message));
}
void log_info(char* message)
{
  current_context.message_handler(current_context.formatter(new_string(message)));
}
void log_err(char* message)
{
  current_context.message_handler(current_context.formatter(new_string(message)));
}
void log_err_(string_ message)
{
  current_context.message_handler(current_context.formatter(message));
}
