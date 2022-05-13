import java.lang.ProcessBuilder.Redirect.Type;
import java.util.ArrayList;
import java.util.List;

/* 
 * File: Parser.java
 * Date: Spring 2022
 * Auth: Linden Beemer
 * Desc: This file implements the beginnings of a parser for MyPL
 */


public class ASTParser {

  private Lexer lexer = null; 
  private Token currToken = null;
  private final boolean DEBUG = false;
  
  // constructor
  public ASTParser(Lexer lexer) {
    this.lexer = lexer;
  }

  // do the parse
  public Program parse() throws MyPLException
  {
    // <program> ::= (<tdecl> | <fdecl>)*
    Program progNode = new Program();
    advance();
    while (!match(TokenType.EOS)) {
      if (match(TokenType.TYPE))
        tdecl(progNode);
      else
        fdecl(progNode);
    }
    advance(); // eat the EOS token
    return progNode;
  }

  
  //------------------------------------------------------------ 
  // Helper Functions
  //------------------------------------------------------------

  // get next token
  private void advance() throws MyPLException {
    currToken = lexer.nextToken();
  }

  // advance if current token is of given type, otherwise error
  private void eat(TokenType t, String msg) throws MyPLException {
    if (match(t))
      advance();
    else
      error(msg);
  }

  // true if current token is of type t
  private boolean match(TokenType t) {
    return currToken.type() == t;
  }
  
  // throw a formatted parser error
  private void error(String msg) throws MyPLException {
    String s = msg + ", found '" + currToken.lexeme() + "' ";
    s += "at line " + currToken.line();
    s += ", column " + currToken.column();
    throw MyPLException.ParseError(s);
  }

  // output a debug message (if DEBUG is set)
  private void debug(String msg) {
    if (DEBUG)
      System.out.println("[debug]: " + msg);
  }

  // return true if current token is a (non-id) primitive type
  private boolean isPrimitiveType() {
    return match(TokenType.INT_TYPE) || match(TokenType.DOUBLE_TYPE) ||
      match(TokenType.BOOL_TYPE) || match(TokenType.CHAR_TYPE) ||
      match(TokenType.STRING_TYPE);
  }

  // return true if current token is a (non-id) primitive value
  private boolean isPrimitiveValue() {
    return match(TokenType.INT_VAL) || match(TokenType.DOUBLE_VAL) ||
      match(TokenType.BOOL_VAL) || match(TokenType.CHAR_VAL) ||
      match(TokenType.STRING_VAL);
  }
    
  // return true if current token starts an expression
  private boolean isExpr() {
    return match(TokenType.NOT) || match(TokenType.LPAREN) ||
      match(TokenType.NIL) || match(TokenType.NEW) ||
      match(TokenType.ID) || match(TokenType.NEG) ||
      match(TokenType.INT_VAL) || match(TokenType.DOUBLE_VAL) ||
      match(TokenType.BOOL_VAL) || match(TokenType.CHAR_VAL) ||
      match(TokenType.STRING_VAL);
  }

  private boolean isOperator() {
    return match(TokenType.PLUS) || match(TokenType.MINUS) ||
      match(TokenType.DIVIDE) || match(TokenType.MULTIPLY) ||
      match(TokenType.MODULO) || match(TokenType.AND) ||
      match(TokenType.OR) || match(TokenType.EQUAL) ||
      match(TokenType.LESS_THAN) || match(TokenType.GREATER_THAN) ||
      match(TokenType.LESS_THAN_EQUAL) || match(TokenType.GREATER_THAN_EQUAL) ||
      match(TokenType.NOT_EQUAL);
  }

  // helper function I wrote for <stmts>
  private boolean isStmt() {
    return match(TokenType.ID) || match(TokenType.VAR) || match(TokenType.IF) ||
      match(TokenType.WHILE) || match(TokenType.WHILE) || match(TokenType.FOR) ||
      match(TokenType.RETURN) || match(TokenType.DELETE);
  }

  
  //------------------------------------------------------------
  // Recursive Descent Functions 
  //------------------------------------------------------------

