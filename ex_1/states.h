typedef enum {
    Initial, ReadFirstSlash, ReadSecondSlash, DigestLineComment, ReadStar, 
    DigestMultiLineComment, ReadSecondStar, ReadSecondSlash, ReadLineBreak, 
    Accept
} State;
