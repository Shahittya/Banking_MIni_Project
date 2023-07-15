#include <stdio.h>
#include <string.h>
#include<time.h>
struct User { //dummy database for the user
    char username[20];
    char password[20];
    int balance;
    char address[20];
    char phone[15];
    int transaction_history[100];
    int transaction_count;
    int ref_number;
    int day;
    int month;
    int year;
};

struct Admin { //dummy database for the Admin
    char username[20];
    char password[20];
};

int authenticate(struct User* users, char* username, char* password) {  //function for the authentication user
    for (int i = 0; i < 3; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1; // Authentication successful
        }
    }
    return 0; // Authentication failed
}

int authenticate_admin(struct Admin* admin, char* username, char* password) {  //function for the authentication admin
    for (int i = 0; i < 3; i++) {
        if (strcmp(admin[i].username, username) == 0 && strcmp(admin[i].password, password) == 0) {
            return 1; // Authentication successful
        }
    }
    return 0; // Authentication failed
}

void showProfile(struct User* user,char* username) {

    for (int i = 0; i < 3; i++) {
    if (strcmp(user[i].username, username) == 0) {
    printf("***************YOUR PROFILE*************** \n");
    printf("Your User Name is %s \n", user[i].username);
    printf("Your Remaining balance is %d RM. \n",user[i].balance);
    printf("Your present address is %s \n", user[i].address);
    printf("Your cell No. is %s \n", user[i].phone);
                        }
                    }
}

void showTransactionHistory(struct User* users, char* username) {  //transaction history for the user
    for (int i = 0; i < 3; i++) {
        if (strcmp(users[i].username, username) == 0) {
            for (int j = 0; j < users[i].transaction_count; j++) {
                printf("Transaction %d: %d RM \n", j + 1, users[i].transaction_history[j]);
                printf("Reference Number: %d \n ",users[i].ref_number);
                 printf("Date: Day:%d Month:%d Year:%d\n",users[i].day,users[i].month,users[i].year);
                 printf("\n\n");
            }
            return;
        }
    }
}

void showUsers(struct User* user,int i)
{   printf("-------------------------USER INFORMATION-------------------------\n");
    printf("User Name is %s \n", user[i].username);
    printf("Remaining balance is %d RM. \n",user[i].balance);
    printf("Present address is %s \n",user[i].address);
    printf("Cell No. is %s \n",user[i].phone);
    printf("User Password is %s \n",user[i].password);

}

int addAmount(struct User* users,char* username,int user_balance,int amount,int total_balance){


            for (int i = 0; i < 3; i++) {
        if ((strcmp(users[i].username, username) == 0)) {

                user_balance=users[i].balance;
                int total_Balance=user_balance+amount;
                users[i].balance=total_Balance;
            //total_Balance=users[i].balance+=amount;
            printf("Balance Updated For The User! \n");  //update the balance for the user
            printf("%s has now %d RM",users[i].username,total_Balance);
            return 1;
        }

            }
            return 0;

}

showBalance(struct User* users,char* username)
{
                        for (int j = 0; j < 3; j++) {
                        if (strcmp(users[j].username, username) == 0) {
                            printf("Your Total Balance is %d RM.\n", users[j].balance);  //showing the total balance
                        }
                    }
}
void Transfer_Amount(struct User* users, char* username, char* receiver, int sufficient_amount, int amount) {
    sufficient_amount = 0;
    int sender_index = -1;
    int receiver_index = -1;

    for (int i = 0; i < 3; i++) {
        if (strcmp(users[i].username, username) == 0) {
            sender_index = i;
            if (users[i].balance >= amount && amount>0) {
                sufficient_amount = 1;
            }
        } else if (strcmp(users[i].username, receiver) == 0) {
            receiver_index = i;
        }
    }

    if (sender_index != -1 && receiver_index != -1 && sufficient_amount) {
        users[sender_index].balance -= amount;
        users[receiver_index].balance += amount;

        printf("Transaction Successful\n");
        printf("Your Remaining Balance is %d RM\n", users[sender_index].balance);

        int randomNumber = rand();  // Generate a random number
        printf("Transfer Reference Number: %d\n", randomNumber);
        users[sender_index].ref_number = randomNumber;

        time_t currentTime;
        struct tm* dateInfo;

        currentTime = time(NULL);
        dateInfo = localtime(&currentTime);

        // Extract the date components
        int day = dateInfo->tm_mday;
        int month = dateInfo->tm_mon + 1; // Month starts from 0
        int year = dateInfo->tm_year + 1900; // Year starts from 1900

        printf("Current Date: %02d-%02d-%04d\n", day, month, year);
        users[sender_index].day = day;
        users[sender_index].month = month;
        users[sender_index].year = year;

        int transaction_index = users[sender_index].transaction_count;
        users[sender_index].transaction_history[transaction_index] = -amount; // negative amount for debits
        users[sender_index].transaction_count++; // Update transaction count
        transaction_index++;

        users[receiver_index].transaction_history[transaction_index] = amount; // positive amount for credits
        users[receiver_index].transaction_count++; // Update transaction count

    } else {
        printf("Transaction Failed\n");
        if (sender_index == -1) {
            printf("Sender user does not exist\n");
        }
        if (receiver_index == -1) {
            printf("Receiver user does not exist\n");
        }
        if (!sufficient_amount) {
            printf("Insufficient balance\n");
        }
    }
}



