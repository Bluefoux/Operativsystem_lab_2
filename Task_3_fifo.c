#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    FILE *file;
    int pagefaults = 0;
    int hit = 0;
    int pages = atoi(argv[1]);
    int page_size = atoi(argv[2]);
    char *filename = argv[3];
    const size_t line_size = 10;
    int tmp[pages];
    char* line = malloc(line_size);
    
    for(int i =0; i < pages; i++){
        tmp[i] = -1;
    }

    printf("Number of pages: %d \n", pages);
    printf("Page size: %d \n", page_size);
    printf("filename: %s \n", filename);

    file = fopen(filename, "r");

    if (file == NULL){
        perror(filename);
        free(line);
        return 1;
    }

    while (fgets(line, line_size, file) != NULL){
        int file_line = atoi(line);
        int div = (int)file_line / (int)page_size;
        int search_int = div*page_size;
        for(int i = 0; i< pages; i++){
            if(tmp[i] == -1){
                tmp[i] = search_int;
                pagefaults++;
                break;
            }
            else if(tmp[i] == search_int){
                break;
            }
            else if(i == pages-1){
                tmp[pagefaults%pages] = search_int;
                pagefaults++;
            }
        }
    }

    free(line);
    fclose(file);

    printf("Number of pagefaults: %d \n", pagefaults);
    return 0;
}

