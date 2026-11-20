#include <stdio.h>

static void clear_input(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int main(void)
{
    int choice;
    float balance = 5000.0f, amount;

    printf("===== ATM SYSTEM =====\n");

    while (1)
    {
        printf("\n1. Balance Enquiry");
        printf("\n2. Deposit");
        printf("\n3. Withdraw");
        printf("\n4. Exit");

        printf("\nEnter your choice: ");
        if (scanf("%d", &choice) != 1)      
        {
            if (feof(stdin))
                return 0;                   
            printf("Invalid Choice!\n");
            clear_input();                  
            continue;
        }

        switch (choice)
        {
            case 1:
                printf("Balance = %.2f\n", balance);
                break;

            case 2:
                printf("Enter deposit amount: ");
                if (scanf("%f", &amount) != 1)
                {
                    printf("Invalid Amount!\n");
                    clear_input();
                    break;
                }

                if (amount > 0)
                {
                    balance = balance + amount;
                    printf("Deposit Successful!\n");
                    printf("Balance = %.2f\n", balance);
                break;

                    
                }
                else
                    printf("Invalid Amount!\n");
                break;

            case 3:
                printf("Enter withdrawal amount: ");
                if (scanf("%f", &amount) != 1)
                {
                    printf("Invalid Amount!\n");
                    clear_input();
                    break;
                }

                if (amount > 0 && amount <= balance)
                {
                    balance = balance - amount;
                    printf("Withdrawal Successful!\n");
                    printf("Balance = %.2f\n", balance);
                break;

                }
                else
                    printf("Insufficient Balance or Invalid Amount!\n");
                break;

            case 4:
                printf("Thank You for Using ATM!\n");
                return 0;

            default:
                printf("Invalid Choice!\n");
                break;
        }
    }

    return 0;
}
