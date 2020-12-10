#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>

int main()
{
  int fd_file,fd_mem_map;
  char file_name[32];
  char *file_in_memory;
  struct stat file_stat;
  off_t file_size;
  
  while(1)
    {
      do{
	printf("Podaj nazwe pliku tekstowego: ");
	scanf("%s",file_name);
      }while((fd_file=open(file_name,O_RDONLY))<0); //otwarcie pliku tekstowego
      
      stat(file_name,&file_stat); //okreslenie dlugosci pliku
      file_size=file_stat.st_size;
      
      if((fd_mem_map=open("mem_map",O_RDWR|O_CREAT,S_IRWXU))<0) //tworzy plik mem_map
      	{
       printf("Nie udalo sie utworzyc mem_map");
       return 1;
      	}
      
      truncate("mem_map",file_size); //ustala dlugosc mapowanego pliku
      
      file_in_memory = mmap(NULL,file_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd_mem_map,0); //mapowanie danych pliku do pamieci
      
      read(fd_file,file_in_memory,file_size); //przeslanie danych z pliku(z pamieci) do mapowanego obszaru
      
      msync(file_in_memory,file_size,MS_SYNC); //synchronizacja danych pliku i pamieci 
      
      munmap(file_in_memory,file_size); //zwalnia mapowany obszar pamięci
      
      close(fd_mem_map);
      close(fd_file);
    }
  return 0;
}
