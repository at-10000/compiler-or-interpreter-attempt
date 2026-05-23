#include <iostream>
#include <fstream>
#include <vector>

#include "lexer.h"

// ifstream fin("main.myl");
// ofstream fout("main.tok");

// use as separator ( ) { } : \n = + - * / % and maybe space as well?
// implement == < > != and ! as well
// also implement [ ]

/*
std :: vector<std :: string> getWords(std :: string filename){
  std :: string inputfile = filename;
  std :: ifstream fin(inputfile);

  std :: vector<std :: string> words = {};

  char c;
  std :: string currentWord = "";


  while (fin.get(c)){
    if (isSeparator(c)){
      if (currentWord != ""){
        words.push_back(currentWord);
      }
      
      if (c != ' '){
        words.push_back({c}); // learn why this works
      }

      currentWord = "";
      continue;
    }

    currentWord += c;
  }

  if (currentWord != ""){
    words.push_back(currentWord);
  }

  return words;
}
*/

std :: string tokenStrings[] = {
  "LEFT_PAREN", "RIGHT_PAREN",
  "LEFT_BRACE", "RIGHT_BRACE",
  "LEFT_BRACKET", "BRACKET",
  "COMMA", "DOT", "MINUS", "PLUS",
  "DIV", "MOD", "ENDLINE", "MULT",
  "EQUAL", "COLON", "SEMICOLON", "AND", "OR",
  "XOR", "NOT", "LEFT_BITSHIFT", "RIGHT_BITSHIFT",
  "EQUAL_EQUAL", "NOT_EQUAL", "LESS", "LESS_EQUAL",
  "GREATER", "GREATER_EQUAL", "AND_AND", "OR_OR",
  "IDENTIFIER", "INT", "FLOAT", "STRING",
  "TRUE", "FALSE", "IF", "LET", "FN",
  "NO_TYPE",
  "END_OF_FILE"
};

int main (int argc, char *argv[]){
  std :: vector<char> text = readText("main.myl");
  
  std :: cout << text.size() << "\n";
  
  std :: vector<Token> tokens = getIncompleteTokens(text);
  std :: ofstream fout("main.tok");
  
  for (const auto &elem: tokens){
    fout << tokenStrings[elem.type] << " " << elem.str << " " << elem.line << " " << elem.column << "\n";
  }

  /*
  std :: vector<std :: string> words = getWords("main.myl");
  std :: ofstream fout("main.tok");
  
  for (const auto &elem : words){
    if (elem == "\n"){
      fout << "\\n\n";
      continue;
    }

    fout << elem << "\n";
  }
  */
}

