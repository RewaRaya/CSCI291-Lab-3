#include <stdio.h>
#include <stdbool.h>

//Program Constants
#define SIZE 24
#define NROWS 8
#define NCOLS 3

// Function Prototypes
bool isValid(const int arr[], int length, int pos, int row, int col, int numR, int numC);
void remove_element(int arr[], int length, int pos, int row, int col, int numR, int numC, bool arrIs2D);
void insert_element(int arr[], int length, int pos, int row, int col, int value, int numR, int numC, bool arrIs2D);
void reshape(const int arr[], int length, int numR, int numC, int arr2D[numR][numC]);
void trans_matrix(int numR, int numC, const int mat[numR][numC], int mat_transp[numC][numR]);
bool found_duplicate(const int arr[], int length, int numR, int numC, bool arrIs2D);
void displayArray(int arr[], int length, int numR, int numC, bool arrIs2D); //extra function to display before and after changes.

//Main Function of Program 
int main() {
    /*Declaring the 1D and 2D arrays*/
    int arr[SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23};
    int arr2[NROWS][NCOLS] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {9, 10, 11}, {12, 13, 14}, {15, 16, 17}, {18, 19, 20}, {21, 22, 23}};
    
    /*Declaring Variables*/
    int x, pos, value, arrX, row, col; 
    
    /*Interface Loop*/
    while (1) {
        /*Displaying the 1D and 2D arrays*/
        printf("\n1D Array:\n");
        displayArray(arr, SIZE, NROWS, NCOLS, false);
        printf("\n\n2D Array:\n");
        displayArray(&arr2[0][0], SIZE, NROWS, NCOLS, true); 
        
        /*Printing Menu*/
        printf("\n      --- Menu ---\n");
        printf("1. Remove an Element Function\n");
        printf("2. Insert an Element Function\n");
        printf("3. Reshape Array Function\n");
        printf("4. Transpose 2D Array Function\n");
        printf("5. Find a Duplicate Function\n");
        printf("\n0. Exit\n");
        printf("\nEnter Operation number: ");
        scanf("%d", &x); //variable x stores value of choice of operation
     
        
        /* When exit is chosen*/
        if (x == 0) {
            printf("\nProgram exited successfully.\n");
            break;
        }
        
        /* If exit is not chosen*/
        // Choose which array to operate on:
        printf("\nChoose the array (1 for 1D array & 2 for 2D array): "); 
        scanf("%d", &arrX); //arrX stores the value for which array.
        
        /*Scenario for Invalid array number chosen*/
        if (arrX != 1 && arrX != 2){
            puts("ERROR! Invalid array size!");
        }
        
        /*Valid input scenario*/
        //Declaration of the boolean variable arrIs2D
        bool arrIs2D = (arrX == 2); //True if arrX=2, otherwise False
        
        //Using switch for each according to user input
        switch (x) {
            // Remove element function
            case 1:
                if (arrIs2D) { // 2D array case
                    printf("\nEnter row (0-%d) and column (0-%d) to remove: ", NROWS-1, NCOLS-1); 
                    //subtract 1 as index starts from 0
                    scanf("%d %d", &row, &col); 
                    /*User enters the row and the column
                    
                    /*use isValid to check if input is withing array size*/
                    if (isValid(arr, SIZE, -1, row, col, NROWS, NCOLS)) {
                        //call to function if true is returned from isValid
                        remove_element(&arr2[0][0], SIZE, -1, row, col, NROWS, NCOLS, true);
                        printf("\nElement removed from 2D array.\n");
                    } //end of nested if
                    
                    //if not valid position:
                    else {
                        printf("\nERROR! Invalid position!\n");
                    }//end of nested else
                } //end of 1st if 
                
                else { // 1D array case
                    printf("\nEnter position to remove (0-%d): ", SIZE-1);
                    scanf("%d", &pos);
                    
                    /*use isValid to check if input is withing array size*/
                    if (isValid(arr, SIZE, pos, -1, -1, NROWS, NCOLS)) {
                        remove_element(arr, SIZE, pos, -1, -1, NROWS, NCOLS, false);
                        printf("\nElement removed from 1D array.\n");
                    } 
                    
                    //if not valid position:
                    else {
                        printf("\nERROR! Invalid position!\n");
                    }
                }
            break;

            case 2: // Insert element function
                printf("\nEnter value to insert: ");
                scanf("%d", &value); //value of element inserted
                
                if (arrIs2D) { //2D array case
                    printf("\nEnter row (0-%d) and column (0-%d) to insert value in: ", NROWS-1, NCOLS-1);
                    scanf("%d %d", &row, &col); //position to insert element in
                    
                    if (isValid(arr, SIZE, -1, row, col, NROWS, NCOLS)) {
                        insert_element(&arr2[0][0], SIZE, -1, row, col, value, NROWS, NCOLS, true);
                        printf("\nElement inserted into 2D array.\n");
                    } 
                    
                    else {
                        printf("\nERROR! Invalid position!\n");
                    }
                } 
                
                else { //1D array case
                    printf("\nEnter position to insert (0-%d): ", SIZE-1);
                    scanf("%d", &pos); //position to insert element in
                    
                    if (isValid(arr, SIZE, pos, -1, -1, NROWS, NCOLS)) {
                        insert_element(arr, SIZE, pos, -1, -1, value, NROWS, NCOLS, false);
                        printf("\nElement inserted into 1D array.\n");
                    } 
                    
                    else {
                        printf("\nERROR! Invalid position!\n");
                    }
                }
                break;

            case 3: // Reshape 1D array into 2D array function
                if(SIZE != NROWS*NCOLS){ //Valdiating the Compatibility of 1D to become a 3x8 matrix
                    puts("ERROR! Array sizes do NOT match."); break;  //printed if not compatible 
                }
                
                if (arrX == 2){ //when 2D is inserted to be reshaped
                    puts("ERROR! 2D arry cannot be reshaped as it is of matrix form.");
                    break;
                }
                
                else { 
                reshape(arr, SIZE, NROWS, NCOLS, arr2); //calling reshape function
                printf("\n1D array reshaped into 2D array.\n"); //message printed after reshape function is complete
                break;
                }
                
            case 4: // Transpose 2D array
                {
                    if(arrX == 1) //case when 1D array is chosen to be transposed
                    puts("ERROR! Array 1 Cannot be transposed!");
                    
                    else {
                    int arr2_transp[NCOLS][NROWS]; //array that stores the transposed 2D array
                    trans_matrix(NROWS, NCOLS, arr2, arr2_transp); //calling transpose function
                    }
                }
                break;

            case 5: // Check for duplicates in 1D or 2D array 
            /*if for duplicate presence, else for no duplicate present*/
                if (arrIs2D) {
                    if (found_duplicate(&arr2[0][0], SIZE, NROWS, NCOLS, true)) {
                        printf("\nDuplicates found in 2D array.\n"); //when return is true
                    } else {
                        printf("\nNo duplicates in 2D array.\n"); //when return is false
                    }
                } 
                
                 if (arrX == 1) {
                    if (found_duplicate(arr, SIZE, NROWS, NCOLS, false)) {
                        printf("\nDuplicates found in 1D array.\n"); //when return is true
                    } else {
                        printf("\nNo duplicates in 1D array.\n"); //when return is false
                    }
                }
                break;
                
            //When invalid number scanned:
            default:
                printf("ERROR! Invalid choice! Please try again.\n");
                break;
        }
    }
    return 0;
}

