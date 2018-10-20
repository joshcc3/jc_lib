#include <stdlib.h>
#include "time/sleep.h"
#include <sys/time.h>
#include <time.h>

int rand_in_range(int mx) { return (int)((double)rand()/RAND_MAX * mx); }

void rand_sleep(int max)
{
  int rand_sleep = rand_in_range(200000);
  const struct timespec tm = (struct timespec){ .tv_sec = 0, .tv_nsec = rand_sleep };
  nanosleep(&tm, NULL);
}

