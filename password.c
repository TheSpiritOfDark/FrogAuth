#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>

#define MaxLines 36
#define MaxLineLength 64
int LL = 0;
int passlim = 0;

void TrimPass(char *Lines){
    //this removes spaces and tabs and whatnot that come after the actual text of the password

    int Length = strlen(Lines);
    while(Length > 0 && isspace((unsigned char)Lines[Length - 1])){
        Lines[--Length] = '\0';
    }
}

char** initfile(){
    //assign variables needed
    FILE *File = fopen("passlist.txt", "r");
    if (File == NULL){
        return NULL;
    }

    char **Lines = malloc(MaxLines * sizeof(char*));
    if(Lines == NULL){
        fclose(File);
        return NULL;
    }

    int LineCount = 0;

    //assing passwords to the Lines array

    while(LineCount < MaxLines && !feof(File)){
        char buffer[MaxLineLength];
        if(fgets(buffer, MaxLineLength, File) != NULL){
            buffer[strcspn(buffer, "\n")] = '\0';
            Lines[LineCount] = malloc(strlen(buffer) + 1);
            if(buffer != NULL){
                TrimPass(buffer);
                strcpy(Lines[LineCount], buffer);
                LL = LL + 1;
            }
            LineCount++;
        }
    }
    
    fclose(File);

    return Lines;
}

char *GetNewPass(char **Lines){
    char *Pass = NULL;
    while(Pass == NULL){
        srand( (unsigned) time(NULL) * getpid());
        int RandomNumber = rand() % LL;
        Pass = Lines[RandomNumber];
        if(Pass != NULL){
            return Pass;
        }
    }
}
int Attempts = 0;
void Passfail(){
    int FailTime[] = {60, 120, 240, 580, 1160, 9999, 15000, 150000}; //numbors
    if(Attempts > 7){ Attempts = 7; }

    printf("Please wait %d seconds to try again. \n", FailTime[Attempts]);
    sleep(FailTime[Attempts]);
}

char **rmpass(char **Lines, char *UsedPass){
    for(int i = 0; i< MaxLines; i++){
        if(Lines[i] !=NULL && strcmp(Lines[i], UsedPass)){
            free(Lines[i]);
            Lines[i] = NULL;
            return Lines;
            break;
        }
    }
}

int UserDoPassStuff(char CorPass[], char **Lines, int first){
    char inp[33];

    if(passlim >= 3){
        Passfail();
        Attempts = Attempts + 1;
        passlim = 0;
    }

    printf("Your hint is %c. Enter password:", CorPass[0]);

    while(1){
        if(fgets(inp, sizeof(inp), stdin) != NULL){
            inp[strcspn(inp, "\n")] = '\0';

            if (strcmp(inp, CorPass) == 0){
                printf("Pass Correct!\n");
                exit(0);
            } else {
                printf("Pass Incorrect!\n");
                passlim = passlim + 1;
                Lines = rmpass(Lines, CorPass);
                if(first == 1){
                    int result = 1;
                    while(result == 1){
                        result = UserDoPassStuff(GetNewPass(Lines), Lines, 0);
                    }
                } else{
                    return 1;
                }
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

    UserDoPassStuff(GetNewPass(Lines), Lines, 1);

    return 0;
}