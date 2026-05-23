#include <iostream>
#include <fstream>
#include <vector>

#include "lexer.h"

std::string tokenStrings[] = {
  "LEFT_PAREN", "RIGHT_PAREN",
  "LEFT_BRACE", "RIGHT_BRACE",
  "LEFT_BRACKET", "RIGHT_BRACKET",
  "COMMA", "DOT", "MINUS", "PLUS",
  "DIV", "MOD", "ENDLINE", "MULT",
  "EQUAL", "COLON", "SEMICOLON", "AND", "OR",
  "XOR", "NOT", "LEFT_BITSHIFT", "RIGHT_BITSHIFT",
  "EQUAL_EQUAL", "NOT_EQUAL", "LESS", "LESS_EQUAL",
  "GREATER", "GREATER_EQUAL", "AND_AND", "OR_OR",
  "IDENTIFIER", "INT", "FLOAT", "STRING",
  "TRUE", "FALSE", "IF", "ELSE", "LET", "FN",
  "NO_TYPE",
  "END_OF_FILE"
};

int main (int argc, char *argv[]){
  std :: vector<char> text = readText("main.myl");
  
  std :: cout << text.size() << "\n";
  
  std :: vector<Token> tokens = getIncompleteTokens(text);
  tokens = completeTokens(tokens);
  std :: ofstream fout("main.tok");
  
  for (const auto &elem: tokens){
    fout << tokenStrings[elem.type] << " " << elem.str << " " << elem.line << " " << elem.column << "\n";
  }
}

