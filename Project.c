#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#define MAX_NAME_LENGTH 30
#define MAX_PHONE_NUMBER_LENGTH 30
#define MAX_EMAIL_LENGTH 256
#define MAX_PASSWORD_LENGTH 30
#define PHONE_NUMBER_LENGTH 10

typedef struct
{
    char FullName[MAX_NAME_LENGTH];
    char UserName[MAX_NAME_LENGTH];
    char PhoneNumber[MAX_PHONE_NUMBER_LENGTH];
    char Email[MAX_EMAIL_LENGTH];
    char PassWord[MAX_PASSWORD_LENGTH];
    char AccType[MAX_NAME_LENGTH];
} ACC;

int AccNum = 1;
int num = 2;
int index_to_sign_in = -1;
int found = -1;

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
    printf("==>Contact name is accepted !!\n");
    printf("----------------------------------------------------------------\n");
    return 0;
}

int username_validator(int AccNum, ACC *accounts)
{
    if (strlen(accounts[AccNum].UserName) == 0)
    {
        printf("==>UserName is not valid .\n(Empty!!)\n");
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

    printf("==>The email accepted !!\n");
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
            printf("No such account include with this email.\nYou may want to sign up with this adress first\n");
            printf("---------------------------------------------------\n");
            return;
        }
        found = -1;
        Pass_Word_Sign_in(accounts);
        break;

    case '2':
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
            printf("No such account include with this number.\nYou may want to sign up with this number first\n");
            printf("---------------------------------------------------\n");
            return;
        }
        found = -1;
        Pass_Word_Sign_in(accounts);
        break;

    case '3':
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
            printf("No such account include with this user name.\nYou may want to sign up with this user name first\n");
            printf("---------------------------------------------------\n");
            return;
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

void admin_panel(ACC *accounts)
{
    printf("Welcom %s (%s)\n",accounts[index_to_sign_in].FullName,accounts[index_to_sign_in].AccType);
    index_to_sign_in = -1;
    char choice;
    do
    {
        printf("Press 0 to sign out\n");
        printf("Press 1 to see all the complains\n");
        printf("Press 2 to see all the users\n");
        printf("Press 3 to generate the statistics\n");
        printf("Press 4 to manage the assignment roles\n");
        printf("==> ");
        scanf(" %c",&choice);
        getchar();
        printf("---------------------------------\n");

        switch (choice)
        {
        case 0:
            break;
        
        default:
            printf("Invalid choice, please select a valid option.\n");
            printf("----------------------------------------\n");
            break;
        }
    } while (choice != '0');
    return;
}

void client_panel(ACC *accounts)
{
    printf("Welcom %s (%s)\n",accounts[index_to_sign_in].FullName,accounts[index_to_sign_in].AccType);
    index_to_sign_in = -1;
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
        case 0:
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
            break;
        
        default:
            printf("Invalid choice, please select a valid option.\n");
            printf("----------------------------------------\n");
            break;
        }
    } while (choice != '0');
    return;
}