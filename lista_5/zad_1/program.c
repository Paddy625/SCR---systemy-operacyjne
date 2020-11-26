#include <stdio.h> 
#include <unistd.h> 
#include <fcntl.h> 

#define BUF_SIZE 1

int main(int argc, char ** argv) {

    int potok[2], des_plik, n, pid;			
    char buf[BUF_SIZE];
    char fname[32];
   

    if(pipe(potok) < 0) { //Utworzenie potoku
        fprintf(stderr, "Nie udało się utworzyć potoku\n");
        return 1;
    }

    pid = fork(); 

    if(pid == 0) { //Kod dziecka
        close(potok[1]); //Nie można zapisać do potoku

	while(read(potok[0], &buf, BUF_SIZE) > 0){ //Odczyt z potoku
		write(STDOUT_FILENO, "\n#", 2);
		write(STDOUT_FILENO, &buf, BUF_SIZE);
		write(STDOUT_FILENO, "#", 1);	
	}
	close(potok[0]); //Zamkniecie odczytu z potoku
    }
    else { //Kod rodzica
        close(potok[0]); //Nie można czytać z potoku

        if((des_plik = open(argv[1], O_RDONLY)) < 0) { //Otwarcie pliku z tekstem
            
            fprintf(stderr, "Nie udało się otworzyć pliku\n");
            return 2;
        }
        
        while((n = read(des_plik, &buf, BUF_SIZE)) > 0) { //Odczyt z pliku
            if(write(potok[1], &buf, n) < 0) { //Zapis do potoku
                fprintf(stderr, "Nie udało się zapisać danych do potku\n");
                return 3;
            }  
	}
	close(potok[1]); //Zamkniecie zapisu do potoku
        close(des_plik); //Zamknięcie pliku z tekstem
    }
}

