/* This code calculates the house price of a house by learing from
 * training data. It uses pseudo inverse of a given matrix to find the 
 * weight of different features.
 * 
 * Predicted Price : Y = W0 + W1*x1 + W2*X2 + W3*X3 + W4*X4
 * Weight Matrix : W = pseudoInv(X)*Y
 * pseudoInv(X) = inverse(transpose(X)*X) * transpose(X)  
 * 
 * weight(w) = pseudoInv(X) * Y
 * 			where	X = Input data matrix
 * 					Y = Target vector
 * 
 */
 
#include<stdio.h>
#include<stdlib.h>

// all methods declarations
double** multiplyMatrix(double **matA, double **matB, int r1, int c1, int r2, int c2);
double** transposeMatrix(double** mat, int row, int col);
double** inverseMatrix(double **matA, int dimension);
void printMatrix(double **matA, int row,int column){
        for (int i=0;i<row;i++){
            for (int j=0;j<column;j++){
                printf("%lf\t",matA[i][j]);
            }
            printf("\n");
        }
}
void freeMatrix(double **matA, int row){
        for (int i=0;i<row;i++){
          free(matA[i]);
        }
        free(matA);
}
void printArray(double * matA, int row){
    for (int i=0;i<row;i++){
        printf("%lf\n",matA[i]);
    }
}
// main method starts here
int main(int argc, char** argv){
    //-------------------------------------------------------------------------
    //                   **INITIALIZE ALL VARIABLES**
    //-------------------------------------------------------------------------
    //test variables are testFile,testRow, and testColumn
    //train variables are trainFile,trainRow, and trainColumn
    //price variables are just priceMatrix
    FILE *testFile;
    FILE *trainFile;
    testFile=fopen(argv[2],"r");
    trainFile=fopen(argv[1],"r");
    //printf("opened both files\n");
    // scan dim of first array
    int trainColumn;
    fscanf(trainFile,"%d\n",&trainColumn);
    //printf("train column =%d\n",trainColumn);
    int trainRow;
    fscanf(trainFile,"%d\n",&trainRow);
    //printf("train row= %d\n",trainRow);
    int testRow;
    fscanf(testFile,"%d\n",&testRow);
    //printf("test row =%d\n",testRow);
    //column number for train and test matrices are the same
    int testColumn=trainColumn;
    //printf("test column=%d\n",testColumn);
    double ** trainMatrix=malloc(trainRow*sizeof(double*));
    double *  priceMatrix=malloc (trainRow*sizeof(double));
    double ** testMatrix=malloc(testRow*sizeof(double*));
    //------------------------------------------------------------------------
    //           **POPULATE TRAIN MATRIX AND PRICE MATRIX**
    //------------------------------------------------------------------------
    //populate with the values in the text file with first column being 1s
    //printf("starting to populate train and price matrix\n");
    for (int i=0;i<trainRow;i++){
        trainMatrix[i]=(double*)malloc((trainColumn+1)*sizeof(double));
        //printf("finished dynammically allocating memory for columns\n");
        //you do less than or equal to because there is a column plus 1 
        for (int j=0;j<trainColumn+1;j++){
            //printf("entered for loop to populate for the %d time\n",j);
            if(j==0){
                //allocates the first column as 1
                trainMatrix[i][j]=(double)1;
                //printf("%lf\t",trainMatrix[i][j]);
            }
            else{
                //scans train file and inputs values into an array
                //printf("entered scanf statement\n");
                fscanf(trainFile,"%lf,",&trainMatrix[i][j]);
                //printf("left scanf statement\n");
                //printf("%lf\t",trainMatrix[i][j]);
            }
            //printf("\n");
        }
        //inputs prices into a separate price matrix
        fscanf(trainFile,"%lf\n",&priceMatrix[i]);
    }
    //printf("finished populating train and price matrix\n");
    fclose(trainFile);
    //------------------------------------------------------------------------
    //                   **POPULATE TEST MATRIX**
    //-----------------------------------------------------------------------
    //populate test array with values in the test file
    for (int i=0;i<testRow;i++){
        testMatrix[i]=(double*)malloc(testColumn*sizeof(double));
        for (int j=0;j<testColumn;j++){
            //after the pointer is at the last column, make sure it goes to the next row
            if (j!=testColumn-1){
             fscanf(testFile,"%lf,",&testMatrix[i][j]);
            }
            else{
             fscanf(testFile,"%lf\n",&testMatrix[i][j]);
            }
        }
    }
    fclose(testFile);
    //-------------------------------------------------------------------------
    //                      *CALL METHODS*
    //-------------------------------------------------------------------------
    // printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
    //  printf("Train Matrix:\n");
    //  printMatrix(trainMatrix,trainRow,trainColumn+1);
    //  printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
    // printf("Price Matrix:\n");
    //  printArray(priceMatrix,trainRow);
    //  printf("-----------------------------------------------------------------------------------------------------------------------------------------\n");
    //   printf("Test Matrix:\n");
    //  printMatrix(testMatrix,testRow,testColumn);
    //   printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
    // printf("Transposed Matrix:\n");
    double ** t=transposeMatrix(trainMatrix,trainRow,trainColumn+1);
    double ** m=multiplyMatrix(t,trainMatrix,trainColumn+1,trainRow,trainRow,trainColumn+1);
    double ** i=inverseMatrix(m,trainColumn+1);
    //printMatrix(i,trainColumn+1,trainColumn+1);
    // printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
    //  printf("Multiplied Matrix:\n");
    // printMatrix(m,trainColumn+1,trainColumn+1);
    //  printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
    //  printf("W Matrix:\n");
    //printMatrix(w,trainColumn+1,trainColumn+1);
    // printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
    // printf("((X^TX)^-1)X^T:\n");
    double **w=multiplyMatrix(i,t,trainColumn+1,trainColumn+1,trainColumn+1,trainRow);
    //printMatrix(w,trainColumn+1,trainRow);
    // //cuz this dumbass program wont freaking run for 1d arrays smh
    double * semiFinal =malloc ((trainColumn+1)*sizeof(double));
    double * final =malloc(testRow*sizeof(double));
    //w is the below function
    for (int i =0;i<trainColumn+1;i++){
        semiFinal[i]=0;
        for(int j=0;j<trainRow;j++){
             semiFinal[i] += (w[i][j] * priceMatrix[j]);
         }
     }
    // printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
    // printf("X:\n");
    // printMatrix(testMatrix,testRow,testColumn);
    // printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
    //printf("Weights:\n");
    //printArray(semiFinal,trainColumn+1);
    // printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
    // printf("semiFinal[4]=%lf\n",semiFinal[4]);
    //printf("sfinal:\n");
    //printArray(semiFinal,testRow);
    for (int k =0;k<testRow;k++){
            for (int j=0;j<trainColumn+1;j++){
                if (j==0){
                final[k]=semiFinal[j];
                //printf("w[%d]=%lf\n",k,semiFinal[j]);
                }
                else{
                final[k] = final[k]+(testMatrix[k][j-1] * semiFinal[j]);
                //printf("testMatrix[%d][%d]=%lf,semifinal[%d]=%lf\n",k,j-1,testMatrix[k][j-1],j,semiFinal[j]);
                //printf("final +testmatrix[%d][%d]*semifinal[%d]=%lf\n",k,j-1,j,final[k]);
                }
            }
        //printf("final[%d]%lf\n",k,final[k]);
    }
    for (int i=0;i<testRow;i++){
       printf("%0.0lf\n",final[i]);
    }
    freeMatrix(trainMatrix,trainRow);
    freeMatrix(testMatrix,testRow);
    freeMatrix(t,trainColumn+1);
    freeMatrix(m,trainColumn+1);
    freeMatrix(i,trainColumn+1);
    freeMatrix(w,trainColumn+1);
    free(priceMatrix);
    free(semiFinal);
    free(final);
	return 0;
}

