/*
write a scanner that recognizes a function gettoken() that 
recognizes the lexemes of the language and returns 
a token corresponding to that lexeme.
*/

#include <stdio.h>  

void gettoken() {
    char c = getchar();  // get character 
    
   
    while (c == ' ' || c == '\n')   // skip spaces 
        c = getchar();


    if (c >= '0' && c <= '9') {                     // token number if numbers are found 
        printf("toknumber\n");
        while ((c = getchar()) >= '0' && c <= '9'); 
    }
    else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {     // token word if not letter or number 
        printf("tokword\n");
        while (((c = getchar()) >= 'a' && c <= 'z') || 
               (c >= 'A' && c <= 'Z') || 
               (c >= '0' && c <= '9')); // skip rest of word
    }
    else if (c != EOF)         // not word or number tokop if operator is found 
        printf("tokop\n");
}

int main() {
    char c;
    while ((c = getchar()) != EOF) {
        ungetc(c, stdin);  // Put the character back
        gettoken();        // Process the token
    }
    return 0;
}