#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LINE_LENGTH 255

unsigned char fileNameCorrect(char *fileName) {
    if(fileName != NULL && strstr(fileName, ".txt") != NULL) {
        return 1;
    }
    printf("Klaida! Neteisingas failo pavadinimas.");
    return 0;
}

FILE *openFile(char *fileName, char *mode) {
    if(fileNameCorrect(fileName)) {
        FILE *ptr;
        ptr = fopen(fileName, mode);

        if(!ptr) {
            printf("Klaida! Failo nepavyko atidaryti.\n");
            exit(-1);
        } else {
            printf("Failas atidarytas sekmingai!\n");
        }
        return ptr;
    }
    exit(-1);
}

void connectSplitWords (char *line) {
    size_t j = 1;
    while(line[j] != '\0') {
        if(line[j] == '-' && line[j-1] != ' ' && line[j+1] != ' ' && line[j+1] != '\n') {
                for(size_t k = j; line[k] != '\0'; ++k)
                    line[k] = line[k + 1];
            }
        ++j;
    }
}

int main(int argc, char **argv) {
    FILE *inputPtr = openFile(argv[1], "r");
    FILE *outputPtr = openFile(argv[2], "w+");
    char *buffer = malloc(sizeof(char) * LINE_LENGTH);

    while(fgets(buffer, LINE_LENGTH, inputPtr)) {
        connectSplitWords(buffer);
        fprintf(outputPtr, buffer);
    }

    free(buffer);
    fclose(inputPtr);
    fclose(outputPtr);
    return 0;
}