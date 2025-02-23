#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct DOG_struct {
    char name[20];
    int payoutRate;
    int odds;
} DOG;

char Menu(void);
void InitializeDogs(DOG dog[]);
char BankingMenu(void);
void BankingDeposit(double* moneyInBank, double* moneyOnHand);
void BankingWithdrawal(double* moneyInBank, double* moneyOnHand);
void Banking(double* moneyInBank, double* moneyOnHand);
void GambleChoices(const DOG dog[], double* wager, int* chosenDog, double* moneyOnHand);
double Gamble(const DOG dog[], double* moneyOnHand, double result[], int numRaces);
void PrintResults(const double RESULT[], const int NUM_RACES);

int main(void) {
    const char GAMBLE_OPTION = 'G';
    const char BANKING_OPTION = 'B';
    const char RESULTS_OPTION = 'R';
    const char LEAVE_OPTION = 'L';
    char menuOption;
    DOG dog[9];
    int numRaces = 0;
    double result[50];
    double moneyInBank = 10000.00;
    double moneyOnHand = 0.00;

    InitializeDogs(dog); //FIXME: Change dog names in InitializeDogs

    menuOption = Menu();

    while (menuOption != LEAVE_OPTION) {
        if (menuOption == GAMBLE_OPTION) {
            if (moneyOnHand <= 0) {
                printf("Please first withdraw money from your bank account to wager\n\n");
                menuOption = Menu();
            }
            else {
                moneyOnHand += Gamble(dog, &moneyOnHand, result, numRaces);  //Asks user for wager and dog to bet on and shows result of race
                if (numRaces < 50) {
                    ++numRaces;    //numRaces increments after each iteration of Gamble function for results function, max 50 increments
                }
                menuOption = Menu();
            } 
        }
        else if (menuOption == BANKING_OPTION) {
            Banking(&moneyInBank, &moneyOnHand);  //Opens banking menu, which gives user option to deposit or withdraw money
            menuOption = Menu();
        }
        else if (menuOption == RESULTS_OPTION) {
            PrintResults(result, numRaces);  //Prints betting results after max 50 races
            menuOption = Menu();
        }
    }

    return 0;
}

char Menu(void) {
    char userInput;
    bool isValidInput;

    printf("--Dog Racing--\n");
    printf("[G]amble\n");
    printf("[B]anking\n");
    printf("[R]esults\n");
    printf("[L]eave\n");

    printf("\nEnter option character: ");

    do {
        scanf("%c", &userInput);

        if (userInput == '\n') {
            scanf("%c", &userInput);
        }

        if (userInput == 'G' || userInput == 'B' || userInput == 'R' || userInput == 'L') {
            isValidInput = true;
        }
        else {
            printf("Please enter a valid option character (G, B, R, or L): ");
            isValidInput = false;
        }
    } while (isValidInput == false);

    printf("\n");

    return userInput;
}

void InitializeDogs(DOG dog[]) {
    strcpy(dog[0].name, "Ace");
    dog[0].odds = 40;
    dog[0].payoutRate = 2;

    strcpy(dog[1].name, "Chaos");
    dog[1].odds = 10;
    dog[1].payoutRate = 5;

    strcpy(dog[2].name, "Finn");
    dog[2].odds = 8;
    dog[2].payoutRate = 10;

    strcpy(dog[3].name, "Apollo");
    dog[3].odds = 6;
    dog[3].payoutRate = 15;

    strcpy(dog[4].name, "Kiva");
    dog[4].odds = 1;
    dog[4].payoutRate = 50;

    strcpy(dog[5].name, "Flash");
    dog[5].odds = 4;
    dog[5].payoutRate = 20;

    strcpy(dog[6].name, "Gator");
    dog[6].odds = 8;
    dog[6].payoutRate = 10;

    strcpy(dog[7].name, "Raven");
    dog[7].odds = 10;
    dog[7].payoutRate = 5;

    strcpy(dog[8].name, "Cooper");
    dog[8].odds = 13;
    dog[8].payoutRate = 3;
}

char BankingMenu(void) {
    char userInput;
    bool isValidInput;

    printf("[D]eposit\n");
    printf("[W]ithdraw\n");
    printf("[L]eave\n");

    printf("\nEnter option character: ");

    do {
        scanf("%c", &userInput);

        if (userInput == '\n') {
            scanf("%c", &userInput);
        }

        if (userInput == 'D' || userInput == 'W' || userInput == 'L') {
            isValidInput = true;
        }
        else {
            printf("Please enter a valid option character (D, W, or L): ");
            isValidInput = false;
        }
    } while (isValidInput == false);

    printf("\n");

    return userInput;
}

