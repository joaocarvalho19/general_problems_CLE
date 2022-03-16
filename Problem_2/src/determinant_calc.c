#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/** Read and process file content
 *
 * @param file
 * @return int
 */
int** process_file(FILE *file){
    unsigned int M; // Number of matrices 
    fread(&M,sizeof(M),1,file);
    printf("M: %d\n", M);

    unsigned int N; // Order of matrices
    fread(&N,sizeof(N),1,file);
    printf("N: %d\n", N);

    double coef[N][N]; // Matrix Coefficients
    fread(&coef, sizeof(double [N*N]), 1, file);  

    for (int i=0; i<N; i++){
        for (int k=0; k<N; k++){
            printf("Coef %d %d: %f\n", i, k, coef[i][k]);
        }
    }

    return 0;
}

/** Compute the determinant of the matrix
 *
 * @param c
 * @return int
 */
int calc_determinant(){
    return 0;
}

int main(int argc, char **argv){
    FILE *file;

    //for all files in arguments
    for (int i = 1; i < argc; ++i){

        file = fopen(argv[i],"rb+");  // r for read, b for binary

        if (file == NULL)
        {
            printf("\nUnable to open file.\n");
            exit(EXIT_FAILURE);
        }

        process_file(file);
    }

    return 0;
}