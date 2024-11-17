#include <stdio.h>

int main() {
    // Initial balance declaration 
    int balance = 1000;

    // Declaring Arrays: 
    /*positive = deposit, negative = withdrawal*/
    int transactions[] = {200, -150, -500, -400, -50, -200, 300}; 
    int num_transactions = sizeof(transactions) / sizeof(transactions[0]); //obtaining the number of elements in the transactions array. 

    //initiating array for unprocessed transactions
    int tobeprocessed[100];
    int tobeprocessed_count = 0;

    // Process each transaction
    for (int i = 0; i < num_transactions; i++) {
        int transaction = transactions[i]; //storing transaction into its slot. 

        // When transaction is a withdrawal
        if (transaction < 0) {
            if (balance + transaction < 0) { //withdrawal exceeds the current balance and skip transaction.
                printf("Transaction %d is invalid (insufficient balance).\n", transaction);
                // Store it in the tobeprocessed array
                tobeprocessed[tobeprocessed_count++] = transaction;
                continue; // Skip this transaction
            }
        }

        // Update balance if the transaction is valid
        balance += transaction;
        
        if (transaction > 0) //when transaction is a deposit
        printf("Transaction %d, is successful.\n", transaction);
        

        // If balance reaches 0, stop further transactions
        if (balance == 0) {
            printf("Balance reached 0. No further transactions will be processed.\n");
            // Store remaining transactions in tobeprocessed array
            for (int j = i + 1; j < num_transactions; j++) {
                tobeprocessed[tobeprocessed_count++] = transactions[j];
            }
            break; // Exit the loop since no more transactions should be processed
        }
    }

    // Print final balance
    printf("\nFinal Balance: %d AED\n", balance);

    // Print unprocessed transactions
    printf("\nUnprocessed Transactions:"); //use for loop as it is an array
    for (int i = 0; i < tobeprocessed_count; i++) {
        printf("%d\n", tobeprocessed[i]);
    }
    printf("\n");

    return 0;
}

