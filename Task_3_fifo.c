#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    FILE *file;
    int pagefaults = 0;
    int pages = atoi(argv[1]);
    int frames = atoi(argv[2]);
    const size_t line_size = 300;
    int tmp[frames];
    char* line = malloc(line_size);
    char *filename = argv[3];
    
    for(int i =0; i < frames; i++){
        tmp[i] = -1;
    }

    file = fopen(filename, "r");

    if (file == NULL){
        perror(filename);
        return 1;
    }

    while (fgets(line, line_size, file) != NULL){
        for(int i=0; i< pages; i++){
            for(int k=0; k< pages; k++){

            }
        }
    }

    free(line);
    fclose(file);
    return 0;
}