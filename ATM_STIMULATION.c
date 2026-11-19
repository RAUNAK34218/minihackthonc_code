#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define INITIAL_BALANCE 5000.00
#define MAX_TRANSACTION 1000000.00
#define LINE_SIZE       64

typedef enum { INPUT_OK, INPUT_INVALID, INPUT_EOF } InputStatus;

static void        displayMenu(void);
static InputStatus readLine(char *buf, size_t size);
static InputStatus readInt(int *value);
static InputStatus readAmount(double *value);
static void        checkBalance(double balance);
static double      depositMoney(double balance);
static double      withdrawMoney(double balance);

int main(void) {
    double balance = INITIAL_BALANCE;
    int choice = 0;

    printf("========================================\n");
    printf("      WELCOME TO THE ATM SIMULATION     \n");
    printf("========================================\n");
    printf("Sample Account Initial Balance: %.2f\n", balance);

    for (;;) {
        displayMenu();

        InputStatus st = readInt(&choice);
        if (st == INPUT_EOF) {
            printf("\n\nInput ended. Final Balance: %.2f\nGoodbye!\n", balance);
            break;
        }
        if (st == INPUT_INVALID) {
            printf("\n[Error] Invalid input! Please enter a number between 1 and 4.\n");
            continue;
        }

        if (choice == 4) {
            printf("\nThank you for using the ATM. Final Balance: %.2f\n", balance);
            printf("Exiting program. Goodbye!\n");
            break;
        }

        switch (choice) {
            case 1: checkBalance(balance);              break;
            case 2: balance = depositMoney(balance);    break;
            case 3: balance = withdrawMoney(balance);   break;
            default:
                printf("\n[Error] Invalid choice! Please select an option from 1 to 4.\n");
        }
    }
    return 0;
}

static void displayMenu(void) {
    printf("\n--------------- ATM MENU ---------------\n");
    printf("1. Balance Enquiry\n");
    printf("2. Cash Deposit\n");
    printf("3. Cash Withdrawal\n");
    printf("4. Exit\n");
    printf("----------------------------------------\n");
    printf("Enter your choice (1-4): ");
}

static InputStatus readLine(char *buf, size_t size) {
    if (fgets(buf, (int)size, stdin) == NULL)
        return INPUT_EOF;

    size_t len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\n') {
        buf[len - 1] = '\0';
        return INPUT_OK;
    }
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) { }
    return INPUT_INVALID;
}

static InputStatus readInt(int *value) {
    char line[LINE_SIZE], *end;
    InputStatus st = readLine(line, sizeof line);
    if (st != INPUT_OK) return st;

    long v = strtol(line, &end, 10);
    if (end == line) return INPUT_INVALID;
    while (*end == ' ' || *end == '\t') end++;
    if (*end != '\0' || v < -1000000 || v > 1000000) return INPUT_INVALID;

    *value = (int)v;
    return INPUT_OK;
}

static InputStatus readAmount(double *value) {
    char line[LINE_SIZE], *end;
    InputStatus st = readLine(line, sizeof line);
    if (st != INPUT_OK) return st;

    double v = strtod(line, &end);
    if (end == line) return INPUT_INVALID;
    while (*end == ' ' || *end == '\t') end++;
    if (*end != '\0') return INPUT_INVALID;

    if (!isfinite(v) || v <= 0 || v > MAX_TRANSACTION)
        return INPUT_INVALID;
    if (fabs(v * 100.0 - round(v * 100.0)) > 1e-6)
        return INPUT_INVALID;

    *value = v;
    return INPUT_OK;
}

static void checkBalance(double balance) {
    printf("\n--- Balance Enquiry ---\n");
    printf("Current Available Balance: %.2f\n", balance);
}

static double depositMoney(double balance) {
    double amount;
    printf("\n--- Cash Deposit ---\n");
    printf("Enter amount to deposit: ");

    if (readAmount(&amount) != INPUT_OK) {
        printf("[Error] Invalid amount! Enter a positive number (max %.2f, 2 decimals).\n",
               MAX_TRANSACTION);
        return balance;
    }

    balance = round((balance + amount) * 100.0) / 100.0;
    printf("Deposit successful! Amount deposited: %.2f\n", amount);
    printf("Updated Balance: %.2f\n", balance);
    return balance;
}

static double withdrawMoney(double balance) {
    double amount;
    printf("\n--- Cash Withdrawal ---\n");
    printf("Available Balance: %.2f\n", balance);
    printf("Enter amount to withdraw: ");

    if (readAmount(&amount) != INPUT_OK) {
        printf("[Error] Invalid amount! Enter a positive number (max %.2f, 2 decimals).\n",
               MAX_TRANSACTION);
        return balance;
    }
    if (amount > balance) {
        printf("[Error] Insufficient balance! Cannot withdraw %.2f (Available: %.2f).\n",
               amount, balance);
        return balance;
    }

    balance = round((balance - amount) * 100.0) / 100.0;
    printf("Withdrawal successful! Amount withdrawn: %.2f\n", amount);
    printf("Remaining Balance: %.2f\n", balance);
    return balance;
}
