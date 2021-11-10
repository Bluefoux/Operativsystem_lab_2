#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    FILE *file;
    int pagefaults = 0;
    int current_line = 0; // current line in file
    int pages = atoi(argv[1]);
    int page_size = atoi(argv[2]);
    char *filename = argv[3];
    const size_t line_size = 10;
    int tmp[pages]; // array for pages
    int used[pages];
    char* line = malloc(line_size);

    // Initialization
    for(int i =0; i < pages; i++){
        tmp[i] = -1; // the memory references is never negative, and so -1 means never used
        used[i] = 0; // 0 means not used yet
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

    while (fgets(line, line_size, file) != NULL){ // loop while there are lines left to read in the file (fgets return NULL)
        current_line++;
        int file_line = atoi(line); // convert file line value to integer
        int div = (int)file_line / (int)page_size; // floor of quotient
        int search_int = div*page_size; // start address
        for(int i = 0; i< pages; i++){ // loop through array of pages
            // page never used
            if(tmp[i] == -1){
                tmp[i] = search_int;
                used[i] = current_line; // increase the current used
                pagefaults++;
                break;
            }
            // if hit then no need to look further in page array and increase the current used
            else if(tmp[i] == search_int){
                used[i] = current_line;
                break;
            }
            // last position in in page array
            else if(i == pages-1){
                int check = 0;
                // search for the least recently used
                for (int k = 0; k < pages; k++){
                    if (used[k] < used[check]){
                        check = k;
                    }
                }
                // swap the LRU
                tmp[check] = search_int;
                // increase the current used
                used[check] = current_line;
                pagefaults++;
            }
        }
    }

    free(line); // free memory
    fclose(file); // close file

    printf("Number of pagefaults: %d \n", pagefaults);
    return 0;
}
