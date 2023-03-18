/* Scanner
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <conio.h>
#include "reader.c"
#include "charcode.c"
#include "token.c"
#include "error.c"


extern int lineNo;
extern int colNo;
extern int currentChar;

extern CharCode charCodes[];

/***************************************************************/

void skipBlank() {
  // TODO
  while((currentChar != EOF) && (charCodes[currentChar] == CHAR_SPACE))
    readChar();
}

void skipComment() {
  // TODO

  while(charCodes[currentChar] != CHAR_TIMES){
    readChar();
    if(currentChar == EOF){
      error(ERR_ENDOFCOMMENT, lineNo, colNo);
      return;
    }


    
  }
  readChar();
  if(currentChar == EOF){
      error(ERR_ENDOFCOMMENT, lineNo, colNo);
  }
  if(charCodes[currentChar] != CHAR_RPAR)
    skipComment();
  readChar();
}

void skipSingleLineComment() {
  while(currentChar != '\n' && currentChar != EOF){
    readChar();
  }
}

Token* readIdentKeyword(void) {
  // TODO
  Token* token = makeToken(TK_IDENT, lineNo, colNo);
  char string[MAX_IDENT_LEN];
  int i = 0;
  // printf("\n%c\n\n", currentChar);
  while(charCodes[currentChar] == CHAR_LETTER || charCodes[currentChar] == CHAR_DIGIT || charCodes[currentChar] == CHAR_UNDERSCORE || charCodes[currentChar] == CHAR_DOLA){

    string[i] = currentChar;
    readChar();
    i ++;
  }
  if(i > MAX_IDENT_LEN){
    error(ERR_IDENTTOOLONG, token->lineNo, token->colNo);
    token->tokenType = TK_NONE;
    return token;
  }
  
  string[i] = '\0';
  TokenType type = checkKeyword(string);
  // printf("\n%s\n\n", string);

  if(type != TK_NONE){
    token->tokenType = type;
  }
  else{
    strcpy(token->string, string);
  }
  return token;
}

Token* readNumber(void) {
  Token *tok = makeToken(TK_NUMBER, lineNo, colNo);
  char num[MAX_IDENT_LEN] = "\0";
  int i = 0;
  int isTooLong = 0;
  // printf("\n%d\n\n", thisColNo);
  while(charCodes[currentChar] == CHAR_DIGIT){
    if(i < MAX_IDENT_LEN){
      num[i] = (char)currentChar;
    }else{
      isTooLong = 1;
    }
    // printf("\n%c\n\n", num[i]);
    readChar();
    i ++;
    // printf("\n%d\n\n", thisColNo);
  }
  num[i] = '\0';
  if(isTooLong == 1){
    // error(ERR_NUMBERTOOLONG, tok->lineNo, tok->colNo);
    tok->tokenType = TK_NONE;
    return tok;
  }

  long numInt = atol(num);
  if(numInt < LONG_MAX){
    strcpy(tok->string, num);
    return tok;
  }
  else{
    // error(ERR_NUMBERTOOLONG, tok->lineNo, tok->colNo);
    tok->tokenType = TK_NONE;
    return tok;
  }
  // char maxInt[15];
  // sprintf(maxInt, "%d", __INT_MAX__);
  // if(strcmp(num, maxInt) <= 0){
  //   Token *tok = makeToken(TK_NUMBER, lineNo, colNo);
  //   // printf("\n%d\n", atoi(num));
  //   strcpy(tok->string, num);
  //   return tok;
  // }
  // else{
  //   error(ERR_IDENTTOOLONG, lineNo, colNo);
  //   return makeToken(TK_NONE, lineNo, colNo);
  // }
  
  // TODO
}

