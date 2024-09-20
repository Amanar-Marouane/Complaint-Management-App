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
#define MAX_DESCRIPTION_LENGTH 256
#define MAX_COMPLAINS 20
#define MAX_ID_DIGITS 10
#define KeyWords_Num 4

typedef struct
{
    char ID[MAX_ID_DIGITS];
    char motif[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    char categorie[MAX_DESCRIPTION_LENGTH];
    char status[MAX_NAME_LENGTH];
    char date[MAX_NAME_LENGTH];
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
    complain complains[MAX_COMPLAINS];
} ACC;

int AccNum = 1;
int num = 2;
int index_to_sign_in = -1;
int found = -1;
int Acc_Index = -1;
int Com_Index = -1;

void Sign_Up(ACC *accounts);
void Sign_in(ACC *accounts);
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
void Status_Sort(ACC *accounts);
void Search(ACC *accounts);
void Search_ID(ACC *accounts);
void Search_NAME(ACC *accounts);
void Search_Date(ACC *accounts);
void Status_change(ACC *accounts);

void cleanup(ACC *accounts)
{
    if (accounts != NULL)
    {
        free(accounts);
    }
}

int main()
{
    char choix;

    ACC *accounts = malloc(num * sizeof(ACC));
    if (accounts == NULL)
    {
        printf("Memory allocation failed!\n");
        printf("-------------------------------------\n");
        cleanup(accounts);
        return 1;
    }

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
        scanf(" %c",&choix);
        printf("-------------------------------------\n");
        getchar();

        switch (choix)
        {
        case '0':
            break;
        case '1':
            Sign_Up(accounts);
            AccNum ++;
            num ++;
            ACC *NewAccounts = realloc(accounts, num * sizeof(ACC));
            if (accounts == NULL)
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
    } while (choix != '0');

    cleanup(accounts);
    return 0;
}

void Sign_Up(ACC *accounts)
{
    accounts[AccNum].NumOfCom = 0;
    do
    {
        printf("Enter your full name : ");
        fgets(accounts[AccNum].FullName, MAX_NAME_LENGTH, stdin);
        accounts[AccNum].FullName[strcspn(accounts[AccNum].FullName, "\n")] = '\0';
        printf("---------------------------------------------------\n");
    } while (name_validator(AccNum, accounts) == 1);
    

    do
    {
        printf("Enter your UserName : ");
        fgets(accounts[AccNum].UserName, MAX_NAME_LENGTH, stdin);
        accounts[AccNum].UserName[strcspn(accounts[AccNum].UserName, "\n")] = '\0';
        printf("----------------------------------------------------------------\n");
    } while (username_validator(AccNum, accounts) == 1);
    
    do
    {
        printf("Enter your phone number : ");
        fgets(accounts[AccNum].PhoneNumber, MAX_PHONE_NUMBER_LENGTH, stdin);
        accounts[AccNum].PhoneNumber[strcspn(accounts[AccNum].PhoneNumber, "\n")] = '\0';
        printf("----------------------------------------------------------------\n");
    } while (num_validator(AccNum, accounts) == 0);
    
    do
    {
        printf("Enter your email : ");
        fgets(accounts[AccNum].Email, MAX_EMAIL_LENGTH, stdin);
        accounts[AccNum].Email[strcspn(accounts[AccNum].Email, "\n")] = '\0';
        printf("----------------------------------------------------------------\n");
    } while (email_validator(AccNum, accounts) == 1);

    do
    {
        printf("Enter your password : \nPassword must have \n");
        printf("- At least 8 characters\n");
        printf("- One uppercase letter\n");
        printf("- One lowercase letter\n");
        printf("- One number\n");
        printf("- One special character (!@#$%^&*)\n");
        printf("==> ");
        fgets(accounts[AccNum].PassWord, MAX_PASSWORD_LENGTH, stdin);
        accounts[AccNum].PassWord[strcspn(accounts[AccNum].PassWord, "\n")] = '\0';
        printf("----------------------------------------------------------------\n");
    } while (pass_word_validator(AccNum, accounts) == 1);
    
    strcpy(accounts[AccNum].AccType, "Client");

    printf("Sign-up successful for %s\n", accounts[AccNum].FullName);
    printf("----------------------------------------------------------------\n");
}

int name_validator(int AccNum, ACC *accounts)
{   
    if (strlen(accounts[AccNum].FullName) == 0)
    {
        printf("==>Contact name is not valid .\n(Empty!!)\n");
        printf("----------------------------------------------------------------\n");
        return 1;
    }
    if (accounts[AccNum].FullName[0] == ' ')
    {
        printf("==>Contact name is not valid .\n(Must not start with space!!)\n");
        printf("----------------------------------------------------------------\n");
        return 1;
    }
    for (int i = 0;accounts[AccNum].FullName[i] != '\0' ; i++)
    {
        if (!isalpha(accounts[AccNum].FullName[i]) && !isspace(accounts[AccNum].FullName[i]))
        {
            printf("==>Contact name is not valid .\n(Must contain only alphabets!!)\n");
            printf("----------------------------------------------------------------\n");
            return 1;
        }
    }
    for (int i = 0; i < AccNum; i++)
    {
        if (strcmp(accounts[i].FullName, accounts[AccNum].FullName) == 0)
        {
            printf("==> Contact name is already used.\n");
            printf("----------------------------------------------------------------\n");
            return 1;
        }
    }
    
    printf("==>Contact name is accepted !!\n");
    printf("----------------------------------------------------------------\n");
    return 0;
}

int username_validator(int AccNum, ACC *accounts)
{   
    int alpha = 0;
    if (strlen(accounts[AccNum].UserName) < 4)
    {
        printf("==>UserName is too short.\n");
        printf("----------------------------------------------------------------\n");
        return 1;
    }
    for (int i = 0;accounts[AccNum].UserName[i] != '\0' ; i++)
    {
        if (!isalnum(accounts[AccNum].UserName[i]))
        {
            printf("==>UserName is not valid.\n(Must contain only alphabets and digits.)\n");
            printf("----------------------------------------------------------------\n");
            return 1;
        }
        if (isalpha(accounts[AccNum].UserName[i]))
        {
            alpha ++;
        }
    }
    if (alpha == 0)
    {
        printf("==>UserName is not valid.\n(Must contain alphabets.)\n");
        printf("----------------------------------------------------------------\n");
        return 1;
    }
    for (int i = 0; i < AccNum; i++)
    {
        if (strcmp(accounts[i].UserName, accounts[AccNum].UserName) == 0)
        {
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
    for (int i = 0;accounts[AccNum].PhoneNumber[i] != '\0' ; i++)
    {
        if (!isdigit(accounts[AccNum].PhoneNumber[i]))
        {
            printf("==>Phone number is not valid.\n(Must contain only digits!!)\n");
            printf("----------------------------------------------------------------\n");
            return 0;
        }
    }
    if (strlen(accounts[AccNum].PhoneNumber) != PHONE_NUMBER_LENGTH)
    {
        printf("==>Phone number is not valid.\n(Must contain 10 digits!!)\n");
        printf("----------------------------------------------------------------\n");
        return 0;
    }
    for (int i = 0; i < AccNum; i++)
    {
        if (strcmp(accounts[i].PhoneNumber, accounts[AccNum].PhoneNumber) == 0)
        {
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

    if (at == NULL || dot == NULL || dot < at)
    {
        printf("==>Email is not valid.\n(Must be in the format username@gmail.com)\n");
        printf("----------------------------------------------------------------\n");
        return 1;
    }

    if (at == accounts[AccNum].Email)
    {
        printf("==> The username part before '@' cannot be empty. (username@gmail.com)\n");
        printf("-----------------------------------------------------------------------\n");
        return 1;
    }
    if (at + 1 == dot)
    {
        printf("==> The example part between '@' and '.' cannot be empty. (username@gmail.com)\n");
        printf("----------------------------------------------------------------\n");
        return 1;
    }
    if (*(dot + 1) == '\0')
    {
        printf("==> The domain extension after '.' cannot be empty. (username@gmail.com)\n");
        printf("----------------------------------------------------------------\n");
        return 1;
    }
    
    for (int i = 0; i < (at - accounts[AccNum].Email); i++)
    {
        if (!(isalnum(accounts[AccNum].Email[i]) || accounts[AccNum].Email[i] == '.' || accounts[AccNum].Email[i] == '-' || accounts[AccNum].Email[i] == '_') && isspace(accounts[AccNum].Email[i]))
        {
            printf("==>The username part accept only ('A-Z', 'a-z', '0-9', '.', '-', '_'), Space not include.\n");
            printf("-----------------------------------------------------------------------\n");
            return 1;
        }
    }
    for (int i = (at - accounts[AccNum].Email) + 1; i < (dot - accounts[AccNum].Email); i++)
    {
        if (!isalpha(accounts[AccNum].Email[i]))
        {
            printf("==>Special symbol and numbers not valid atfer '@'.\n");
            printf("-----------------------------------------------------------------------\n");
            return 1;
        }
    }

    const char* gmail = "gmail";
    if (strncmp(at + 1, gmail, strlen(gmail)) != 0 || at + 1 + strlen(gmail) != dot) 
    {   
        printf("==>Only accept (username@gmail.com).\n");
        printf("-----------------------------------------------------------------------\n");
        return 1;
    }

    for (int i = (dot - accounts[AccNum].Email) + 1; accounts[AccNum].Email[i] != '\0'; i++)
    {
        if (!isalpha(accounts[AccNum].Email[i]))
        {
            printf("==>Special symbol and numbers not valid in the extension part.\n");
            printf("-----------------------------------------------------------------------\n");
            return 1;
        }
    }

    const char* com = "com";
    if (strcmp(dot + 1,com) != 0)
    {
        printf("==>Only accept (username@gmail.com).\n");
        printf("-----------------------------------------------------------------------\n");
        return 1;
    }
    for (int i = 0; i < AccNum; i++)
    {
        if (strcmp(accounts[i].Email, accounts[AccNum].Email) == 0)
        {
            printf("==> This address email is already used.\n");
            printf("----------------------------------------------------------------\n");
            return 1;
        }
    }

    printf("==>The address email is accepted !!\n");
    printf("-----------------------------------------------------------------------\n");
    return 0;
}

int pass_word_validator(int AccNum, ACC *accounts)
{
    int lower = 0, upper = 0, number = 0, special = 0;

    if (strlen(accounts[AccNum].PassWord) < 8)
    {
        printf("Password too short! Must be at least 8 characters.\n");
        printf("----------------------------------------------------------------\n");
        return 1;
    }
    if (strstr(accounts[AccNum].PassWord, accounts[AccNum].UserName) != NULL)
    {
        printf("Password should not include the username!\n");
        printf("----------------------------------------------------------------\n");
        return 1;
    }
    
    for (int i = 0; accounts[AccNum].PassWord[i] != '\0'; i++)
    {
        if (islower(accounts[AccNum].PassWord[i])) lower++;
        else if (isupper(accounts[AccNum].PassWord[i])) upper++;
        else if (isdigit(accounts[AccNum].PassWord[i])) number++;
        else if (strchr("!@#$%^&*", accounts[AccNum].PassWord[i])) special++;
        else {
            printf("Invalid characters in password! Only allowed special characters are !@#$%^&*\n");
            printf("----------------------------------------------------------------\n");
            return 1;
        }
    }
    if (lower > 0 && upper > 0 && number > 0 && special > 0) {
        printf("Password is valid.\n");
        printf("----------------------------------------------------------------\n");
        return 0;
    }

    printf("Password invalid! It must contain at least one lowercase letter, one uppercase letter, one number, and one special character.\n");
    printf("------------------------------------------------------------------------------------------------------------------------------\n");
    return 1;
}

void Sign_in(ACC *accounts)
{
    char choice;
    char email_to_sign_in[MAX_EMAIL_LENGTH];
    char number_to_sign_in[MAX_PHONE_NUMBER_LENGTH];
    char username_to_sign_in[MAX_NAME_LENGTH];

    printf("Press 0 to cancel sign in\n");
    printf("Press 1 to sign in by email\n");
    printf("Press 2 to sign in by number\n");
    printf("Press 3 to sign in by user name\n");
    printf("==> ");
    scanf(" %c",&choice);
    getchar();
    printf("----------------------------------------\n");

    switch (choice)
    {
    case '0':
        break;
    case '1':
        for (int k = 0; k < 3; k++)
        {
            printf("Enter your email adress to sign in : ");
            fgets(email_to_sign_in, MAX_EMAIL_LENGTH, stdin);
            email_to_sign_in[strcspn(email_to_sign_in, "\n")] = '\0';
            printf("-------------------------------------------------------------\n");
            for (int i = 0; i < AccNum; i++)
            {
                if (strcmp(email_to_sign_in,accounts[i].Email) == 0)
                {   
                    found = 0;
                    index_to_sign_in = i;
                    break;
                }
            }
            if (found == -1)
            {
                printf("No such account include with this email.\n");
                printf("---------------------------------------------------\n");
            }else
            {
                break;
            }

            if (k == 2)
            {
                printf("You've entred incorrect information more then 3 times!!\n");
                printf("You need to wait 1h before Resign in again ....\n");
                sleep(3600);
                return;
            }  
        }
        found = -1;
        Pass_Word_Sign_in(accounts);
        break;

    case '2':
        for (int k = 0; k < 3; k++)
        {
            printf("Enter your number to sign in : ");
            fgets(number_to_sign_in, MAX_EMAIL_LENGTH, stdin);
            number_to_sign_in[strcspn(number_to_sign_in, "\n")] = '\0';
            printf("--------------------------------------------------------\n");
            for (int i = 0; i < AccNum; i++)
            {
                if (strcmp(number_to_sign_in,accounts[i].PhoneNumber) == 0)
                {   
                    found = 0;
                    index_to_sign_in = i;
                    break;
                }
            }
            if (found == -1)
            {
                printf("No such account include with this number.\n");
                printf("---------------------------------------------------\n");
            }else
            {
                break;
            }

            if (k == 2)
            {
                printf("You've entred incorrect information more then 3 times!!\n");
                printf("You need to wait 1h before Resign in again ....\n");
                sleep(3600);
                return;
            }
        }
        
        found = -1;
        Pass_Word_Sign_in(accounts);
        break;

    case '3':
        for (int k = 0; k < 3; k++)
        {
            printf("Enter your user name to sign in : ");
            fgets(username_to_sign_in, MAX_EMAIL_LENGTH, stdin);
            username_to_sign_in[strcspn(username_to_sign_in, "\n")] = '\0';
            printf("--------------------------------------------------------\n");
            for (int i = 0; i < AccNum; i++)
            {
                if (strcmp(username_to_sign_in,accounts[i].UserName) == 0)
                {   
                    found = 0;
                    index_to_sign_in = i;
                    break;
                }
            }
            
            if (found == -1)
            {
                printf("No such account include with this user name.\n");
                printf("---------------------------------------------------\n");
            }else
            {
                break;
            }

            if (k == 2)
            {
                printf("You've entred incorrect information more then 3 times!!\n");
                printf("You need to wait 1h before Resign in again ....\n");
                sleep(3600);
                return;
            }
        }
        found = -1;
        Pass_Word_Sign_in(accounts);
        break;
        
    default:
        printf("Invalid choice, please select a valid option.\n");
        printf("----------------------------------------\n");
        break;
    }

    return;
}

void Pass_Word_Sign_in(ACC *accounts)
{
    char pass_word_to_sign_in[MAX_PASSWORD_LENGTH];

    for (int i = 0; i < 3; i++)
            {
                printf("Enter your password to sign in : ");
                fgets(pass_word_to_sign_in, MAX_EMAIL_LENGTH, stdin);
                pass_word_to_sign_in[strcspn(pass_word_to_sign_in, "\n")] = '\0';
                printf("---------------------------------------------------\n");

                if (strcmp(pass_word_to_sign_in,accounts[index_to_sign_in].PassWord) == 0)
                {   found = 0;
                    break;
                }
                if (found == -1)
                {
                    printf("Incorrect password!!\n");
                    printf("---------------------------------------------------\n");
                }
                if (i == 2)
                {
                    printf("You entered more then 3 times an incorrect password\n");
                    printf("You need to wait for 10sec to Resign in again ....\n");
                    sleep(3600);
                    printf("---------------------------------------------------\n");
                    return;
                }
            }
            printf("You signed in successfuly\n");
            printf("---------------------------------------------------\n");

            if (strcmp(accounts[index_to_sign_in].AccType, "client")) client_panel(accounts);
            else if (strcmp(accounts[index_to_sign_in].AccType, "admin")) admin_panel(accounts);
            else if (strcmp(accounts[index_to_sign_in].AccType, "Agent")) agent_panel(accounts);
            
            found = -1;
}

void client_panel(ACC *accounts)
{
    printf("Welcom %s (%s)\n",accounts[index_to_sign_in].FullName,accounts[index_to_sign_in].AccType);
    
    char choice;
    do
    {
        printf("Press 0 to sign out\n");
        printf("Press 1 to submit a complain\n");
        printf("Press 2 to see your complains\n");
        printf("==> ");
        scanf(" %c",&choice);
        getchar();
        printf("---------------------------------\n");

        switch (choice)
        {
        case '0':
            index_to_sign_in = -1;
            break;

        case '1':
            Complain(accounts);
            break;
            
        case '2':
            if (accounts[index_to_sign_in].NumOfCom == 0)
            {
                printf("No complains to show\n");
                printf("---------------------------------\n");
                break;
            }
            for (int i = 0; i < accounts[index_to_sign_in].NumOfCom; i++)
            {
                printf("ID : %s\nComplaint : %s (%s)\n",accounts[index_to_sign_in].complains[i].ID, accounts[index_to_sign_in].complains[i].motif, accounts[index_to_sign_in].complains[i].status);
                printf("Category : %s\n",accounts[index_to_sign_in].complains[i].categorie);
                printf("Description : %s\n",accounts[index_to_sign_in].complains[i].description);
                printf("Date : %s\n",accounts[index_to_sign_in].complains[i].date);
                printf("---------------------------------------------------------------------------------\n");
            }
            break;

        default:
            printf("Invalid choice, please select a valid option.\n");
            printf("----------------------------------------\n");
            break;
        }
    } while (choice != '0');
    return;
}

void admin_panel(ACC *accounts)
{
    printf("Welcom %s (%s)\n",accounts[index_to_sign_in].FullName,accounts[index_to_sign_in].AccType);
    index_to_sign_in = -1;
    char choice;
    do
    {
        printf("Press 0 to sign out\n");
        printf("Press 1 to see all the users\n");
        printf("Press 2 to see all the complains\n");
        printf("Press 3 to search for a complain\n");
        printf("Press 4 to delete a complain\n");
        printf("Press 5 to manage the assignment roles\n");
        printf("Press 6 to generate the statistics\n");
        printf("==> ");
        scanf(" %c",&choice);
        getchar();
        printf("---------------------------------\n");

        switch (choice)
        {
        case '0':
            index_to_sign_in = -1;
            break;
        case '1':
            Display_ALL_USERS(accounts);
            break;
        case '2':
            Display_Com(accounts);
            break;
        
        default:
            printf("Invalid choice, please select a valid option.\n");
            printf("----------------------------------------\n");
            break;
        }
    } while (choice != '0');
    return;
}

void agent_panel(ACC *accounts)
{
    printf("Welcom %s (%s)\n",accounts[index_to_sign_in].FullName,accounts[index_to_sign_in].AccType);
    index_to_sign_in = -1;
    char choice;
    do
    {
        printf("Press 0 to sign out\n");
        printf("Press 1 to see all the complains");
        printf("Press 2 to manage a complain");
        printf("==> ");
        scanf(" %c",&choice);
        getchar();
        printf("---------------------------------\n");

        switch (choice)
        {
        case 0:
            index_to_sign_in = -1;
            break;
        
        default:
            printf("Invalid choice, please select a valid option.\n");
            printf("----------------------------------------\n");
            break;
        }
    } while (choice != '0');
    return;
}

void Complain(ACC *accounts)
{
    char choice;
    int num;
    srand(time(0));

    for (int i = 0; i < MAX_ID_DIGITS; i++)
    {
        num = rand() % 36; // car 10 (0-9) et 26(A-Z) ==> 10+26 = 36
        if (num < 10)
        {
            accounts[index_to_sign_in].complains[accounts[index_to_sign_in].NumOfCom].ID[i] = num + '0';
        }else
        {
           accounts[index_to_sign_in].complains[accounts[index_to_sign_in].NumOfCom].ID[i] = num - 10 + 'A';
        }
    }
    printf("What's the subject of your complaint : ");
    fgets(accounts[index_to_sign_in].complains[accounts[index_to_sign_in].NumOfCom].motif, MAX_NAME_LENGTH, stdin);
    accounts[index_to_sign_in].complains[accounts[index_to_sign_in].NumOfCom].motif[strcspn(accounts[index_to_sign_in].complains[accounts[index_to_sign_in].NumOfCom].motif, "\n")] = '\0';
    printf("------------------------------------------------------------------\n");

    printf("Description : ");
    fgets(accounts[index_to_sign_in].complains[accounts[index_to_sign_in].NumOfCom].description, MAX_NAME_LENGTH, stdin);
    accounts[index_to_sign_in].complains[accounts[index_to_sign_in].NumOfCom].description[strcspn(accounts[index_to_sign_in].complains[accounts[index_to_sign_in].NumOfCom].description, "\n")] = '\0';
    printf("------------------------------------------------------------------\n");

    printf("To choose a categorie :\n");
    printf("Press 1 for 'Serious Adverse Events'\n");
    printf("Press 2 for 'Moderate Adverse Events'\n");
    printf("Press 3 for 'Administrative/Contractual Complaints'\n");
    printf("Press 4 for 'Technical Complaints'\n");
    printf("Press 5 for 'Customer Service'\n");
    printf("Press 6 for 'Category Not Specified'\n");
    printf("===> ");
    scanf(" %c",&choice);
    getchar();
    printf("-----------------------------------------\n");

    switch (choice)
    {
    case '1':
        strcpy(accounts[index_to_sign_in].complains[accounts[index_to_sign_in].NumOfCom].categorie, "Serious Adverse Events");
        printf("Done!\n");
        printf("-----------------------------------------\n");
        break;
    case '2':
        strcpy(accounts[index_to_sign_in].complains[accounts[index_to_sign_in].NumOfCom].categorie, "Moderate Adverse Events");
        printf("Done!\n");
        printf("-----------------------------------------\n");
        break;
    case '3':
        strcpy(accounts[index_to_sign_in].complains[accounts[index_to_sign_in].NumOfCom].categorie, "Administrative/Contractual Complaints");
        printf("Done!\n");
        printf("-----------------------------------------\n");
        break;
    case '4':
        strcpy(accounts[index_to_sign_in].complains[accounts[index_to_sign_in].NumOfCom].categorie, "Technical Complaints");
        printf("Done!\n");
        printf("-----------------------------------------\n");
        break;
    case '5':
        strcpy(accounts[index_to_sign_in].complains[accounts[index_to_sign_in].NumOfCom].categorie, "Customer Service");
        printf("Done!\n");
        printf("-----------------------------------------\n");
        break;
    case '6':
        strcpy(accounts[index_to_sign_in].complains[accounts[index_to_sign_in].NumOfCom].categorie, "Category Not Specified");
        printf("Done!\n");
        printf("-----------------------------------------\n");
        break;
    default:
        printf("U choosed an invalid choice, this complain will include under the category of 'Category Not Specified'\n");
        printf("-----------------------------------------------------------------------------------------------------------\n");
        strcpy(accounts[index_to_sign_in].complains[accounts[index_to_sign_in].NumOfCom].categorie, "Category Not Specified");
        break;
    }

    printf("This complain will put under 'Under process' while it proccess.\n");
    printf("------------------------------------------------------------\n");
    strcpy(accounts[index_to_sign_in].complains[accounts[index_to_sign_in].NumOfCom].status, "Under process");

    time_t current_time;
    time(&current_time);
    ctime(&current_time);
    strcpy(accounts[index_to_sign_in].complains[accounts[index_to_sign_in].NumOfCom].date, ctime(&current_time));

    printf("Time of submition : %s\n", accounts[index_to_sign_in].complains[accounts[index_to_sign_in].NumOfCom].date);
    printf("------------------------------------------------------------\n");
    accounts[index_to_sign_in].NumOfCom ++;
}

void Display_ALL_USERS(ACC *accounts)
{   
    printf("Administrators : \n\n");
    for (int i = 0; i < AccNum; i++)
    {
        if (strcmp(accounts[i].AccType, "admin"));
        {
            printf("%s\n", accounts[i].FullName);
            printf("UserName : %s\n",accounts[i].UserName);
            printf("Phone number : %s\n",accounts[i].PhoneNumber);
            printf("Email address : %s\n",accounts[i].Email);
        }
    }
    printf("----------------------------------------------------------\n");
    printf("Agents : \n\n");
    for (int i = 0; i < AccNum; i++)
    {
        if (strcmp(accounts[i].AccType, "agent"));
        {
            printf("%s\n", accounts[i].FullName);
            printf("UserName : %s\n",accounts[i].UserName);
            printf("Phone number : %s\n",accounts[i].PhoneNumber);
            printf("Email address : %s\n",accounts[i].Email);
        }
    }
    printf("----------------------------------------------------------\n");
    printf("Clients : \n\n");
    for (int i = 0; i < AccNum; i++)
    {
        if (strcmp(accounts[i].AccType, "client"));
        {
            printf("%s\n", accounts[i].FullName);
            printf("UserName : %s\n",accounts[i].UserName);
            printf("Phone number : %s\n",accounts[i].PhoneNumber);
            printf("Email address : %s\n",accounts[i].Email);
        }
    }
    printf("----------------------------------------------------------\n");
}

void Display_Com(ACC *accounts)
{
    char choice;
    printf("Press 0 to get back to the previous menu\n");
    printf("Press 1 to display all the complains sorted by priorities\n");
    printf("Press 2 to display all the complains sorted by categories\n");
    printf("Press 3 to display all the complains sorted by status\n");
    printf("==> ");
    scanf(" %c",&choice);

    do
    {
        switch (choice)
        {
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
    } while (choice != '0');
    
}

void Priority_Sort(ACC *accounts)
{
    //Sorting all the complains by using key words.
    char KeyWords_1st[KeyWords_Num][MAX_DESCRIPTION_LENGTH] = {"critical failure", "system down", "data loss", "security breach"};
    char KeyWords_2nd[KeyWords_Num][MAX_DESCRIPTION_LENGTH] = {"performance issues", "service disruption", "frequent errors", "backup failure"};
    char KeyWords_3rd[KeyWords_Num][MAX_DESCRIPTION_LENGTH] = {"slow response", "feature request", "minor bug", "UI/UX improvement"};

    printf("Urgent cases : \n\n");
    for (int i = 0; i < AccNum; i++)
    {
        if (accounts[i].NumOfCom == 0)
        {
            i ++;
        }
        for (int j = 0; j < accounts[i].NumOfCom; j++)
        {
            for (int k = 0; k < KeyWords_Num; k++)
            {
                if (strstr(KeyWords_1st[k], accounts[i].complains[j].description) != 0)
                {
                    printf("ID : %s\nComplaint : %s (%s)\n",accounts[index_to_sign_in].complains[i].ID, accounts[index_to_sign_in].complains[i].motif, accounts[index_to_sign_in].complains[i].status);
                    printf("Category : %s\n",accounts[index_to_sign_in].complains[i].categorie);
                    printf("Description : %s\n",accounts[index_to_sign_in].complains[i].description);
                    printf("Date : %s\n\n",accounts[index_to_sign_in].complains[i].date);
                }
            }
        }
    }
    printf("-------------------------------------------------------------------------------------------\n");
    printf("Important cases : \n\n");
    for (int i = 0; i < AccNum; i++)
    {
        if (accounts[i].NumOfCom == 0)
        {
            i ++;
        }
        for (int j = 0; j < accounts[i].NumOfCom; j++)
        {
            for (int k = 0; k < KeyWords_Num; k++)
            {
                if (strstr(KeyWords_2nd[k], accounts[i].complains[j].description) != 0)
                {
                    printf("ID : %s\nComplaint : %s (%s)\n",accounts[index_to_sign_in].complains[i].ID, accounts[index_to_sign_in].complains[i].motif, accounts[index_to_sign_in].complains[i].status);
                    printf("Category : %s\n",accounts[index_to_sign_in].complains[i].categorie);
                    printf("Description : %s\n",accounts[index_to_sign_in].complains[i].description);
                    printf("Date : %s\n\n",accounts[index_to_sign_in].complains[i].date);
                }
            }
        }
    }
    printf("-------------------------------------------------------------------------------------------\n");
    printf("Normal cases : \n\n");
    for (int i = 0; i < AccNum; i++)
    {
        if (accounts[i].NumOfCom == 0)
        {
            i ++;
        }
        for (int j = 0; j < accounts[i].NumOfCom; j++)
        {
            for (int k = 0; k < KeyWords_Num; k++)
            {
                if (strstr(KeyWords_3rd[k], accounts[i].complains[j].description) != 0)
                {
                    printf("ID : %s\nComplaint : %s (%s)\n",accounts[index_to_sign_in].complains[i].ID, accounts[index_to_sign_in].complains[i].motif, accounts[index_to_sign_in].complains[i].status);
                    printf("Category : %s\n",accounts[index_to_sign_in].complains[i].categorie);
                    printf("Description : %s\n",accounts[index_to_sign_in].complains[i].description);
                    printf("Date : %s\n\n",accounts[index_to_sign_in].complains[i].date);
                }
            }
        }
    }
    printf("-------------------------------------------------------------------------------------------\n");
}

void Category_Sort(ACC *accounts)
{
    printf("Serious Adverse Events : \n\n");
    for (int i = 0; i < AccNum; i++)
    {
        if (accounts[i].NumOfCom == 0)
        {
            i ++;
        }
        for (int j = 0; j < accounts[i].NumOfCom; j++)
        {
            for (int k = 0; k < KeyWords_Num; k++)
            {
                if (strcmp(accounts[i].complains[j].categorie, "Serious Adverse Events") == 0)
                {
                    printf("ID : %s\nComplaint : %s (%s)\n",accounts[index_to_sign_in].complains[i].ID, accounts[index_to_sign_in].complains[i].motif, accounts[index_to_sign_in].complains[i].status);
                    printf("Description : %s\n",accounts[index_to_sign_in].complains[i].description);
                    printf("Date : %s\n\n",accounts[index_to_sign_in].complains[i].date);
                }
            }
        }
    }
    printf("-------------------------------------------------------------------------------------------\n");
    printf("Moderate Adverse Events : \n\n");
    for (int i = 0; i < AccNum; i++)
    {
        if (accounts[i].NumOfCom == 0)
        {
            i ++;
        }
        for (int j = 0; j < accounts[i].NumOfCom; j++)
        {
            for (int k = 0; k < KeyWords_Num; k++)
            {
                if (strcmp(accounts[i].complains[j].categorie, "Moderate Adverse Events") == 0)
                {
                    printf("ID : %s\nComplaint : %s (%s)\n",accounts[index_to_sign_in].complains[i].ID, accounts[index_to_sign_in].complains[i].motif, accounts[index_to_sign_in].complains[i].status);
                    printf("Description : %s\n",accounts[index_to_sign_in].complains[i].description);
                    printf("Date : %s\n\n",accounts[index_to_sign_in].complains[i].date);
                }
            }
        }
    }
    printf("-------------------------------------------------------------------------------------------\n");
    printf("Administrative/Contractual Complaints : \n\n");
    for (int i = 0; i < AccNum; i++)
    {
        if (accounts[i].NumOfCom == 0)
        {
            i ++;
        }
        for (int j = 0; j < accounts[i].NumOfCom; j++)
        {
            for (int k = 0; k < KeyWords_Num; k++)
            {
                if (strcmp(accounts[i].complains[j].categorie, "Administrative/Contractual Complaints") == 0)
                {
                    printf("ID : %s\nComplaint : %s (%s)\n",accounts[index_to_sign_in].complains[i].ID, accounts[index_to_sign_in].complains[i].motif, accounts[index_to_sign_in].complains[i].status);
                    printf("Description : %s\n",accounts[index_to_sign_in].complains[i].description);
                    printf("Date : %s\n\n",accounts[index_to_sign_in].complains[i].date);
                }
            }
        }
    }
    printf("-------------------------------------------------------------------------------------------\n");
    printf("Technical Complaints : \n\n");
    for (int i = 0; i < AccNum; i++)
    {
        if (accounts[i].NumOfCom == 0)
        {
            i ++;
        }
        for (int j = 0; j < accounts[i].NumOfCom; j++)
        {
            for (int k = 0; k < KeyWords_Num; k++)
            {
                if (strcmp(accounts[i].complains[j].categorie, "Technical Complaints") == 0)
                {
                    printf("ID : %s\nComplaint : %s (%s)\n",accounts[index_to_sign_in].complains[i].ID, accounts[index_to_sign_in].complains[i].motif, accounts[index_to_sign_in].complains[i].status);
                    printf("Description : %s\n",accounts[index_to_sign_in].complains[i].description);
                    printf("Date : %s\n\n",accounts[index_to_sign_in].complains[i].date);
                }
            }
        }
    }
    printf("-------------------------------------------------------------------------------------------\n");
    printf("Customer Service : \n\n");
    for (int i = 0; i < AccNum; i++)
    {
        if (accounts[i].NumOfCom == 0)
        {
            i ++;
        }
        for (int j = 0; j < accounts[i].NumOfCom; j++)
        {
            for (int k = 0; k < KeyWords_Num; k++)
            {
                if (strcmp(accounts[i].complains[j].categorie, "Customer Service") == 0)
                {
                    printf("ID : %s\nComplaint : %s (%s)\n",accounts[index_to_sign_in].complains[i].ID, accounts[index_to_sign_in].complains[i].motif, accounts[index_to_sign_in].complains[i].status);
                    printf("Description : %s\n",accounts[index_to_sign_in].complains[i].description);
                    printf("Date : %s\n\n",accounts[index_to_sign_in].complains[i].date);
                }
            }
        }
    }
    printf("-------------------------------------------------------------------------------------------\n");
    printf("Category Not Specified : \n\n");
    for (int i = 0; i < AccNum; i++)
    {
        if (accounts[i].NumOfCom == 0)
        {
            i ++;
        }
        for (int j = 0; j < accounts[i].NumOfCom; j++)
        {
            for (int k = 0; k < KeyWords_Num; k++)
            {
                if (strcmp(accounts[i].complains[j].categorie, "Category Not Specified") == 0)
                {
                    printf("ID : %s\nComplaint : %s (%s)\n",accounts[index_to_sign_in].complains[i].ID, accounts[index_to_sign_in].complains[i].motif, accounts[index_to_sign_in].complains[i].status);
                    printf("Description : %s\n",accounts[index_to_sign_in].complains[i].description);
                    printf("Date : %s\n\n",accounts[index_to_sign_in].complains[i].date);
                }
            }
        }
    }
    printf("-------------------------------------------------------------------------------------------\n");
}

void Status_Sort(ACC *accounts)
{
   printf("Under process : \n\n");
    for (int i = 0; i < AccNum; i++)
    {
        if (accounts[i].NumOfCom == 0)
        {
            i ++;
        }
        for (int j = 0; j < accounts[i].NumOfCom; j++)
        {
            for (int k = 0; k < KeyWords_Num; k++)
            {
                if (strcmp(accounts[i].complains[j].status, "Under process") == 0)
                {
                    printf("ID : %s\nComplaint : %s\n",accounts[index_to_sign_in].complains[i].ID, accounts[index_to_sign_in].complains[i].motif);
                    printf("Category : %s\n",accounts[index_to_sign_in].complains[i].categorie);
                    printf("Description : %s\n",accounts[index_to_sign_in].complains[i].description);
                    printf("Date : %s\n\n",accounts[index_to_sign_in].complains[i].date);
                }
            }
        }
    }
    printf("-------------------------------------------------------------------------------------------\n");
    printf("Resolved : \n\n");
    for (int i = 0; i < AccNum; i++)
    {
        if (accounts[i].NumOfCom == 0)
        {
            i ++;
        }
        for (int j = 0; j < accounts[i].NumOfCom; j++)
        {
            for (int k = 0; k < KeyWords_Num; k++)
            {
                if (strcmp(accounts[i].complains[j].status, "Resolved") == 0)
                {
                    printf("ID : %s\nComplaint : %s\n",accounts[index_to_sign_in].complains[i].ID, accounts[index_to_sign_in].complains[i].motif);
                    printf("Category : %s\n",accounts[index_to_sign_in].complains[i].categorie);
                    printf("Description : %s\n",accounts[index_to_sign_in].complains[i].description);
                    printf("Date : %s\n\n",accounts[index_to_sign_in].complains[i].date);
                }
            }
        }
    }
    printf("-------------------------------------------------------------------------------------------\n");
    printf("Rejected : \n\n");
    for (int i = 0; i < AccNum; i++)
    {
        if (accounts[i].NumOfCom == 0)
        {
            i ++;
        }
        for (int j = 0; j < accounts[i].NumOfCom; j++)
        {
            for (int k = 0; k < KeyWords_Num; k++)
            {
                if (strcmp(accounts[i].complains[j].status, "Rejected") == 0)
                {
                    printf("ID : %s\nComplaint : %s\n",accounts[index_to_sign_in].complains[i].ID, accounts[index_to_sign_in].complains[i].motif);
                    printf("Category : %s\n",accounts[index_to_sign_in].complains[i].categorie);
                    printf("Description : %s\n",accounts[index_to_sign_in].complains[i].description);
                    printf("Date : %s\n\n",accounts[index_to_sign_in].complains[i].date);
                }
            }
        }
    }
    printf("-------------------------------------------------------------------------------------------\n"); 
}

void Search(ACC *accounts)
{
    char choice;
    do
    {
        printf("Press 0 to get to the previous menu\n");
        printf("Press 1 to search by ID.\n");
        printf("Press 2 to search by name\n");
        printf("Press 3 to search by Date\n");
        printf("==> ");
        scanf(" %c",&choice);
        printf("------------------------------------\n");
        switch (choice)
        {
        case '0':
            break;
        
        case '1':
            Search_ID(accounts);
            break;

        case '2':
            Search_NAME(accounts);
            break;

        case '3':
            break;
        
        default:
            break;
        }
    } while (choice != '0');
    
}

void Search_ID(ACC *accounts)
{
    char IDtoSearch[MAX_ID_DIGITS];
    printf("Enter the ID : ");
    fgets(IDtoSearch, MAX_ID_DIGITS, stdin);
    IDtoSearch[strcspn(IDtoSearch, "\n")] = '\0';
    printf("----------------------------------------\n");
    for (int i = 0; i < AccNum; i++)
    {
        if (accounts[i].NumOfCom == 0)
        {
            i ++;
        }
        for (int j = 0; j < accounts[i].NumOfCom; j++)
        {
            if (strcmp(IDtoSearch, accounts[i].complains[j].ID) == 0)
            {
                found = 0;
                Acc_Index = i;
                Com_Index = j;
                break;
            }
        }
    }
    if (found == -1)
    {
        printf("Complain is not found\n");
        printf("----------------------------------------\n");
        return;
    }
    Status_change(accounts);
}

void Search_NAME(ACC *accounts)
{
    char NameToSearch[MAX_NAME_LENGTH];
    printf("Enter the name : ");
    fgets(NameToSearch, MAX_NAME_LENGTH, stdin);
    NameToSearch[strcspn(NameToSearch, "\n")] = '\0';
    printf("----------------------------------------\n");
    for (int i = 0; i < AccNum; i++)
    {
        if (strcmp(NameToSearch, accounts[i].FullName) == 0)
        {
            found = 0;
            Acc_Index = i;
            break;
        }
    }
    if (found == -1)
    {
        printf("Complain is not found\n");
        printf("----------------------------------------\n");
        return;
    }

    if (accounts[Acc_Index].NumOfCom == 0)
    {
        printf("This account have no complains yet.\n");
        printf("----------------------------------------\n");
    }
    for (int i = 0; i < accounts[Acc_Index].NumOfCom; i++)
    {
        printf("ID : %s\nComplaint : %s (%s)\n",accounts[Acc_Index].complains[i].ID, accounts[Acc_Index].complains[i].motif, accounts[Acc_Index].complains[i].status);
        printf("Category : %s\n",accounts[Acc_Index].complains[i].categorie);
        printf("Description : %s\n",accounts[Acc_Index].complains[i].description);
        printf("Date : %s\n",accounts[Acc_Index].complains[i].date);
        printf("---------------------------------------------------------------------------------\n");
    }
    Acc_Index = -1;
}

void Search_Date(ACC *accounts)
{
    
}

void Status_change(ACC *accounts)
{
    printf("Complain found!!\n");
    printf("ID : %s\nComplaint : %s (%s)\n",accounts[Acc_Index].complains[Com_Index].ID, accounts[Acc_Index].complains[Com_Index].motif, accounts[Acc_Index].complains[Com_Index].status);
    printf("Category : %s\n",accounts[Acc_Index].complains[Com_Index].categorie);
    printf("Description : %s\n",accounts[Acc_Index].complains[Com_Index].description);
    printf("Date : %s\n",accounts[Acc_Index].complains[Com_Index].date);
    printf("---------------------------------------------------------------------------------\n");
    if (strcmp(accounts[Acc_Index].complains[Com_Index].status, "Under process") != 0)
    {
        return;
    }
    printf("This complain still Under process\n");
    printf("Press 1 to change the status to 'Resolved'\n");
    printf("Press 2 to change the status to 'Rejected'\n");
    printf("Press 3 to keep it under process\n");
    
    char choice;
    printf("==> ");
    scanf(" %c",&choice);
    printf("---------------------------------------------------------------------------------\n");

    switch (choice)
    {
    case '1':
        strcpy(accounts[Acc_Index].complains[Com_Index].status, "Resolved");
        printf("Done!");
        printf("---------------------------------------------------------------------------------\n");
        break;

    case '2':
        strcpy(accounts[Acc_Index].complains[Com_Index].status, "Rejected");
        printf("Done!");
        printf("---------------------------------------------------------------------------------\n");
        break;
    case '3':
        printf("Done!");
        printf("---------------------------------------------------------------------------------\n");
        break;

    default:
        printf("Wrong choice, this complain will stay under the process at the moment.\n");
        printf("---------------------------------------------------------------------------------\n");
        break;
    }
    Acc_Index = -1;
    Com_Index = -1;
}
