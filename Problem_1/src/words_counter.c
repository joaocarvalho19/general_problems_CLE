#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isConsonant(char val){
    char arr[21] = {'b', 'c', 'd', 'f', 'g','h', 'j', 'k', 'l', 'm','n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y', 'z', 'ç'};
    int i;
    for(i = 0; i < 21; i++){
        if(arr[i] == val)
            return 1;
    }
    return 0;
}

int isStopChar(char val){
    char arr[16] = {' ', '\t', '\n', '\0', '.', ',', ':', ';', '?', '!', '-', '"', '(', ')', '[',']'};
    int i;
    for(i = 0; i < 16; i++){
        if(arr[i] == val)
            return 1;
    }
    return 0;
}

int main(int argc, char **argv){
    
    FILE *file;

    char ch;
    int num_words, vowel_begin_words, conso_end_words;

    char first_char;
    char last_char;

    /* Current word method */
    //char current_word[20];
    //char *p;
    //p = current_word;
    
    for (int i = 1; i < argc; ++i){
        printf("File: %s\n", argv[i]);
        num_words = 0;
        vowel_begin_words = 0;
        conso_end_words = 0;

        file = fopen(argv[i],"rb");
        if(file == NULL){
            printf("Error!");   
            exit(1);             
        }
        /*
        * Logic to count words.
        */
        int index = 0;
        while ((ch = fgetc(file)) != EOF){

            ch = tolower(ch);   //lower case

            if(index == 0){
                //First char of file
                first_char = ch;
            }
            if (stopChars(ch)){
                if(last_char){
                    num_words++;    //add word
                    /*char first_char, last_char;
                    first_char = *(p);
                    last_char = *(p + (strlen(current_word) - 1));*/

                    //Check if begins with a vowel
                    if(!isConsonant(first_char)){
                        vowel_begin_words++;
                    }
                    //Check if ends with a consonant
                    if(isConsonant(last_char)){
                        conso_end_words++;
                    }
                    index = 0;
                    last_char = '\0';
                    //memset(current_word, 0, 20);
                }
            }
            else{
                last_char = ch;
                /*current_word[index] = ch;*/
                index++; 
            }            
        }
        num_words++;    //add last word
        /* Last word of file */
        //Check if begins with a vowel
        if(!isConsonant(first_char)){
            vowel_begin_words++;
        }
        //Check if ends with a consonant
        if(isConsonant(last_char)){
            conso_end_words++;
        }
        //Result
        printf("Words: %d\n", num_words);
        printf("Vowel begins words: %d\n", vowel_begin_words);
        printf("Consonant ends words: %d\n", conso_end_words);
    }
    

    /* Close file */
    fclose(file);
    return 0;
}