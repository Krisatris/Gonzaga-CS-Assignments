/*
 * File: Lexer.java
 * Date: Spring 2022
 * Auth: Linden Beemer
 * Desc: 
 */

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.IOException;


public class Lexer {

  private BufferedReader buffer; // handle to input stream
  private int line = 1;          // current line number
  private int column = 0;        // current column number


  //--------------------------------------------------------------------
  // Constructor
  //--------------------------------------------------------------------
  
  public Lexer(InputStream instream) {
    buffer = new BufferedReader(new InputStreamReader(instream));
  }


  //--------------------------------------------------------------------
  // Private helper methods
  //--------------------------------------------------------------------

  // Returns next character in the stream. Returns -1 if end of file.
  private int read() throws MyPLException {
    try {
      return buffer.read();
    } catch(IOException e) {
      error("read error", line, column + 1);
    }
    return -1;
  }

  
  // Returns next character without removing it from the stream.
  private int peek() throws MyPLException {
    int ch = -1;
    try {
      buffer.mark(1);
      ch = read();
      buffer.reset();
    } catch(IOException e) {
      error("read error", line, column + 1);
    }
    return ch;
  }


  // Print an error message and exit the program.
  private void error(String msg, int line, int column) throws MyPLException {
    msg = msg + " at line " + line + ", column " + column;
    throw MyPLException.LexerError(msg);
  }

  
  // Checks for whitespace 
  public static boolean isWhitespace(int ch) {
    return Character.isWhitespace((char)ch);
  }

  
  // Checks for digit
  private static boolean isDigit(int ch) {
    return Character.isDigit((char)ch);
  }

  
  // Checks for letter
  private static boolean isLetter(int ch) {
    return Character.isLetter((char)ch);
  }

  
  // Checks if given symbol
  private static boolean isSymbol(int ch, char symbol) {
    return (char)ch == symbol;
  }

  
  // Checks if end-of-file
  private static boolean isEOF(int ch) {
    return ch == -1;
  }
  

  //--------------------------------------------------------------------
  // Public next_token function
  //--------------------------------------------------------------------
  
