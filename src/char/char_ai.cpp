#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "int_party_ai.hpp"

#include "../poison.hpp"

void ispis(void)
{
    int fd,fd1;
    char buffer[] = "Neki tekst";

    fd1=open("kojo.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if(fd1!=-1){
        printf("file is created.\n");
    }
    write (fd1, buffer, sizeof (buffer)-1);
    close(fd1);

    // FILE *f = fopen("grdobina.txt", "w");

    // /* print some text */
    // const char *text = "Write this to the file";
    // fprintf(f, "Some text: %s\n", text);

    // fclose(f);

    printf("%s\n", "baba");
}

void ispis3 ()
{
    printf("%s\n", "ispis3");
    ispis2();
}