//starting the main function
int main() {
    srand(time(NULL));  //time function
    printf("------------Welcome To Our Online Banking System------------\n \n");
    struct User users[3] = {
        {"sourav", "sourav123", 1000, "Pekan", "018387646",{0},0,{0},{0}},
        {"yash", "123", 3000, "Dhaka", "017734733",{0},0,{0},{0}},
        {"mridul", "mridul123", 2000, "Kuantan", "0137643287",{0},0,{0},{0}}
    };
    struct Admin admin[2] = { //dummy database for the admin
        {"admin", "admin"},
        {"admin1", "admin1"}
    };

while(1)  //loop for showing the user and admin menu after the logged out
{


    char username[20];
    char password[20];

    printf("\nAre you a User or Admin:- \n 1.User \n 2.Admin\n");

    int decision;
    scanf("%d", &decision);
    if (decision == 1) {
        printf("Hi User! Please enter your user name: \n");
        scanf("%s", username);
        printf("Enter your password: \n");
        scanf("%s", password);


        if (authenticate(users, username, password)) {  //authentication process for the user
            printf("You are logged into the system!\n");
            int i;
            int loggedIn=1;
            while(loggedIn) {
                printf("------------------------------------------------------------------\n \n");
                printf("Select any option: \n");
                printf(" 1.SHOW BALANCE \n 2.SHOW PROFILE \n 3.TRANSFER BALANCE \n 4.VIEW TRANSACTIONS \n 5.LOGOUT \n");
                int decision;
                scanf("%d", &decision);
                if (decision == 1) {
                        int balance;
                        showBalance(users,username);  //showing balance function
                } else if (decision == 2) {
                    showProfile(users,username);
                }
                else if(decision==5)
                {
                    printf("Logged Out Successfully.");  //logged out from the program
                    loggedIn=0;
                    break;

                }

    else if (decision == 3) {

    printf("Enter Receiver Username\n \n");
char receiver[20];
scanf("%s",receiver);
    printf("Enter the amount you want to transfer: \n");
    int amount;
    scanf("%d", &amount);

    int sufficient_amount; //flag variable
    //int transaction_index = 0; // declare the transaction_index variable

   Transfer_Amount(users,username,receiver,sufficient_amount,amount);
}else if(decision==4)
                {
        printf("________________________Your Transaction History________________________\n \n");
        showTransactionHistory(users, username);

            }else{

            printf("Invalid Input Error!!");
            break;
            }
}        } else {
            printf("Invalid User login credentials!\n");
        }
        }



     else if(decision==2) {
        printf("Hi Admin! Please enter your user name: \n");
        scanf("%s", username);
        printf("Enter your password: \n");
        scanf("%s", password);

        if (authenticate_admin(admin, username, password)) {
            printf("You are logged into the system!\n");
            printf("\n");
            int loggedIn=0;
            while(1)

              {
                   printf("\n");
                   printf("Select any option\n");
 printf("------------------------------------------------------ \n \n");
            printf("1.SHOW USERS \n2.ADD AMOUNT\n3.LOGOUT \n");

            int option;
            scanf("%d",&option);
            if(option==1)
            {
                for (int i = 0; i < 3; i++) {
                printf("\n \n");
                showUsers(users,i);
            }
        } else if(option==3)
        {
            printf("Logged Out Successfully As An Admin!");  //logging out as an admin
            loggedIn=0;
            break;
        }
        else if(option==2)
        {

            printf("\nAdd Amount\n");
            printf("Enter User UserName: \n");
            char username[20];
            scanf("%s",username);
            printf("Enter Amount \n");
            int amount;
            scanf("%d",&amount);
            int a;
            int total_Balance;
            int user_balance;
            a=addAmount(users,username,user_balance,amount,total_Balance);
            printf("%d",a);
        }
              }
        }
        else {
            printf("Invalid Admin login credentials!\n");  //admin login credential not match

        }

    }
    else{
        printf("Invalid Input!!");
    }

}
}


