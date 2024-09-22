#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>
#define MAX_NAME_LENGTH 60
#define MAX_PHONE_NUMBER_LENGTH 30
#define MAX_EMAIL_LENGTH 256
#define MAX_PASSWORD_LENGTH 30
#define PHONE_NUMBER_LENGTH 10
#define MAX_DESCRIPTION_LENGTH 500
#define MAX_complaints 20
#define MAX_ID_DIGITS 11
#define KeyWords_Num 4
#define MAX_DATE_LENGTH 11

typedef struct
{
    char ID[MAX_ID_DIGITS];
    char motif[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    char categorie[MAX_DESCRIPTION_LENGTH];
    char status[MAX_NAME_LENGTH];
    char date[MAX_DATE_LENGTH];
    char Note[MAX_DESCRIPTION_LENGTH];

} complain;


typedef struct
{
    char FullName[MAX_NAME_LENGTH];
    char UserName[MAX_NAME_LENGTH];
    char PhoneNumber[MAX_PHONE_NUMBER_LENGTH];
    char Email[MAX_EMAIL_LENGTH];
    char PassWord[MAX_PASSWORD_LENGTH];
    char AccType[MAX_NAME_LENGTH];
    int NumOfCom;
    complain complaints[MAX_complaints];
} ACC;

int AccNum = 1;
int num = 2;
int index_to_sign_in = -1;
int found = -1;
int Acc_Index = -1;
int Com_Index = -1;
char IDtoSearch[MAX_ID_DIGITS];

void Sign_Up(ACC *accounts);
void Sign_in(ACC *accounts);
void check_credentials(ACC *accounts, int accNum, const char *input, char type);
void Pass_Word_Sign_in(ACC *accounts);

void admin_panel(ACC *accounts);
void client_panel(ACC *accounts);
void agent_panel(ACC *accounts);

int name_validator(int AccNum, ACC *accounts);
int username_validator(int AccNum, ACC *accounts);
int num_validator(int AccNum, ACC *accounts);
int email_validator(int AccNum, ACC *accounts);
int pass_word_validator(int AccNum, ACC *accounts);

void Complain(ACC *accounts);

void Display_ALL_USERS(ACC *accounts);

void Display_Com(ACC *accounts);
void Priority_Sort(ACC *accounts);
void Category_Sort(ACC *accounts);
void display_complaints_by_category(ACC *accounts, const char *category_name);
void Status_Sort(ACC *accounts);
void display_complaints_by_status(ACC *accounts, const char *status_name);


void Search(ACC *accounts);
void Search_ID(ACC *accounts);
void Search_NAME(ACC *accounts);
void Search_Date(ACC *accounts);
void Search_Category(ACC *accounts);
void S_complaints_by_category(ACC *accounts, const char *category_label, const char *category);
void Search_Status(ACC *accounts);
void S_complaints_by_status(ACC *accounts, const char *status_label, const char *status);
void Status_change(ACC *accounts);

void Com_Mod_Del(ACC *accounts);
void Com_Modification(ACC *accounts);
void Com_Deletion(ACC *accounts);

void Roles_Assign(ACC *accounts);

void cleanup(ACC *accounts)
{
    if (accounts != NULL){
        free(accounts);
    }
}

int main()
{
    char choice;
    ACC *accounts = malloc(num * sizeof(ACC));
    if (accounts == NULL){
        printf("Memory allocation failed!\n");
        printf("-------------------------------------\n");
        cleanup(accounts);
        return 1;
    }

    accounts[0].NumOfCom = 0;
    strcpy(accounts[0].FullName, "Amanar Marouane");
    strcpy(accounts[0].UserName, "MarouAdmin");
    strcpy(accounts[0].Email, "marouane.amanar07@gmail.com");
    strcpy(accounts[0].PhoneNumber, "0644311735");
    strcpy(accounts[0].PassWord, "SLS1g5tQ7M5D9J!");
    strcpy(accounts[0].AccType, "admin");

    printf("Welcome to Claims management Panel\n");
    printf("-----------------------------------\n");
    do
    {
        printf("Press 0 to quit the program\n");
        printf("Press 1 to Sign Up.\n");
        printf("Press 2 to Sign in.\n");
        printf("==> ");
        scanf(" %c",&choice);
        printf("-------------------------------------\n");
        getchar();

        switch (choice)
        {
        case '0':
            break;
        case '1':
            Sign_Up(accounts);
            AccNum ++;
            num ++;
            ACC *NewAccounts = realloc(accounts, num * sizeof(ACC));
            if (NewAccounts == NULL)
            {
                printf("Memory allocation failed!\n");
                printf("-------------------------------------\n");
                cleanup(accounts);
                return 1;
            }
            accounts = NewAccounts;
            break;
        case '2':
            Sign_in(accounts);
            break;
        default:
            printf("Invalid choice, please select a valid option.\n");
            printf("----------------------------------------\n");
            break;
        }
    } while (choice != '0');
    cleanup(accounts);
    return 0;
}

void Sign_Up(ACC *accounts)
{
    accounts[AccNum].NumOfCom = 0;
    do{
        printf("Enter your full name : ");
        fgets(accounts[AccNum].FullName, MAX_NAME_LENGTH, stdin);
        accounts[AccNum].FullName[strcspn(accounts[AccNum].FullName, "\n")] = '\0';
        printf("---------------------------------------------------\n");
    } while (name_validator(AccNum, accounts) == 1);
    

    do{
        printf("Enter your UserName : ");
        fgets(accounts[AccNum].UserName, MAX_NAME_LENGTH, stdin);
        accounts[AccNum].UserName[strcspn(accounts[AccNum].UserName, "\n")] = '\0';
        printf("----------------------------------------------------------------\n");
    } while (username_validator(AccNum, accounts) == 1);
    
    do{
        printf("Enter your phone number : ");
        fgets(accounts[AccNum].PhoneNumber, MAX_PHONE_NUMBER_LENGTH, stdin);
        accounts[AccNum].PhoneNumber[strcspn(accounts[AccNum].PhoneNumber, "\n")] = '\0';
        printf("----------------------------------------------------------------\n");
    } while (num_validator(AccNum, accounts) == 0);
    
    do{
        printf("Enter your email : ");
        fgets(accounts[AccNum].Email, MAX_EMAIL_LENGTH, stdin);
        accounts[AccNum].Email[strcspn(accounts[AccNum].Email, "\n")] = '\0';
        printf("----------------------------------------------------------------\n");
    } while (email_validator(AccNum, accounts) == 1);

    do{
        printf("Enter your password : \nPassword must have \n");
        printf("- At least 8 characters\n");
        printf("- One uppercase letter\n");
        printf("- One lowercase letter\n");
        printf("- One number\n");
        printf("- One special character\n");
        printf("==> ");
        fgets(accounts[AccNum].PassWord, MAX_PASSWORD_LENGTH, stdin);
        accounts[AccNum].PassWord[strcspn(accounts[AccNum].PassWord, "\n")] = '\0';
        printf("----------------------------------------------------------------\n");
    } while (pass_word_validator(AccNum, accounts) == 1);
    
    strcpy(accounts[AccNum].AccType, "client");
    printf("Sign-up successful for %s\n", accounts[AccNum].FullName);
    printf("----------------------------------------------------------------\n");
}

int name_validator(int AccNum, ACC *accounts){   
    if (strlen(accounts[AccNum].FullName) == 0){
        printf("==>Contact name is not valid .\n(Empty!!)\n");
        printf("----------------------------------------------------------------\n");
        return 1;
    }
    if (accounts[AccNum].FullName[0] == ' '){
        printf("==>Contact name is not valid .\n(Must not start with space!!)\n");
        printf("----------------------------------------------------------------\n");
        return 1;
    }
    for (int i = 0;accounts[AccNum].FullName[i] != '\0' ; i++){
        if (!isalpha(accounts[AccNum].FullName[i]) && !isspace(accounts[AccNum].FullName[i])){
            printf("==>Contact name is not valid .\n(Must contain only alphabets!!)\n");
            printf("----------------------------------------------------------------\n");
            return 1;
        }
    }
    for (int i = 0; i < AccNum; i++){
        if (strcmp(accounts[i].FullName, accounts[AccNum].FullName) == 0){
            printf("==> Contact name is already used.\n");
            printf("----------------------------------------------------------------\n");
            return 1;
        }
    }  
    printf("==>Contact name is accepted !!\n");
    printf("----------------------------------------------------------------\n");
    return 0;
}

int username_validator(int AccNum, ACC *accounts){   
    int alpha = 0;
    if (strlen(accounts[AccNum].UserName) < 4){
        printf("==>UserName is too short.\n");
        printf("----------------------------------------------------------------\n");
        return 1;
    }
    for (int i = 0;accounts[AccNum].UserName[i] != '\0' ; i++){
        if (!isalnum(accounts[AccNum].UserName[i])){
            printf("==>UserName is not valid.\n(Must contain only alphabets and digits.)\n");
            printf("----------------------------------------------------------------\n");
            return 1;
        }
        if (isalpha(accounts[AccNum].UserName[i])){
            alpha ++;
        }
    }
    if (alpha == 0){
        printf("==>UserName is not valid.\n(Must contain alphabets.)\n");
        printf("----------------------------------------------------------------\n");
        return 1;
    }
    for (int i = 0; i < AccNum; i++){
        if (strcmp(accounts[i].UserName, accounts[AccNum].UserName) == 0){
            printf("==> User name is already used.\n");
            printf("----------------------------------------------------------------\n");
            return 1;
        }
    }
    printf("==>UserName is accepted !!\n");
    printf("----------------------------------------------------------------\n");
    return 0;
}

int num_validator(int AccNum, ACC *accounts){
    for (int i = 0;accounts[AccNum].PhoneNumber[i] != '\0' ; i++){
        if (!isdigit(accounts[AccNum].PhoneNumber[i])){
            printf("==>Phone number is not valid.\n(Must contain only digits!!)\n");
            printf("----------------------------------------------------------------\n");
            return 0;
        }
    }
    if (strlen(accounts[AccNum].PhoneNumber) != PHONE_NUMBER_LENGTH){
        printf("==>Phone number is not valid.\n(Must contain 10 digits!!)\n");
        printf("----------------------------------------------------------------\n");
        return 0;
    }
    for (int i = 0; i < AccNum; i++){
        if (strcmp(accounts[i].PhoneNumber, accounts[AccNum].PhoneNumber) == 0){
            printf("==> Phone number is already used.\n");
            printf("----------------------------------------------------------------\n");
            return 1;
        }
    }
    printf("==>Phone number is accepted !!\n");
    printf("----------------------------------------------------------------\n");
    return 1;
}

int email_validator(int AccNum, ACC *accounts){
    char *at = strchr(accounts[AccNum].Email, '@');
    char *dot = strrchr(accounts[AccNum].Email, '.');

    if (at == NULL || dot == NULL || dot < at){
        printf("==>Email is not valid.\n(Must be in the format username@gmail.com)\n");
        printf("----------------------------------------------------------------\n");
        return 1;
    }
    if (at == accounts[AccNum].Email){
        printf("==> The username part before '@' cannot be empty. (username@gmail.com)\n");
        printf("-----------------------------------------------------------------------\n");
        return 1;
    }
    if (at + 1 == dot){
        printf("==> The example part between '@' and '.' cannot be empty. (username@gmail.com)\n");
        printf("----------------------------------------------------------------\n");
        return 1;
    }
    if (*(dot + 1) == '\0'){
        printf("==> The domain extension after '.' cannot be empty. (username@gmail.com)\n");
        printf("----------------------------------------------------------------\n");
        return 1;
    }
    for (int i = 0; i < (at - accounts[AccNum].Email); i++){
        if (!(isalnum(accounts[AccNum].Email[i]) || accounts[AccNum].Email[i] == '.' || accounts[AccNum].Email[i] == '-' || accounts[AccNum].Email[i] == '_') && isspace(accounts[AccNum].Email[i])){
            printf("==>The username part accept only ('A-Z', 'a-z', '0-9', '.', '-', '_'), Space not include.\n");
            printf("-----------------------------------------------------------------------\n");
            return 1;
        }
    }
    for (int i = (at - accounts[AccNum].Email) + 1; i < (dot - accounts[AccNum].Email); i++){
        if (!isalpha(accounts[AccNum].Email[i])){
            printf("==>Special symbol and numbers not valid atfer '@'.\n");
            printf("-----------------------------------------------------------------------\n");
            return 1;
        }
    }

    const char* gmail = "gmail";
    if (strncmp(at + 1, gmail, strlen(gmail)) != 0 || at + 1 + strlen(gmail) != dot) {   
        printf("==>Only accept (username@gmail.com).\n");
        printf("-----------------------------------------------------------------------\n");
        return 1;
    }

    for (int i = (dot - accounts[AccNum].Email) + 1; accounts[AccNum].Email[i] != '\0'; i++){
        if (!isalpha(accounts[AccNum].Email[i])){
            printf("==>Special symbol and numbers not valid in the extension part.\n");
            printf("-----------------------------------------------------------------------\n");
            return 1;
        }
    }

    const char* com = "com";
    if (strcmp(dot + 1,com) != 0){
        printf("==>Only accept (username@gmail.com).\n");
        printf("-----------------------------------------------------------------------\n");
        return 1;
    }
    for (int i = 0; i < AccNum; i++){
        if (strcmp(accounts[i].Email, accounts[AccNum].Email) == 0){
            printf("==> This address email is already used.\n");
            printf("----------------------------------------------------------------\n");
            return 1;
        }
    }
    printf("==>The address email is accepted !!\n");
    printf("-----------------------------------------------------------------------\n");
    return 0;
}

int pass_word_validator(int AccNum, ACC *accounts){
    int lower = 0, upper = 0, number = 0, special = 0;

    if (strlen(accounts[AccNum].PassWord) < 8){
        printf("Password too short! Must be at least 8 characters.\n");
        printf("----------------------------------------------------------------\n");
        return 1;
    }
    if (strstr(accounts[AccNum].PassWord, accounts[AccNum].UserName) != NULL){
        printf("Password should not include the username!\n");
        printf("----------------------------------------------------------------\n");
        return 1;
    }
    
    for (int i = 0; accounts[AccNum].PassWord[i] != '\0'; i++){
        if (islower(accounts[AccNum].PassWord[i])) lower++;
        else if (isupper(accounts[AccNum].PassWord[i])) upper++;
        else if (isdigit(accounts[AccNum].PassWord[i])) number++;
        else if (ispunct(accounts[AccNum].PassWord[i])) special++;
    }
    if (lower > 0 && upper > 0 && number > 0 && special > 0){
        printf("Password is valid.\n");
        printf("----------------------------------------------------------------\n");
        return 0;
    }
    printf("Password invalid! It must contain at least one lowercase letter, one uppercase letter, one number, and one special character.\n");
    printf("------------------------------------------------------------------------------------------------------------------------------\n");
    return 1;
}

void Sign_in(ACC *accounts){   
    char choice;
    char input[MAX_EMAIL_LENGTH];  // Input buffer to reuse for email/phone/username
    int accNum = AccNum;

    printf("Press 0 to cancel sign in\n");
    printf("Press 1 to sign in by email\n");
    printf("Press 2 to sign in by number\n");
    printf("Press 3 to sign in by user name\n");
    printf("==> ");
    scanf(" %c",&choice);
    getchar();
    printf("----------------------------------------\n");

    if (choice == '0') return;
    for (int k = 0; k < 3; k++){
        if (choice == '1') printf("Enter your email address: ");
        else if (choice == '2') printf("Enter your phone number: ");
        else if (choice == '3') printf("Enter your username: ");
        else {
            printf("Invalid choice, please select a valid option.\n");
            return;
        }

        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';
        check_credentials(accounts, accNum, input, choice);

        if (index_to_sign_in != -1){
            Pass_Word_Sign_in(accounts);
            return;
        }
        if (k == 2){
            printf("You've entered incorrect information more than 3 times! You need to wait 1 hour before trying again...\n");
            sleep(3600);
            return;
        }
        printf("Invalid input, please try again.\n");
    }
}

void check_credentials(ACC *accounts, int accNum, const char *input, char type){
    for (int i = 0; i < accNum; i++){
        if ((type == '1' && strcmp(input, accounts[i].Email) == 0) || (type == '2' && strcmp(input, accounts[i].PhoneNumber) == 0) || (type == '3' && strcmp(input, accounts[i].UserName) == 0)){
            index_to_sign_in = i;
            return ;
        }
    }
}

void Pass_Word_Sign_in(ACC *accounts){
    char pass_word_to_sign_in[MAX_PASSWORD_LENGTH];
    int attempts = 3;
    for (int i = 0; i < attempts; i++){
        printf("Enter your password to sign in: ");
        fgets(pass_word_to_sign_in, MAX_PASSWORD_LENGTH, stdin);
        pass_word_to_sign_in[strcspn(pass_word_to_sign_in, "\n")] = '\0';
        printf("---------------------------------------------------\n");

        if (strcmp(pass_word_to_sign_in, accounts[index_to_sign_in].PassWord) == 0){
            printf("Signed in successfully!\n");
            printf("---------------------------------------------------\n");

            if (strcmp(accounts[index_to_sign_in].AccType, "client") == 0) client_panel(accounts);
            else if (strcmp(accounts[index_to_sign_in].AccType, "admin") == 0) admin_panel(accounts);
            else if (strcmp(accounts[index_to_sign_in].AccType, "agent") == 0) agent_panel(accounts);

            return;
        }
        else{
            printf("Incorrect password!\n");
        }
        if (i == 2){
            printf("You've entered an incorrect password more than 3 times.\n");
            printf("You need to wait 1 hour before trying again...\n");
            sleep(3600);
            return;
        }
    }
}

void client_panel(ACC *accounts){
    printf("Welcom %s (%s)\n",accounts[index_to_sign_in].FullName,accounts[index_to_sign_in].AccType);
    
    char choice;
    do{
        printf("Press 0 to sign out\n");
        printf("Press 1 to submit a complaint\n");
        printf("Press 2 to see your complaints\n");
        printf("Press 3 to modify/delete one of your complaints\n");
        printf("==> ");
        scanf(" %c",&choice);
        printf("---------------------------------\n");

        switch (choice){
        case '0':
            printf("Signing out...\n");
            printf("---------------------------------\n");
            index_to_sign_in = -1;
            break;
        case '1':
            Complain(accounts);
            break;
        case '2':
            if (accounts[index_to_sign_in].NumOfCom == 0)
            {
                printf("No complaints to show\n");
                printf("---------------------------------\n");
                break;
            }
            for (int i = 0; i < accounts[index_to_sign_in].NumOfCom; i++)
            {
                printf("ID : %s\nComplaint : %s (%s)\n",accounts[index_to_sign_in].complaints[i].ID, accounts[index_to_sign_in].complaints[i].motif, accounts[index_to_sign_in].complaints[i].status);
                printf("Category : %s\n",accounts[index_to_sign_in].complaints[i].categorie);
                printf("Description : %s\n",accounts[index_to_sign_in].complaints[i].description);
                printf("Note from the agency : %s\n",accounts[index_to_sign_in].complaints[i].Note);
                printf("Date : %s\n",accounts[index_to_sign_in].complaints[i].date);
                printf("---------------------------------------------------------------------------------\n");
            }
            break;
        case '3':
            Com_Mod_Del(accounts);
            break;
        default:
            printf("Invalid choice, please select a valid option.\n");
            printf("----------------------------------------\n");
            break;
        }
    } while (choice != '0');
}

void admin_panel(ACC *accounts){
    printf("Welcom %s (%s)\n",accounts[index_to_sign_in].FullName,accounts[index_to_sign_in].AccType);
    char choice;
    do{
        printf("Press 0 to sign out\n");
        printf("Press 1 to display all the users\n");
        printf("Press 2 to display all the complaints\n");
        printf("Press 3 to search for a complain\n");
        printf("Press 4 to treat a complain\n");
        printf("Press 5 to delete/modify a complain\n");
        printf("Press 6 to manage the assignment roles\n");
        printf("Press 7 to generate the statistics\n");
        printf("==> ");
        scanf(" %c",&choice);
        printf("---------------------------------\n");

        switch (choice){
        case '0':
            printf("Signing out...\n");
            printf("---------------------------------\n");
            index_to_sign_in = -1;
            break;
        case '1':
            Display_ALL_USERS(accounts);
            break;
        case '2':
            Display_Com(accounts);
            break;
        case '3':
            Search(accounts);
            break;
        case '4':
            Search_ID(accounts);
            Status_change(accounts);
            break;
        case '5':
            Com_Mod_Del(accounts);
            break;
        case '6':
            Roles_Assign(accounts);
            break;
        case '7':
            break;
        default:
            printf("Invalid choice, please select a valid option.\n");
            printf("----------------------------------------\n");
            break;
        }
    } while (choice != '0');
}

void agent_panel(ACC *accounts){
    printf("Welcom %s (%s)\n",accounts[index_to_sign_in].FullName,accounts[index_to_sign_in].AccType);
    char choice;
    do{
        printf("Press 0 to sign out\n");
        printf("Press 1 to display all the complaints\n");
        printf("Press 2 to search for a complain\n");
        printf("Press 3 to treat a complain\n");
        printf("Press 4 to delete/modify a complain\n");
        printf("==> ");
        scanf(" %c",&choice);
        printf("---------------------------------\n");

        switch (choice)
        {
        case 0:
            printf("Signing out...\n");
            index_to_sign_in = -1;
            break;
        case '1':
            Display_Com(accounts);
            break;
        case '2':
            Search(accounts);
            break;
        case '3':
            Search_ID(accounts);
            Status_change(accounts);
            break;
        case '4':
            Com_Mod_Del(accounts);
            break;
        default:
            printf("Invalid choice, please select a valid option.\n");
            printf("----------------------------------------\n");
            break;
        }
    } while (choice != '0');
}

void Complain(ACC *accounts){
    char choice;
    int num;
    srand(time(0));

    for (int i = 0; i < MAX_ID_DIGITS - 1; i++){
        num = rand() % 36; // car 10 (0-9) et 26(A-Z) ==> 10+26 = 36
        if (num < 10)
        {
            accounts[index_to_sign_in].complaints[accounts[index_to_sign_in].NumOfCom].ID[i] = num + '0';
        }else
        {
           accounts[index_to_sign_in].complaints[accounts[index_to_sign_in].NumOfCom].ID[i] = num - 10 + 'A';
        }
    }
    accounts[index_to_sign_in].complaints[accounts[index_to_sign_in].NumOfCom].ID[MAX_ID_DIGITS] = '\0';

    
    printf("What's the subject of your complaint : ");
    getchar();
    fgets(accounts[index_to_sign_in].complaints[accounts[index_to_sign_in].NumOfCom].motif, MAX_NAME_LENGTH, stdin);
    accounts[index_to_sign_in].complaints[accounts[index_to_sign_in].NumOfCom].motif[strcspn(accounts[index_to_sign_in].complaints[accounts[index_to_sign_in].NumOfCom].motif, "\n")] = '\0';
    printf("------------------------------------------------------------------\n");

    printf("Description : ");
    fgets(accounts[index_to_sign_in].complaints[accounts[index_to_sign_in].NumOfCom].description, MAX_NAME_LENGTH, stdin);
    accounts[index_to_sign_in].complaints[accounts[index_to_sign_in].NumOfCom].description[strcspn(accounts[index_to_sign_in].complaints[accounts[index_to_sign_in].NumOfCom].description, "\n")] = '\0';
    printf("------------------------------------------------------------------\n");

    printf("To choose a categorie :\n");
    printf("Press 1 for 'Service quality'\n");
    printf("Press 2 for 'Product issue'\n");
    printf("Press 3 for 'Factoration problem'\n");
    printf("Press 4 for 'Technical Complaints'\n");
    printf("Press 5 for 'Customer Service'\n");
    printf("Press 6 for 'Category Not Specified'\n");
    printf("===> ");
    scanf(" %c",&choice);
    printf("-----------------------------------------\n");

    switch (choice){
    case '1':
        strcpy(accounts[index_to_sign_in].complaints[accounts[index_to_sign_in].NumOfCom].categorie, "Service quality");
        printf("Done!\n");
        printf("-----------------------------------------\n");
        break;
    case '2':
        strcpy(accounts[index_to_sign_in].complaints[accounts[index_to_sign_in].NumOfCom].categorie, "Product issue");
        printf("Done!\n");
        printf("-----------------------------------------\n");
        break;
    case '3':
        strcpy(accounts[index_to_sign_in].complaints[accounts[index_to_sign_in].NumOfCom].categorie, "Factoration problem");
        printf("Done!\n");
        printf("-----------------------------------------\n");
        break;
    case '4':
        strcpy(accounts[index_to_sign_in].complaints[accounts[index_to_sign_in].NumOfCom].categorie, "Technical Complaints");
        printf("Done!\n");
        printf("-----------------------------------------\n");
        break;
    case '5':
        strcpy(accounts[index_to_sign_in].complaints[accounts[index_to_sign_in].NumOfCom].categorie, "Customer Service");
        printf("Done!\n");
        printf("-----------------------------------------\n");
        break;
    case '6':
        strcpy(accounts[index_to_sign_in].complaints[accounts[index_to_sign_in].NumOfCom].categorie, "Category Not Specified");
        printf("Done!\n");
        printf("-----------------------------------------\n");
        break;
    default:
        strcpy(accounts[index_to_sign_in].complaints[accounts[index_to_sign_in].NumOfCom].categorie, "Category Not Specified");
        printf("U choosed an invalid choice, this complain will include under the category of 'Category Not Specified'\n");
        printf("-----------------------------------------------------------------------------------------------------------\n");
        strcpy(accounts[index_to_sign_in].complaints[accounts[index_to_sign_in].NumOfCom].categorie, "Category Not Specified");
        break;
    }

    printf("This complain will put under 'pending'.\n");
    printf("------------------------------------------------------------\n");
    strcpy(accounts[index_to_sign_in].complaints[accounts[index_to_sign_in].NumOfCom].status, "pending");

    time_t current_time;
    time(&current_time);

    struct tm *time_info = localtime(&current_time);

    time_info->tm_hour = 0;
    time_info->tm_min = 0;
    time_info->tm_sec = 0;

    current_time = mktime(time_info);
    
    sprintf(accounts[index_to_sign_in].complaints[accounts[index_to_sign_in].NumOfCom].date, "%04d-%02d-%02d", time_info->tm_year + 1900, time_info->tm_mon + 1, time_info->tm_mday);

    printf("Date of submission: %s\n", accounts[index_to_sign_in].complaints[accounts[index_to_sign_in].NumOfCom].date);
    printf("------------------------------------------------------------\n");

    strcpy(accounts[index_to_sign_in].complaints[accounts[index_to_sign_in].NumOfCom].Note, "Empty");
    accounts[index_to_sign_in].NumOfCom ++;
}

void Display_ALL_USERS(ACC *accounts){   
    if (AccNum == 1){
        printf("Only the admin's account exist at the moment.\n");
        printf("----------------------------------------------\n");
        return;
    }

    printf("Administrators : \n\n");
    for (int i = 0; i < AccNum; i++){
        if (strcmp(accounts[i].AccType, "admin") == 0)
        {
            printf("%s\n", accounts[i].FullName);
            printf("UserName : %s\n",accounts[i].UserName);
            printf("Phone number : %s\n",accounts[i].PhoneNumber);
            printf("Email address : %s\n",accounts[i].Email);
            printf("Complaints number : %i\n\n",accounts[i].NumOfCom);
        }
    }
    printf("----------------------------------------------------------\n");
    printf("Agents : \n\n");
    for (int i = 0; i < AccNum; i++){
        if (strcmp(accounts[i].AccType, "agent") == 0){
            printf("%s\n", accounts[i].FullName);
            printf("UserName : %s\n",accounts[i].UserName);
            printf("Phone number : %s\n",accounts[i].PhoneNumber);
            printf("Email address : %s\n",accounts[i].Email);
            printf("Complaints number : %i\n\n",accounts[i].NumOfCom);
        }
    }
    printf("----------------------------------------------------------\n");
    printf("Clients : \n\n");
    for (int i = 0; i < AccNum; i++){
        if (strcmp(accounts[i].AccType, "client") == 0){
            printf("%s\n", accounts[i].FullName);
            printf("UserName : %s\n",accounts[i].UserName);
            printf("Phone number : %s\n",accounts[i].PhoneNumber);
            printf("Email address : %s\n",accounts[i].Email);
            printf("Complaints number : %i\n\n",accounts[i].NumOfCom);
        }
    }
    printf("----------------------------------------------------------\n");
}

void Display_Com(ACC *accounts){
    int Total_Com = 0;
    for (int i = 0; i < AccNum; i++){
        Total_Com += accounts[i].NumOfCom;
    }
    if (Total_Com == 0){
        printf("There's no complaints at the moment.\n");
        printf("----------------------------------------------\n");
        return;
    }

    char choice;
    printf("Press 0 to get back to the previous menu\n");
    printf("Press 1 to display all the complaints sorted by priorities\n");
    printf("Press 2 to display all the complaints sorted by categories\n");
    printf("Press 3 to display all the complaints sorted by status\n");
    printf("==> ");
    scanf(" %c",&choice);

    switch (choice){
    case '0':
        break;

    case '1':
        Priority_Sort(accounts);
        break;

    case '2':
        Category_Sort(accounts);
        break;

    case '3':
        Status_Sort(accounts);
        break;
    
    default:
        printf("Invalid choice. Please choose a valid option\n");
        printf("-------------------------------------------------------\n");
        break;
    }
}

void Priority_Sort(ACC *accounts){
    char KeyWords_1st[KeyWords_Num][MAX_DESCRIPTION_LENGTH] = {"critical", "down", "loss", "security"};
    char KeyWords_2nd[KeyWords_Num][MAX_DESCRIPTION_LENGTH] = {"issues", "disruption", "errors", "failure"};

    int count = 0;
    printf("Urgent cases : \n\n");
    for (int i = 0; i < AccNum; i++){
        if (accounts[i].NumOfCom == 0){
            continue;
        }
        for (int j = 0; j < accounts[i].NumOfCom; j++){
            for (int k = 0; k < KeyWords_Num; k++){
                if (strstr(accounts[i].complaints[j].description, KeyWords_1st[k]) != NULL){   
                    count ++;
                    printf("Name : %s\n",accounts[i].FullName);
                    printf("ID : %s\nComplaint : %s (%s)\n",accounts[i].complaints[j].ID, accounts[i].complaints[j].motif, accounts[i].complaints[j].status);
                    printf("Category : %s\n",accounts[i].complaints[j].categorie);
                    printf("Description : %s\n",accounts[i].complaints[j].description);
                    printf("Note from the agency : %s\n",accounts[i].complaints[j].Note);
                    printf("Date : %s\n\n",accounts[i].complaints[j].date);
                    break;
                }
            }
        }
    }
    if (count == 0){
        printf("There's no urgent cases.\n");
    }
    count = 0;
    printf("-------------------------------------------------------------------------------------------\n");
    printf("Important cases : \n\n");
    for (int i = 0; i < AccNum; i++){
        if (accounts[i].NumOfCom == 0){
            continue;
        }
        for (int j = 0; j < accounts[i].NumOfCom; j++){
            for (int k = 0; k < KeyWords_Num; k++){
                if (strstr(accounts[i].complaints[j].description, KeyWords_2nd[k]) != NULL){
                    count ++;
                    printf("Name : %s\n",accounts[i].FullName);
                    printf("ID : %s\nComplaint : %s (%s)\n",accounts[i].complaints[j].ID, accounts[i].complaints[j].motif, accounts[i].complaints[j].status);
                    printf("Category : %s\n",accounts[i].complaints[j].categorie);
                    printf("Description : %s\n",accounts[i].complaints[j].description);
                    printf("Note from the agency : %s\n",accounts[i].complaints[j].Note);
                    printf("Date : %s\n\n",accounts[i].complaints[j].date);
                    break;
                }
            }
        }
    }
    if (count == 0){
        printf("There's no important cases.\n");
    }
    count = 0;
    printf("-------------------------------------------------------------------------------------------\n");
    printf("Normal cases : \n\n");
    for (int i = 0; i < AccNum; i++){
        if (accounts[i].NumOfCom == 0){
            continue;
        }
        for (int j = 0; j < accounts[i].NumOfCom; j++){
            for (int k = 0; k < KeyWords_Num; k++){
                if (strstr(accounts[i].complaints[j].description, KeyWords_2nd[k]) == NULL || strstr(accounts[i].complaints[j].description, KeyWords_1st[k]) == NULL){
                    count ++;
                    printf("Name : %s\n",accounts[i].FullName);
                    printf("ID : %s\nComplaint : %s (%s)\n",accounts[i].complaints[j].ID, accounts[i].complaints[j].motif, accounts[i].complaints[j].status);
                    printf("Category : %s\n",accounts[i].complaints[j].categorie);
                    printf("Description : %s\n",accounts[i].complaints[j].description);
                    printf("Note from the agency : %s\n",accounts[i].complaints[j].Note);
                    printf("Date : %s\n\n",accounts[i].complaints[j].date);
                    break;
                }
            }
        }
    }
    if (count == 0){
        printf("There's no normal cases.\n");
    }
    count = 0;
    printf("-------------------------------------------------------------------------------------------\n");
}

void Category_Sort(ACC *accounts) {
    const char *categories[] = {
        "Service quality",
        "Product issue",
        "Factoration problem",
        "Technical Complaints",
        "Customer Service",
        "Category Not Specified"
    };

    for (int i = 0; i < 6; i++) {
        display_complaints_by_category(accounts, categories[i]);
    }
}

void display_complaints_by_category(ACC *accounts, const char *category_name) {
    int count = 0;
    printf("%s : \n\n", category_name);
    for (int i = 0; i < AccNum; i++) {
        if (accounts[i].NumOfCom == 0) {
            continue;
        }
        for (int j = 0; j < accounts[i].NumOfCom; j++) {
            if (strcmp(accounts[i].complaints[j].categorie, category_name) == 0) {
                count++;
                printf("Name : %s\n", accounts[i].FullName);
                printf("ID : %s\nComplaint : %s (%s)\n", accounts[i].complaints[j].ID, accounts[i].complaints[j].motif, accounts[i].complaints[j].status);
                printf("Description : %s\n", accounts[i].complaints[j].description);
                printf("Note from the agency : %s\n", accounts[i].complaints[j].Note);
                printf("Date : %s\n\n", accounts[i].complaints[j].date);
            }
        }
    }
    if (count == 0) {
        printf("There's no complaints in this section.\n");
    }
    printf("-------------------------------------------------------------------------------------------\n");
}

void Status_Sort(ACC *accounts) {
    const char *statuses[] = {
        "pending",
        "Under process",
        "Resolved",
        "Rejected"
    };

    for (int i = 0; i < 4; i++) {
        display_complaints_by_status(accounts, statuses[i]);
    }
}

void display_complaints_by_status(ACC *accounts, const char *status_name) {
    int found = 0;
    printf("%s : \n\n", status_name);
    for (int i = 0; i < AccNum; i++) {
        if (accounts[i].NumOfCom == 0) {
            continue;
        }
        for (int j = 0; j < accounts[i].NumOfCom; j++) {
            if (strcmp(accounts[i].complaints[j].status, status_name) == 0) {
                found = 1;
                printf("Name : %s\n", accounts[i].FullName);
                printf("ID : %s\nComplaint : %s\n", accounts[i].complaints[j].ID, accounts[i].complaints[j].motif);
                printf("Category : %s\n", accounts[i].complaints[j].categorie);
                printf("Description : %s\n", accounts[i].complaints[j].description);
                printf("Note from the agency : %s\n", accounts[i].complaints[j].Note);
                printf("Date : %s\n\n", accounts[i].complaints[j].date);
            }
        }
    }
    if (!found) {
        printf("No complaints found with status '%s'.\n\n", status_name);
    }
    printf("-------------------------------------------------------------------------------------------\n");
}

void Search(ACC *accounts){
    int Total_Com = 0;
    for (int i = 0; i < AccNum; i++){
        Total_Com += accounts[i].NumOfCom;
    }
    if (Total_Com == 0){
        printf("There's no complaints at the moment.\n");
        printf("----------------------------------------------\n");
        return;
    }
    
    char choice;
    printf("Press 0 to get to the previous menu\n");
    printf("Press 1 to search by ID.\n");
    printf("Press 2 to search by name\n");
    printf("Press 3 to search by Date\n");
    printf("Press 4 to search by category\n");
    printf("==> ");
    scanf(" %c",&choice);
    printf("------------------------------------\n");
    switch (choice){
    case '0':
        break;
    
    case '1':
        Search_ID(accounts);
        Acc_Index = -1;
        Com_Index = -1;
        break;

    case '2':
        Search_NAME(accounts);
        break;

    case '3':
        Search_Date(accounts);
        break;

    case '4':
        Search_Category(accounts);
        break;
    
    default:
        printf("Invalid choice.\n");
        printf("----------------------------------------\n");
        break;
    }
}

void Search_ID(ACC *accounts){
    printf("Enter the ID : ");
    getchar();
    fgets(IDtoSearch, MAX_ID_DIGITS, stdin);
    IDtoSearch[strcspn(IDtoSearch, "\n")] = '\0';
    printf("----------------------------------------\n");
    for (int i = 0; i < AccNum; i++){
        if (accounts[i].NumOfCom == 0){
            continue;
        }
        for (int j = 0; j < accounts[i].NumOfCom; j++){
            if (strcmp(IDtoSearch, accounts[i].complaints[j].ID) == 0)
            {
                found = 0;
                Acc_Index = i;
                Com_Index = j;
                break;
            }
        }
    }
    if (found == -1){
        printf("Complain is not found\n");
        printf("----------------------------------------\n");
        return;
    }
}

void Search_NAME(ACC *accounts){
    char NameToSearch[MAX_NAME_LENGTH];
    printf("Enter the name : ");
    getchar();
    fgets(NameToSearch, MAX_NAME_LENGTH, stdin);
    NameToSearch[strcspn(NameToSearch, "\n")] = '\0';
    printf("----------------------------------------\n");
    for (int i = 0; i < AccNum; i++){
        if (strcmp(NameToSearch, accounts[i].FullName) == 0)
        {
            found = 0;
            Acc_Index = i;
            break;
        }
    }
    if (found == -1){
        printf("User is not found\n");
        printf("----------------------------------------\n");
        return;
    }

    if (accounts[Acc_Index].NumOfCom == 0){
        printf("This account have no complaints yet.\n");
        printf("----------------------------------------\n");
    }
    for (int i = 0; i < accounts[Acc_Index].NumOfCom; i++){
        printf("ID : %s\nComplaint : %s (%s)\n",accounts[Acc_Index].complaints[i].ID, accounts[Acc_Index].complaints[i].motif, accounts[Acc_Index].complaints[i].status);
        printf("Category : %s\n",accounts[Acc_Index].complaints[i].categorie);
        printf("Description : %s\n",accounts[Acc_Index].complaints[i].description);
        printf("Note from the agency : %s\n",accounts[Acc_Index].complaints[i].Note);
        printf("Date : %s\n",accounts[Acc_Index].complaints[i].date);
        printf("---------------------------------------------------------------------------------\n");
    }
    Acc_Index = -1;
}

void Search_Date(ACC *accounts){
    char date_input[100];
    struct tm date__input = {0};

    do{
        printf("Enter a date (format: YYYY-MM-DD): ");
        getchar();
        fgets(date_input, sizeof(date_input), stdin);
        date_input[strcspn(date_input, "\n")] = '\0';
        printf("---------------------------------------------------------------------------------\n");

        if (strlen(date_input) != 10 || date_input[4] != '-' || date_input[7] != '-') {
            printf("Invalid date format! Please use YYYY-MM-DD.\n");
        }else if (sscanf(date_input, "%4d-%2d-%2d", &date__input.tm_year, &date__input.tm_mon, &date__input.tm_mday) != 3 || date__input.tm_mon < 1 || date__input.tm_mon > 12 || date__input.tm_mday < 1 || date__input.tm_mday > 31){
            printf("Invalid date! Please ensure the values are correct.\n");
        }else{
            break;
        }
    } while (1);

    int count = 0;
    printf("Searching complaints for date: %s\n\n", date_input);
    for (int i = 0; i < AccNum; i++){
        if (accounts[i].NumOfCom == 0){
            continue;
        }
        for (int j = 0; j < accounts[i].NumOfCom; j++){
            if (strcmp(accounts[i].complaints[j].date, date_input) == 0) {
                count ++;
                printf("Name : %s\n",accounts[i].FullName);
                printf("ID : %s\nComplaint : %s (%s)\n",accounts[i].complaints[j].ID, accounts[i].complaints[j].motif, accounts[i].complaints[j].status);
                printf("Category : %s\n",accounts[i].complaints[j].categorie);
                printf("Description : %s\n",accounts[i].complaints[j].description);
                printf("Note from the agency : %s\n",accounts[i].complaints[j].Note);
                printf("---------------------------------------------------------------------------------\n");
            } 
        }
    }
    if (count == 0){
        printf("There's no complaints under this date.\n");
    }
}

void Search_Category(ACC *accounts){
    char choice;

    printf("Press 0 to get back to the previous menu.\n");
    printf("Press 1 to display all the complaints in 'Service quality' section.\n");
    printf("Press 2 to display all the complaints in 'Product issue' section.\n");
    printf("Press 3 to display all the complaints in 'Factoration problem' section.\n");
    printf("Press 4 to display all the complaints in 'Technical Complaints' section.\n");
    printf("Press 5 to display all the complaints in 'Customer Service' section.\n");
    printf("Press 6 to display all the complaints in 'Category Not Specified' section.\n");
    printf("==> ");
    scanf(" %c", &choice);
    printf("----------------------------------------------------------------------------------\n");

    switch (choice){
    case '0':
        break;
    case '1':
        S_complaints_by_category(accounts, "Service quality", "Service quality");
        break;
    case '2':
        S_complaints_by_category(accounts, "Product issue", "Product issue");
        break;
    case '3':
        S_complaints_by_category(accounts, "Factoration problem", "Factoration problem");
        break;
    case '4':
        S_complaints_by_category(accounts, "Technical Complaints", "Technical Complaints");
        break;
    case '5':
        S_complaints_by_category(accounts, "Customer Service", "Customer Service");
        break;
    case '6':
        S_complaints_by_category(accounts, "Category Not Specified", "Category Not Specified");
        break;
    default:
        printf("Invalid choice.\n");
        break;
    }
}

void S_complaints_by_category(ACC *accounts, const char *category_label, const char *category){
    printf("%s : \n", category_label);
    for (int i = 0; i < AccNum; i++){
        if (accounts[i].NumOfCom == 0){
            continue;
        }
        for (int j = 0; j < accounts[i].NumOfCom; j++){
            if (strcmp(accounts[i].complaints[j].categorie, category) == 0){
                printf("Name : %s\n", accounts[i].FullName);
                printf("(%s)\n", accounts[i].complaints[j].date);
                printf("ID : %s\nComplaint : %s (%s)\n", accounts[i].complaints[j].ID, accounts[i].complaints[j].motif, accounts[i].complaints[j].status);
                printf("Description : %s\n", accounts[i].complaints[j].description);
                printf("Note from the agency : %s\n", accounts[i].complaints[j].Note);
                printf("---------------------------------------------------------------------------------\n");
            }
        }
    }
    printf("-----------------------------------------------------------------------------------------------------------------------------\n");
}

void Search_Status(ACC *accounts){
    char choice;

    printf("Press 0 to get back to the previous menu.\n");
    printf("Press 1 to display all the complaints in 'pending' status.\n");
    printf("Press 2 to display all the complaints in 'Resolved' status.\n");
    printf("Press 3 to display all the complaints in 'Rejected' status.\n");
    printf("==> ");
    scanf(" %c", &choice);
    printf("----------------------------------------------------------------------------------\n");

    switch (choice){
    case '0':
        break;
    case '1':
        S_complaints_by_status(accounts, "pending", "pending");
        break;
    case '2':
        S_complaints_by_status(accounts, "Resolved", "Resolved");
        break;
    case '3':
        S_complaints_by_status(accounts, "Rejected", "Rejected");
        break;
    default:
        printf("Invalid choice.\n");
        break;
    }
}

void S_complaints_by_status(ACC *accounts, const char *status_label, const char *status){
    printf("%s : \n", status_label);
    for (int i = 0; i < AccNum; i++){
        if (accounts[i].NumOfCom == 0){
            continue;
        }
        for (int j = 0; j < accounts[i].NumOfCom; j++){
            if (strcmp(accounts[i].complaints[j].status, status) == 0){
                printf("Name : %s\n", accounts[i].FullName);
                printf("(%s)\n", accounts[i].complaints[j].date);
                printf("ID : %s\nComplaint : %s (%s)\n", accounts[i].complaints[j].ID, accounts[i].complaints[j].motif, accounts[i].complaints[j].status);
                printf("Description : %s\n", accounts[i].complaints[j].description);
                printf("Note from the agency : %s\n", accounts[i].complaints[j].Note);
                printf("---------------------------------------------------------------------------------\n");
            }
        }
    }
    printf("-----------------------------------------------------------------------------------------------------------------------------\n");
}

void Status_change(ACC *accounts){
    printf("Complain found!!\n");
    printf("Name : %s\n",accounts[Acc_Index].FullName);
    printf("ID : %s\nComplaint : %s (%s)\n",accounts[Acc_Index].complaints[Com_Index].ID, accounts[Acc_Index].complaints[Com_Index].motif, accounts[Acc_Index].complaints[Com_Index].status);
    printf("Category : %s\n",accounts[Acc_Index].complaints[Com_Index].categorie);
    printf("Description : %s\n",accounts[Acc_Index].complaints[Com_Index].description);
    printf("Note from the agency : %s\n",accounts[Acc_Index].complaints[Com_Index].Note);
    printf("Date : %s\n",accounts[Acc_Index].complaints[Com_Index].date);
    printf("---------------------------------------------------------------------------------\n");
    if (strcmp(accounts[Acc_Index].complaints[Com_Index].status, "Resolved") == 0 || strcmp(accounts[Acc_Index].complaints[Com_Index].status, "Rejected") == 0){
        printf("This complaint already have been treated.\n");
        printf("---------------------------------------------------------------------------------\n");
        return;
    }
    if (strcmp(accounts[Acc_Index].complaints[Com_Index].status, "pending") == 0){
        printf("This complain is still pending.\n");
    }
    printf("Press 1 to change the status to 'Resolved'\n");
    printf("Press 2 to change the status to 'Rejected'\n");
    printf("Press 3 to  change the status to 'under process'\n");
    
    char choice;
    printf("==> ");
    scanf(" %c",&choice);
    printf("---------------------------------------------------------------------------------\n");

    switch (choice){
    case '1':
        strcpy(accounts[Acc_Index].complaints[Com_Index].status, "Resolved");
        printf("Done!\n");
        printf("---------------------------------------------------------------------------------\n");
        break;

    case '2':
        strcpy(accounts[Acc_Index].complaints[Com_Index].status, "Rejected");
        printf("Done!\n");
        printf("---------------------------------------------------------------------------------\n");
        break;
    case '3':
        strcpy(accounts[Acc_Index].complaints[Com_Index].status, "under process");
        printf("Done!\n");
        printf("---------------------------------------------------------------------------------\n");
        break;

    default:
        printf("Wrong choice, this complain will stay under the process at the moment.\n");
        printf("---------------------------------------------------------------------------------\n");
        break;
    }
    char Second_Choice;

    printf("Press 0 to leave the note empty.\n");
    printf("Press 1 to write a note about the complaint.\n");
    printf("==> ");
    scanf(" %c",&Second_Choice);
    getchar();
    printf("-----------------------------------------------------\n");

    switch (Second_Choice){
    case '0':
        break;

    case '1':
        printf("==> ");
        fgets(accounts[Acc_Index].complaints[Com_Index].Note, MAX_DESCRIPTION_LENGTH, stdin);
        accounts[Acc_Index].complaints[Com_Index].Note[strcspn(accounts[Acc_Index].complaints[Com_Index].Note, "\n")] = '\0';
        printf("----------------------------------------------------------------------------------------\n");
        break;
    
    default:
        printf("Invalid choice. Please choose a valid option.\n");
        printf("-----------------------------------------------------\n");
        break;
    }
}

void Com_Mod_Del(ACC *accounts){
    char choice;
    printf("Press 0 to get back to the previous menu.\n");
    printf("Press 1 to delete a complain.\n");
    printf("Press 2 to modify a complain.\n");
    printf("==> ");
    scanf(" %c",&choice);
    printf("--------------------------------------------\n");

    switch (choice){
    case '0':
        break;
    case '1':
        Com_Deletion(accounts);
        break;
    case '2':
        Com_Modification(accounts);
        break;
    default:
        printf("Invalid choice. Please try again.\n");
        printf("--------------------------------------------");
        break;
    }
}

void Com_Modification(ACC *accounts){
    Search_ID(accounts);
    if (strcmp(accounts[index_to_sign_in].AccType, "client") != 0 && strcmp(accounts[Acc_Index].Email, accounts[index_to_sign_in].Email) != 0){
        printf("ID not found in your IDs complaints\n");
        printf("-----------------------------------------------------\n");
        return;
    }
    char Y_N;
    char answer;

    printf("Do you want to modify the motif's title ( Y/N ).\n");
    printf("==> ");
    scanf(" %c",&Y_N);
    getchar();
    printf("-----------------------------------------------------\n");
    answer = tolower(Y_N);
    if (answer == 'y'){
        memset(accounts[Acc_Index].complaints[Com_Index].motif, 0, sizeof(accounts[Acc_Index].complaints[Com_Index].motif));
        printf("Enter the new motif title : ");
        fgets(accounts[Acc_Index].complaints[Com_Index].motif, MAX_NAME_LENGTH, stdin);
        accounts[Acc_Index].complaints[Com_Index].motif[strcspn(accounts[Acc_Index].complaints[Com_Index].motif, "\n")] = '\0';
        printf("-----------------------------------------------------\n");
    }

    printf("Do you want to modify the description content ( Y/N ).\n");
    printf("==> ");
    scanf(" %c",&Y_N);
    getchar();
    printf("-----------------------------------------------------\n");
    answer = tolower(Y_N);
    if (answer == 'y'){
        memset(accounts[Acc_Index].complaints[Com_Index].description, 0, sizeof(accounts[Acc_Index].complaints[Com_Index].description));
        printf("Enter the new description : ");
        fgets(accounts[Acc_Index].complaints[Com_Index].description, MAX_DESCRIPTION_LENGTH, stdin);
        accounts[Acc_Index].complaints[Com_Index].description[strcspn(accounts[Acc_Index].complaints[Com_Index].description, "\n")] = '\0';
        printf("------------------------------------------------------------------------------\n");
    }
    
    printf("Do you want to modify the category ( Y/N ).\n");
    printf("==> ");
    scanf(" %c",&Y_N);
    getchar();
    printf("-----------------------------------------------------\n");
    answer = tolower(Y_N);
    if (answer == 'y'){
        memset(accounts[Acc_Index].complaints[Com_Index].categorie, 0, sizeof(accounts[Acc_Index].complaints[Com_Index].categorie));
        printf("To choose a categorie :\n");
        printf("Press 1 for 'Service quality'\n");
        printf("Press 2 for 'Product issue'\n");
        printf("Press 3 for 'Factoration problem'\n");
        printf("Press 4 for 'Technical Complaints'\n");
        printf("Press 5 for 'Customer Service'\n");
        printf("Press 6 for 'Category Not Specified'\n");
        printf("===> ");
        scanf(" %c",&Y_N);
        getchar();
        printf("-----------------------------------------\n");

        switch (Y_N){
        case '1':
            strcpy(accounts[Acc_Index].complaints[Com_Index].categorie, "Service quality");
            printf("Done!\n");
            printf("-----------------------------------------\n");
            break;
        case '2':
            strcpy(accounts[Acc_Index].complaints[Com_Index].categorie, "Product issue");
            printf("Done!\n");
            printf("-----------------------------------------\n");
            break;
        case '3':
            strcpy(accounts[Acc_Index].complaints[Com_Index].categorie, "Factoration problem");
            printf("Done!\n");
            printf("-----------------------------------------\n");
            break;
        case '4':
            strcpy(accounts[Acc_Index].complaints[Com_Index].categorie, "Technical Complaints");
            printf("Done!\n");
            printf("-----------------------------------------\n");
            break;
        case '5':
            strcpy(accounts[Acc_Index].complaints[Com_Index].categorie, "Customer Service");
            printf("Done!\n");
            printf("-----------------------------------------\n");
            break;
        case '6':
            strcpy(accounts[Acc_Index].complaints[Com_Index].categorie, "Category Not Specified");
            printf("Done!\n");
            printf("-----------------------------------------\n");
            break;
        default:
            strcpy(accounts[Acc_Index].complaints[Com_Index].categorie, "Category Not Specified");
            printf("U choosed an invalid choice, this complain will include under the category of 'Category Not Specified'\n");
            printf("-----------------------------------------------------------------------------------------------------------\n");
            strcpy(accounts[Acc_Index].complaints[Com_Index].categorie, "Category Not Specified");
            break;
        }
    }

    if (strcmp(accounts[Acc_Index].AccType, "client") != 0){
        printf("Do you want to modify the note ( Y/N ).\n");
        printf("==> ");
        scanf(" %c",&Y_N);
        printf("-----------------------------------------------------\n");
        answer = tolower(Y_N);
        if (answer == 'y'){   
            memset(accounts[Acc_Index].complaints[Com_Index].Note, MAX_DESCRIPTION_LENGTH, sizeof(MAX_DESCRIPTION_LENGTH));
            char choice;
            do{
                printf("Press 0 to leave the note empty.\n");
                printf("Press 1 to write a note about the complaint.\n");
                printf("==> ");
                scanf(" %c",&choice);
                getchar();
                printf("-----------------------------------------------------\n");

                switch (choice){
                case '0':
                    break;

                case '1':
                    printf("==> ");
                    fgets(accounts[Acc_Index].complaints[Com_Index].Note, MAX_DESCRIPTION_LENGTH, stdin);
                    accounts[Acc_Index].complaints[Com_Index].Note[strcspn(accounts[Acc_Index].complaints[Com_Index].Note, "\n")] = '\0';
                    printf("---------------------------------------------------------------\n");
                    break;
                
                default:
                    printf("Invalid choice. Please choose a valid option.\n");
                    printf("-----------------------------------------------------\n");
                    break;
                }
            } while (choice != '0');
        }
    }
    Acc_Index = -1;
    Com_Index = -1;
}

void Com_Deletion(ACC *accounts){   
    Search_ID(accounts);
    if (strcmp(accounts[index_to_sign_in].AccType, "client") != 0 &&
        strcmp(accounts[Acc_Index].Email, accounts[index_to_sign_in].Email) != 0){
        printf("ID not found in your IDs complaints\n");
        printf("-----------------------------------------------------\n");
        return;
    }

    char choice;

    printf("Press 0 to cancel the deletion of that complaint.\n");
    printf("Press 1 to confirm the deletion of that complaint.\n");
    printf("==> ");
    scanf(" %c", &choice);
    printf("------------------------------------------------------\n");

    switch (choice){
    case '0':
        printf("The deletion has been canceled.\n");
        printf("------------------------------------------------------\n");
        break;
    case '1':
        if (accounts[Acc_Index].NumOfCom > 0){
            for (int i = Com_Index; i < accounts[Acc_Index].NumOfCom - 1; i++)
            {
                accounts[Acc_Index].complaints[i] = accounts[Acc_Index].complaints[i + 1];
            }
            memset(&accounts[Acc_Index].complaints[accounts[Acc_Index].NumOfCom - 1], 0, sizeof(accounts[Acc_Index].complaints[accounts[Acc_Index].NumOfCom - 1]));
            accounts[Acc_Index].NumOfCom -= 1;
            printf("The complaint has been deleted successfully.\n");
            printf("------------------------------------------------------\n");
        }
        else{
            printf("No complaints to delete.\n");
            printf("------------------------------------------------------\n");
        }
        break;
    default:
        printf("Invalid choice. Please try again.\n");
        printf("------------------------------------------------------\n");
        break;
    }
    
    Acc_Index = -1;
    Com_Index = -1;
}

void Roles_Assign(ACC *accounts){   
    char NameToSearch[MAX_NAME_LENGTH];
    printf("Enter the name : ");
    getchar();
    fgets(NameToSearch, MAX_NAME_LENGTH, stdin);
    NameToSearch[strcspn(NameToSearch, "\n")] = '\0';
    printf("----------------------------------------\n");
    for (int i = 0; i < AccNum; i++){
        if (strcmp(NameToSearch, accounts[i].FullName) == 0)
        {
            found = 0;
            Acc_Index = i;
            break;
        }
    }
    if (found == -1){
        printf("User is not found\n");
        printf("----------------------------------------\n");
        return;
    }

    char choice;
    printf("Press 1 to change the account type to admin.\n");
    printf("Press 2 to change the account type to agent.\n");
    printf("Press 3 to change the account type to client.\n");
    printf("==> ");
    scanf(" %c",&choice);
    printf("-----------------------------------------------\n");

    switch (choice){
    case '1':
        if (strcmp(accounts[Acc_Index].AccType, "admin") == 0){
            printf("This account already an admin.\n");
            break;
        }
        strcpy(accounts[Acc_Index].AccType, "admin");
        printf("%s now an %s.",accounts[Acc_Index].FullName, accounts[Acc_Index].AccType);
        break;
    case '2':
        if (strcmp(accounts[Acc_Index].AccType, "agent") == 0){
            printf("This account already an agent.\n");
            break;
        }
        strcpy(accounts[Acc_Index].AccType, "agent");
        printf("%s now an %s.",accounts[Acc_Index].FullName, accounts[Acc_Index].AccType);
        break;
    case '3':
        if (strcmp(accounts[Acc_Index].AccType, "client") == 0){
            printf("This account already a client.\n");
            break;
        }
        strcpy(accounts[Acc_Index].AccType, "client");
        printf("%s now an %s.",accounts[Acc_Index].FullName, accounts[Acc_Index].AccType);
        break;
    default:
        break;
    }
    Acc_Index = -1;
}
