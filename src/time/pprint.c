#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>

void time_of_day(struct timeval *tv)
{
  gettimeofday(tv, NULL);
}

void useconds_elapsed(struct timeval *t1, struct timeval *t2, struct timeval *res)
{
  res->tv_sec = t2->tv_sec - t1->tv_sec;
  res->tv_usec = t2->tv_usec - t1->tv_usec;
}

void pprint_time1(struct timeval *t) { printf("%lds %ldus", t->tv_sec, t->tv_usec); }

unsigned long long usec_since_epoch(struct timeval *t)
{
  unsigned long long result = t->tv_sec;
  result = result * 1000000 + t->tv_usec;
  return result;
}

unsigned long long now()
{
  struct timeval tmp;
  gettimeofday(&tmp, NULL);
  return usec_since_epoch(&tmp);
}
