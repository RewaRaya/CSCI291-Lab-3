#include<stdio.h> 
#include <stdbool.h> 
#define SIZE 24
#define nRows 8
#define nCols 3
// PROTOTYPES
void print_array(int array[], int length);
void print_matrix(int mat[][nCols], int rows);

/*Prototypes given:*/
bool isValid(const int arr[], int length, int pos, int nRows, int nCols);
void remove_element(int arr[], int length, int pos, int nRows, int nCols, int arr2[nRows][nCols]);
void insert_element(int arr[],int length, int pos, int value);
void reshape(const int arr[], int length, int nRows, int nCols, int arr2d[nRows][nCols]);
void trans_matrix(int nRows, int nCols, const int mat[nRows][nCols], int mat[nCols][ nRows]);
bool found_duplicate(int arr[], int length);


int main()
{
int arr[SIZE];
int arr2d[nRows][nCols];
print_matrix(arr2d,nRows);
//Call to different functions
}

void print_array(int array[], int length){
   for(int i=0;i<length; i++)
      printf("array[%d]= %d\n", i, array[i]);
}

void print_matrix(int mat[][nCols], int rows){
   for(int i=0;i<rows; i++){
    for(int j=0;j<nCols; j++)
         printf("mat[%d][%d]= %d\n", i,j, mat[i][j]);
    puts("");     
   }     
}

//FUNCTION DEFINITIONS
bool isValid(const int arr[], int length, int pos, int nRows, int nCols){
   if (nRows == 0 && nCols == 0){ //Definition of 1D array
      return (pos >= 0 && pos < length); //Condtions for position in 1D array
   }
   else {
      int row = pos / nCols; //position in rows 
      int col = pos % nCols; //position in the row (column of row)
      return (row >= 0 && row < nRows && col >= 0 && col < nCols); //Condtions for position in 2D array
   }
}

void remove_element(int arr[], int length, int pos, int nRows, int nCols, int arr2[nRows][nCols]) {
   //if the position given was not within array
   if (!isValid(arr, length, pos)) { 
      printf("ERROR! Invalid Position!");
      return;
   }

   if (nRows == 0 && nCols == 0) {
      //if position given is in 1D array 
      for (int i = pos; i < length - 1; i++){ 
         arr[i] = arr[i+1]; //shifting to the left of the row (1D array is a row)
      }
      arr[length-1]=0; //setting the last index to zero 
   }

   else {
      int row = pos / nCols;
      int col = pos % nCols;


      for(int i = (row*nCols)+col; i < (nRows * nCols)-1; i++){ //Shifts elements to the left in 2D matrix
         int currentR = i / nCols;
         int currentC = i % nCols;
         int nextR = (i+1)/nCols;
         int nextC = (i+1)&nCols;
         arr2[currentR][currentC] = arr2[nextR][nextC];
      }
      arr2[nRows-1][nCols-1]=0; //last variable of the matrix is zero
   }
}

void insert_element(int arr[], int length, int pos, int value, int nRows, int nCols, int arr2[nRows][nCols]) {
   if (!isValid(length, pos, nRwos, nCols)) { //position that is not in 1D and 2D array
      printf("ERROR! Invalid Position!");
      return
   }

   if (nRows==0 && nCols==0){ //1D array case
      for (int i=length-1; i>pos; i--){
         arr[i]=arr[i-1];
      }
      arr[pos]=value;
   }
   else{ //2D array case
   //Find coordinate:
      int row = pos / nCols;
      int col = pos % nCols;

      for (int i = (nRows*nCols)-1; i < nRowss*nCols; i++){ //shift elements to the right in the 2D matrix
         int currentR = i /nCols;
         int currentC = i%nCols;
         int previousR = (i-1)/nCols;
         int perviousC = (i-1)%nCols;
         arr2[currentR][currentC]=arr2[previousR][perviousC];
      }
      arr2[row][col] = value; //putting the value in place
   }
}

 