Token* readConstChar(void) {
  char string[MAX_IDENT_LEN];
  int i = 0;
  int isLong = 0;
  Token *newToken = makeToken(TK_CHAR, lineNo, colNo);
  // printf("\n %d-%d\n\n", newToken->lineNo, newToken->colNo);
  while (currentChar >= 32 && currentChar <= 126 && charCodes[currentChar] != CHAR_SINGLEQUOTE)
  {
    // printf("\n-%d-\n\n", currentChar);
    if(i < MAX_IDENT_LEN)
      string[i] = currentChar;
    else
      isLong = 1;
    readChar();
    i ++;
  }
  // *(string + i) = '\0';
  // printf("\n-%c-\n\n", currentChar);
  string[i] = '\0';
  if(charCodes[currentChar] != CHAR_SINGLEQUOTE){
    error(ERR_INVALIDCHARCONSTANT, newToken->lineNo, newToken->colNo);
    newToken->tokenType = TK_NONE;
    return newToken;
  }
  if(isLong == 1){
    error(ERR_CONSTANTTOOLONG, newToken->lineNo, newToken->colNo);
    newToken->tokenType = TK_NONE;
    return newToken;
  }
  if(charCodes[currentChar] == CHAR_SINGLEQUOTE){
    strcpy(newToken->string, string);
    readChar();
    return newToken;
  }

}

Token* getToken(void) {
  Token *token;
  int ln, cn;

  if (currentChar == EOF) 
    return makeToken(TK_EOF, lineNo, colNo);

  switch (charCodes[currentChar]) {
  case CHAR_SPACE: skipBlank(); return getToken();
  case CHAR_LETTER: return readIdentKeyword();
  case CHAR_UNDERSCORE: return readIdentKeyword();
  case CHAR_DIGIT: return readNumber();
  case CHAR_PLUS: 
    token = makeToken(SB_PLUS, lineNo, colNo);
    readChar(); 
    return token;
  case CHAR_MINUS:
    token = makeToken(SB_MINUS, lineNo, colNo);
    readChar(); 
    return token;
  case CHAR_TIMES:
    token = makeToken(SB_TIMES, lineNo, colNo);
    readChar(); 
    return token;
  case CHAR_GT:
    token = makeToken(SB_GT, lineNo, colNo);
    readChar(); 
    return token;
  case CHAR_EXCLAIMATION:
    token = makeToken(TK_NONE, lineNo, colNo);
    readChar();
    // if(charCodes[currentChar] == CHAR_EQ){
    //   token = makeToken(SB_NEQ, lineNo, colNo);
    //   readChar();
    // }
    // if(token->tokenType == TK_NONE)
    //   error(ERR_INVALIDSYMBOL, lineNo, colNo);
    return token;
  case CHAR_LT:
    token = makeToken(SB_LT, lineNo, colNo);
    readChar();
    if(charCodes[currentChar] == CHAR_GT){
      token->tokenType = SB_NEQ;
      readChar();
    }
    return token;

  case CHAR_EQ:
    token = makeToken(SB_EQ, lineNo, colNo);
    readChar(); 
    return token;
  case CHAR_COMMA:
    token = makeToken(SB_COMMA, lineNo, colNo);
    readChar(); 
    return token;
  case CHAR_PERIOD:
    token = makeToken(SB_PERIOD, lineNo, colNo);
    readChar(); 
    return token;
  case CHAR_COLON:
    token = makeToken(SB_COLON, lineNo, colNo);
    readChar(); 
    if(charCodes[currentChar] == CHAR_EQ){
      token = makeToken(SB_ASSIGN, lineNo, colNo);
      readChar();
    }
    
    return token;
  case CHAR_SEMICOLON:
    token = makeToken(SB_SEMICOLON, lineNo, colNo);
    readChar(); 
    return token;
  // case CHAR_SINGLEQUOTE:
  //   token = makeToken(TK_NONE, lineNo, colNo);
  //   readChar(); 
  //   return token;
  case CHAR_SINGLEQUOTE:
    readChar();
    return readConstChar();
  case CHAR_LPAR:
    // printf("\n--%c--\n\n", '(');
    token = makeToken(SB_LPAR, lineNo, colNo);
    readChar(); 
    if(charCodes[currentChar] == CHAR_TIMES){
      skipComment();
      return getToken();
    }
    return token;
  case CHAR_SLASH:
    token = makeToken(SB_SLASH, lineNo, colNo);
    readChar(); 
    if(charCodes[currentChar] == CHAR_SLASH){
      skipSingleLineComment();
      return getToken();
    }
    return token;
  case CHAR_RPAR:
    token = makeToken(SB_RPAR, lineNo, colNo);
    readChar();
    return token;
    // TODO
    // ....
  default:
    token = makeToken(TK_NONE, lineNo, colNo);
    error(ERR_INVALIDSYMBOL, lineNo, colNo);
    readChar(); 
    return token;
  }
}