void BankingDeposit(double* moneyInBank, double* moneyOnHand) {
    double userInput;
    bool isValidInput;

    printf("Enter amount you wish to deposit: ");
            
    do {
        scanf("%lf", &userInput);

        if (userInput > *moneyOnHand) {
            printf("You cannot deposit more than what you have on hand. Try again: ");
            isValidInput = false;
        }
        else if (userInput < 0.00) {
            printf("You cannot deposit a negative value. Try again: ");
            isValidInput = false;
        }
        else {
            *moneyInBank = *moneyInBank + userInput;
            *moneyOnHand = *moneyOnHand - userInput;
            printf("Deposited $%0.2lf into account.\n\n", userInput);
            isValidInput = true;
        }
    } while (isValidInput == false);
}

void BankingWithdrawal(double* moneyInBank, double* moneyOnHand) {
    double userInput;
    bool isValidInput;

    printf("Enter amount you wish to withdraw: ");
            
    do {
        scanf("%lf", &userInput);

        if (userInput > *moneyInBank) {
            printf("You cannot withdraw more than what you have in your account. Try again: ");
            isValidInput = false;
        }
        else if (userInput < 0.00) {
            printf("You cannot withdraw a negative value. Try again: ");
            isValidInput = false;
        }
        else {
            *moneyInBank = *moneyInBank - userInput;
            *moneyOnHand = *moneyOnHand + userInput;
            printf("Withdrew $%0.2lf from account.\n\n", userInput);
            isValidInput = true;
        }
    } while (isValidInput == false);
}

void Banking(double* moneyInBank, double* moneyOnHand) {
    const char DEPOSIT_OPTION = 'D';
    const char WITHDRAW_OPTION = 'W';
    const char LEAVE_OPTION = 'L';
    char menuOption;
    double userInput;
    bool isValidInput;

    printf("Money available in account: $%0.2lf\n", *moneyInBank);
    printf("Money currently on hand: $%0.2lf\n\n", *moneyOnHand);

    menuOption = BankingMenu();

    while (menuOption != LEAVE_OPTION) {
        if (menuOption == DEPOSIT_OPTION) {
            BankingDeposit(moneyInBank, moneyOnHand);

            printf("Money available in account: $%0.2lf\n", *moneyInBank);
            printf("Money currently on hand: $%0.2lf\n\n", *moneyOnHand);

            menuOption = BankingMenu();
        }
        else if (menuOption == WITHDRAW_OPTION) {
            BankingWithdrawal(moneyInBank, moneyOnHand);

            printf("Money available in account: $%0.2lf\n", *moneyInBank);
            printf("Money currently on hand: $%0.2lf\n\n", *moneyOnHand);

            menuOption = BankingMenu();
        }
    }
}

void GambleChoices(const DOG dog[], double* wager, int* chosenDog, double* moneyOnHand) {
    bool isValidWager;
    
    printf("Input your desired wager: ");
    do {
        scanf("%lf", wager);

        if (*wager < 0.00) {
            printf("You cannot wager a negative value. Try again: ");
            isValidWager = false;
        }
        else if (*wager > *moneyOnHand) {
            printf("Wager cannot be greater than the money you have on hand. Try again");
            isValidWager = false;
        }
       else {
            isValidWager = true;
       }
    } while (isValidWager == false);

    printf("\nChoose a dog:\n\n");

    for (int i = 0; i < 9; ++i) {
        printf("%d) %s\n", i + 1, dog[i].name);
    }

    printf("\nInput number of your desired dog: ");
    scanf("%d", chosenDog);
    
    while (*chosenDog < 1 || *chosenDog > 9) {
        printf("Please input a number from 1 to 9: ");
        scanf("%d", chosenDog);
    }

    *chosenDog = *chosenDog - 1;
}

double Gamble(const DOG dog[], double* moneyOnHand, double result[],int numRaces) {
    double wager;
    int chosenDog;
    int roll;
    bool wonBet;
    double winnings;
    srand(time(0));

    GambleChoices(dog, &wager, &chosenDog, moneyOnHand);

    roll = (rand() % 100) + 1;

    if (roll <= dog[chosenDog].odds) {
        wonBet = true;
        winnings = wager * dog[chosenDog].payoutRate;
    }
    else {
        wonBet = false;
        winnings = -wager;
    }

    result[numRaces] = winnings;
    
    if (wonBet == true) {
        printf("You won!\n");
        printf("Earnings: $%0.2lf\n\n", winnings);

        *moneyOnHand = *moneyOnHand - wager;
        return winnings;
    }
    else {
        printf("You lost.\n");
        printf("Losses: -$%0.2lf\n\n", wager);
        return winnings;
    }
}

void PrintResults(const double RESULT[], const int NUM_RACES) {
    if (NUM_RACES == 0) {
        printf("No race data available. Try running a few races.\n\n");
    }
    else {
        for (int i = 0; i < NUM_RACES; ++i) {
            printf("Race #%d:\n", i + 1);
            if (RESULT[i] <= 0) {
                printf("Bet lost.\n");
            }
            else {
                printf("Bet won.\n");
            }
            printf("Earnings: $%0.2lf\n\n", RESULT[i]);
        }
    }
}