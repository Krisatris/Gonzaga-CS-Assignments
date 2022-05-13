/* 
 * File: Parser.java
 * Date: Spring 2022
 * Auth: Linden Beemer
 * Desc: This file implements the beginnings of a parser for MyPL
 */


public class Parser {

  private Lexer lexer = null; 
  private Token currToken = null;
  private final boolean DEBUG = false;
  
  // constructor
  public Parser(Lexer lexer) {
    this.lexer = lexer;
  }

  // do the parse
  public void parse() throws MyPLException
  {
    // <program> ::= (<tdecl> | <fdecl>)*
    advance();
    while (!match(TokenType.EOS)) {
      if (match(TokenType.TYPE))
        tdecl();
      else
        fdecl();
    }
    advance(); // eat the EOS token
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

  private void tdecl() throws MyPLException {
    // <tdecl> ::= TYPE ID LBRACE <vdecls> RBRACE
    eat(TokenType.TYPE, "expected type declaration");
    eat(TokenType.ID, "expected variable declaration");
    eat(TokenType.LBRACE, "expected left curly bracket");
    vdecls();
    eat(TokenType.RBRACE, "expected right curly bracket");
  }

  private void vdecls() throws MyPLException {
    //<vdecls> ::= ( <vdecl_stmt> )∗
    while(!match(TokenType.RBRACE)) {
      vdecl_stmt();
    }
  }

  private void fdecl() throws MyPLException {
    // FUN ( <dtype> | VOID ) ID LPAREN <params> RPAREN LBRACE <stmts> RBRACE
    eat(TokenType.FUN, "expected function declaration");
    if(isPrimitiveType() || match(TokenType.ID) || match(TokenType.VOID_TYPE)) { // <dtype> | void
      advance();
    }
    else {
      error("expected type declaration");
    }
    eat(TokenType.ID, "expected identifier");
    eat(TokenType.LPAREN, "expected '('");
    params();
    eat(TokenType.RPAREN, "expected ')'");
    eat(TokenType.LBRACE, "expected '{'");
    while(isStmt()) {
      stmt();
    }
    eat(TokenType.RBRACE, "expected '}'");
  }

  private void params() throws MyPLException {
    // <params> ::= <dtype> ID ( COMMA <dtype> ID )∗ | (empty)
    if(isPrimitiveType() || match(TokenType.ID)) { // <dtype>
      advance();
      eat(TokenType.ID, "expected identifier");
      while(match(TokenType.COMMA)) {
        advance();
        if(isPrimitiveType() || match(TokenType.ID)) { // <dtype>
          advance();
        }
        else {
          error("expected type declaration");
        }
        eat(TokenType.ID, "expected identifier");
      }
    }
  }

  /*
  private void dtype() throws MyPLException {
    if(isPrimitiveType() || match(TokenType.ID)) {
      advance();
    }
    else {
      error("expected type declaration");
    }
  }
  */

  private void stmt() throws MyPLException {
    /* <stmt> ::= <vdecl_stmt> | <assign_stmt> | <cond_stmt> | 
    <while_stmt> | <for_stmt> | <call_expr> | <ret_stmt> | <delete_stmt> */
    if(match(TokenType.VAR)) {
      vdecl_stmt();
    }
    else if(match(TokenType.IF)) {
      cond_stmt();
    }
    else if(match(TokenType.WHILE)) {
      while_stmt();
    }
    else if(match(TokenType.FOR)) {
      for_stmt();
    }
    else if(match(TokenType.RETURN)) {
      ret_stmt();
    }
    else if(match(TokenType.DELETE)) {
      delete_stmt();
    }
    else if(match(TokenType.ID)) {
      advance();
      if(match(TokenType.DOT) || match(TokenType.ASSIGN)) { // <assign_stmt>
        if(match(TokenType.DOT)) { // finish <lvalue>
          advance();
          eat(TokenType.ID, "expected identifier");
          while(match(TokenType.DOT)) {
            advance();
            eat(TokenType.ID, "expected identifier");
          }
        }
        eat(TokenType.ASSIGN, "expected assignment");
        expr();
      }
      else if(match(TokenType.LPAREN)) { // <call_expr>
        advance();
        if(isExpr()) { // <args>
          expr();
          while(match(TokenType.COMMA)) {
            advance();
            expr();
          }
        }
        eat(TokenType.RPAREN, "expected ')");
      }
    }
  }

  private void vdecl_stmt() throws MyPLException {
    // <vdecl_stmt> ::= VAR ( <dtype> | (empty) ) ID ASSIGN <expr>
    eat(TokenType.VAR, "expecteed var keyword");
    if(isPrimitiveType() || match(TokenType.ID)) {
      advance();
    }
    if(match(TokenType.ID)) {
      advance();
      eat(TokenType.ASSIGN, "expected assignment");
      expr();
    } 
    else if(match(TokenType.ASSIGN)) {
      advance();
      expr();
    } 
    else {
      error("expected identifier or assignment");
    }
  }

  private void cond_stmt() throws MyPLException {
    // <cond_stmt> ::= IF <expr> LBRACE <stmts> RBRACE <condt>
    eat(TokenType.IF, "expecting if statement");
    expr();
    eat(TokenType.LBRACE, "expected '{");
    while(isStmt()) {
      stmt();
    }
    eat(TokenType.RBRACE, "expected '}");
    condt();
  }

  private void condt() throws MyPLException {
    // <condt> ::= ELIF <expr> LBRACE <stmts> RBRACE <condt> | ELSE LBRACE <stmts> RBRACE | (empty)
    if(match(TokenType.ELIF)) {
      advance();
      expr();
      eat(TokenType.LBRACE, "expected '{'");
      while(isStmt()) {
        stmt();
      }
      eat(TokenType.RBRACE, "expected '}'");
      condt();
    }
    else if(match(TokenType.ELSE)) {
      advance();
      eat(TokenType.LBRACE, "expected '{'");
      while(isStmt()) {
        stmt();
      }
      eat(TokenType.RBRACE, "expected '}'");
    }
  }

  private void while_stmt() throws MyPLException {
    // <while_stmt> ::= WHILE <expr> LBRACE <stmts> RBRACE
    eat(TokenType.WHILE, "expected while statement declaration");
    expr();
    eat(TokenType.LBRACE, "expected '{'");
    while(isStmt()) {
      stmt();
    }
    eat(TokenType.RBRACE, "expected '}'");
  }

  private void for_stmt() throws MyPLException {
    // <for_stmt> ::= FOR ID FROM <expr> ( UPTO | DOWNTO ) <expr> LBRACE <stmts> RBRACE
    eat(TokenType.FOR, "expected for statement declaration");
    eat(TokenType.ID, "expected identifier");
    eat(TokenType.FROM, "expected from keyword");
    expr();
    if(match(TokenType.UPTO) || match(TokenType.DOWNTO)) {
      advance();
    }
    else {
      error("expected upto or downto keyword");
    }
    expr();
    eat(TokenType.LBRACE, "expected '{'");
    while(isStmt()) {
      stmt();
    }
    eat(TokenType.RBRACE, "expected '}'");
  }

  private void ret_stmt() throws MyPLException {
    // <ret_stmt> ::= RETURN ( <expr> | (empty) )
    eat(TokenType.RETURN, "expecting return keyword");
    if(isExpr()) {
      expr();
    }
  }

  private void delete_stmt() throws MyPLException {
    // <delete_stmt> ::= DELETE ID
    eat(TokenType.DELETE, "expected delete keyword");
    eat(TokenType.ID, "expected identifier");
  }

  private void expr() throws MyPLException {
    // <expr> ::= ( <rvalue> | NOT <expr> | LPAREN <expr> RPAREN ) ( <operator> <expr> | (empty) )
    if(!isExpr()) { // error out immediately if expression is not passed in
      error("expected expression");
    }

    if(match(TokenType.NOT)) { // NOT <expr>
      advance();
      expr();
    } 
    else if(match(TokenType.LPAREN)) { // LPAREN <expr> RPAREN
      advance();
      expr();
      eat(TokenType.RPAREN, "expected ')");
    } 
    else { // <rvalue>
      rvalue();
    }

    if(isOperator()) {
      advance();
      expr();
    }
  }

  private void rvalue() throws MyPLException {
    // <rvalue> ::= <pval> | NIL | NEW ID | <idrval> | <call_expr> | NEG <expr>
    if(match(TokenType.NIL)) { // NIL
      advance();
    } 
    else if(match(TokenType.NEW)) { // NEW ID
      advance();
      eat(TokenType.ID, "expected ID");
    } 
    else if(match(TokenType.NEG)) { // NEG <expr>
      advance();
      expr();
    } else if(isPrimitiveValue()) { // <pval>
      advance();
    } else if(match(TokenType.ID)) { 
      advance();
      if(match(TokenType.DOT)) { // <idrval>
        advance();
        eat(TokenType.ID, "expected identifier");
        while(match(TokenType.DOT)) {
          advance();
          eat(TokenType.ID, "expected identifier");
        }
      } 
      else if(match(TokenType.LPAREN)) { // <call_expr>
        advance();
        if(isExpr()) { // <args>
          expr();
          while(match(TokenType.COMMA)) {
            advance();
            expr();
          }
        }
        eat(TokenType.RPAREN, "expected ')");
      }
    } else {
      error("expected nil, new, neg, or primitive value");
    }
  }
  
}
