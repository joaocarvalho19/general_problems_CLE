#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int M;
int N;
static void printUsage(char *cmdName);
#define MAX_STRING_SIZE 20

/** \brief gaussian elimination process return { 1-singular matrix; 0-upper triangular} */
int gaussianElimination(double mat[N][N]);

/** \brief return matrix determinant  */
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

/** \brief swap row i to j and vice-versa  */
void swap_row(double mat[N][N], int i, int j){
    for (int k=0; k<=N; k++){
        double temp = mat[i][k];
        mat[i][k] = mat[j][k];
        mat[j][k] = temp;
    }
}

/** \brief gaussian elimination process return { 1-singular matrix; 0-upper triangular} */
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

/** \brief print the matrix */
void showMatrix(double mat[N][N]){
    /* Display the matrix */
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            printf("%f\t", mat[i][j]);
        }
        printf("\n");
    }
}

/** \brief Read and process file content */
int** process_file(FILE *file){
    fread(&M,sizeof(M),1,file);
    printf("Number of matrices to be read = %d\n", M);

    fread(&N,sizeof(N),1,file);
    printf("Matrices order = %d\n", N);

    double coef[M][N][N]; // Matrix Coefficients
    for (int m=0; m<M; m++) {
        fread(&coef[m], sizeof(double[N * N]), 1, file);

        printf("Processing matrix %d ...\n", m+1);
        //showMatrix(coef[m]);
        double determinat = det(coef[m]);
        //printf("\n\n");
        //showMatrix(coef[m]);
        printf("The determinant is %f\n", determinat);
        //printf("\n\n\n\n");
    }

    return 0;
}

/** \brief print usage  */
static void printUsage(char *cmdName){
    fprintf(stderr, "\nSynopsis: %s OPTIONS [filename / positive number]\n"
    " OPTIONS:\n"
    " -h --- print this help\n"
    " -f --- filename\n"
    " -n --- positive number\n", cmdName);
}

/** \brief main function  */
int main(int argc, char **argv){
    int opt; /* selected option */
    //char *fName = "no name"; /* file name (initialized to "no name" by default) */
    int val = -1; /* numeric value (initialized to -1 by default) */
    opterr = 0;
    char *files_array[MAX_STRING_SIZE];
    int array_index = 0;
    do{ 
        switch ((opt = getopt (argc, argv, "f:n:h"))){ 
            case 'f': /* file name */
                if (optarg[0] == '-'){
                    fprintf(stderr, "%s: file name is missing\n", basename (argv[0]));
                    printUsage (basename (argv[0]));
                    return EXIT_FAILURE;
                }
                files_array[array_index] = optarg;
                array_index++;
                //fName = optarg;
                break;
            case 'n': /* numeric argument */
                if (atoi(optarg) <= 0){
                    fprintf(stderr, "%s: non positive number\n", basename (argv[0]));
                    printUsage (basename (argv[0]));
                    return EXIT_FAILURE;
                }
                val = (int) atoi(optarg);
                break;
            case 'h': /* help mode */
                printUsage(basename (argv[0]));
                return EXIT_SUCCESS;
            case '?': /* invalid option */
                fprintf(stderr, "%s: invalid option\n", basename(argv[0]));
                printUsage (basename (argv[0]));
                return EXIT_FAILURE;
            case -1: break;
        }
    } while (opt != -1);
    if (argc == 1){ 
        fprintf(stderr, "%s: invalid format\n", basename(argv[0]));
        printUsage (basename (argv[0]));
        return EXIT_FAILURE;
    }

    // Calculate the time taken
    clock_t t;
    t = clock();

    FILE *file;

    //for all files in arguments
    for(int i = 0; i < array_index; ++i){
        printf("\nFile %d: \n", i+1);
        file = fopen(files_array[i],"rb+");  // r for read, b for binary

        if (file == NULL){
            printf("\nUnable to open file.\n");
            exit(EXIT_FAILURE);
        }
        process_file(file);
        fclose(file);
    }

    /*file = fopen(fName,"rb+");  // r for read, b for binary
    if (file == NULL){
        printf("\nUnable to open file.\n");
        exit(EXIT_FAILURE);
    }
    process_file(file);
    fclose(file);*/

    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // calculate the elapsed time
    printf("Elapsed time: %f s\n", time_taken);

    return 0;
}