  private void tdecl(Program progNode) throws MyPLException {
    // <tdecl> ::= TYPE ID LBRACE <vdecls> RBRACE
    TypeDecl tDeclNode = new TypeDecl();
    eat(TokenType.TYPE, "expected type declaration");
    if(match(TokenType.ID)) {
      tDeclNode.typeName = currToken;
      advance();
    }
    else {
      error("expected identifier");
    }
    eat(TokenType.LBRACE, "expected left curly bracket");
    vdecls(tDeclNode);
    eat(TokenType.RBRACE, "expected right curly bracket");
    progNode.tdecls.add(tDeclNode);
  }

  private void vdecls(TypeDecl tDeclNode) throws MyPLException {
    //<vdecls> ::= ( <vdecl_stmt> )∗
    while(!match(TokenType.RBRACE)) {
      VarDeclStmt vDeclNode = new VarDeclStmt();
      vdecl_stmt(vDeclNode);
      tDeclNode.vdecls.add(vDeclNode);
    }
  }

  private void fdecl(Program progNode) throws MyPLException {
    // FUN ( <dtype> | VOID ) ID LPAREN <params> RPAREN LBRACE <stmts> RBRACE
    FunDecl fDeclNode = new FunDecl();
    eat(TokenType.FUN, "expected function declaration");
    if(isPrimitiveType() || match(TokenType.ID) || match(TokenType.VOID_TYPE)) { // <dtype> | void
      fDeclNode.returnType = currToken;
      advance();
    }
    else {
      error("expected return type (primitive value or type)");
    }
    if(match(TokenType.ID)) {
      fDeclNode.funName = currToken;
      advance();
    }
    else {
      error("expected function name");
    }
    eat(TokenType.LPAREN, "expected '('");
    params(fDeclNode);
    eat(TokenType.RPAREN, "expected ')'");
    eat(TokenType.LBRACE, "expected '{'");
    List<Stmt> stmtsNode = new ArrayList<>();
    while(isStmt()) {
      stmt(stmtsNode);
    }
    eat(TokenType.RBRACE, "expected '}'");
    fDeclNode.stmts = stmtsNode;
    progNode.fdecls.add(fDeclNode);
  }

  private void params(FunDecl fDeclNode) throws MyPLException {
    // <params> ::= <dtype> ID ( COMMA <dtype> ID )∗ | (empty)
    FunParam fParamNode = new FunParam();
    if(isPrimitiveType() || match(TokenType.ID)) { // <dtype>
      fParamNode.paramType = currToken;
      advance();
      if(match(TokenType.ID)) {
        fParamNode.paramName = currToken;
        advance();
      }
      else {
        error("expected parameter name");
      }
      fDeclNode.params.add(fParamNode);
      while(match(TokenType.COMMA)) {
        advance();
        if(isPrimitiveType() || match(TokenType.ID)) { // <dtype>
          fParamNode.paramType = currToken;
          advance();
        }
        else {
          error("expected type declaration");
        }
        if(match(TokenType.ID)) {
          fParamNode.paramName = currToken;
          advance();
        }
        else {
          error("expected parameter name");
        }
        fDeclNode.params.add(fParamNode);
      }
    }
  }

