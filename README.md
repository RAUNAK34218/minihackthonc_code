[README.md](https://github.com/user-attachments/files/35163689/README.md)
# ATM Simulation

> A menu-driven ATM simulation for a single sample account, written in C.

---

## Team Details

| | |
|---|---|
| **Team Name** | SPARTANS |
| **Member 1** | Raunak Pandey |
| **Member 2** | Yash Jindal |

---

## Problem Statement

Build a menu-driven ATM simulation for one sample account. The program must allow:

- balance enquiry
- cash deposit
- cash withdrawal
- exit

It must reject invalid amounts and any withdrawal greater than the available balance.

---

## Objective

To apply fundamental C programming concepts to a practical problem by creating a simple, understandable, menu-driven program that:

- validates user input
- updates the account balance correctly after every transaction
- never allows the balance to be reduced below zero

---

## Features

| # | Feature | Description |
|:---:|---|---|
| 1 | **Balance Enquiry** | Displays the current balance. |
| 2 | **Cash Deposit** | Adds a positive amount to the balance. |
| 3 | **Cash Withdrawal** | Subtracts an amount only when funds are sufficient. |
| 4 | **Exit** | Closes the program. |
| 5 | **Invalid Amount Handling** | Rejects zero, negative and non-numeric amounts and leaves the balance unchanged. |
| 6 | **Insufficient Balance Handling** | Rejects a withdrawal greater than the available balance, so the balance never goes below zero. |

Additional behaviour:

- The sample account starts with an initial balance of **5000.00**.
- Zero, negative and non-numeric amounts are rejected, and the balance stays unchanged.
- A withdrawal greater than the available balance is rejected.
- Invalid menu input (letters or numbers outside 1-4) shows an error and the menu is displayed again.
- Leftover characters in the input buffer are cleared so the program never gets stuck in an endless loop.
- If the input ends (EOF), the program exits cleanly.

---

## Algorithm

```
1.  START
2.  Set balance = 5000.00
3.  Print the welcome heading
4.  REPEAT forever:
      4.1  Display the menu (1. Balance Enquiry, 2. Deposit, 3. Withdraw, 4. Exit)
      4.2  Read the choice
           - if input is not a number:
                 if input has ended (EOF) -> STOP
                 otherwise print "Invalid Choice!", clear the input buffer, go to 4.1
      4.3  If choice = 1:
                 print the balance
      4.4  If choice = 2 (Deposit):
                 read the amount
                 if the amount is not a number            -> print "Invalid Amount!"
                 else if amount > 0                        -> balance = balance + amount
                                                              print "Deposit Successful!"
                 else                                      -> print "Invalid Amount!"
      4.5  If choice = 3 (Withdraw):
                 read the amount
                 if the amount is not a number            -> print "Invalid Amount!"
                 else if amount > 0 AND amount <= balance  -> balance = balance - amount
                                                              print "Withdrawal Successful!"
                 else                                      -> print "Insufficient Balance or Invalid Amount!"
      4.6  If choice = 4:
                 print "Thank You for Using ATM!" -> STOP
      4.7  Otherwise:
                 print "Invalid Choice!"
5.  STOP
```

### Flow of the program

```
          +-------------+
          |    START    |
          +------+------+
                 |
        balance = 5000.00
                 |
                 v
        +-----------------+  <-----------------------------+
        |  Display menu   |                                |
        |  Read choice    |                                |
        +--------+--------+                                |
                 |                                         |
       valid number? --- no --> "Invalid Choice!" ---------+
                 | yes
                 v
        +--------+--------+--------+--------+
        |        |        |        |        |
        1        2        3        4      other
        |        |        |        |        |
     show     deposit  withdraw   exit    "Invalid
     balance  (amt>0)  (0<amt     (STOP)   Choice!"
        |        |      <=balance)           |
        +--------+--------+                  |
                 |                           |
                 +---------------------------+
                 |
                 +--> back to "Display menu"
```

---

## C Concepts Used

| Concept | Where it is used |
|---|---|
| **Header file** (`#include <stdio.h>`) | Gives access to `printf`, `scanf`, `getchar`, `feof`, `EOF` and `stdin`. |
| **Variables and data types** (`int`, `float`) | `choice` is an `int`; `balance` and `amount` are `float` so that decimal amounts work. |
| **Initialisation** | `balance = 5000.0f` sets the initial account balance. |
| **Input and output** (`printf`, `scanf`) | Menu display, prompts, and reading the choice and amounts. |
| **Format specifiers** (`%d`, `%f`, `%.2f`) | Reading an integer and a float, and printing the balance with 2 decimal places. |
| **Infinite loop** (`while (1)`) | Keeps showing the menu until the user selects Exit. |
| **`switch-case` statement** | Selects the action for options 1-4, with `default` for invalid choices. |
| **`break` and `continue`** | `break` ends a case; `continue` returns to the menu after invalid input. |
| **`if-else` and relational/logical operators** | `amount > 0 && amount <= balance` decides whether a withdrawal is allowed. |
| **Input validation** (return value of `scanf`) | `scanf` returns the number of items read, so `!= 1` detects non-numeric input. |
| **User-defined function** (`static void clear_input(void)`) | Clears the leftover characters from the input buffer. |
| **Character input and `EOF`** (`getchar`, `feof`) | Discards invalid input up to the newline and detects the end of input. |
| **Arithmetic operators** (`+`, `-`) | Updating the balance on deposit and withdrawal. |
| **`return` statement** | Ends the program from `main` on Exit or end of input. |

---

## Project Structure

```
ATM-Simulation/
├── ATM_STIMULATION.c    # complete source code
└── README.md            # project documentation
```

---

## How to Compile and Run

**Requirements:** a C compiler such as GCC (MinGW-w64 / MSYS2 on Windows). VS Code with the *C/C++* extension is recommended.

### Windows (PowerShell / Command Prompt)

```
gcc -Wall -Wextra -std=c99 ATM_STIMULATION.c -o atm
.\atm
```

### Linux / macOS

```
gcc -Wall -Wextra -std=c99 ATM_STIMULATION.c -o atm
./atm
```

### Quick compile without options

```
gcc ATM_STIMULATION.c
.\a.exe          # Windows (use ./a.out on Linux/macOS)
```

| Option | Meaning |
|---|---|
| `-Wall -Wextra` | Turn on compiler warnings. |
| `-std=c99` | Use the C99 standard. |
| `-o atm` | Name the output program `atm` (`atm.exe` on Windows). |

---

## Sample Test Cases

All seven cases below were run on the actual program. The menu is printed before every prompt; it is left out of the transcripts to keep them short. Text after a prompt is what the user typed.

### Test 1: Balance enquiry

**Input:** `1`, then `4`

```
Enter your choice: 1
Balance = 5000.00
Enter your choice: 4
Thank You for Using ATM!
```

**Result:** the initial balance is displayed correctly.

### Test 2: Valid deposit

**Input:** `2`, `500`, then `1`

```
Enter your choice: 2
Enter deposit amount: 500
Deposit Successful!
Enter your choice: 1
Balance = 5500.00
```

**Result:** 500 is added; the balance becomes 5500.00.

### Test 3: Invalid deposit (negative, non-numeric, zero)

**Input:** `2` with `-10`, `2` with `abc`, `2` with `0`, then `1`

```
Enter your choice: 2
Enter deposit amount: -10
Invalid Amount!
Enter your choice: 2
Enter deposit amount: abc
Invalid Amount!
Enter your choice: 2
Enter deposit amount: 0
Invalid Amount!
Enter your choice: 1
Balance = 5000.00
```

**Result:** all three invalid deposits are rejected and the balance is unchanged.

### Test 4: Valid withdrawal

**Input:** `3`, `1000`, then `1`

```
Enter your choice: 3
Enter withdrawal amount: 1000
Withdrawal Successful!
Enter your choice: 1
Balance = 4000.00
```

**Result:** 1000 is subtracted; the balance becomes 4000.00.

### Test 5: Withdrawal greater than the balance

**Input:** `3`, `999999`, then `1`

```
Enter your choice: 3
Enter withdrawal amount: 999999
Insufficient Balance or Invalid Amount!
Enter your choice: 1
Balance = 5000.00
```

**Result:** the withdrawal is rejected and the balance is unchanged.

### Test 6: Invalid menu choice

**Input:** `abc`, `9`, `0`

```
Enter your choice: abc
Invalid Choice!
Enter your choice: 9
Invalid Choice!
Enter your choice: 0
Invalid Choice!
```

**Result:** letters and out-of-range numbers show an error and the menu is displayed again; the program does not crash or loop endlessly.

### Test 7: Exit

**Input:** `4`

```
Enter your choice: 4
Thank You for Using ATM!
```

**Result:** the program ends normally.

### Summary of test cases

| # | Test | Input | Expected result | Status |
|:-:|---|---|---|:-:|
| 1 | Balance enquiry | `1` | Shows 5000.00 | Pass |
| 2 | Valid deposit | `2`, `500` | Balance becomes 5500.00 | Pass |
| 3 | Invalid deposit | `-10`, `abc`, `0` | "Invalid Amount!", balance unchanged | Pass |
| 4 | Valid withdrawal | `3`, `1000` | Balance becomes 4000.00 | Pass |
| 5 | Overdraw | `3`, `999999` | "Insufficient Balance or Invalid Amount!" | Pass |
| 6 | Invalid menu choice | `abc`, `9`, `0` | "Invalid Choice!" and menu again | Pass |
| 7 | Exit | `4` | "Thank You for Using ATM!" and program ends | Pass |

---

## Conclusion

The ATM Simulation meets the requirements of the assignment. It provides balance enquiry, cash deposit, cash withdrawal and exit through a simple menu-driven interface. Deposits and withdrawals update the balance correctly, zero, negative and non-numeric amounts are rejected, and a withdrawal larger than the available balance is refused, so the balance never goes below zero. Invalid menu input is handled without crashing or looping endlessly.

Building the project helped us apply core C concepts: variables and data types, loops, `switch-case`, conditional statements, functions, and input validation using the return value of `scanf`.

**Possible future improvements:** PIN authentication, multiple accounts, a mini statement (transaction history), saving the balance to a file, and storing money as whole paise instead of `float` for exact arithmetic.

---

**Team SPARTANS**: Raunak Pandey and Yash Jindal
