#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *print_message(void *ptr)
{
  sleep(1);
  printf("Thread #:%ld \n", pthread_self());
}

main()
{
  int num_thread = 10;

  pthread_t threads[num_thread];
  int i;

  for(i=0; i<num_thread; ++i)
  {
    pthread_create(&threads[i], NULL, print_message, NULL);
  }

  FILE *fp;
  fp = fopen("/proc/lfprng", "r");
  char ch = fgetc(fp);

  for(i=0; i<num_thread; ++i)
  {
    pthread_join(threads[i], NULL);
  }

  exit(0);
}
