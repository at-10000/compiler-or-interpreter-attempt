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

std :: vector<Token> completeTokens (std :: vector<Token> toks){
  for (auto &elem: toks){
    if (elem.str == "if"){
      elem.type = IF;
    }
    else if (elem.str == "else"){
      elem.type = ELSE;
    }
    else if (elem.str == "let"){
      elem.type = LET;
    }
    else if (elem.str == "fn"){
      elem.type = FN;
    }
    else if (elem.str == "True"){
      elem.type = TRUE;
    }
    else if (elem.str == "False"){
      elem.type = FALSE;
    }
  }
  return toks;
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




