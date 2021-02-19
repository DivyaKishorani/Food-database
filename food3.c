#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//using namespace std;
//used macro
#define MAX_PRICE 999
#define MAX_SIZE_USER_NAME 30
#define MAX_SIZE_PASSWORD 20
#define FILE_NAME "HOTEL MENU.bin"
//macro related to the menu info
#define MAX_VARIETY_NAME 50
//#define MAX_PRICE 30
#define FILE_HEADER_SIZE sizeof(sFileHeader)
//structure to store price
typedef struct
{
    char price;
} Price;
typedef struct
{
    char username[MAX_SIZE_USER_NAME];
    char password[MAX_SIZE_PASSWORD];
} sFileHeader;
//elements of structure
typedef struct//to call in program
{
    unsigned int food_id;//declare the integer data type
    char varietyname[MAX_VARIETY_NAME];//declare character data type
    int price;//declare integer data type
} s_FoodInfo;
//align the message
void printMessageCenter(const char* message)
{
    int len=0;
    int pos=0;
    //calculate how many space need to print
    len = (78 - strlen(message))/2;
    printf("/t/t/t");
    for(pos=0;pos<len;pos++)
    {
        //print space
        printf(" ");
    }
    //print message
    printf("%s",message);
}
//head message
void headMessage(const char *message)
{
    printf("\t\t\t#################################################################################");
    printf("\n\t\t\t############                                         ##########################");
    printf("\n\t\t\t############   FOOD VARIETY OF PETPOOJA RESTAURANT   ##########################");
    printf("\n\t\t\t############                                         ##########################");
    printf("\n\t\t\t###############################################################################");
    printf("\n\t\t\t------------------------------------------------------------------------------\n");
    printMessageCenter(message);
    printf("\n\t\t\t--------------------------------------------------------------------------------");
}
//display message
void welcomeMessage()
{
    printf("\n\n\n\n\n");
    printf("\n\t\t\t**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\n\t\t\t   =========================================================================");
    printf("\n\t\t\t   =======                     WELCOME                               =======");
    printf("\n\t\t\t   =======                        TO                                 =======");
    printf("\n\t\t\t   =======                   PETPOOJA RESTAURANT                     =======");
    printf("\n\t\t\t   =========================================================================");
    printf("\n\t\t\t**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\n\n\n\t\t\t Enter any key to continue.......");
}
//valid name
int isNameValid(const char *name)
{
    int validname=1;
    int len=0;
    int index=0;
    len=strlen(name);
    for(index=0;index<len;++index)
    {
        if(!(isalpha(name[index])) && (name[index] !='\n') && (name[index] !='\n'))
        {
            validname=0;
            break;
        }
    }
    return validname;

}
//add variety in list
void addVarietyInDatabase()
{
    s_FoodInfo addVarietyInfoInDatabase = {0};
    FILE *fp = NULL;
    int status=0;
    fp = fopen(FILE_NAME,"ab+");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    headMessage("ADD NEW VARIETY");
    printf("\n\n\t\t\tENTER DETAILS BELOW:");
    printf("\n\t\t\t------------------------------------------------------------------\n");
    printf("\n\t\t\tFood ID =");
    fflush(stdin);
    scanf("%u",&addVarietyInfoInDatabase.food_id);
    do
    {
        printf("\n\t\t\tVARIETY Name =");
        fflush(stdin);
        fgets(addVarietyInfoInDatabase.varietyname,MAX_VARIETY_NAME,stdin);
        status= isNameValid(addVarietyInfoInDatabase.varietyname);
        if(!status)
        {
            printf("\n\t\t\tName contain invalid character.Please enter again.");
        }
        }
     while(!status);
     do
     {
         printf("\n\t\t\tVariety Price =");
         fflush(stdin);
         scanf("%d",&addVarietyInfoInDatabase.price);
         //status= isNameValid(addVarietyInfoInDatabase.price);
         if(!status)
         {
            printf("\n\t\t\tPrice contain invalid value.Please enter again.");
         }
         }
      while(!status);
      fwrite(&addVarietyInfoInDatabase,sizeof(addVarietyInfoInDatabase), 1, fp);
      fclose(fp);
}
//search variety
void searchvariety()
{
    int found=0;
    int varietyid=0;
    s_FoodInfo addVarietyInfoInDatabase ={0};
    FILE *fp = NULL;
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("\n\t\t\tFile is not opened.\n");
        exit(1);
    }
    headMessage("SEARCH VARIETY");
    //put the control on variety detail
    if(fseek(fp,FILE_HEADER_SIZE,SEEK_SET) !=0 )
    {
        fclose(fp);
        printf("\n\t\t\tFacing issues while reading file\n");
        exit(1);
    }
    printf("\n\n\t\t\tEnter Variety ID to search:");
    fflush(stdin);
    scanf("%u",&varietyid);
    while(fread (&addVarietyInfoInDatabase, sizeof(addVarietyInfoInDatabase), 1, fp))
    {
        if(addVarietyInfoInDatabase.food_id == varietyid)
        {
            found = 1;
            break;
        }
    }
    if(found)
    {
        printf("\n\t\t\tFood ID =%d\n",addVarietyInfoInDatabase.food_id);
        printf("\n\t\t\tVariety Name =%s",addVarietyInfoInDatabase.varietyname);
        printf("\n\t\t\tPrice =%d",addVarietyInfoInDatabase.price);
    }
    else
    {
        printf("\n\t\t\tNo Record");
    }
    fclose(fp);
    printf("\n\n\n\t\t\tPress any key to go to main menu....");
    fflush(stdin);
    getchar();
}
//view variety
void viewVariety()
{
    int found=0;
    s_FoodInfo addVarietyInfoInDatabase = {0};
    FILE *fp = NULL;
    unsigned int countvariety = 1;
    headMessage("VIEW VARIETY DETAILS");
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    if(fseek(fp,FILE_HEADER_SIZE,SEEK_SET) !=0)
    {
        fclose(fp);
        printf("Facing issue while reading file.\n");
        exit(1);
    }
    while(fread(&addVarietyInfoInDatabase, sizeof(addVarietyInfoInDatabase),1, fp))
    {
        printf("\n\t\t\tVariety Count =%d\n\n",countvariety);
        printf("\t\t\tFood ID =%u\n",addVarietyInfoInDatabase.food_id);
        printf("\t\t\tVariety Name =%s",addVarietyInfoInDatabase.varietyname);
        printf("\t\t\tPrice =%d",addVarietyInfoInDatabase.price);
        found =1;
        ++countvariety;
    }
    fclose(fp);
    if(!found)
    {
        printf("\n\t\t\tNo Record.");
    }
    printf("\n\n\t\t\tPress any key to go to main menu...");
    fflush(stdin);
    getchar();
}
//delete food entry
void deleteVariety()
{
    int found=0;
    int varietydelete=0;
    sFileHeader fileHeaderInfo ={0};
    s_FoodInfo addVarietyInfoInDatabase ={0};
    FILE *fp = NULL;
    FILE *tmpFp = NULL;
    headMessage("DELETE FOOD DETAILS");
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    tmpFp = fopen("tmp.bin","wb");
    if(tmpFp == NULL)
    {
        fclose(fp);
        printf("File is not opened.\n");
        exit(1);
    }
    fread(&fileHeaderInfo,FILE_HEADER_SIZE,1,fp);
    fwrite(&fileHeaderInfo,FILE_HEADER_SIZE,1,tmpFp);
    printf("\n\t\t\tEnter Food ID. for delete:");
    scanf("%d",&varietydelete);
    while(fread(&addVarietyInfoInDatabase, sizeof(addVarietyInfoInDatabase),1, fp))
    {
        if(addVarietyInfoInDatabase.food_id != varietydelete)
        {
            fwrite(&addVarietyInfoInDatabase, sizeof(addVarietyInfoInDatabase),1, tmpFp);
        }
        else
        {
            found=1;
        }
    }
    (found)?printf("\n\t\t\tRecord deleted successfully...."):printf("\n\t\t\tRecord not found");
    fclose(fp);
    fclose(tmpFp);
    remove(FILE_NAME);
    rename("tmp.bin",FILE_NAME);
}
//function to update credential
void updatecredential()
{
    sFileHeader fileHeaderInfo ={0};
    FILE *fp = NULL;
    unsigned char username[MAX_SIZE_USER_NAME] = {0};
    unsigned char password[MAX_SIZE_PASSWORD] = {0};
    headMessage("UPDATE Credential");
    fp =fopen(FILE_NAME,"rb+");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    fread(&fileHeaderInfo,FILE_HEADER_SIZE,1, fp);
    if(fseek(fp,0,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\t\t\tFacing issue while updating password\n");
        exit(1);
    }
    printf("\n\n\t\t\tNew User name :");
    fflush(stdin);
    fgets(username,MAX_SIZE_USER_NAME,stdin);
    printf("\n\n\t\t\tNew Password :");
    fflush(stdin);
    fgets(password,MAX_SIZE_PASSWORD,stdin);
    strncpy(fileHeaderInfo.username,username,sizeof(username));
    strncpy(fileHeaderInfo.password,password,sizeof(password));
    fwrite(&fileHeaderInfo,FILE_HEADER_SIZE,1, fp);
    fclose(fp);
    printf("\n\t\t\tYour Password has been changed successfully");
    printf("\n\t\t\tLogin Again:");
    fflush(stdin);
    getchar();
    exit(1);
}
//display menu
void menu()
{
    int choice=0;
    do
    {
        headMessage("MAIN MENU");
        printf("\n\n\n\t\t\t 1.Add variety");
        printf("\n\t\t\t 2.Search variety");
        printf("\n\t\t\t 3.View variety");
        printf("\n\t\t\t 4.Delete variety");
        printf("\n\t\t\t 5.Update password");
        printf("\n\t\t\t 0.Exit");
        printf("\n\n\n\t\t\tEnter your choice=>");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            addVarietyInDatabase();
            break;
        case 2:
            searchvariety();
            break;
        case 3:
            viewVariety();
            break;
        case 4:
            deleteVariety();
            break;
        case 5:
            updatecredential();
            break;
        case 0:
            printf("\n\n\n\t\t\t\tThank You!!!!\n\n\n");
            exit(1);
            break;
        default :
            printf("\n\n\n\t\t\tINVALID INPUT!!! Try again....");
        }
    }
    while(choice!=0);
}
//login password
void login()
{
    unsigned char username[MAX_SIZE_USER_NAME] = {0};
    unsigned char password[MAX_SIZE_PASSWORD] = {0};
    int L=0;
    sFileHeader fileHeaderInfo = {0};
    FILE *fp = NULL;
    headMessage("LOGIN");
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    fread(&fileHeaderInfo,FILE_HEADER_SIZE,1, fp);
    fclose(fp);
    do
    {
        printf("\n\n\n\t\t\tUser name:");
        fgets(username,MAX_SIZE_USER_NAME,stdin);
        printf("n\t\t\tPassword:");
        fgets(password,MAX_SIZE_PASSWORD,stdin);
        if((!strcmp(username,fileHeaderInfo.username)) && (!strcmp(password,fileHeaderInfo.password)))
        {
            menu();
        }
        else
        {
            printf("\t\t\t\tLogin failed enter again user name & password\n\n");
            L++;
        }
    }
    while(L<=3);
    if(L>3)
    {
        headMessage("Login failed");
        printf("\t\t\tSorry unknown, user.");
        getchar();
        system("cls");
    }
}
//check file exist or not
int isfileexists(const char *path)
{
    //try to open file
    FILE *fp = fopen(path, "rb");
    int status =0;
    //if file does not exist
    if(fp != NULL)
    {
        status=1;
        //file exists hence close file
        fclose(fp);
    }
    return status;
}
void initt()
{
    FILE *fp=NULL;
    int status =0;
    const char defaultusername[] ="dk\n";
    const char defaultpassword[] ="dk\n";
    sFileHeader fileHeaderInfo ={0};
    status = isfileexists(FILE_NAME);
    if(!status)
    {
        //create binary file
        fp = fopen(FILE_NAME,"wb");
        if(fp!=NULL)
        {
            //copy default password
            strncpy(fileHeaderInfo.password,defaultpassword,sizeof(defaultpassword));
            strncpy(fileHeaderInfo.username,defaultusername,sizeof(defaultusername));
            fwrite(&fileHeaderInfo,FILE_HEADER_SIZE,1, fp);
            fclose(fp);
        }
    }
}
int main()
{
    initt();
    welcomeMessage();
    login();
    return 0;
}






