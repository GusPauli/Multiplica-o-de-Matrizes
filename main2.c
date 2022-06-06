//compilar
    //gcc main2.c -o main2
//executar
    // exemplo: ./main 20 20 20 20 t -n 
    // argumento t para multiplicação com matriz transposta; argumento o para multiplicação normal
    //caso queira printar trocar -n por -p

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

double randomDouble();
double randomInterval(double a, double b);
int verifyOperation(char* op);
void randomInitialize(double** mat1, double** mat2, int linA, int linB, int colA, int colB);
double** transposta(double** mat2, double** M2t, int linB, int colB);
double multiply(double** m1, double** m2, double** ans, int linA, int linB, int colA, int colB);
double multiplyTransposed(double** m1, double** m2, double** ans, int linA, int linB, int colA, int colB);
void print(double** m1, double** m2, double** m2t, double** ans, int linA, int linB, int colA, int colB);

void main(int argc, char** argv){
    int linA,linB,colA,colB;
    double** mat1 = NULL;
    double** mat2 = NULL;
    double** mat2T= NULL;
    double** ans= NULL;
    clock_t start, end;

    srand(time(NULL));

    linA = strtol(argv[1], NULL, 10);
    colA = strtol(argv[2], NULL, 10);
    linB = strtol(argv[3], NULL, 10);
    colB = strtol(argv[4], NULL, 10);

    mat1 = malloc(linA * sizeof(double*));
    mat2 = malloc(linB * sizeof(double*));
    mat2T= malloc(colB * sizeof(double*));
    ans  = malloc(linA * sizeof(double*));

    for(int i=0; i<linA; i++){
        mat1[i] = malloc(colA * sizeof(double));
        mat2[i] = malloc(colB * sizeof(double));
    }

    for(int i=0; i<colB; i++){
        ans[i]  = malloc(linB * sizeof(double));
        mat2T[i]= malloc(linB * sizeof(double));
    }

    randomInitialize(mat1,mat2,linA,linB,colA,colB);

    if((strcmp(argv[5], "o")==0)){
        start=clock();

            multiply(mat1,mat2,ans,linA,linB,colA,colB);
        
        end = clock();
        printf("%f\n", (float)(end - start) / CLOCKS_PER_SEC);

        if((strcmp(argv[6], "-p")==0)){
            print(mat1,mat2,mat2T,ans,linA,linB,colA,colB);
        }
        else
            exit(-1);
    }
    else if((strcmp(argv[5], "t")==0)){
        start=clock();

            transposta(mat2,mat2T,linB,colB);
            multiplyTransposed(mat1,mat2T,ans,linA,linB,colA,colB);
        
        end=clock();
        printf("%f\n", (float)(end - start) / CLOCKS_PER_SEC);
        
        if((strcmp(argv[6], "-p")==0)){
            print(mat1,mat2,mat2T,ans,linA,linB,colA,colB);
        }
        else
            exit(-1);
    }

}

double randomDouble() { return ((double)rand()) / ((double)RAND_MAX); }

double randomInterval(double a, double b) {
    return randomDouble() * (b - a) + a;
}

void randomInitialize(double** mat1, double** mat2, int linA, int linB, int colA, int colB) {
    for (int i=0; i < linA && i<linB; i++) {
        for(int j=0; j<colA && j<colB; j++){
            mat1[i][j]= randomInterval(10,100);
            mat2[i][j]= randomInterval(10,100);
        }
    }
}

double** transposta(double** mat2, double** mat2t, int linB, int colB){
    double aux;

    for(int i=0; i<linB; i++){
        for(int j=0; j<colB; j++){
            mat2t[j][i] = mat2[i][j];            
        }
    }
    return mat2t;
}

double multiply(double** m1, double** m2, double** ans, int linA, int linB, int colA, int colB){
    double aux;

    for(int i=0; i<linA; i++){
        for(int j=0; j<colB; j++){
            aux=0;
            for(int k=0; k<colB; k++){
                aux += m1[i][k] * m2[k][j];
            }
            ans[i][j] = aux;
            aux = 0;
        }
    }
    return **ans;
}
double multiplyTransposed(double** m1, double** m2t, double** ans, int linA, int linB, int colA, int colB){
    double aux;

    for(int i=0; i<linA; i++){
        for(int j=0; j< colB; j++){
            aux=0;
            for(int k=0; k < linB; k++){
                aux += m1[i][k] * m2t[j][k];
            }
            ans[i][j]= aux;
            aux=0;
        }
    }
    return **ans;
}
void print(double** m1, double** m2, double** m2t, double** ans, int linA, int linB, int colA, int colB){
    printf("matriz A\n");

    for(int i=0; i<linA; i++){
        for(int j=0; j<colA; j++){
            printf("%lf ", m1[i][j]);
        }
        printf("\n");
    }

    printf("matriz B\n");

    for(int i=0; i<linB; i++){
        for(int j=0; j<colB; j++){
            printf("%lf ", m2[i][j]);
        }
        printf("\n");
    }

    printf("matriz BT\n");

    for(int i=0; i<linB; i++){
        for(int j=0; j<colB; j++){
            printf("%lf ", m2t[i][j]);
        }
        printf("\n");
    }

    printf("matriz Resultante\n");

    for(int i=0; i<linA; i++){
        for(int j=0; j<colB; j++){
            printf("%lf ", ans[i][j]);
        }
        printf("\n");
    }
}
