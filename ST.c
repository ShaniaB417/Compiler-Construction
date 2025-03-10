#include <stdio.h>  
#include <string.h> 

#define Max_Word_Length 12 // Max length identifiers can be
#define Max_Symbols 50 

const char* reserved_words[] = { "if", "while", "for", "int", "return", "void", "main", "Shania",
    "PROGRAM", "CONST", "BEGIN", "END", "VAR", "PROCEDURE", "FUNCTION"};

#define Num_reserve_word 15 // updated amount of reserved words 

int line_number = 1;

char symbol_table[Max_Symbols][Max_Word_Length + 1];  //symbol table to store names 
int symbol_count = 0; 

void add_symbol (char* name) {                      // add symbol to table 
    for(int i = 0; i < symbol_count; i++) {         // check if its already there 
        if(strcmp(symbol_table[i], name) == 0) {
            return; 
        }
    }

    if(symbol_count < Max_Symbols) {                    // add symbol if the table is not full 
        strcpy(symbol_table[symbol_count], name); 
        symbol_count++; 
        printf("Added to table: %s\n", name);
    } else {
        printf("Symbol table full\n");
    }
}  

int symbol_exists(char* name) {                // check if a symbol is already there 
    for(int i = 0; i < symbol_count; i++) {
        if (strcmp(symbol_table[i], name) == 0) {
            return 1;  // Found it!
        }
    }
    return 0; // Not there
}

void print_symbols() {                       // print symbols 
    printf("\n---- Symbol Table ------\n"); 
    for(int i = 0; i < symbol_count; i++) {
        printf("%d: %s\n", i, symbol_table[i]);
    }
    printf("------------------\n");
}
  
void gettoken() {                                         //old code from SimpleScanner.c
    char c = getchar(); // Get character
    char word[Max_Word_Length + 1];
    int word_length = 0;
    
    // Skip whitespace
    while (c == ' ' || c == '\n' || c == '\t') {
        if (c == '\n') { // Track new lines
            line_number++; // Increment line counter
        }
        c = getchar();
    }
    
    if (c == EOF) {
        return;
    }
    
                                   
    if (c >= '0' && c <= '9') {                  // Check for numbers - Fixed to handle multi-digit numbers
        int value = 0;
        int digit_count = 0;
        
        do {
                                                
            value = value * 10 + (c - '0');      // Update the value and count
            digit_count++;
            
                                           
            if (digit_count > 6) {              // Check if number is too long
                printf("ERROR: YOU CAN NOT HAVE A NUMBER THAT LARGE ON LINE: %d\n", line_number);
                                                               
                while ((c = getchar()) >= '0' && c <= '9');          // Skip the rest of the number
                break;
            }
          
            c = getchar();
        } while (c >= '0' && c <= '9');   // Get next character
  
        if (c != EOF) {
            ungetc(c, stdin);
        }
        
        printf("%d tokennumber\n", value);
    }
   
    else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {   // Check for words
        word[word_length++] = c; // First character of word
        
        while (((c = getchar()) >= 'a' && c <= 'z') ||              // Read rest of word
               (c >= 'A' && c <= 'Z') ||
               (c >= '0' && c <= '9')) {
            
            word[word_length++] = c;
            
            // Check if word is too long                        

            if (word_length >= Max_Word_Length) {                                          
                printf("ERROR: THE IDENTIFIER IS TOO LONG ON LINE %d\n", line_number);                   
              
                while (((c = getchar()) >= 'a' && c <= 'z') ||
                       (c >= 'A' && c <= 'Z') ||
                       (c >= '0' && c <= '9'));
                break;
            }
        }
        
        // Put back the non-word character
        if (c != EOF) {
            ungetc(c, stdin);
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
            
            // Add to symbol table if it's not already there
            add_symbol(word);
        }
    }
     
    else if (c == '.') {
        printf("%c", c);                         
        
        c = getchar();
        if (c == '.') {
            printf("%c", c);
            c = getchar();
            if (c == '.') {
                printf("%c tokellipsis\n", c);  // It's an ellipsis "..."
            } else {
                printf(" tokop\n");  // It's just ".."
                if (c != EOF) {
                    ungetc(c, stdin);
                }
            }
        } else {
            printf(" tokop\n");  // It's just a single "."
            if (c != EOF) {
                ungetc(c, stdin);
            }
        }
    }
    
    else if (c == '!') {
        printf("%c", c);
        c = getchar();
        if (c == '=') {
            printf("%c tokop\n", c);
        } else {
            printf(" ERROR: INVALID OPERATOR COMBINATION ON LINE %d\n", line_number);
            if (c != EOF) {
                ungetc(c, stdin);
            }
        }
    }
    else {
        printf("%c tokop\n", c);
    }
}

int main() {
    char c;
    while ((c = getchar()) != EOF) {
        ungetc(c, stdin);                // Put the character back
        gettoken();                     // Process the token
    }
    
    // added Print the symbol table at the end
    print_symbols();
    
    return 0;
}

    


