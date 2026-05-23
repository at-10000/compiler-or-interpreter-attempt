#ifndef LEXER_H
#define LEXER_H

#include <vector>
#include <string>
#include <fstream>

enum TokenType {
  // Single-character tokens
  LEFT_PAREN, RIGHT_PAREN,
  LEFT_BRACE, RIGHT_BRACE,
  LEFT_BRACKET, RIGHT_BRACKET,
  COMMA, DOT, MINUS, PLUS,
  DIV, MOD, ENDLINE, MULT,
  EQUAL, COLON, SEMICOLON,

  // Binary operators
  AND, OR, XOR, NOT,
  LEFT_BITSHIFT, RIGHT_BITSHIFT,

  // True/False operators
  EQUAL_EQUAL, NOT_EQUAL,
  LESS, LESS_EQUAL,
  GREATER, GREATER_EQUAL,
  AND_AND, OR_OR,

  // Types of literals
  IDENTIFIER, INT, FLOAT, STRING,

  // Keywords
  TRUE, FALSE, IF, LET, FN,

  NO_TYPE, // What the hell are you doing?

  END_OF_FILE
};

// make an array of strings that match each value of the TokenType enum for outputting purposes

struct Token {
  TokenType type = NO_TYPE;
  std :: string str = "";
  int line = 0;
  int column = 0;
};

std :: vector<char> readText(std :: string filename);

std :: vector<Token> getIncompleteTokens (std :: vector<char> text);

TokenType isSeparator (char c1, char c2);

bool is2charSeparator (TokenType tok);

#endif