  // Returns next token in input stream
  public Token nextToken() throws MyPLException {

    int currChar = read();
    column++;

    // check for new line
    while(isSymbol(currChar, '\n')) {
      currChar = read();
      ++line;
      column = 1;
    }

    // remove white space and comments
    if(isWhitespace(currChar)) {
      while(isWhitespace(currChar) || isSymbol(currChar, '\n')) {
        currChar = read();
        ++column;
        // check for new line
        if(isSymbol(currChar, '\n')) {
          currChar = read();
          ++line;
          column = 1;
        }
      }
    }
    else if(isSymbol(currChar, '#')) {
      while(isSymbol(currChar, '#')) {
        while(!isSymbol(currChar, '\n')) {
          currChar = (char)read();
          ++column;
        }
        currChar = (char)read();
        column = 1;
        ++line;
        if(isWhitespace(currChar)) {
          while(isWhitespace(currChar) || isSymbol(currChar, '\n')) {
            // check for new line
            if(isSymbol(currChar, '\n')) {
              //currChar = read();
              ++line;
              column = 0;
            }
            currChar = read();
            ++column;
          }
        }
      }
    }

    // check for EOF
    if(isEOF(currChar)) {
      return new Token(TokenType.EOS, "end-of-file", line, column);
    }

    // check for single character tokens
    else if(isSymbol(currChar, ',')) {
      return new Token(TokenType.COMMA, ",", line, column);
    }
    else if(isSymbol(currChar, '.')) {
      if(isDigit(peek())) {
        error("malformed double, missing leading int value", line, column);
      }
      else {
        return new Token(TokenType.DOT, ".", line, column);
      }
    }
    else if(isSymbol(currChar, '+')) {
      return new Token(TokenType.PLUS, "+", line, column);
    }
    else if(isSymbol(currChar, '-')) {
      return new Token(TokenType.MINUS, "-", line, column);
    }
    else if(isSymbol(currChar, '*')) {
      return new Token(TokenType.MULTIPLY, "*", line, column);
    }
    else if(isSymbol(currChar, '/')) {
      return new Token(TokenType.DIVIDE, "/", line, column);
    }
    else if(isSymbol(currChar, '%')) {
      return new Token(TokenType.MODULO, "%", line, column);
    }
    else if(isSymbol(currChar, '{')) {
      return new Token(TokenType.LBRACE, "{", line, column);
    }
    else if(isSymbol(currChar, '}')) {
      return new Token(TokenType.RBRACE, "}", line, column);
    }
    else if(isSymbol(currChar, '(')) {
      return new Token(TokenType.LPAREN, "(", line, column);
    }
    else if(isSymbol(currChar, ')')) {
      return new Token(TokenType.RPAREN, ")", line, column);
    }

    // comparators
    else if(isSymbol(currChar, '>')) {
      if(isSymbol(peek(), '=')) {
        read();
        ++column;
        return new Token(TokenType.GREATER_THAN_EQUAL, ">=", line, column - 1);
      } 
      else {
        return new Token(TokenType.GREATER_THAN, ">", line, column);
      }
    }
    else if(isSymbol(currChar, '<')) {
      if(isSymbol(peek(), '=')) {
        read();
        ++column;
        return new Token(TokenType.LESS_THAN_EQUAL, "<=", line, column - 1);
      }
      else {
        return new Token(TokenType.LESS_THAN, "<", line, column);
      }
    }
    else if(isSymbol(currChar, '=')) {
      if(isSymbol(peek(), '=')) {
        read();
        ++column;
        return new Token(TokenType.EQUAL, "==", line, column - 1);
      }
      else {
        return new Token(TokenType.ASSIGN, "=", line, column);
      }
    }
    else if(isSymbol(currChar, '!')) {
      if(isSymbol(peek(), '=')) {
        read();
        ++column;
        return new Token(TokenType.NOT_EQUAL, "!=", line, column - 1);
      }
      else {
        error("expecting '=', found '" + (char)peek() + "'", line, column + 1);
      }
    }

    // char values
    else if(isSymbol(currChar, '\'')) {
      if(isSymbol(peek(), '\'')) { // empty char
        error("empty character", line, column);
      }
      else {
        currChar = read();
        if(isSymbol(peek(), '\'')) { // normal char
          if(isSymbol(currChar, '\n')) {
            error("found newline in character", line, column);
          } else if(isSymbol(currChar, '\t')) {
            error("found tab in character", line, column);
          }
          column += 2;
          read();
          return new Token(TokenType.CHAR_VAL, String.valueOf((char)currChar), line, column - 2);
        }
        else if(isSymbol(currChar, '\\')) { // \n or \t
          currChar = read();
          if(isSymbol(currChar, 'n')) {
            if(isSymbol(peek(), '\'')) {
              column += 3;
              read();
              return new Token(TokenType.CHAR_VAL, "\\n", line, column - 3);
            }
            else {
              error("expecting ' found, '" + (char)peek() + "'", line, column + 1);
            }
          }
          else if(isSymbol(currChar, 't')) {
            if(isSymbol(peek(), '\'')) {
              column += 3;
              read();
              return new Token(TokenType.CHAR_VAL, "\\t", line, column - 3);
            }
            else {
              error("expecting ' found, '" + (char)peek() + "'", line, column + 1);
            }
          }
          else {
            error("expecting n or t found, " + (char)currChar, line, column + 1);
          }
        }
        else {
          error("expecting ' found, '" + (char)peek() + "'", line, column + 1);
        }
      }
    }

    // string values
    else if(isSymbol(currChar, '\"')) {
      currChar = read();
      String resultStr = "";
      while(!isSymbol(currChar, '\"')) {
        if(currChar == -1) {
          error("found end-of-file in string", line, column + resultStr.length());
        }
        if(isSymbol(currChar, '\n')) {
          error("found newline within string", line, column + 1);
        }
        resultStr += (char)currChar;
        currChar = read();
      }
      int offset = resultStr.length() + 1;
      column += offset;
      return new Token(TokenType.STRING_VAL, resultStr, line, column - offset);
    }

    // integer and double values
    else if(isDigit(currChar)) {
      String resultStr = "";
      boolean dotFound = false;
      while(isSymbol(peek(), '.') || isDigit(peek())) {
        if(isSymbol(currChar, '.')) {
          if(dotFound) {
            error("too many decimal points in double value '" + resultStr + "'", line, column);
          } else {
            dotFound = true;
            resultStr += (char)currChar;
          }
        }
        else {
          resultStr += (char)currChar;
        }
        currChar = read();
      }
      resultStr += (char)currChar;
      int offset = resultStr.length() - 1;
      column += offset;
      if(dotFound) {
        if(resultStr.charAt(0) == '0' && resultStr.charAt(1) != '.') {
          error("leading zero in '" + resultStr + "'", line, column - offset);
        }
        return new Token(TokenType.DOUBLE_VAL, resultStr, line, column - offset);
      }
      else {
        if(resultStr.charAt(0) == '0' && resultStr.length() > 1) { // easy way to check for leading zeroes
          error("leading zero in '" + resultStr + "'", line, column - offset);
        }
        return new Token(TokenType.INT_VAL, resultStr, line, column - offset);
      }
    }

    // reserved words
    String resultStr = "";
    while(isLetter(peek())) {
      resultStr += (char)currChar;
      currChar = read();
    }
    if(!isLetter(currChar)) {
      error("invalid symbol '" + (char)currChar + "'", line, column);
    }
    resultStr += (char)currChar;
    int offset = resultStr.length() - 1;
    column += offset;

    // check data types
    if(isDigit(peek()) || isSymbol(peek(), '_')) {
      // bypass reserved words because this is actually an ID
    }
    else if(resultStr.equals("int")) {
      return new Token(TokenType.INT_TYPE, resultStr, line, column - offset);
    }
    else if(resultStr.equals("double")) {
      return new Token(TokenType.DOUBLE_TYPE, resultStr, line, column - offset);
    }
    else if(resultStr.equals("char")) {
      return new Token(TokenType.CHAR_TYPE, resultStr, line, column - offset);
    }
    else if(resultStr.equals("string")) {
      return new Token(TokenType.STRING_TYPE, resultStr, line, column - offset);
    }
    else if(resultStr.equals("bool")) {
      return new Token(TokenType.BOOL_TYPE, resultStr, line, column - offset);
    }
    else if(resultStr.equals("void")) {
      return new Token(TokenType.VOID_TYPE, resultStr, line, column - offset);
    }

    // check boolean operators
    else if(resultStr.equals("and")) {
      return new Token(TokenType.AND, resultStr, line, column - offset);
    }
    else if(resultStr.equals("or")) {
      return new Token(TokenType.OR, resultStr, line, column - offset);
    }
    else if(resultStr.equals("not")) {
      return new Token(TokenType.NOT, resultStr, line, column - offset);
    }
    else if(resultStr.equals("neg")) {
      return new Token(TokenType.NEG, resultStr, line, column - offset);
    }

    // check for reserved words
    else if(resultStr.equals("var")) {
      return new Token(TokenType.VAR, resultStr, line, column - offset);
    }
    else if(resultStr.equals("type")) {
      return new Token(TokenType.TYPE, resultStr, line, column - offset);
    }
    else if(resultStr.equals("while")) {
      return new Token(TokenType.WHILE, resultStr, line, column - offset);
    }
    else if(resultStr.equals("for")) {
      return new Token(TokenType.FOR, resultStr, line, column - offset);
    }
    else if(resultStr.equals("from")) {
      return new Token(TokenType.FROM, resultStr, line, column - offset);
    }
    else if(resultStr.equals("upto")) {
      return new Token(TokenType.UPTO, resultStr, line, column - offset);
    }
    else if(resultStr.equals("downto")) {
      return new Token(TokenType.DOWNTO, resultStr, line, column - offset);
    }
    else if(resultStr.equals("if")) {
      return new Token(TokenType.IF, resultStr, line, column - offset);
    }
    else if(resultStr.equals("elif")) {
      return new Token(TokenType.ELIF, resultStr, line, column - offset);
    }
    else if(resultStr.equals("else")) {
      return new Token(TokenType.ELSE, resultStr, line, column - offset);
    }
    else if(resultStr.equals("fun")) {
      return new Token(TokenType.FUN, resultStr, line, column - offset);
    }
    else if(resultStr.equals("new")) {
      return new Token(TokenType.NEW, resultStr, line, column - offset);
    }
    else if(resultStr.equals("delete")) {
      return new Token(TokenType.DELETE, resultStr, line, column - offset);
    }
    else if(resultStr.equals("return")) {
      return new Token(TokenType.RETURN, resultStr, line, column - offset);
    }
    else if(resultStr.equals("nil")) {
      return new Token(TokenType.NIL, resultStr, line, column - offset);
    }
    else if(resultStr.equals("true")) {
      return new Token(TokenType.BOOL_VAL, resultStr, line, column - offset);
    }
    else if(resultStr.equals("false")) {
      return new Token(TokenType.BOOL_VAL, resultStr, line, column - offset);
    }

    // anything left is an ID or unexpected character, unexpected char wont be found till next call of nextToken()
    if(!(isLetter(peek()) || isDigit(peek()) || isSymbol(peek(), '_'))) {
      return new Token(TokenType.ID, resultStr, line, column - offset);
    }
    //check for nums and underscores
    else {
      currChar = read();
      while(isLetter(peek()) || isDigit(peek()) || isSymbol(peek(), '_')) {
        resultStr += (char)currChar;
        currChar = read();
        /*
        if(!(isDigit(currChar) || isLetter(currChar) || isSymbol(currChar, '_'))) { //error if invalid char found
          error("unexpected character " + (char)currChar + " in identifier", line, column);
        }
        */
      }
    }
    /*
    else { 
      error("an unknown error has occured at", line, column);
    }
    */
    resultStr += (char)currChar;
    column -= offset; // reset column
    offset = resultStr.length() - 1; // calculate new offset
    column += offset; // set column correctly

    return new Token(TokenType.ID, resultStr, line, column - offset);
  }

}
