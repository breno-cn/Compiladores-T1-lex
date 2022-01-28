typedef enum {
    SingleLineCommment, MultiLineComment, Eof
} TokenType;

typedef struct Token {
    TokenType type;
    union {
        struct {
            char *value;
            int size;
        } singleLineToken;

        struct {
            char *value;
            int size;
        } multiLineToken;
    };
} Token;
