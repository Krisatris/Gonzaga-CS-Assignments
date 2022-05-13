/*
* File: ErrorHandlingCodeGeneratorTest.java
* Date: Spring 2022
* Auth: Linden Beemer
* Desc: Various code genertor tests for the error handling add on
*/

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;
import static org.junit.Assert.fail;
import org.junit.Ignore;
import org.junit.Test;
import org.junit.Before;
import org.junit.After;

import java.beans.Transient;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.InputStream;
import java.io.PrintStream;
import java.util.List;
import java.util.ArrayList;


public class ErrorHandlingCodeGeneratorTest {

  //------------------------------------------------------------
  // HELPER FUNCTIONS
  //------------------------------------------------------------

  private PrintStream stdout = System.out;
  private ByteArrayOutputStream output = new ByteArrayOutputStream(); 

  private static String buildString(String... args) {
    String str = "";
    for (String s : args)
      str += s + "\n";
    return str;
  }

  @Before
  public void changeSystemOut() {
    // redirect System.out to output
    System.setOut(new PrintStream(output));
  }

  @After
  public void restoreSystemOut() {
    // reset System.out to standard out
    System.setOut(stdout);
  }

  private static VM buildVM(String s) throws Exception {
    InputStream in = new ByteArrayInputStream(s.getBytes("UTF-8"));
    ASTParser parser = new ASTParser(new Lexer(in));
    Program program = parser.parse();
    TypeInfo  typeInfo = new TypeInfo();
    program.accept(new StaticChecker(typeInfo));
    VM vm = new VM();
    CodeGenerator genVisitor = new CodeGenerator(typeInfo, vm);
    program.accept(genVisitor);
    return vm;
  }

  //------------------------------------------------------------
  // Throw Statement valid cases
  //------------------------------------------------------------

  @Test
  public void throwStmtTest() throws Exception {
    String s = buildString(
      "type MyPLException {",
      "  var message = \"\"",
      "  var errorCode = 0",
      "}",
      "fun void main() {",
      "  var MyPLException e = new MyPLException",
      "  e.message = \"error found\"",
      "  throw e",
      "}"
    );
    VM vm = buildVM(s);
    vm.run();
    assertEquals("", output.toString());
  }

  //------------------------------------------------------------
  // Try-Catch valid cases
  //------------------------------------------------------------

  @Test
  public void tryCatchStmtTest() throws Exception {
    String s = buildString(
      "type MyPLError {",
      "  var string msg = nil",
      "}",
      "fun void f(int i) {",
      "  var MyPLError x = new MyPLError",
      "  x.msg = \"positive int\"",
      "  if i > 0 {",
      "    throw x",
      "  }",
      "}",
      "fun void main() {",
      "  try {",
      "    f(1)",
      "  } catch MyPLError x {",
      "    print(x.msg)",
      "  }",
      "}"
    );
    VM vm = buildVM(s);
    vm.run();
    assertEquals("positive int", output.toString());
  }

  @Test
  public void doubleCatchStmt() throws Exception {
    String s = buildString(
      "type LexerError {",
      "  var string msg = nil",
      "}",
      "type ParserError {",
      "  var string msg = nil",
      "}",
      "fun void f(int i) {",
      "  if i > 10 {",
      "    var LexerError x = new LexerError",
      "    x.msg = \"lexer error detected\"",
      "    throw x",
      "  } else {",
      "    var ParserError x = new ParserError",
      "    x.msg = \"parser error detected\"",
      "    throw x",
      "  }",
      "}",
      "fun void main() {",
      "  try {",
      "    f(1)",
      "  } catch LexerError x {",
      "    print(x.msg)",
      "  } catch ParserError x {",
      "    print(x.msg)",
      "  }",
      "}"
    );
    VM vm = buildVM(s);
    vm.run();
    assertEquals("parser error detected", output.toString());
  }

  @Test
  public void tryCatchWithNoThrow() throws Exception {
    String s = buildString(
      "type MyPLException {",
      "  var message = \"\"",
      "  var errorCode = 0",
      "}",
      "fun void main() {",
      "  try {}",
      "  catch MyPLException e {}",
      "}"
    );
    VM vm = buildVM(s);
    vm.run();
    assertEquals("", output.toString());
  }
}