/******************************************************************/

void printToken(Token *token) {

  printf("%d-%d:", token->lineNo, token->colNo);

  switch (token->tokenType) {
  case TK_NONE: printf("TK_NONE\n"); break;
  case TK_IDENT: printf("TK_IDENT(%s)\n", token->string); break;
  case TK_NUMBER: printf("TK_NUMBER(%s)\n", token->string); break;
  case TK_CHAR: printf("TK_CHAR(\"%s\")\n", token->string); break;
  case TK_EOF: printf("TK_EOF\n"); break;

  case KW_PROGRAM: printf("KW_PROGRAM\n"); break;
  case KW_CONST: printf("KW_CONST\n"); break;
  case KW_TYPE: printf("KW_TYPE\n"); break;
  case KW_VAR: printf("KW_VAR\n"); break;
  case KW_INTEGER: printf("KW_INTEGER\n"); break;
  case KW_CHAR: printf("KW_CHAR\n"); break;
  case KW_ARRAY: printf("KW_ARRAY\n"); break;
  case KW_OF: printf("KW_OF\n"); break;
  case KW_FUNCTION: printf("KW_FUNCTION\n"); break;
  case KW_PROCEDURE: printf("KW_PROCEDURE\n"); break;
  case KW_BEGIN: printf("KW_BEGIN\n"); break;
  case KW_END: printf("KW_END\n"); break;
  case KW_CALL: printf("KW_CALL\n"); break;
  case KW_IF: printf("KW_IF\n"); break;
  case KW_THEN: printf("KW_THEN\n"); break;
  case KW_ELSE: printf("KW_ELSE\n"); break;
  case KW_WHILE: printf("KW_WHILE\n"); break;
  case KW_DO: printf("KW_DO\n"); break;
  case KW_FOR: printf("KW_FOR\n"); break;
  case KW_TO: printf("KW_TO\n"); break;

  case SB_SEMICOLON: printf("SB_SEMICOLON\n"); break;
  case SB_COLON: printf("SB_COLON\n"); break;
  case SB_PERIOD: printf("SB_PERIOD\n"); break;
  case SB_COMMA: printf("SB_COMMA\n"); break;
  case SB_ASSIGN: printf("SB_ASSIGN\n"); break;
  case SB_EQ: printf("SB_EQ\n"); break;
  case SB_NEQ: printf("SB_NEQ\n"); break;
  case SB_LT: printf("SB_LT\n"); break;
  case SB_LE: printf("SB_LE\n"); break;
  case SB_GT: printf("SB_GT\n"); break;
  case SB_GE: printf("SB_GE\n"); break;
  case SB_PLUS: printf("SB_PLUS\n"); break;
  case SB_MINUS: printf("SB_MINUS\n"); break;
  case SB_TIMES: printf("SB_TIMES\n"); break;
  case SB_SLASH: printf("SB_SLASH\n"); break;
  case SB_LPAR: printf("SB_LPAR\n"); break;
  case SB_RPAR: printf("SB_RPAR\n"); break;
  case SB_LSEL: printf("SB_LSEL\n"); break;
  case SB_RSEL: printf("SB_RSEL\n"); break;
  }
}

int scan(char *fileName) {
  Token *token;

  if (openInputStream(fileName) == IO_ERROR)
    return IO_ERROR;

  token = getToken();
  while (token->tokenType != TK_EOF) {
    printToken(token);
    free(token);
    token = getToken();
  }

  free(token);
  closeInputStream();
  return IO_SUCCESS;
}

/******************************************************************/

/*int main(int argc, char *argv[]) {
  if (argc <= 1) {
    printf("scanner: no input file.\n");
    return -1;
  }

  if (scan(argv[1]) == IO_ERROR) {
    printf("Can\'t read input file!\n");
    return -1;
  }

  return 0;
}*/

int main()
{

if (scan("example2.kpl") == IO_ERROR) {
   printf("Can\'t read input file!\n");
      }
return 0;

}


