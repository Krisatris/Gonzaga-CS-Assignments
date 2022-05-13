/*
* File: StatiCheckerTest.java
* Date: Spring 2022
* Auth: Linden Beemer
* Desc: Various static analysis tests for HW-5
*/

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;
import static org.junit.Assert.fail;
import org.junit.Ignore;
import org.junit.Test;

import java.beans.Transient;
import java.io.ByteArrayInputStream;
import java.io.InputStream;
import java.util.List;
import java.util.ArrayList;


public class ErrorHandlingStaticCheckerTest {

  //------------------------------------------------------------
  // HELPER FUNCTIONS
  //------------------------------------------------------------

  private static ASTParser buildParser(String s) throws Exception {
    InputStream in = new ByteArrayInputStream(s.getBytes("UTF-8"));
    ASTParser parser = new ASTParser(new Lexer(in));
    return parser;
  }

  private static StaticChecker buildChecker() throws Exception {
    TypeInfo types = new TypeInfo();
    StaticChecker checker = new StaticChecker(types);
    return checker;
  }

  private static String buildString(String... args) {
    String str = "";
    for (String s : args)
      str += s + "\n";
    return str;
  }

  //------------------------------------------------------------
  // Throw Statement cases
  //------------------------------------------------------------

  @Test
  public void invalidVarType() throws Exception {
    String s = buildString(
      "fun void main() {",
      "  var string x = \"hello world!\"",
      "  throw x",
      "}"
    );
    try {
      buildParser(s).parse().accept(buildChecker());
      fail("error not detected");
    } catch(MyPLException ex) {
      assertTrue(ex.getMessage().startsWith("STATIC_ERROR:"));
    }
  }

  @Test
  public void undefinedThrowType() throws Exception {
    String s = buildString(
      "fun void main() {",
      "  throw e",
      "}"
    );
    try {
      buildParser(s).parse().accept(buildChecker());
      fail("error not detected");
    } catch(MyPLException ex) {
      assertTrue(ex.getMessage().startsWith("STATIC_ERROR:"));
    }
  }

  //------------------------------------------------------------
  // no specific try cases for static checker since
  // it's errors come from the parser and those are tested
  //------------------------------------------------------------

  //------------------------------------------------------------
  // Catch Statement cases
  //------------------------------------------------------------

  @Test
  public void catchNameAlreadyDefined() throws Exception {
    String s = buildString(
      "type MyPLError {",
      "  var string msg = nil",
      "}",
      "fun void main() {",
      "  var int x = 10",
      "  try {}",
      "  catch MyPLError x {}",
      "}"
    );
    try {
      buildParser(s).parse().accept(buildChecker());
      fail("error not detected");
    } catch(MyPLException ex) {
      assertTrue(ex.getMessage().startsWith("STATIC_ERROR:"));
    }
  }

  @Test
  public void twoCatchStmts() throws Exception {
    String s = buildString(
      "type ParserError {",
      "  var string msg = nil",
      "}",
      "type LexerError {",
      "  var string msg = nil",
      "}",
      "fun void main() {",
      "  try {}",
      "  catch ParserError e {}",
      "  catch LexerError e {}",
      "}"
    );
    buildParser(s).parse().accept(buildChecker());
  }
}
