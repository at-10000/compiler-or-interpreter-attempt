#include "lexer.h"

Token initToken(TokenType type, std :: string str, int col, int lin){
  Token tok;
  tok.type = type;
  tok.str = str;
  tok.column = col;
  tok.line = lin;

  return tok;
}

std :: vector<char> readText (std :: string filename){
  std :: ifstream fin(filename);
  
  std :: vector<char> text;
  char c;

  while (fin.get(c)){
    text.push_back(c);
  }

  return text;
}

// use function definitions for the two functions above and put the next function above

std :: vector<Token> getNonDescribedTokens_bad (std :: vector<char> text){
  int i = 0;
  int j = 0;
  int line = 0;
  int limit = text.size();
  std :: string currentWord = "";
  Token currentTok;
  std :: vector<Token> tokens = {};

  while (i <= limit && j <= limit){ 
    if (text[j] == ' '){
      currentTok.str = currentWord;
      currentTok.line = line;
      currentTok.column = i;
      if (currentWord != " " && currentWord != ""){ 
        tokens.push_back(currentTok);
      }

      currentWord = "";

      i = j + 1;
      j ++;
      
      /*
      if (i <= limit) {
        currentWord = text[i];
      }
      */
    }
    TokenType sep = isSeparator(text[j], text[j + 1]);
    if (sep != NO_TYPE){
      if (text[j] == '\n' || text[j + 1] == '\n'){
        line ++;
      }

      currentTok.type = NO_TYPE;
      currentTok.str = currentWord;
      currentTok.line = line;
      currentTok.column = i;

      tokens.push_back(currentTok);

      if (is2charSeparator(sep)){
        currentWord = text[j] + text[j + 1];
        i = j + 2;
        j = j + 2;
      }
      else {
        currentWord = text[j];
        i = j + 1;
        j = j + 1;
      }

      currentTok.type = sep;
      currentTok.str = currentWord;
      currentTok.line = line;
      currentTok.column = j;
      currentTok.type = NO_TYPE;

      tokens.push_back(currentTok);

      currentWord = "";
    }
    
    currentWord = currentWord + text[j];
    
    /*
    if (text[j] == '\n'){ // move this at end
      line ++;
    }
    */

    j ++;
  }

  return tokens;
}

std :: vector<Token> getIncompleteTokens (std :: vector<char> text){
  if (text.empty()){
    return {};
  }

  int line = 0;
  int column = 0;

  std :: string currentWord;
  Token currentToken;
  TokenType currentType = NO_TYPE;

  std :: vector<Token> tokens = {};

  for (int i = 0; i < (text.size() - 1); i ++){
    currentType = isSeparator(text[i], text[i + 1]);
    if (currentType != NO_TYPE){
      if (currentWord != ""){
        currentToken = initToken(NO_TYPE, currentWord, column, line);

        tokens.push_back(currentToken);

        currentToken = Token{};
      }

      if (is2charSeparator(currentType)){
        currentWord = std::string{ text[i], text[i + 1] };
        i ++;
        column ++;
      }
      else {
        currentWord = std::string(1, text[i]);
      }
      
      currentToken = initToken(currentType, currentWord, column, line);

      tokens.push_back(currentToken);

      currentWord = "";
    }
    else if (text[i] == ' ' && currentWord != ""){
      currentToken = initToken(NO_TYPE, currentWord, column, line);

      tokens.push_back(currentToken);

      currentWord = "";
    }
    else if (text[i] == ' '){
      currentWord = "";
    }
    else if (text[i] == '\n'){
      line ++;
      column = 0;
    }
    else {
      currentWord += text[i];
    }
    column ++;
  }
  
  char last = text[text.size() - 1];

  currentType = isSeparator(last, ' ');

  if (currentType != NO_TYPE) {
    if (currentWord != "") {
      tokens.push_back(initToken(NO_TYPE, currentWord, column, line));
    }

    currentWord = std::string(1, last);

    tokens.push_back(initToken(currentType, currentWord, column, line));
  }
  else if (last != ' ' && last != '\n') {
    currentWord += last;

    tokens.push_back(initToken(NO_TYPE, currentWord, column, line));
  }
  
  return tokens;
}

TokenType isSeparator (char c1, char c2){
  TokenType type;

  switch (c1) {
    case ';':
      type = SEMICOLON;
      break;

    case '(':
      type = LEFT_PAREN;
      break;

    case ')':
      type = RIGHT_PAREN;
      break;

    case '{':
      type = LEFT_BRACE;
      break;

    case '}':
      type = RIGHT_BRACE;
      break;

    case '[':
      type = LEFT_BRACKET;
      break;

    case ']':
      type = RIGHT_BRACKET;
      break;

    case '+':
      type = PLUS;
      break;

    case '-':
      type = MINUS;
      break;

    case '*':
      type = MULT;
      break;

    case '%':
      type = MOD;
      break;

    case '/':
      type = DIV;
      break;
    
    case '=':
      if (c2 == '=') {
        type = EQUAL_EQUAL;
      }
      else {
        type = EQUAL;
      }
      break;
    
    case '!':
      if (c2 == '=') {
        type = NOT_EQUAL;
      }
      else {
        type = NOT;
      }
      break;
    
    case '&':
      if (c2 == '&') {
        type = AND_AND;
      }
      else {
        type = AND;
      }
      return type;
      break;
    
    case '|':
      if (c2 == '|') {
        type = OR_OR;
      }
      else {
        type = OR;
      }
      break;
    
    case '<':
      if (c2 == '=') {
        type = LESS_EQUAL;
      }
      else {
        type = LESS;
      }
      break;
    
    case '>':
      if (c2 == '=') {
        type = GREATER_EQUAL;
      }
      else {
        type = GREATER;
      }
      break;
    
    default:
      type = NO_TYPE;
      break;
  }
  
  return type;
}

bool is2charSeparator (TokenType tok){
  switch (tok) {
    case EQUAL_EQUAL:
      return 1;
      break;

    case NOT_EQUAL:
      return 1;
      break;

    case LESS_EQUAL:
      return 1;
      break;

    case GREATER_EQUAL:
      return 1;
      break;

    case LEFT_BITSHIFT:
      return 1;
      break;

    case RIGHT_BITSHIFT:
      return 1;
      break;
    
    default:
      return 0;
      break;
  }
}




