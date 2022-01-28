#include <stdio.h>
#include <stdlib.h>

#include "lexer.h"
#include "states.h"
#include "lexem.h"
#include "lexer_utils.h"

typedef struct {
    FILE *file;
    int line;
    int col;
    int bufferIndex;
    State currentState;
    char buffer[BUFFER_SIZE];
} Lexer;

Lexer *Lexer_new(FILE *file) {
    Lexer *lexer = malloc(sizeof(Lexer));

    if (lexer) {
        lexer->file = file;
        lexer->line = 0;
        lexer->col = 0;
        lexer->bufferIndex = 0;
        lexer->currentState = Initial;

        for (int i = 0; i < BUFFER_SIZE; i++) {
            lexer->buffer[i] = 0;
        }
    }

    return lexer;
}

void Lexer_delete(Lexer *lexer) {
    fclose(lexer->file);
    free(lexer);
}

char Lexer_readNextChar(Lexer *lexer) {
    size_t bytesRead;
    if (lexer->bufferIndex == 0 || lexer->bufferIndex == BUFFER_SIZE) {
        bytesRead = fread(lexer->buffer, sizeof(char), BUFFER_SIZE, lexer->file);
    }

    char currentChar = lexer->buffer[lexer->bufferIndex];
    lexer->bufferIndex++;

    if (currentChar == '\n') {
        lexer->line++;
        lexer->col = 0;
    } else {
        lexer->col++;
    }

    return currentChar;
}

Lexem *Lexer_getNextLexem(Lexer *lexer) {
    char currentLexem[MAX_LEXEM_SIZE];
    int currentLexemIndex = 0;

    while (lexer->currentState != Accept) {
        char currentChar = Lexer_readNextChar(lexer);
        currentLexem[currentLexemIndex] = currentChar;
        currentLexemIndex++;

        switch (lexer->currentState) {
            case Initial:
                if (currentChar == '/')
                    lexer->currentState = ReadFirstSlash;
                break;

            case ReadFirstSlash:
                if (currentChar == '/') 
                    lexer->currentState = DigestLineComment;
                else if (currentChar == '*')
                    lexer->currentState = DigestMultiLineComment;
                break;

            case DigestLineComment:
                if (isLineBreak(currentChar))
                    lexer->currentState = Accept;

                if (!isSingleLineDigest(currentChar))
                    /* TODO: Erro aqui */
                break;

            case DigestMultiLineComment:
                if (currentChar == '*')
                    lexer->currentState = ReadSecondStar;
                else if (!isMultiLineDigest(currentChar))
                    /* TODO: Outro erro aqui */
                break;
            
            case ReadSecondStar:
                if (currentChar == '/')
                    lexer->currentState = Accept;
                break;
        }
    }
}
