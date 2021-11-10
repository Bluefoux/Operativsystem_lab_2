#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    FILE *file;
    FILE *tmpfile;
    int pagefaults = 0;
    int hit = 0;
    int remember_line = 0;
    int recently_used = 0;
    int search_int_tmp =0;
    int fulkod = 0;
    int pages = atoi(argv[1]);
    int page_size = atoi(argv[2]);
    char *filename = argv[3];
    const size_t line_size = 10;
    int tmp[pages];
    int used[pages];
    char* line = malloc(line_size);
    char* line2 = malloc(line_size);

    // Initialization
    for(int i =0; i < pages; i++){
        tmp[i] = -1;
        used[i] = 0;
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
        recently_used++;
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
                tmpfile = fopen(filename, "r");
                for(int k =0; k <= recently_used; k++){
                    fgets(line, line_size, tmpfile);
                }

                for(int k =0; k < pages; k++){
                    used[k] = 0;
                }

                while (fgets(line2, line_size, tmpfile) != NULL){
                    int file_line = atoi(line2);
                    int div = (int)file_line / (int)page_size;
                    int search_int_tmp = div*page_size;
                    for(int k=0; k< pages; k++){
                        if(search_int_tmp == tmp[k] && used[k] == 0){
                            used[k] = 1;
                            fulkod++;
                        }
                    }
                    if(fulkod == pages-1){
                        break;
                    }
                }
                fclose(tmpfile);

                for (int k = 0; k < pages; k++){
                    if (used[k] == 0){
                        tmp[k] = search_int;
                        break;
                    }
                }
                fulkod=0;
                pagefaults++;
            }
        }
    }

    free(line);
    fclose(file);

    printf("Number of pagefaults: %d \n", pagefaults);
    return 0;
}
