#include <stdio.h>
#include <stdlib.h>
#define SIZE 100000

int main(int argc, char *argv[]){
    FILE *file;
    int pagefaults = 0;
    int current_line = 0;
    int check=0;
    int search_int =0;
    int count = 0;
    int pages = atoi(argv[1]);
    int page_size = atoi(argv[2]);
    char *filename = argv[3];
    const size_t line_size = 10;
    int tmp[pages]; // array for pages
    int used[pages];
    int references[SIZE]; // memory references array
    char* line = malloc(line_size);

    // Initialization
    for(int i =0; i < pages; i++){
        tmp[i] = -1;
        used[i] = 0;
    }

    // print statements
    printf("Number of pages: %d \n", pages);
    printf("Page size: %d \n", page_size);
    printf("filename: %s \n", filename);

    // Open the file
    file = fopen(filename, "r");

    // check if file could be opened
    if (file == NULL){
        perror(filename);
        free(line);
        return 1;
    }

    // add the start references to memory references array
    while (fgets(line, line_size, file) != NULL){
        int file_line = atoi(line);
        int div = (int)file_line / (int)page_size;
        int search_int = div*page_size;
        references[count++] = search_int;
    }
    free(line); // free memory
    fclose(file); // close file


    for(int i=0; i < SIZE; i++){ // loop through memory references array
        current_line++;
        for(int j=0; j< pages; j++){ // loop through array of pages
            // page never used
            if(tmp[j] == -1){
                tmp[j] = references[i];
                pagefaults++;
                break;
            }
            // if hit then no need to look further in page array
            else if(tmp[j] == references[i]){
                break;
            }
            // last position in in page array
            else if(j == pages-1){
                // reset used array
                for(int k =0; k < pages; k++){
                    used[k] = 0;
                }
                // search for the last memory reference used again in the future
                for(int k=current_line; k< SIZE; k++){
                    for(int y=0; y < pages; y++){
                        if(references[k] == tmp[y] && used[y] == 0){
                            used[y] = 1;
                            check++;
                        }
                    }
                    // dont want to know the last memory reference used again in the future
                    if(check == pages-1)
                        break;
                }
                // find the last memory reference used again in the future
                for (int k = 0; k < pages; k++){
                    if (used[k] == 0){
                        tmp[k] = references[i];
                        break;
                    }
                }
                check =0;
                pagefaults++;
            }
        }
    }

    printf("Number of pagefaults: %d \n", pagefaults);
    return 0;
}
