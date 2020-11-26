#include <stdio.h> 
#include <unistd.h> 
#include <fcntl.h> 

#define BUF_SIZE 100

int main(int argc, char ** argv) {

    int potok[2], des_pliku, pid, n;
    char buf[BUF_SIZE];
    char fname[32];
    
    if(pipe(potok) < 0) { //utworzenie potoku
        fprintf(stderr, "Nie udało się otworzyć potoku\n");
        return 1;
    }

    pid = fork(); //jesli dziecko to pid=0

    if(pid == 0) { //Kod dziecka
        //child
        close(potok[1]); //Zamknięcie pisania do potoku
        close(0);     //Zamkniecie wejścia procesu dziecka
        dup(potok[0]);   //Przypisanie wyjścia potoku do wejscia procesu (najniższy dostępny fd)  
        close(potok[0]); //Zamknięcie czytania z potoku
        execlp("display", "display", NULL); //Wyswietlenie obrazu za pomoca programu display
					    //Display myśli, że czyta z STDIN, a przez zamianę FD
 					    //czyta z wyjscia potoku
    }
    else {
        close(potok[0]); //Zamknięcie odczytu z potoku
        if((des_pliku = open(argv[1], O_RDONLY)) < 0) { //Otwarcie pliku z obrazem
            fprintf(stderr, "Nie udało się otworzyć pliku\n");
            return 2;
        }
        
        while((n = read(des_pliku, &buf, BUF_SIZE)) > 0) { //Odczyt z pliku
            if(write(potok[1], &buf, n) < 0) { //Zapis do potoku
                fprintf(stderr, "Nie udało się zapisać danych do potoku\n");
                return 3;
            }  
        }
	//sleep(5);
	close(potok[1]);
        close(des_pliku); //Zamkniecie pliku z obrazem
    } 
}