  private void stmt(List<Stmt> stmtsListNode) throws MyPLException {
    /* <stmt> ::= <vdecl_stmt> | <assign_stmt> | <cond_stmt> | 
    <while_stmt> | <for_stmt> | <call_expr> | <ret_stmt> | <delete_stmt> */
    if(match(TokenType.VAR)) {
      VarDeclStmt stmtNode = new VarDeclStmt();
      vdecl_stmt(stmtNode);
      stmtsListNode.add(stmtNode);
    }
    else if(match(TokenType.IF)) {
      CondStmt stmtNode = new CondStmt();
      cond_stmt(stmtNode);
      stmtsListNode.add(stmtNode);
    }
    else if(match(TokenType.WHILE)) {
      WhileStmt stmtNode = new WhileStmt();
      while_stmt(stmtNode);
      stmtsListNode.add(stmtNode);
    }
    else if(match(TokenType.FOR)) {
      ForStmt stmtNode = new ForStmt();
      for_stmt(stmtNode);
      stmtsListNode.add(stmtNode);
    }
    else if(match(TokenType.RETURN)) {
      ReturnStmt stmtNode = new ReturnStmt();
      ret_stmt(stmtNode);
      stmtsListNode.add(stmtNode);
    }
    else if(match(TokenType.DELETE)) {
      DeleteStmt stmtNode = new DeleteStmt();
      delete_stmt(stmtNode);
      stmtsListNode.add(stmtNode);
    }
    else if(match(TokenType.ID)) {
      Token temp = currToken;
      advance();
      if(match(TokenType.DOT) || match(TokenType.ASSIGN)) { // <assign_stmt>
        AssignStmt stmtNode = new AssignStmt();
        stmtNode.lvalue.add(temp);
        if(match(TokenType.DOT)) { // finish <lvalue>
          advance();
          if(match(TokenType.ID)) {
            stmtNode.lvalue.add(currToken);
            advance();
          }
          else {
            error("expected identifier");
          }
          while(match(TokenType.DOT)) {
            advance();
            if(match(TokenType.ID)) {
              stmtNode.lvalue.add(currToken);
              advance();
            }
            else {
              error("expected identifier");
            }
          }
        }
        eat(TokenType.ASSIGN, "expected assignment");
        Expr exprNode = new Expr();
        expr(exprNode);
        stmtNode.expr = exprNode;
        stmtsListNode.add(stmtNode);
      }
      else if(match(TokenType.LPAREN)) { // <call_expr>
        CallExpr stmtNode = new CallExpr();
        stmtNode.funName = temp;
        advance();
        if(isExpr()) { // <args>
          Expr exprNode = new Expr();
          expr(exprNode);
          stmtNode.args.add(exprNode);
          while(match(TokenType.COMMA)) {
            advance();
            expr(exprNode);
            stmtNode.args.add(exprNode);
          }
        }
        eat(TokenType.RPAREN, "expected ')");
        stmtsListNode.add(stmtNode);
      }
    }
  }

  private void vdecl_stmt(VarDeclStmt vDeclNode) throws MyPLException {
    // <vdecl_stmt> ::= VAR ( <dtype> | (empty) ) ID ASSIGN <expr>
    Expr exprNode = new Expr();
    eat(TokenType.VAR, "expected var keyword");
    if(isPrimitiveType() || match(TokenType.ID)) {
      vDeclNode.typeName = currToken;
      advance();
    }
    if(match(TokenType.ID)) {
      vDeclNode.varName = currToken;
      advance();
      eat(TokenType.ASSIGN, "expected assignment");
      expr(exprNode);
      vDeclNode.expr = exprNode;
    } 
    else if(match(TokenType.ASSIGN)) {
      vDeclNode.varName = vDeclNode.typeName; // implicit declaration, replace varName w/typeName
      vDeclNode.typeName = null;              // make typeName null
      advance();
      expr(exprNode);
      vDeclNode.expr = exprNode;
    } 
    else {
      error("expected identifier or assignment");
    }
  }

  private void cond_stmt(CondStmt cStmtNode) throws MyPLException {
    // <cond_stmt> ::= IF <expr> LBRACE <stmts> RBRACE <condt>
    eat(TokenType.IF, "expecting if statement");
    BasicIf ifNode = new BasicIf();
    Expr condNode = new Expr();
    expr(condNode);
    ifNode.cond = condNode;
    eat(TokenType.LBRACE, "expected '{");
    List<Stmt> stmtsNode = new ArrayList<>();
    while(isStmt()) {
      stmt(stmtsNode);
    }
    eat(TokenType.RBRACE, "expected '}");
    ifNode.stmts = stmtsNode;
    cStmtNode.ifPart = ifNode;
    condt(cStmtNode);
  }

