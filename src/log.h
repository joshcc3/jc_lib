#ifndef LOG_H
#define LOG_H

struct log_context {
  struct message_format fmt;
  void (*message_handler)(char *);
};

void push_context(struct log_context);
void pop_context(struct log_context);
void with_context(struct log_context, void* (*fn)(void*));

//void (*file_output_handler)(char*);
struct log_context std_log_context;

struct message_format std_format;
void (*stdout_handler)(char*);


void info(char *str);
void err(char *str);

#endif
