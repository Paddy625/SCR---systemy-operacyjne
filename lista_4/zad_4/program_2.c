#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>

void catch(int signal_ID)
{
  if (signal_ID == SIGALRM){
    printf("\nzlapano SIGALARM, program zakonczy dzialanie\n");
    exit(0);
  }
  
  if (signal_ID == SIGTERM){
    printf("\nzlapano SIGTERM\n");
    signal(SIGUSR1, catch);
  }
  
  if (signal_ID == SIGUSR1){
    signal(SIGUSR1, SIG_IGN);
    printf("\nzlapano SIGUSR1\n");
  }
}

int main(void)
{
  signal(SIGALRM, catch);
  signal(SIGTERM, catch);
  signal(SIGUSR1, catch);
  signal(SIGUSR2, SIG_IGN);
  printf("%d \n", getpid());
  while(1) 
    sleep(1);
  return 0;
}
