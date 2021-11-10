#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    FILE *file;
    int pagefaults = 0; // Number of page faults
    int pages = atoi(argv[1]); // Number of pages
    int page_size = atoi(argv[2]); // page size
    char *filename = argv[3]; // the filename
    const size_t line_size = 10; // max number of characters in the line
    int tmp[pages]; // array for pages
    char* line = malloc(line_size); // the current line in the file

    // Initialize the page array
    for(int i =0; i < pages; i++){
        tmp[i] = -1; // the memory references is never negative, and so -1 means never used
    }

    // print statements
    printf("Number of pages: %d \n", pages);
    printf("Page size: %d \n", page_size);
    printf("filename: %s \n", filename);

    file = fopen(filename, "r"); // Open the file

    // check if file could be opened
    if (file == NULL){
        perror(filename);
        free(line);
        return 1;
    }

    while (fgets(line, line_size, file) != NULL) { // loop while there are lines left to read in the file (fgets return NULL)
        int file_line = atoi(line); // convert file line value to integer
        int div = (int)file_line / (int)page_size; // floor of quotient
        int search_int = div*page_size; // start address

        // fifo
        for(int i = 0; i< pages; i++){ // loop through array of pages
            // page never used
            if(tmp[i] == -1){
                tmp[i] = search_int;
                pagefaults++;
                break;
            }
            // if hit then no need to look further in page array
            else if(tmp[i] == search_int){
                break;
            }
            else if(i == pages-1){ // last position in in page array
                tmp[pagefaults%pages] = search_int; // pages % pages = 0 & pagefaults = page first time => pagefaults % pages = 0 first time
                pagefaults++;
            }
        }
    }

    free(line); // free memory
    fclose(file); // close file

    printf("Number of pagefaults: %d \n", pagefaults);
    return 0;
}
