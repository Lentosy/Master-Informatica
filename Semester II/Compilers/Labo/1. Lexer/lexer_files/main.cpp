#include <cstring>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>

#include "lexer.hpp"


// render a token to a string, either the name of the token or its ASCII value
std::string to_token_string(int token) {
  if (token > 255) {
    switch (token) {
      case RETURN:     return "RETURN";
      case IF:         return "IF";
      case ELSE:       return "ELSE";
      case WHILE:      return "WHILE";
      case FOR:        return "FOR";
      case IDENTIFIER: return "IDENTIFIER";
      case INTEGER:    return "INTEGER";
      case FLOAT:      return "FLOAT";
      case STRING:     return "STRING";
      case EQUAL:      return "EQUAL";
      case CEQ:        return "CEQ";
      case CNE:        return "CNE";
      case CLT:        return "CLT";
      case CLE:        return "CLE";
      case CGT:        return "CGT";
      case CGE:        return "CGE";
      case PLUS:       return "PLUS";
      case MINUS:      return "MINUS";
      case MUL:        return "MUL";
      case DIV:        return "DIV";
      case EXP:        return "EXP";
      case MOD:        return "MOD";
      default:         return "UNKNOWN";
    }
  } else {
    std::string str;
    str = (char)token;
    return "'" + str + "'";
  }
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " FILENAME" << std::endl;
    return EXIT_FAILURE;
  }
  auto path = argv[1];

  std::ifstream input(path);
  if (!input.is_open()) {
    std::cerr << "Could not open " << path << ": " << strerror(errno) << std::endl;
    return EXIT_FAILURE;
  }

  Lexer lexer(&input);
  // lexer.set_debug_level(1);
  while (int token = lexer.yylex()) {
    // column 1: location information
    std::stringstream location;
    location << lexer.begin.line << ":" << lexer.begin.column << " → "
             << lexer.end.line << ":" << lexer.end.column;
    std::cout << std::setw(20) << location.str();

    // column 2: token string
    std::cout << std::setw(10) << lexer.YYText();

    // column 3: token type
    std::cout << std::setw(16) << to_token_string(token) << std::endl;
  }

  return EXIT_SUCCESS;
}
