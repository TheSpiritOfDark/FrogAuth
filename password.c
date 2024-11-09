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
            buffer[strcspn(buffer, "\n")] = '\0';
            Lines[LineCount] = malloc(strlen(buffer) + 1);
            strcpy(Lines[LineCount], buffer);
            LineCount++;
        }
    }
    
    fclose(file);

    return Lines;
}

char *GetNewPass(char **Lines){
    printf("2");
    srand( (unsigned) time(NULL) * getpid());
    int RandomNumber = rand() % MaxLines;
    char *Pass = Lines[RandomNumber];
    if(Pass != NULL){
        return Pass;
    }
    printf("BAD");
    return Lines[5]; //fix me
}

void rmpass(char **Lines, char *UsedPass){

}

int UserDoPassStuff(char CorPass[], char **Lines, int passlim){
    char inp[33];

    if(passlim >= 3){
        exit(1); //replace with lockout of somekind so we dont lock users other than the one that guessed incorectly out
    }

    printf("Your hint is %c. Enter password:", CorPass[0]);

    while(1){
        if(fgets(inp, sizeof(inp), stdin) != NULL){
            inp[strcspn(inp, "\n")] = '\0';

            if (strcmp(inp, CorPass) == 0){
                printf("Pass Correct!\n");
                return 0;
            } else {
                printf("Pass Incorrect!\n");
                printf("%s\n", CorPass); //debug
                passlim = passlim + 1;

                UserDoPassStuff(GetNewPass(Lines), Lines, passlim);
            }
        }
        else { exit(1); }
    }
}

int main(){
    //get the password candidates from passlist.txt
    char **Lines = initfile();
    if(Lines == NULL){
        printf("failed to read and/or allocate passwords");
        return 1;
    }
    printf("1");

    UserDoPassStuff(GetNewPass(Lines), Lines, 0);

    return 0;
}

