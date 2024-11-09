#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MaxLines 10
#define MaxLineLength 32

char** initfile(){
    //assign variables needed
    FILE *file = fopen("passlist.txt", "r");
    if (file == NULL){
        return NULL;
    }

    char **Lines = malloc(MaxLines * sizeof(char*));
    if(Lines == NULL){
        fclose(file);
        return NULL;
    }

    int LineCount = 0;

    //assing passwords to the Lines array

    while(LineCount < MaxLines && !feof(file)){
        char buffer[MaxLineLength];
        if(fgets(buffer, MaxLineLength, file) != NULL){
            Lines[LineCount] = malloc(strlen(buffer) + 1);
            strcpy(Lines[LineCount], buffer);
            LineCount++;
        }
    }
    
    fclose(file);

    return Lines;
}

char *GetNewPass(char **Lines){
    srand( (unsigned) time(NULL) * getpid());
    int RandomNumber = rand() % 10;
    char *Pass = Lines[RandomNumber];
    return Pass;
}

int UserDoPassStuff(char CorPass[]){
    char inp[33];
    int passlim = 0;

    printf("Your hint is %d. Enter password:", CorPass[0]);

    while(1){
        if(passlim >= 3){
            return 1;
        }
        if(fgets(inp, sizeof(inp), stdin) != NULL){
            inp[strcspn(inp, "\n")] = '\0';

            if (strcmp(inp, CorPass) == 0){
                printf("Pass Correct!");
                return 0;
            } else {
                printf("Pass Incorrect!");
                passlim = passlim + 1;
            }
        }
        else { return 1; }
    }
}

int main(){
    //get the password candidates from passlist.txt
    char **Lines = initfile();
    if(Lines == NULL){
        printf("failed to read and/or allocate passwords");
        return 1;
    }

    UserDoPassStuff(GetNewPass(Lines));

    return 0;
}