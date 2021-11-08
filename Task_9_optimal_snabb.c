#include <stdio.h>
#include <stdlib.h>
#define SIZE 100000

int main(int argc, char *argv[]){
    FILE *file;
    int pagefaults = 0;
    //int hit = 0;
    int remember_line = 0;
    //int recently_used = 0;
    int check=0;
    int search_int =0;
    //int fulkod = 0;
    int count = 0;
    int pages = atoi(argv[1]);
    int page_size = atoi(argv[2]);
    char *filename = argv[3];
    const size_t line_size = 10;
    int tmp[pages];
    int used[pages];
    int references[SIZE];
    char* line = malloc(line_size);
    //char* line2 = malloc(line_size);
    
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
        int file_line = atoi(line);
        int div = (int)file_line / (int)page_size;
        int search_int = div*page_size;
        references[count++] = search_int;
    }
    free(line);
    fclose(file);
    

    for(int i=0; i < SIZE; i++){
        remember_line++;
        for(int j=0; j< pages; j++){
            if(tmp[j] == -1){
                tmp[j] = references[i];
                pagefaults++;
                break;
            }
            else if(tmp[j] == references[i]){
                break;
            }
            else if(j == pages-1){
                for(int k =0; k < pages; k++){
                    used[k] = 0;
                }
                for(int k=remember_line; k< SIZE && check < pages; k++){
                    for(int y=0; y < pages; y++){
                        if(references[k] == tmp[y] && used[y] == 0){
                            used[y] = 1;
                            check++;
                        }
                    }
                    if(check == pages-1)
                        break;
                }
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

    /*while (fgets(line, line_size, file) != NULL){
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
                
                for(int k =0; k <= recently_used; k++){
                    fgets(line, line_size, tmpfile);
                }

                for(int k =0; k < pages; k++){
                    used[k] = 0;
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
    }*/

    printf("Number of pagefaults: %d \n", pagefaults);
    return 0;
}