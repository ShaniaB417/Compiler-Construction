#include <stdio.h>  

void gettoken() {
    char c = getchar();
    
    // Skip spaces
    while (c == ' ' || c == '\n')
        c = getchar();

    // Process each type of token
    if (c >= '0' && c <= '9') {
        printf("toknumber\n");
        while ((c = getchar()) >= '0' && c <= '9'); // skip rest of number
    }
    else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
        printf("tokword\n");
        while (((c = getchar()) >= 'a' && c <= 'z') || 
               (c >= 'A' && c <= 'Z') || 
               (c >= '0' && c <= '9')); // skip rest of word
    }
    else if (c != EOF)
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