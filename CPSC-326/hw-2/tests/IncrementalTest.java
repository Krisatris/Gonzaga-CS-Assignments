/*
 * File: LexerTest.java
 * Date: Spring 2022
 * Auth: Linden Beemer
 * Desc: The incremental tests I wrote as I built up this assignment
 */

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.fail;
import org.junit.Ignore;
import org.junit.Test;
import java.io.ByteArrayInputStream;
import java.io.InputStream;

public class IncrementalTest {
    
    @Test
    public void checkSingleChars() throws Exception {
        String s = ",.+-*/%{}()=";
        InputStream in = new ByteArrayInputStream(s.getBytes("UTF-8"));
        Lexer lexer = new Lexer(in);
        TokenType[] types = {
        TokenType.COMMA, TokenType.DOT, TokenType.PLUS, TokenType.MINUS,
        TokenType.MULTIPLY, TokenType.DIVIDE, TokenType.MODULO,
        TokenType.LBRACE, TokenType.RBRACE, TokenType.LPAREN,
        TokenType.RPAREN, TokenType.ASSIGN, TokenType.EOS
        };
        for (int i = 0; i < types.length; ++i) {
            Token t = lexer.nextToken();
            assertEquals(types[i], t.type());
            assertEquals(1, t.line());
            assertEquals(1 + i, t.column());
        }
    }

    @Test 
    public void checkSingleCharsWhiteSpace() throws Exception {
        String s = ", . + - * / % { } ( ) = ";
        InputStream in = new ByteArrayInputStream(s.getBytes("UTF-8"));
        Lexer lexer = new Lexer(in);
        TokenType[] types = {
        TokenType.COMMA, TokenType.DOT, TokenType.PLUS, TokenType.MINUS,
        TokenType.MULTIPLY, TokenType.DIVIDE, TokenType.MODULO,
        TokenType.LBRACE, TokenType.RBRACE, TokenType.LPAREN,
        TokenType.RPAREN, TokenType.ASSIGN, TokenType.EOS
        };
        for (int i = 0; i < types.length; ++i) {
            Token t = lexer.nextToken();
            assertEquals(types[i], t.type());
            assertEquals(1, t.line());
            assertEquals(1 + (2 * i), t.column());
        }
    }

    @Test
    public void multiComment() throws Exception {
        String s = "#comment1 \n #comment 2 \n ,.";
        InputStream in = new ByteArrayInputStream(s.getBytes("UTF-8"));
        Lexer lexer = new Lexer(in);
        TokenType[] types = {
            TokenType.COMMA, TokenType.DOT, TokenType.EOS
        };
        for(int i = 0; i < types.length; ++i) {
            Token t = lexer.nextToken();
            assertEquals(types[i], t.type());
            assertEquals(3, t.line());
            assertEquals(2 + i, t.column());
        }
    }

    @Test
    public void simpleChar() throws Exception {
        String s = "'a' '1' '!' '\\t' ''";
        InputStream in = new ByteArrayInputStream(s.getBytes("UTF-8"));
        Lexer lexer = new Lexer(in);
        Token t = lexer.nextToken();
        assertEquals(TokenType.CHAR_VAL, t.type());
        assertEquals("a", t.lexeme());
        assertEquals(1, t.line());
        assertEquals(1, t.column());
        t = lexer.nextToken();
        assertEquals(TokenType.CHAR_VAL, t.type());
        assertEquals("1", t.lexeme());
        assertEquals(1, t.line());
        assertEquals(5, t.column());
        t = lexer.nextToken();
        assertEquals(TokenType.CHAR_VAL, t.type());
        assertEquals("!", t.lexeme());
        assertEquals(1, t.line());
        assertEquals(9, t.column());
        t = lexer.nextToken();
        assertEquals(TokenType.CHAR_VAL, t.type());
        assertEquals("\\t", t.lexeme());
        assertEquals(1, t.line());
        assertEquals(13, t.column());
        t = lexer.nextToken();
        assertEquals(TokenType.CHAR_VAL, t.type());
        assertEquals("", t.lexeme());
        assertEquals(1, t.line());
        assertEquals(18, t.column());
        t = lexer.nextToken();
        assertEquals(TokenType.EOS, t.type());
    }

    @Test
    public void simpleString() throws Exception {
        String s = "\"test string\"";
        InputStream in = new ByteArrayInputStream(s.getBytes("UTF-8"));
        Lexer lexer = new Lexer(in);
        Token t = lexer.nextToken();
        assertEquals(TokenType.STRING_VAL, t.type());
        assertEquals("test string", t.lexeme());
        assertEquals(1, t.line());
        assertEquals(1, t.column());
    }

    @Test
    public void simpleIntDouble() throws Exception {
        String s = "3 3.14";
        InputStream in = new ByteArrayInputStream(s.getBytes("UTF-8"));
        Lexer lexer = new Lexer(in);
        Token t = lexer.nextToken();
        assertEquals(TokenType.INT_VAL, t.type());
        assertEquals("3", t.lexeme());
        assertEquals(1, t.line());
        assertEquals(1, t.column());
        t = lexer.nextToken();
        assertEquals(TokenType.DOUBLE_VAL, t.type());
        assertEquals("3.14", t.lexeme());
        assertEquals(1, t.line());
        assertEquals(3, t.column());
        t = lexer.nextToken();
        assertEquals(TokenType.EOS, t.type());
    }

    @Test
    public void reservedWords() throws Exception {
        String s = "var type while";
        InputStream in = new ByteArrayInputStream(s.getBytes("UTF-8"));
        Lexer lexer = new Lexer(in);
        Token t = lexer.nextToken();
        assertEquals(TokenType.VAR, t.type());
        assertEquals("var", t.lexeme());
        assertEquals(1, t.line());
        assertEquals(1, t.column());
        t = lexer.nextToken();
        assertEquals(TokenType.TYPE, t.type());
        assertEquals("type", t.lexeme());
        assertEquals(1, t.line());
        assertEquals(5, t.column());
        t = lexer.nextToken();
        assertEquals(TokenType.WHILE, t.type());
        assertEquals("while", t.lexeme());
        assertEquals(1, t.line());
        assertEquals(10, t.column());
        t = lexer.nextToken();
        assertEquals(TokenType.EOS, t.type());
    }

    @Test
    public void identifierWords() throws Exception {
        String s = "x myVar sum1";
        InputStream in = new ByteArrayInputStream(s.getBytes("UTF-8"));
        Lexer lexer = new Lexer(in);
        Token t = lexer.nextToken();
        assertEquals(TokenType.ID, t.type());
        assertEquals("x", t.lexeme());
        assertEquals(1, t.line());
        assertEquals(1, t.column());
        t = lexer.nextToken();
        assertEquals(TokenType.ID, t.type());
        assertEquals("myVar", t.lexeme());
        assertEquals(1, t.line());
        assertEquals(3, t.column());
        t = lexer.nextToken();
        assertEquals(TokenType.ID, t.type());
        assertEquals("sum1", t.lexeme());
        assertEquals(1, t.line());
        assertEquals(9, t.column());
        t = lexer.nextToken();
        assertEquals(TokenType.EOS, t.type());
    }
}
