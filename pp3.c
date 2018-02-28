#include "buffer.h"
int main(int argc, char *argv[]) {
/* 1. Get command line arguments argv[1],argv[2],argv[3] */
if (argc < 4) {
  fprintf(stderr, "Usage: ./pp3 *sleep length as int* *number of producer threads* *number of consumer threads*.\n");
  return -1;
}
int sleepTime = atoi(argv[1]);
int prodThreads = atoi(argv[2]);
int consumerThreads = atoi(argv[3]);
pthread_t tid[prodThreads + consumerThreads];
pthread_attr_t attr;
pthread_attr_init(&attr);
/* 2. Initialize buffer */

/* 3. Create producer thread(s) */
int i,j;
for (i = 0; i < prodThreads; ++i;) {
  pthread_create(&tid[i], &attr, prodMain, NULL);

}
/* 4. Create consumer thread(s) */
for (j = 0; j < consumerThreads; ++j) {
  pthread_create(&tid[i], &attr, consumerMain, NULL);

}
/* 5. Sleep */
sleep(sleepTime);
/* 6. Exit */
return 1;
}
