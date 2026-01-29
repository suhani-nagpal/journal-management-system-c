#include<stdio.h>
#include<string.h>

void addEntry(){
    FILE *fptr;
    char date[20],title[70],content [500];
    fptr = fopen("journal.txt","a");
    if (fptr == NULL){
        printf("Error opening file...\n");
    }

    printf("Enter the date (DD-MM-YYYY): ");
    scanf(" %[^\n]",date);

    printf("\nEnter the title: ");
    scanf(" %[^\n]",title);
    
    printf("\nEnter the content: ");
    scanf(" %[^\n]",content);
    
    fprintf(fptr,"\n%s | %s | %s \n",date,title,content);
    fclose(fptr);
    printf("\nEntry saved successfully\n\n");
}

void viewEntry(){
    FILE *fptr;
    fptr = fopen("journal.txt","r");
    if (fptr == NULL){
        printf("Entry not found...\n");
        return;
    }
    printf("\n\tReading your journal file...\n");
    int ch=fgetc(fptr);
    while( ch != EOF){
        printf("%c",ch);
        ch = fgetc(fptr);
    }
    fclose(fptr);
}
void searchEntry(){
    FILE *fptr;
    int found =0;

    fptr = fopen("journal.txt","r");
    if (fptr == NULL){
        printf("Error opening file...\n");
        return;
    }

    char search[1000];
    printf("Enter date or word to search: ");
    scanf(" %[^\n]",search);

    char line[1000];
    printf("\n\tSearch results\n");
    while(fgets(line,sizeof(line),fptr) != NULL){
        if (strstr(line,search) != NULL){
            printf("%s",line);
            found = 1;
        }
    }
        if (found == 0){
            printf("\n\tNo entry found...\n");
        
    }

    fclose(fptr);
}
void deleteEntry(){
    FILE *fptr,*temp;
    int found =0;

    fptr = fopen("journal.txt","r");
    temp = fopen("temporary.txt","w");

    if (fptr == NULL || temp == NULL){
        printf("\n\tEntry not found...\n");
        return;
    }

    char search[1000];
    printf("Enter date or word to delete entry: ");
    scanf(" %[^\n]",search);

    char line[1000];
    while(fgets(line,sizeof(line),fptr) != NULL){
        if (strstr(line,search) != NULL){
            found = 1;
        }
        else{
            fputs(line,temp);
        }
    }
    
    fclose(fptr);
    fclose(temp);

    remove("journal.txt");
    rename("temporary.txt","journal.txt");

    if(found == 1){
        printf("\n\tEntry deleted sucessfull...\n");
    }
    else{
        printf("\n\tNo such entry is found...\n");
    }
}
int main(){
    int choice;
    do{
         printf("\nEnter the number according to the following:\n 1. Add Entry\n 2. View Entry\n 3. Search Entry\n 4. Delete Entry\n 5. Exit\nYou want: ");
    scanf("%d",&choice);
        switch(choice){
            case 1: addEntry();break;
            case 2: viewEntry();break;
            case 3: searchEntry();break;
            case 4: deleteEntry();break;
            case 5: printf("Exiting...\n");break;
            default: printf("Invalid choice \n");break;
        }
    }
    while (choice!=5);
    return 0;
}