  private void condt(CondStmt cStmtNode) throws MyPLException {
    // <condt> ::= ELIF <expr> LBRACE <stmts> RBRACE <condt> | ELSE LBRACE <stmts> RBRACE | (empty)
    if(match(TokenType.ELIF)) {
      BasicIf ifNode = new BasicIf();
      Expr condNode = new Expr();
      advance();
      expr(condNode);
      ifNode.cond = condNode;
      eat(TokenType.LBRACE, "expected '{'");
      List<Stmt> stmtsNode = new ArrayList<>();
      while(isStmt()) {
        stmt(stmtsNode);
      }
      eat(TokenType.RBRACE, "expected '}'");
      ifNode.stmts = stmtsNode;
      cStmtNode.elifs.add(ifNode);
      condt(cStmtNode);
    }
    else if(match(TokenType.ELSE)) {
      advance();
      eat(TokenType.LBRACE, "expected '{'");
      List<Stmt> elseNode = new ArrayList<>();
      while(isStmt()) {
        stmt(elseNode);
      }
      eat(TokenType.RBRACE, "expected '}'");
      cStmtNode.elseStmts = elseNode;
    }
  }

  private void while_stmt(WhileStmt wStmtNode) throws MyPLException {
    // <while_stmt> ::= WHILE <expr> LBRACE <stmts> RBRACE
    eat(TokenType.WHILE, "expected while statement declaration");
    Expr condNode = new Expr();
    expr(condNode);
    wStmtNode.cond = condNode;
    eat(TokenType.LBRACE, "expected '{'");
    List<Stmt> stmtsNode = new ArrayList<>();
    while(isStmt()) {
      stmt(stmtsNode);
    }
    eat(TokenType.RBRACE, "expected '}'");
    wStmtNode.stmts = stmtsNode;
  }

  private void for_stmt(ForStmt fStmtNode) throws MyPLException {
    // <for_stmt> ::= FOR ID FROM <expr> ( UPTO | DOWNTO ) <expr> LBRACE <stmts> RBRACE
    eat(TokenType.FOR, "expected for statement declaration");
    if(match(TokenType.ID)) {
      fStmtNode.varName = currToken;
      advance();
    }
    eat(TokenType.FROM, "expected from keyword");
    Expr startNode = new Expr();
    expr(startNode);
    fStmtNode.start = startNode;
    if(match(TokenType.UPTO)) {
      fStmtNode.upto = true;
      advance();
    }
    else if(match(TokenType.DOWNTO)) {
      fStmtNode.upto = false;
      advance();
    }
    else {
      error("expected upto or downto keyword");
    }
    Expr endNode = new Expr();
    expr(endNode);
    fStmtNode.end = endNode;
    eat(TokenType.LBRACE, "expected '{'");
    List<Stmt> stmtsNode = new ArrayList<>();
    while(isStmt()) {
      stmt(stmtsNode);
    }
    eat(TokenType.RBRACE, "expected '}'");
    fStmtNode.stmts = stmtsNode;
  }

  private void ret_stmt(ReturnStmt rStmtNode) throws MyPLException {
    // <ret_stmt> ::= RETURN ( <expr> | (empty) )
    eat(TokenType.RETURN, "expecting return keyword");
    Expr exprNode = new Expr();
    if(isExpr()) {
      expr(exprNode);
    }
    rStmtNode.expr = exprNode;
  }

  private void delete_stmt(DeleteStmt dStmtNode) throws MyPLException {
    // <delete_stmt> ::= DELETE ID
    eat(TokenType.DELETE, "expected delete keyword");
    if(match(TokenType.ID)) {
      dStmtNode.varName = currToken;
      advance();
    }
    else {
      error("expected identifier");
    }
  }

