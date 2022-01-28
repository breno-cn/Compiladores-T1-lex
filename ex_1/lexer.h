#define BUFFER_SIZE 1024
#define MAX_LEXEM_SIZE 128

Lexer *Lexer_new(FILE *file);
void Lexer_delete(Lexer *lexer);
char Lexer_readNextChar(Lexer *lexer);