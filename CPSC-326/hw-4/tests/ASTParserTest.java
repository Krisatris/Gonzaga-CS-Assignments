/*
 * File: ASTParserTest.java
 * Date: Spring 2022
 * Auth: 
 * Desc: Basic unit tests for the MyPL ast-based parser class.
 */

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotEquals;
import static org.junit.Assert.fail;
import org.junit.Ignore;
import org.junit.Test;
import java.io.ByteArrayInputStream;
import java.io.InputStream;


public class ASTParserTest {

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
  public void emptyParse() throws Exception {
    ASTParser parser = buildParser("");
    Program p = parser.parse();
    assertEquals(0, p.tdecls.size());
    assertEquals(0, p.fdecls.size());
  }

  @Test
  public void oneTypeDeclInProgram() throws Exception {
    String s = buildString
      ("type Node {",
       "}");
    ASTParser parser = buildParser(s);
    Program p = parser.parse();
    assertEquals(1, p.tdecls.size());
    assertEquals(0, p.fdecls.size());
  }
  
  @Test
  public void oneFunDeclInProgram() throws Exception {
    String s = buildString
      ("fun void main() {",
       "}"
       );
    ASTParser parser = buildParser(s);
    Program p = parser.parse();
    assertEquals(0, p.tdecls.size());
    assertEquals(1, p.fdecls.size());
  }

  @Test
  public void multipleTypeAndFunDeclsInProgram() throws Exception {
    String s = buildString
      ("type T1 {}",
       "fun void F1() {}",
       "type T2 {}",
       "fun void F2() {}",
       "fun void main() {}");
    ASTParser parser = buildParser(s);
    Program p = parser.parse();
    assertEquals(2, p.tdecls.size());
    assertEquals(3, p.fdecls.size());
  }

  @Test
  public void assignStmtTest() throws Exception {
    String s = buildString
    ("fun void main() {",
     "  x = 10",
     "}"
    );
    ASTParser parser = buildParser(s);
    Program p = parser.parse();
    AssignStmt stmtNode = (AssignStmt)p.fdecls.get(0).stmts.get(0);
    assertEquals(TokenType.ID, stmtNode.lvalue.get(0).type());
    assertEquals("x", stmtNode.lvalue.get(0).lexeme());
    Expr exprNode = (Expr)stmtNode.expr;
    assertEquals(false, exprNode.logicallyNegated);
    assertEquals(null, exprNode.op);
    assertEquals(null, exprNode.rest);
    SimpleRValue r = (SimpleRValue)((SimpleTerm)exprNode.first).rvalue;
    assertEquals(TokenType.INT_VAL, r.value.type());
    assertEquals("10", r.value.lexeme());
  }

  @Test
  public void varDeclTest() throws Exception {
    String s = buildString
    ("fun void main() {",
     "  var int x = 10",
     "}"
    );
    ASTParser parser = buildParser(s);
    Program p = parser.parse();
    VarDeclStmt stmtNode = (VarDeclStmt)p.fdecls.get(0).stmts.get(0);
    assertEquals(TokenType.INT_TYPE, stmtNode.typeName.type());
    assertEquals("int", stmtNode.typeName.lexeme());
    assertEquals(TokenType.ID, stmtNode.varName.type());
    assertEquals("x", stmtNode.varName.lexeme());
    Expr exprNode = (Expr)stmtNode.expr;
    assertEquals(false, exprNode.logicallyNegated);
    assertEquals(null, exprNode.op);
    assertEquals(null, exprNode.rest);
    SimpleRValue r = (SimpleRValue)((SimpleTerm)exprNode.first).rvalue;
    assertEquals(TokenType.INT_VAL, r.value.type());
    assertEquals("10", r.value.lexeme());
  }

