/*
 * File: ErrorHandlingLexerTest.java
 * Date: Spring 2022
 * Auth: Linden Beemer
 * Desc: Lexer tests for the error handling add-on of MyPL
 */

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.fail;
import org.junit.Ignore;
import org.junit.Test;
import java.io.ByteArrayInputStream;
import java.io.InputStream;


public class ErrorHandlingLexerTest {

  // helper method
  private static String buildString(String... args) {
    String str = "";
    for (String s : args)
      str += s + "\n";
    return str;
  }


  //------------------------------------------------------------
  // POSITIVE TEST CASES
  //------------------------------------------------------------
  
  @Test
  public void checkTryStmts() throws Exception {
    String s = buildString(
      "try {",
      "  x = 10",
      "}",
      "try {",
      " print(x)",
      "}"
    );
    InputStream in = new ByteArrayInputStream(s.getBytes("UTF-8"));
    Lexer lexer = new Lexer(in);
    TokenType[] types = {
      TokenType.TRY, TokenType.LBRACE, TokenType.ID, TokenType.ASSIGN,
      TokenType.INT_VAL, TokenType.RBRACE, TokenType.TRY,
      TokenType.LBRACE, TokenType.ID, TokenType.LPAREN,
      TokenType.ID, TokenType.RPAREN, TokenType.RBRACE
    };
    for(int i = 0; i < types.length; ++i) {
      Token t = lexer.nextToken();
      assertEquals(types[i], t.type());
    }
  }
  
  @Test
  public void checkCatchStmts() throws Exception {
    String s = buildString(
      "catch LexerError e {",
      "  x = 10",
      "}",
      "catch ParseError e {",
      " print(x)",
      "}"
    );
    InputStream in = new ByteArrayInputStream(s.getBytes("UTF-8"));
    Lexer lexer = new Lexer(in);
    TokenType[] types = {
      TokenType.CATCH, TokenType.ID, TokenType.ID, TokenType.LBRACE, 
      TokenType.ID, TokenType.ASSIGN, TokenType.INT_VAL, TokenType.RBRACE, 
      TokenType.CATCH, TokenType.ID, TokenType.ID, TokenType.LBRACE, 
      TokenType.ID, TokenType.LPAREN, TokenType.ID, TokenType.RPAREN, TokenType.RBRACE
    };
    for(int i = 0; i < types.length; ++i) {
      Token t = lexer.nextToken();
      assertEquals(types[i], t.type());
    }
  }

  @Test
  public void checkThrowStmts() throws Exception {
    String s = buildString(
      "throw e1",
      "throw e2",
      "throw e3"
    );
    InputStream in = new ByteArrayInputStream(s.getBytes("UTF-8"));
    Lexer lexer = new Lexer(in);
    TokenType[] types = {
      TokenType.THROW, TokenType.ID, 
      TokenType.THROW, TokenType.ID,
      TokenType.THROW, TokenType.ID
    };
    for(int i = 0; i < types.length; ++i) {
      Token t = lexer.nextToken();
      assertEquals(types[i], t.type());
    }
  }

}