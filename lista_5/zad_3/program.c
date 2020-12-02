#include <stdio.h> 
#include <unistd.h> 
#include <fcntl.h> 
#include <sys/stat.h> //dla funkcji mkfifo()
#include <errno.h> //dla obslugi bledow mkfifo()

#define BUF_SIZE 1

//odczyt z potoku "tail -c +1 pipe"

int main(int argc, char ** argv) {

    int des_plik, des_potoku, n;			
    char buf[BUF_SIZE];
    char * fifo = "pipe"; 

	
	 if(mkfifo(fifo, S_IRWXU) < 0)
   	      if(errno==EEXIST) printf("Potok FIFO juz istnieje!");
   	         else printf("Nie udalo sie utworzyc potoku");
	

	for(int i = 1; i<argc; i++){

        des_potoku = open(fifo, O_WRONLY);

            if((des_plik = open(argv[i], O_RDONLY)) < 0) { //Otwarcie pliku z tekstem
            
            fprintf(stderr, "Nie udało się otworzyć pliku\n");
            return 2;
        }
        
        while((n = read(des_plik, &buf, BUF_SIZE)) > 0) { //Odczyt z pliku
            if(write(des_potoku, &buf, n) < 0) { //Zapis do potoku
                fprintf(stderr, "Nie udało się zapisać danych do potku\n");
                return 3;
            }
	}
	close(des_plik); //Zamknięcie pliku z tekstem
	write(des_potoku, "\n", 1);
	close(des_potoku);
	sleep(5);
	}
}    

