#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include <time.h>

void addTransaction(char type[], float amount) {
    FILE *fp = fopen("history.txt", "a");

    time_t t = time(NULL);
    char *dt = ctime(&t);

    fprintf(fp, "%s - %s : %.2f\n", dt, type, amount);

    fclose(fp);
}

void lockaccount();



void savebalance(float balance)
{
    FILE *fp=fopen("balance.txt", "w");
    fprintf(fp,"%.2f",balance);
    fclose(fp);
}
int loadPin() {
    int pin;
    FILE *fp = fopen("pin.txt", "r");

    if (fp == NULL) {
        return 1234;  // default PIN
    }

    fscanf(fp, "%d", &pin);
    fclose(fp);
    return pin;
}

void savePin(int newPin) {
    FILE *fp = fopen("pin.txt", "w");
    fprintf(fp, "%d", newPin);
    fclose(fp);
}
int islocked() {
    FILE *fp=fopen("lock.txt","r");
    int status;
    if (fp==NULL){
        return 0;
    }
    else{
        fscanf(fp,"%d",&status);
        fclose(fp);
        return status;
    }
}
    void lockaccount()
    {
        FILE *fp=fopen("lock.txt","w");
        if(fp!=NULL){
        fprintf(fp,"1");
        fclose(fp);
        }
    }
    void unlockaccount() {
    FILE *fp = fopen("lock.txt", "w");
    if (fp != NULL) {
        fprintf(fp, "0");
        fclose(fp);
    }
}
int hiddenPinInput() {
    int pin = 0;
    char ch;
    int digits = 0;

    while (digits < 4) {
        ch = getch();   

        if (ch >= '0' && ch <= '9') {
            printf("*");     
            pin = pin * 10 + (ch - '0');
            digits++;
        }
    }

    printf("\n");
    return pin;
}


    



int main() {
   if (islocked()) {
    int adminChoice;
    printf("Account is LOCKED.\n");
    printf("1. Admin Login\n");
    printf("2. Exit\n");
    printf("Enter choice: ");
    scanf("%d", &adminChoice);

    if (adminChoice == 1) {
        int adminPass;
        printf("Enter Admin Password: ");
        adminPass = hiddenPinInput();

        if (adminPass == 9999) {   // Admin password
            unlockaccount();
            printf("Account successfully UNLOCKED.\n");
        } else {
            printf("Wrong Admin Password.\n");
            return 0;
        }
    } else {
        return 0;
    }
}


    int pin, correctPin;
correctPin = loadPin();


    printf("===== WELCOME TO ATM =====\n");
    

    int attempts = 0;

while (attempts < 3) {
    printf("Enter your PIN: ");
    pin = hiddenPinInput();


    if (pin == correctPin) {
        break;
    } else {
        attempts++;
        printf("Wrong PIN! Attempts left: %d\n", 3 - attempts);
    }
}

if (attempts == 3) {
    printf("Too many wrong attempts!\n");
    lockaccount();
    printf("Account has been LOCKED.\n");
    return 0;
}


    int choice;
    float balance = 1000;  // initial balance
        FILE *fp = fopen("balance.txt", "r");

    if (fp == NULL)
     {
        balance = 1000;   // default balance first time
    } 
    else {
        fscanf(fp, "%f", &balance);
        fclose(fp);
    }


    while (1) {
        printf("\n==== ATM MENU ====\n");
        printf("1. Check Balance\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Transaction history\n");
        printf("5. Change PIN\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Your balance is: %.2f\n", balance);
                break;

            case 2: {
                float amount;
                printf("Enter amount to deposit: ");
                scanf("%f", &amount);
                balance += amount;
                savebalance(balance);
                FILE *hist= fopen("history.txt","a");
                addTransaction("Deposited", amount);

                fclose(hist);

                printf("Deposit successful!\n");
                break;
            }

            case 3: {
                float amount;
                printf("Enter amount to withdraw: ");
                scanf("%f", &amount);

                if (amount > balance)
                    printf("Insufficient balance!\n");
                else {
                    balance -= amount;
                     savebalance(balance);
                FILE *hist= fopen("history.txt","a");
                addTransaction("Withdrawal", amount);

                fclose(hist);

                    printf("Withdrawal successful!\n");
                }
                break;
            }

            case 4:
                    {
                FILE *hist = fopen("history.txt", "r");
                char line[100];

                if (hist == NULL) {
                    printf("No transactions yet.\n");
                } else {
                    printf("\n--- Transaction History ---\n");
                    while (fgets(line, sizeof(line), hist)) {
                        printf("\n%s", line);
                    }
                    fclose(hist);
                }
                break;
            }
            case 5: {
    int oldPin, newPin;

    printf("Enter current PIN: ");
   oldPin = hiddenPinInput();

    if (oldPin != correctPin) {
        printf("Incorrect current PIN!\n");
        break;
    }

    printf("Enter new PIN: ");
    newPin = hiddenPinInput();

    if (newPin < 1000 || newPin > 9999) {
        printf("PIN must be 4 digits!\n");
        break;
    }

    savePin(newPin);
    correctPin = newPin;

    printf("PIN changed successfully!\n");
    break;
}



            case 6:
                printf("Thank you for using ATM!\n");
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }

}