// Unified displayArray function for both 1D and 2D arrays
void displayArray(int arr[], int length, int numR, int numC, bool arrIs2D) {
    if (arrIs2D) {
        // Display as 2D array
        for (int i=0; i < numR; i++) {
            for (int j=0; j < numC; j++) {
                printf("%d ", arr[i*numC+j]); // Flat indexing for 2D
            }
            printf("\n");
        }
    } else {
        // Display as 1D array
        for (int i=0; i < length; i++) {
            printf("%d ", arr[i]);
        }
    }
}

// isValid function for both 1D and 2D arrays
bool isValid(const int arr[], int length, int pos, int row, int col, int numR, int numC) {
    if (row == -1 && col == -1) {
        return pos >= 0 && pos < length;
    } else if (pos == -1) {
        return (row >= 0 && row < numR) && (col >= 0 && col < numC);
    }
    return false;
}

// Function to remove an element
void remove_element(int arr[], int length, int pos, int row, int col, int numR, int numC, bool arrIs2D) {
    if (arrIs2D) {
        // 2D array removal
        int n = row * numC + col; //index position for flattened 2D array
        for (int i = n; i < length-1; i++) {
            arr[i] = arr[i+1]; //shifiting values after position n
        }
    } else {
        // 1D array removal
        for (int i = pos; i < length-1; i++) {
            arr[i] = arr[i+1]; //shifiting values after pos position
        }
    }
}

// Function to insert an element
void insert_element(int arr[], int length, int pos, int row, int col, int value, int numR, int numC, bool arrIs2D) {
    if (arrIs2D) {
        // Handle 2D array insertion
        int n = row * numC + col;
        if (n < length) {  // Check if insertion is within bounds
            for (int i = length-1; i > n; i--) {
                arr[i] = arr[i-1]; //shifting to the right
            }
            arr[n] = value; //space for the element to be inserted in position
        } else { //invalid position inputted case
            printf("ERROR! Position out of bounds for 2D array.\n");
        }
    } else {
        // Handle 1D array insertion
        if (pos < length) {  // Ensure position is within bounds
            for (int i = length-1; i > pos; i--) {
                arr[i] = arr[i-1]; //shifting to the right
            }
            arr[pos] = value; //space for the element to be inserted in position
        } else { //invalid position inputted case
            printf("ERROR! Position out of bounds for 1D array.\n");
        }
    }
}


// Function to reshape 1D array to 2D
void reshape(const int arr[], int length, int numR, int numC, int arr2D[numR][numC]) {
    int n=0;
    for (int i=0; i < numR; i++) {
        for (int j=0; j < numC; j++) {
            arr2D[i][j] = arr[n++]; //reshaping the array into a matrix of i rows and j cols
            //incrementing n starting from 0 uptill limit (23)
        }
    }
    printf("\nArray after reshaping:\n");//displaying array after reshaping using function
    displayArray(&arr2D[0][0], length, numR, numC, true);  
}

// Function to transpose a 2D array
void trans_matrix(int numR, int numC, const int mat[numR][numC], int mat_transp[numC][numR]) {
    for (int i=0; i < numR; i++) {
        for (int j=0; j < numC; j++) {
            mat_transp[j][i] = mat[i][j]; //reshaping 2D array into a 1D array
        }
        //mat[][] represents original array
        //mat_transp[][] is transposed value assigned to the value of mat[][]
    }
    printf("\nTransposed 2D Array:\n"); //printing tranposed array using function
    displayArray(&mat_transp[0][0], numR * numC, numC, numR, true);
}

// Function to check for duplicates
bool found_duplicate(const int arr[], int length, int numR, int numC, bool arrIs2D) {
    for (int i=0; i < length; i++) {
        for (int j=i+1; j < length; j++) {
            if (arr[i] == arr[j]) { //going through every element to check if the are the same
                return true;
            }
        }
    }
    return false; //case when no duplicates
}