  @Test
  public void ifStmtTest() throws Exception {
    String s = buildString
    ("fun void main() {",
     "  if true {",
     "  }",
     "  elif x > 10 {",
     "  }",
     "  else {",
     "  }",
     "}"
    );
    ASTParser parser = buildParser(s);
    Program p = parser.parse();
    CondStmt stmtNode = (CondStmt)p.fdecls.get(0).stmts.get(0);

    //if
    BasicIf ifNode = (BasicIf)stmtNode.ifPart;
    Expr exprNode = (Expr)ifNode.cond;
    assertEquals(false, exprNode.logicallyNegated);
    assertEquals(null, exprNode.op);
    assertEquals(null, exprNode.rest);
    SimpleRValue r = (SimpleRValue)((SimpleTerm)exprNode.first).rvalue;
    assertEquals(TokenType.BOOL_VAL, r.value.type());
    assertEquals("true", r.value.lexeme());

    //elif
    ifNode = (BasicIf)stmtNode.elifs.get(0);
    exprNode = (Expr)ifNode.cond;
    assertEquals(false, exprNode.logicallyNegated);
    assertEquals(TokenType.GREATER_THAN, exprNode.op.type());
    assertEquals(">", exprNode.op.lexeme());
    IDRValue i = (IDRValue)((SimpleTerm)exprNode.first).rvalue;
    assertEquals(TokenType.ID, i.path.get(0).type());
    assertEquals("x", i.path.get(0).lexeme());
    exprNode = (Expr)ifNode.cond.rest;
    r = (SimpleRValue)((SimpleTerm)exprNode.first).rvalue;
    assertEquals(TokenType.INT_VAL, r.value.type());
    assertEquals("10", r.value.lexeme());

    //else
    assertNotEquals(null, stmtNode.elseStmts);
    assertEquals(0, stmtNode.elseStmts.size());
  }

  @Test
  public void forStmtTest() throws Exception {
    String s = buildString
    ("fun void main() {",
     "  for i from 0 upto 10 {",
     "  }",
     "}"
    );
    ASTParser parser = buildParser(s);
    Program p = parser.parse();
    ForStmt stmtNode = (ForStmt)p.fdecls.get(0).stmts.get(0);
    assertEquals(TokenType.ID, stmtNode.varName.type());
    assertEquals("i", stmtNode.varName.lexeme());
    assertEquals(true, stmtNode.upto);
    Expr exprNode = (Expr)stmtNode.start;
    assertEquals(false, exprNode.logicallyNegated);
    assertEquals(null, exprNode.op);
    assertEquals(null, exprNode.rest);
    SimpleRValue r = (SimpleRValue)((SimpleTerm)exprNode.first).rvalue;
    assertEquals(TokenType.INT_VAL, r.value.type());
    assertEquals("0", r.value.lexeme());
    exprNode = (Expr)stmtNode.end;
    assertEquals(false, exprNode.logicallyNegated);
    assertEquals(null, exprNode.op);
    assertEquals(null, exprNode.rest);
    r = (SimpleRValue)((SimpleTerm)exprNode.first).rvalue;
    assertEquals(TokenType.INT_VAL, r.value.type());
    assertEquals("10", r.value.lexeme());
  }

  @Test
  public void whileStmtTest() throws Exception {
    String s = buildString
    ("fun void main() {",
     "  while true {",
     "  }",
     "}"
    );
    ASTParser parser = buildParser(s);
    Program p = parser.parse();
    WhileStmt stmtNode = (WhileStmt)p.fdecls.get(0).stmts.get(0);
    assertEquals(0, stmtNode.stmts.size());
    Expr exprNode = (Expr)stmtNode.cond;
    assertEquals(false, exprNode.logicallyNegated);
    assertEquals(null, exprNode.op);
    assertEquals(null, exprNode.rest);
    SimpleRValue r = (SimpleRValue)((SimpleTerm)exprNode.first).rvalue;
    assertEquals(TokenType.BOOL_VAL, r.value.type());
    assertEquals("true", r.value.lexeme());
  }
}
