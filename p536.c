#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <pthread.h>

#define MIN PID 300;
#define MAX PID 5000;
pthread_mutex_t mutex;
int *bitmap;
int counter = 0;

int allocate_map(void) {
  printf("Allocating array for pids...\t");

  bitmap = malloc(sizeof(int) * 4700);
  int i;
  for (i = 0; i < 4700; ++i) {
    bitmap[i] = 0;
  }
  if (bitmap) {
    return 1;
  }
  else {
    fprintf(stderr, "Array allocation failed.\n");
    return -1;
  }
}

int allocate_pid(void) {
  int i;

  for (i = 0; i < 4700; ++i) {
    if (bitmap[i] == 0) {
      bitmap[i] = 1;
      return i + 300;
    }
  }
  if (i == 4699) {
    fprintf(stderr, "Array allocation failed.\n");
    return -1;
  }
  return 1;
}

void release_pid(int pid) {
  bitmap[(pid-300)] = 0;
}

void *thread_main(void *x) {
  int pid = allocate_pid();
  int sec = rand() % 10;
  printf("-Sleeping time: %d secs ;", sec);
  printf(" Thread Id = %d;", pid);
  sleep(sec);
  pthread_mutex_lock(&mutex);
  counter++;
  pthread_mutex_unlock(&mutex);
  printf(" Counter Value = %d\n", counter);

  release_pid(pid);
  pthread_exit(0);
  sleep((rand() % 10));
}

int main(int argc, char **argv) {
  pthread_t tid[100];
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  allocate_map();
  int i;

  for (i = 0; i < 100; ++i) {
    pthread_create(&tid[i], &attr, thread_main, NULL);

  }

  for (i = 0; i < 100; ++i) {
    pthread_join(tid[i], NULL);
  }
}
