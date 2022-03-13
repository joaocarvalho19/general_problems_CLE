#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

	char a[13];
	
	char *pa;
	pa = a;
	a[0] = 'o';
	a[1] = 'l';
	a[2] = 'a';
	printf("Current word: %s\n", a);
	printf("--: %c\n", *pa);

	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isConsonant(char val){
    char arr[21] = {'b', 'c', 'd', 'f', 'g','h', 'j', 'k', 'l', 'm','n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y', 'z'};
    int i;
    for(i = 0; i < 21; i++){
        if(arr[i] == val)
            return 1;
    }
    return 0;
}

int main(int argc, char **argv){
    
    FILE *file;

    char ch;
    int num_words, vowel_begin_words, conso_end_words;
    char current_word[20];
    char *p;
    p = current_word;
    num_words, vowel_begin_words, conso_end_words = 0;
    
    for (int i = 1; i < argc; ++i){
        //printf("argv[%d]: %s\n", i, argv[i]);

        file = fopen(argv[i],"rb");
        if(file == NULL){
            printf("Error!");   
            exit(1);             
        }
        /*
        * Logic to count words.
        */
        
        
        
        current_word[0] = 'o';
	    current_word[1] = 'l';
	    current_word[2] = 'a';
	    
        printf("first_char: %d\n", *p);
        int j = 0;
        while ((ch = fgetc(file)) != EOF){
            ch = tolower(ch);   //lower case
            /* Check words */
            
            if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\0'){
                num_words++;    //add word
                printf("Current word: %s\n", current_word);
                char first_char, last_char;
                first_char = *(p);
                last_char = *(p + (strlen(current_word) - 1));
                printf("first_char: %d\n", first_char);
                printf("last_char: %d\n", last_char);
                j = 0;
                break;
            }


            current_word[j] = ch;
            j++;
        }

        
    }
    //Results
    printf("Words: %d\n", num_words);

    /* Close file */
    fclose(file);
    return 0;
}