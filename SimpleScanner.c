/*
write a scanner that recognizes a function gettoken() that 
recognizes the lexemes of the language and returns 
a token corresponding to that lexeme.

Use your own creativity to set the features and apply restrictions.
*/

#include <stdio.h>  
#include <string.h> 

#define Max_Word_Length 12 // Max length identifiers can be
const char* reserved_words[] = {"if", "while", "for", "int", "return", "void", "main", "Shania"};
#define Num_reserve_word 8

int line_number = 1;

void gettoken() {
    char c = getchar(); // Get character
    char word[Max_Word_Length + 1];
    int word_length = 0;
    
  
    while (c == ' ' || c == '\n') {
        if (c == '\n') { // Track new lines
            line_number++; // Increment line counter
        }
        c = getchar();  
    }
    
    if (c == EOF) {
        return;
    }
    
    // Check for numbers
    if (c >= '0' && c <= '9') { // Token number if numbers are found
        int digit_count = 1;
        printf("%c", c);  
        
        // Read rest of number
        while ((c = getchar()) >= '0' && c <= '9') {        // Place a restriction on the length
            digit_count++;
            printf("%c", c);
            
            // Check if number is too long
            if (digit_count > 6) {     // Number cant be longer than 6 digits
                printf(" ERROR: YOU CAN NOT HAVE A NUMBER THAT LARGE ON LINE: %d\n", line_number);
                
                while ((c = getchar()) >= '0' && c <= '9');
                break;
            }
        }
        printf(" toknumber\n");
    }
    
    // Check for words
    else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) { // Token word if letter
        word[word_length++] = c; // First character of word
        
        // Read rest of word
        while (((c = getchar()) >= 'a' && c <= 'z') ||
               (c >= 'A' && c <= 'Z') ||
               (c >= '0' && c <= '9')) {  
            
            word[word_length++] = c;  

            // Check if word is too long
            if (word_length >= Max_Word_Length) {
                printf("%s ERROR: THE IDENTIFIER IS TOO LONG ON LINE %d\n:", word, line_number);
                // Skip rest of word
                while (((c = getchar()) >= 'a' && c <= 'z') ||
                       (c >= 'A' && c <= 'Z') ||
                       (c >= '0' && c <= '9'));
                break;
            }
        }
        
 
        word[word_length] = '\0';
        
        // Check if it's a reserved word
        int is_reserved = 0;
        for (int i = 0; i < Num_reserve_word; i++) {  
            if (strcmp(word, reserved_words[i]) == 0) { 
                printf("%s tokenreserved\n", word);
                is_reserved = 1;
                break;
            }
        }
        
        // If not reserved, it's a regular word
        if (!is_reserved) {
            printf("%s tokenword\n", word);  
        }
    }
    
    // Check for invalid operator combinations
    else if (c == '!') {
        printf("%c", c);  
        c = getchar();
        if (c == '=') {  
            printf("%c tokop\n", c);
        } else {
            printf(" ERROR: INVALID OPERATOR COMBINATION ON LINE %d\n:", line_number);
        }
    }
    
    // Regular operators
    else {
        printf("%c tokop\n", c);
    }
}

int main() {
    char c;
    while ((c = getchar()) != EOF) {
        ungetc(c, stdin); // Put the character back
        gettoken(); // Process the token
    }
    return 0;
}