double** multiplyMatrix(double **matA, double **matB, int r1, int c1, int r2, int c2){
    double** result=malloc(r1*sizeof(double*)); 
    for (int i = 0; i < r1; i++) {
        //matrix of dimension r1xc1 multiplied by r2xc2 results in dimensions r1xc2
        result[i]=(double*)malloc(c2*sizeof(double));
      for (int j = 0; j < c2; j++) {
          result[i][j]=0;
         for (int k = 0; k < c1; k++) {
            result[i][j] += matA[i][k] * matB[k][j];
            //printf("Multiplied Matrix:");
            //printf("%lf\t",result[i][j]);
         }
      }
     // printf("\n");
    }    

    return result;
}


double** transposeMatrix(double** mat, int row, int col){
    //switch rows an columns
	double** matTran=malloc(col*sizeof(double*));

    for (int i=0; i<col; i++){
        matTran[i]=(double*)malloc(row*sizeof(double));
        for (int j=0;j<row;j++){
            matTran[i][j]=mat[j][i];
        }
    }
    return matTran;        
}


double** inverseMatrix(double **matA, int dimension){
    double** matI=malloc(dimension*sizeof(double*)); 
    //create an identity matrix
    for (int i=0;i<dimension;i++){
        matI[i]=(double*)malloc(dimension*sizeof(double));
        for (int j=0;j<dimension;j++){
            if (i==j){
                matI[i][j]=(double)1;
            }
            else{
                matI[i][j]=(double)0;
            }
        }
    }
    for (int i=0;i<dimension;i++){
        double f=matA[i][i];
        //divide both matrices
        for (int j=0;j<dimension;j++){
            matA[i][j]=matA[i][j]/f;
            matI[i][j]=matI[i][j]/f;
        }
        for (int j=i+1;j<dimension;j++){
            f=matA[j][i];
            for (int k=0;k<dimension;k++){
                matA[j][k]=matA[j][k]-(matA[i][k]*f);
                matI[j][k]=matI[j][k]-(matI[i][k]*f);
            }
        }
    }
    for (int i=dimension-1;i>=0;i--){
        for (int j=i-1;j>=0;j--){
            double f=matA[j][i];
            for (int k=0;k<dimension;k++){
                matA[j][k]=matA[j][k]-(matA[i][k]*f);
                matI[j][k]=matI[j][k]-(matI[i][k]*f);
            }
        }
    }
	return matI;
}
