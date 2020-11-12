#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>

int ign_usr1 = 10;

void catch(int signal_ID)
{
  if (signal_ID == SIGALRM){
    printf("\nzlapano SIGALARM, program zakonczy dzialanie\n");
    exit(0);
  }
  
  if (signal_ID == SIGTERM)
    printf("\nzlapano SIGTERM\n");
  
  if (signal_ID == SIGUSR1){
    if(ign_usr1 >= 10 )
      {
	printf("\nzlapano SIGUSR1\n");
	signal(SIGUSR1, SIG_IGN);
	ign_usr1 = 0; 
      }
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
    {
    ign_usr1++;
    if(ign_usr1 >= 10)
      signal(SIGUSR1, catch);
    printf("\n %d", ign_usr1);
    sleep(1);
    }
  return 0;
}
