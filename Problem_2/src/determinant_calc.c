#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

int M;
int N;

int gaussianElimination(double mat[N][N]);

/** return matrix determinant
 *
 * @param mat
 * @return
 */
double det(double mat[N][N]){
    float res = 1;
    // gaussian elimination process
    int singular_matrix = gaussianElimination(mat);

    // if matrix is singular
    if (singular_matrix)
        return 0;

    for (int i = 0; i < N; ++i) {
        res *= mat[i][i];
    }
    return res;
}

/** swap row i to j and vice-versa
 *
 * @param mat
 * @param i
 * @param j
 */
void swap_row(double mat[N][N], int i, int j){
    for (int k=0; k<=N; k++){
        double temp = mat[i][k];
        mat[i][k] = mat[j][k];
        mat[j][k] = temp;
    }
}

/** gaussian elimination process return { 1-singular matrix; 0-upper triangular}
 *
 * @param matrix[N][N]
 * @return bool
 */
int gaussianElimination(double mat[N][N]){
    for (int k=0; k<N; k++){
        int index_pivot = k;
        int value_pivot = mat[index_pivot][k];

        // update pivot if exists any bigger
        for (int i = k+1; i < N; i++)
            if (abs(mat[i][k]) > value_pivot){
                value_pivot = mat[i][k];
                index_pivot = i;
            }

        //check if diagonal is zero (singular matrix)
        if (!mat[k][index_pivot])
            return 1;

        // swap rows
        if (index_pivot != k)
            swap_row(mat, k, index_pivot);

        // apply formula
        for (int i=k+1; i<N; i++){
            double aux = mat[i][k]/mat[k][k];
            for (int j=k; j<N; j++)
                mat[i][j] -= aux * mat[k][j];
        }
    }
    return 0;
}
/** print the matrix
 *
 * @param matrix[N][N]
 */
void showMatrix(double mat[N][N]){
    /* Display the matrix */
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            printf("%f\t", mat[i][j]);
        }
        printf("\n");
    }
}


/** Read and process file content
 *
 * @param file
 * @return int
 */
int** process_file(FILE *file){
    fread(&M,sizeof(M),1,file);
    printf("M: %d\n", M);

    fread(&N,sizeof(N),1,file);
    printf("N: %d\n", N);

    double coef[M][N][N]; // Matrix Coefficients
    for (int m=0; m<M; m++) {
        fread(&coef[m], sizeof(double[N * N]), 1, file);

        //showMatrix(coef[m]);
        double determinat = det(coef[m]);
        //printf("\n\n");
        //showMatrix(coef[m]);
        printf("MATRIX: %d \t Determinat: %f\n", m, determinat);
        //printf("\n\n\n\n");
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
    // Calculate the time taken
    clock_t t;
    t = clock();

    FILE *file;

    //for all files in arguments
    for (int i = 1; i < argc; ++i){

        file = fopen(argv[i],"rb+");  // r for read, b for binary

        if (file == NULL){
            printf("\nUnable to open file.\n");
            exit(EXIT_FAILURE);
        }
        process_file(file);
        fclose(file);
    }

    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // calculate the elapsed time
    printf("Elapsed time: %f seconds\n", time_taken);

    return 0;
}