  private void expr(Expr exprNode) throws MyPLException {
    // <expr> ::= ( <rvalue> | NOT <expr> | LPAREN <expr> RPAREN ) ( <operator> <expr> | (empty) )
    if(!isExpr()) { // error out immediately if expression is not passed in
      error("expected expression");
    }

    if(match(TokenType.NOT)) { // NOT <expr>
      exprNode.logicallyNegated = true;
      ComplexTerm cTermNode = new ComplexTerm();
      advance();
      Expr cExprNode = new Expr();
      expr(cExprNode);
      cTermNode.expr = cExprNode;
      exprNode.first = cTermNode;
    } 
    else if(match(TokenType.LPAREN)) { // LPAREN <expr> RPAREN
      ComplexTerm cTermNode = new ComplexTerm();
      advance();
      Expr cExprNode = new Expr();
      expr(cExprNode);
      eat(TokenType.RPAREN, "expected ')");
      cTermNode.expr = cExprNode;
      exprNode.first = cTermNode;
    } 
    else { // <rvalue>
      SimpleTerm sTermNode = new SimpleTerm();
      rvalue(sTermNode);
      exprNode.first = sTermNode;
    }

    if(isOperator()) {
      exprNode.op = currToken;
      advance();
      Expr restExprNode = new Expr();
      expr(restExprNode);
      exprNode.rest = restExprNode;
    }
  }

  private void rvalue(SimpleTerm sTermNode) throws MyPLException {
    // <rvalue> ::= <pval> | NIL | NEW ID | <idrval> | <call_expr> | NEG <expr>
    if(match(TokenType.NIL)) { // NIL
      SimpleRValue rValNode = new SimpleRValue();
      rValNode.value = currToken;
      advance();
      sTermNode.rvalue = rValNode;
    } 
    else if(match(TokenType.NEW)) { // NEW ID
      advance();
      NewRValue rValNode = new NewRValue();
      if(match(TokenType.ID)) {
        rValNode.typeName = currToken;
        advance();
      }
      else {
        error("expected identifier");
      }
      sTermNode.rvalue = rValNode;
    } 
    else if(match(TokenType.NEG)) { // NEG <expr>
      advance();
      NegatedRValue rValNode = new NegatedRValue();
      Expr negExprNode = new Expr();
      expr(negExprNode);
      rValNode.expr = negExprNode;
      sTermNode.rvalue = rValNode;
    } 
    else if(isPrimitiveValue()) { // <pval>
      SimpleRValue rValNode = new SimpleRValue();
      rValNode.value = currToken;
      advance();
      sTermNode.rvalue = rValNode;
    } 
    else if(match(TokenType.ID)) { 
      Token temp = currToken;
      advance(); 
      if(match(TokenType.LPAREN)) { // <call_expr>
        CallExpr rValNode = new CallExpr();
        rValNode.funName = temp;
        advance();
        if(isExpr()) { // <args>
          Expr callExprNode = new Expr();
          expr(callExprNode);
          rValNode.args.add(callExprNode);
          while(match(TokenType.COMMA)) {
            Expr newExprNode = new Expr();
            advance();
            expr(newExprNode);
            rValNode.args.add(newExprNode);
          }
        }
        eat(TokenType.RPAREN, "expected ')");
        sTermNode.rvalue = rValNode;
      }
      else { // <idrval>
        IDRValue rValNode = new IDRValue();
        rValNode.path.add(temp);
        /*
        advance();
        if(match(TokenType.ID)) {
          rValNode.path.add(currToken);
          advance();
        }
        else {
          error("expected identifier");
        }
        */
        while(match(TokenType.DOT)) {
          advance();
          if(match(TokenType.ID)) {
            rValNode.path.add(currToken);
            advance();
          }
          else {
            error("expected identifier");
          }
        }
        sTermNode.rvalue = rValNode;
      }
    } else {
      error("expected nil, new, neg, or primitive value");
    }
  }
}
