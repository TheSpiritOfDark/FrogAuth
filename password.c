#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxLines 10
#define MaxLineLength 32
int main(){
    char Lines[] = initfile();
    UserDoPassStuff(GetNewPass(Lines));

    return 0;
}

char initfile(){
    FILE *file = fopen("passlist.txt", "r");
    if (file == NULL){
        return 1;
    }
    char Lines[MaxLines];
    int LineCount = 0;

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

char GetNewPass(char Lines[]){
    srand( (unsigned) time(NULL) * getpid());
    int RandomNumber = rand() % 10;
    char Pass[] = Lines[RandomNumber];
    return Pass;
}

int UserDoPassStuff(char CorPass[]){
    char inp[33];
    int passlim;

    prinf("Your hint is %s. Enter password:", CorPass[0]);

    while(0){
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
    }
}