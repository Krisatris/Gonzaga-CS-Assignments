/*
 * File: ASTParserTest.java
 * Date: Spring 2022
 * Auth: Linden Beemer
 * Desc: Basic parser unit tests for the error-handling add-on
 */

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;
import static org.junit.Assert.assertNotEquals;
import static org.junit.Assert.fail;
import org.junit.Ignore;
import org.junit.Test;
import java.io.ByteArrayInputStream;
import java.io.InputStream;


public class ErrorHandlingParserTest {

  //------------------------------------------------------------
  // HELPER FUNCTIONS
  //------------------------------------------------------------
  
  private static ASTParser buildParser(String s) throws Exception {
    InputStream in = new ByteArrayInputStream(s.getBytes("UTF-8"));
    ASTParser parser = new ASTParser(new Lexer(in));
    return parser;
  }

  private static String buildString(String... args) {
    String str = "";
    for (String s : args)
      str += s + "\n";
    return str;
  }

  //------------------------------------------------------------
  // TEST CASES
  //------------------------------------------------------------

  @Test
  public void throwStmtTest() throws Exception {
    String s = buildString
    ("fun void main() {",
     "  throw e",
     "}"
    );
    ASTParser parser = buildParser(s);
    Program p = parser.parse();
    ThrowStmt stmtNode = (ThrowStmt)p.fdecls.get(0).stmts.get(0);
    assertEquals(TokenType.ID, stmtNode.varName.type());
    assertEquals("e", stmtNode.varName.lexeme());
  }

  @Test
  public void invalidThrowType() throws Exception {
    String s = buildString(
      "fun void main() {",
      "  throw 42",
      "}"
    );
    try {
      buildParser(s).parse();
      fail("error not detected");
    } catch(MyPLException ex) {
      System.out.println(ex);
      assertTrue(ex.getMessage().startsWith("PARSE_ERROR:"));
    }
  }

  @Test
  public void tryStmtTest() throws Exception {
    String s = buildString
    ("fun void main() {",
     "  try {",
     "  } catch MyPLError e {",
     "  }",
     "}"
    );
    ASTParser parser = buildParser(s);
    Program p = parser.parse();
    TryStmt tStmtNode = (TryStmt)p.fdecls.get(0).stmts.get(0);
    assertEquals(0, tStmtNode.stmts.size());
    CatchStmt cStmtNode = (CatchStmt)tStmtNode.catchStmt;
    assertEquals(0, cStmtNode.stmts.size());
    assertEquals(TokenType.ID, cStmtNode.typeName.type());
    assertEquals("MyPLError", cStmtNode.typeName.lexeme());
    assertEquals(TokenType.ID, cStmtNode.varName.type());
    assertEquals("e", cStmtNode.varName.lexeme());
  }

  @Test
  public void twoCatchStmtsTest() throws Exception {
    String s = buildString
    ("fun void main() {",
     "  try {",
     "  } catch LexerError e {",
     "  } catch ParserError e {",
     "  }",
     "}"
    );
    ASTParser parser = buildParser(s);
    Program p = parser.parse();
    TryStmt tStmtNode = (TryStmt)p.fdecls.get(0).stmts.get(0);
    assertEquals(0, tStmtNode.stmts.size());
    CatchStmt cStmtNode1 = (CatchStmt)tStmtNode.catchStmt;
    assertEquals(0, cStmtNode1.stmts.size());
    assertEquals(TokenType.ID, cStmtNode1.typeName.type());
    assertEquals("LexerError", cStmtNode1.typeName.lexeme());
    assertEquals(TokenType.ID, cStmtNode1.varName.type());
    assertEquals("e", cStmtNode1.varName.lexeme());
    CatchStmt cStmtNode2 = (CatchStmt)cStmtNode1.otherCatch;
    assertEquals(0, cStmtNode2.stmts.size());
    assertEquals(TokenType.ID, cStmtNode2.typeName.type());
    assertEquals("ParserError", cStmtNode2.typeName.lexeme());
    assertEquals(TokenType.ID, cStmtNode2.varName.type());
    assertEquals("e", cStmtNode2.varName.lexeme());
  }

  @Test
  public void hangingTryStmtTest() throws Exception {
    String s = buildString
    ("fun void main() {",
     "  try {",
     "  }",
     "}"
    );
    try {
      buildParser(s).parse();
      fail("error not detected");
    } catch(MyPLException e) {
      assertTrue(e.getMessage().startsWith("PARSE_ERROR:"));
    }
  }

  @Test
  public void hangingCatchStmtTest() throws Exception {
    String s = buildString
    ("fun void main() {",
     "  catch MyPLError e {",
     "  }",
     "}"
    );
    try {
      buildParser(s).parse();
      fail("error not detected");
    } catch(MyPLException e) {
      assertTrue(e.getMessage().startsWith("PARSE_ERROR:"));
    }
  }

  @Test
  public void catchNotUDT() throws Exception {
    String s = buildString(
      "fun void main() {",
      "  var int x = 10",
      "  try {}",
      "  catch int x {}",
      "}"
    );
    try {
      buildParser(s).parse();
      fail("error not detected");
    } catch(MyPLException ex) {
      System.out.println(ex);
      assertTrue(ex.getMessage().startsWith("PARSE_ERROR:"));
    }
  }
}
