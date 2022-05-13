/*
 * File: StaticChecker.java
 * Date: Spring 2022
 * Auth: Linden Beemer
 * Desc: 
 */

import java.util.Arrays;
import java.util.ArrayList;
import java.util.List;
import java.util.Set;


// NOTE: Some of the following are filled in, some partly filled in,
// and most left for you to fill in. The helper functions are provided
// for you to use as needed. 


public class StaticChecker implements Visitor {

  // the symbol table
  private SymbolTable symbolTable = new SymbolTable();
  // the current expression type
  private String currType = null;
  // the program's user-defined (record) types and function signatures
  private TypeInfo typeInfo = null;

  //--------------------------------------------------------------------
  // helper functions:
  //--------------------------------------------------------------------
  
  // generate an error
  private void error(String msg, Token token) throws MyPLException {
    String s = msg;
    if (token != null)
      s += " near line " + token.line() + ", column " + token.column();
    throw MyPLException.StaticError(s);
  }

  // return all valid types
  // assumes user-defined types already added to symbol table
  private List<String> getValidTypes() {
    List<String> types = new ArrayList<>();
    types.addAll(Arrays.asList("int", "double", "bool", "char", "string",
                               "void"));
    for (String type : typeInfo.types())
      if (symbolTable.get(type).equals("type"))
        types.add(type);
    return types;
  }

  // return the build in function names
  private List<String> getBuiltinFunctions() {
    return Arrays.asList("print", "read", "length", "get", "stoi",
                         "stod", "itos", "itod", "dtos", "dtoi");
  }
  
  // check if given token is a valid function signature return type
  private void checkReturnType(Token typeToken) throws MyPLException {
    if (!getValidTypes().contains(typeToken.lexeme())) {
      String msg = "'" + typeToken.lexeme() + "' is an invalid return type";
      error(msg, typeToken);
    }
  }

  // helper to check if the given token is a valid parameter type
  private void checkParamType(Token typeToken) throws MyPLException {
    if (typeToken.equals("void"))
      error("'void' is an invalid parameter type", typeToken);
    else if (!getValidTypes().contains(typeToken.lexeme())) {
      String msg = "'" + typeToken.lexeme() + "' is an invalid return type";
      error(msg, typeToken);
    }
  }

  
  // helpers to get first token from an expression for calls to error
  
  private Token getFirstToken(Expr expr) {
    return getFirstToken(expr.first);
  }

  private Token getFirstToken(ExprTerm term) {
    if (term instanceof SimpleTerm)
      return getFirstToken(((SimpleTerm)term).rvalue);
    else
      return getFirstToken(((ComplexTerm)term).expr);
  }

  private Token getFirstToken(RValue rvalue) {
    if (rvalue instanceof SimpleRValue)
      return ((SimpleRValue)rvalue).value;
    else if (rvalue instanceof NewRValue)
      return ((NewRValue)rvalue).typeName;
    else if (rvalue instanceof IDRValue)
      return ((IDRValue)rvalue).path.get(0);
    else if (rvalue instanceof CallExpr)
      return ((CallExpr)rvalue).funName;
    else 
      return getFirstToken(((NegatedRValue)rvalue).expr);
  }

  
  //---------------------------------------------------------------------
  // constructor
  //--------------------------------------------------------------------
  
  public StaticChecker(TypeInfo typeInfo) {
    this.typeInfo = typeInfo;
  }
  

  //--------------------------------------------------------------------
  // top-level nodes
  //--------------------------------------------------------------------
  
  public void visit(Program node) throws MyPLException {
    // push the "global" environment
    symbolTable.pushEnvironment();

    // (1) add each user-defined type name to the symbol table and to
    // the list of rec types, check for duplicate names
    for (TypeDecl tdecl : node.tdecls) {
      String t = tdecl.typeName.lexeme();
      if (symbolTable.nameExists(t))
        error("type '" + t + "' already defined", tdecl.typeName);
      // add as a record type to the symbol table
      symbolTable.add(t, "type");
      // add initial type info (rest added by TypeDecl visit function)
      typeInfo.add(t);
    }
    
    // TODO: (2) add each function name and signature to the symbol
    // table check for duplicate names
    for (FunDecl fdecl : node.fdecls) {
      String funName = fdecl.funName.lexeme();
      // make sure not redefining built-in functions
      if (getBuiltinFunctions().contains(funName)) {
        String m = "cannot redefine built in function " + funName;
        error(m, fdecl.funName);
      }
      // check if function already exists
      if (symbolTable.nameExists(funName))
        error("function '" + funName + "' already defined", fdecl.funName);

      // TODO: Build the function param names and signature.

      // make sure the return type is a valid type
      checkReturnType(fdecl.returnType);
      // add to the symbol table as a function
      symbolTable.add(funName, "fun");
      // add to typeInfo
      typeInfo.add(funName);
      // add params
      for(FunParam fparam : fdecl.params) {
        // check if param is a duplicate
        List<String> currTypes = new ArrayList<>(typeInfo.components(funName));
        for(int i = 0; i < currTypes.size(); ++i) {
          if(currTypes.get(i).equals(fparam.paramName.lexeme())) {
            error("functions cannot have duplicate parameters", fdecl.funName);
          }
        }
        // add param if it's not duplicate
        typeInfo.add(funName, fparam.paramName.lexeme(), fparam.paramType.lexeme());
      }

      // TODO: add each formal parameter as a component type

      // add the return type
      typeInfo.add(funName, "return", fdecl.returnType.lexeme());
    }
    
    // TODO: (3) ensure "void main()" defined and it has correct
    // signature
    Token mainError = new Token(null, currType, 0, 0);
    if(!symbolTable.nameExists("main")) {
      String m = "main function not defined in file";
      error(m, mainError);
    }

    List<String> params = new ArrayList<>(typeInfo.components("main"));
    if(params.size() != 1) {
      String m = "main function should not have parameters";
      error(m, mainError);
    }

    String paramType = typeInfo.get("main", "return");
    if(!paramType.equals("void")) {
      error("main function must have return type void", mainError);
    }
    
    // check each type and function
    for (TypeDecl tdecl : node.tdecls) 
      tdecl.accept(this);
    for (FunDecl fdecl : node.fdecls) 
      fdecl.accept(this);

    // all done, pop the global table
    symbolTable.popEnvironment();
  }
  

  public void visit(TypeDecl node) throws MyPLException {
    // create type decl environment
    symbolTable.pushEnvironment();
    for(VarDeclStmt vdecl : node.vdecls) {
      vdecl.accept(this);
      // vdecl has been type checked, so add it to typeInfo for this node
      typeInfo.add(node.typeName.lexeme(), vdecl.varName.lexeme(), currType);
    }
    symbolTable.popEnvironment();
  }

  
  public void visit(FunDecl node) throws MyPLException {
    // create function decl environment
    currType = "void";
    boolean returned = false;
    symbolTable.pushEnvironment();

    // add params to the environment
    List<String> params = new ArrayList<>(typeInfo.components(node.funName.lexeme()));
    String paramName = "";
    String paramType = "";
    for(int i = 0; i < params.size() - 1; ++i) {
      paramName = params.get(i);
      paramType = typeInfo.get(node.funName.lexeme(), paramName);
      symbolTable.add(paramName, paramType);
    }

    // check stmts
    for(Stmt stmtNode : node.stmts) {
      if(stmtNode instanceof ReturnStmt) {
        returned = true;
      }
      stmtNode.accept(this);
    }

    // check return type
    String returnType = typeInfo.get(node.funName.lexeme(), "return");
    if(returned) {
      if(!returnType.equals(currType) && !currType.equals("void")) {
        String m = "returned value does not match function return type " + node.funName.lexeme();
        error(m, node.funName);
      }
    }
    symbolTable.popEnvironment();
  }


  //--------------------------------------------------------------------
  // statement nodes
  //--------------------------------------------------------------------
  
  public void visit(VarDeclStmt node) throws MyPLException {
    // type check expr and remember it
    node.expr.accept(this);
    String exprType = currType;
    String varName = node.varName.lexeme();

    // check for shadowing
    if(symbolTable.nameExistsInCurrEnv(varName)) {
      error("variable redefined", node.varName);
    }

    // implicit definitions
    if(node.typeName == null) {
      if(exprType.equals("void")) {
        error("bad implicit variable declaration", node.varName);
      }
    }
    else { // explicit definitions
      if(!node.typeName.lexeme().equals(exprType) && !exprType.equals("void")) {
        String m = "expected " + node.typeName.lexeme() + ", found " + exprType;
        error(m, node.varName);
      }
    }

    // check for type or function
    if(!exprType.equals("int") && !exprType.equals("double") && !exprType.equals("char") && !exprType.equals("bool") &&
        !exprType.equals("string") && !exprType.equals("void") && !(node.expr.first instanceof NewRValue)) {
      if(node.expr.first instanceof SimpleTerm) {
        SimpleTerm s = (SimpleTerm)node.expr.first;
        if(!(s.rvalue instanceof NewRValue)) {
          if(s.rvalue instanceof IDRValue) {
            IDRValue i = (IDRValue)s.rvalue;
            if(i.path.size() < 2) {
              error("expecting variable, path, or new", getFirstToken(node.expr));
            }
          }
          else {
            error("expecting variable, path, or new", getFirstToken(node.expr));
          }
        }
      } 
      else {
        error("expecting variable", getFirstToken(node.expr));
      }
    }

    // add to symbol table if no errors
    if(exprType.equals("void")) {
      symbolTable.add(node.varName.lexeme(), node.typeName.lexeme());
      currType = node.typeName.lexeme();
    }
    else {
      symbolTable.add(node.varName.lexeme(), exprType);
    }

  }
  

  public void visit(AssignStmt node) throws MyPLException {
    node.expr.accept(this);
    String rhsType = currType;

    // get the first var
    String varName = node.lvalue.get(0).lexeme();
    //check that the variable is defined
    if (!symbolTable.nameExists(varName)) {
      String m = varName + " is not defined" ;
      error(m, node.lvalue.get(0));
    }
    // get the left - hand side type
    String lhsType = symbolTable.get(varName);

    // check for more complex paths
    if(node.lvalue.size() > 1) {
      for(int i = 1; i < node.lvalue.size(); ++i) {
        // check that the variable is a UDT
        if(!symbolTable.get(lhsType).equals("type")) {
          String m = lhsType + " is not an object variable";
          error(m, node.lvalue.get(i - 1));
        }
        // get components of current lhsType
        Set<String> components = typeInfo.components(lhsType);

        // check it's a valid field
        varName = node.lvalue.get(i).lexeme();
        if(!components.contains(varName)) {
          String m = "objects of type " + lhsType + " do not have field " + varName;
          error(m, node.lvalue.get(i - 1));
        }
        else {
          lhsType = typeInfo.get(lhsType, varName);
        }
      }
    }
    if(!rhsType.equals(lhsType) && !rhsType.equals("void")) {
      String m = "type " + lhsType + " is not compatible with type " + rhsType;
      error(m, node.lvalue.get(0));
    }
  }
  
  
  public void visit(CondStmt node) throws MyPLException {
    BasicIf ifNode = node.ifPart;
    ifNode.cond.accept(this);
    if(!currType.equals("bool")) {
      error("expression must resolve to boolean", getFirstToken(ifNode.cond));
    }
    symbolTable.pushEnvironment();
    for(Stmt stmtNode : ifNode.stmts) {
      stmtNode.accept(this);
    }
    symbolTable.popEnvironment();

    // do the same for else if
    for(BasicIf elifNode : node.elifs) {
      elifNode.cond.accept(this);
      if(!currType.equals("bool")) {
        error("expression must resolve to boolean", getFirstToken(elifNode.cond));
      }
      symbolTable.pushEnvironment();
      for(Stmt elifStmt : elifNode.stmts) {
        elifStmt.accept(this);
      }
      symbolTable.popEnvironment();
    }

    // check the else stmts
    symbolTable.pushEnvironment();
    if(node.elseStmts != null) {
      for(Stmt elseStmt : node.elseStmts) {
        elseStmt.accept(this);
      }
    }
    symbolTable.popEnvironment();
  }
  

  public void visit(WhileStmt node) throws MyPLException {
    node.cond.accept(this);
    if(!currType.equals("bool")) {
      error("expression must resolve to boolean", getFirstToken(node.cond));
    }
    symbolTable.pushEnvironment();
    for(Stmt stmtNode : node.stmts) {
      stmtNode.accept(this);
    }
    symbolTable.popEnvironment();
  }
  

  public void visit(ForStmt node) throws MyPLException {
    // check that for var hasn't already been declared in current environment
    /*
    if(symbolTable.nameExistsInCurrEnv(node.varName.lexeme())) {
      String m = "variable " + node.varName.lexeme() + " has already been declared";
      error(m, node.varName);
    }
    */
    symbolTable.pushEnvironment();

    // ensure start and end are of int_type
    node.start.accept(this);
    if(!currType.equals("int")) {
      error("starting variable is not of type int", node.varName);
    }
    node.end.accept(this);
    if(!currType.equals("int")) {
      error("ending variable is not of type int", node.varName);
    }

    // if everything passes its okay to add var to environment as int type
    symbolTable.add(node.varName.lexeme(), "int");

    // visit stmts
    for(Stmt stmtNode : node.stmts) {
      stmtNode.accept(this);
    }
    symbolTable.popEnvironment();
  }
  
  
  public void visit(ReturnStmt node) throws MyPLException {
    // set up currType to have the return stmt type in it
    node.expr.accept(this);
  }
  
  public void visit(DeleteStmt node) throws MyPLException {
    // check that var to be deleted was defined
    String varName = node.varName.lexeme();
    if(!symbolTable.nameExistsInCurrEnv(varName)) {
      error("variable " + varName + " is not defined", node.varName);
    }
    // check that var is a UDT
    if(!symbolTable.get(varName).equals("type")) {
      error(varName + " is not a user-defined type", node.varName);
    }
    String typeName = symbolTable.get(varName);
    Set<String> types = typeInfo.types();
    if(!types.contains(typeName)) {
      error("variable " + " is not a user-defined type", node.varName);
    }
  }
  

  //----------------------------------------------------------------------
  // statement and rvalue node
  //----------------------------------------------------------------------

  private void checkBuiltIn(CallExpr node) throws MyPLException {
    String funName = node.funName.lexeme();
    if (funName.equals("print")) {
      node.args.get(0).accept(this);
      // has to have one argument, any type is allowed
      if (node.args.size() != 1)
        error("print expects one argument", node.funName);
      currType = "void";
    }
    else if (funName.equals("read")) {
      // no arguments allowed
      if (node.args.size() != 0)
        error("read takes no arguments", node.funName);
      currType = "string";
    }
    else if (funName.equals("length")) {
      // one string argument
      if (node.args.size() != 1)
        error("length expects one argument", node.funName);
      Expr e = node.args.get(0);
      e.accept(this);
      if (!currType.equals("string"))
        error("expecting string in length", getFirstToken(e));
      currType = "int";
    }
    else if (funName.equals("get")) {
      // two args, one int one string
      if(node.args.size() != 2) {
        error("get expects two arguments", node.funName);
      }
      Expr e = node.args.get(0);
      e.accept(this);
      if(!currType.equals("int")) {
        error("get expects first argument to be of type int", node.funName);
      }
      e = node.args.get(1);
      e.accept(this);
      if(!currType.equals("string")) {
        error("get expectes second argument to be of type string", node.funName);
      }
      currType = "char";
    }
    else if (funName.equals("stoi")) {
      // one string argument
      if(node.args.size() != 1) {
        error("stoi expects one argument", node.funName);
      }
      Expr e = node.args.get(0);
      e.accept(this);
      if (!currType.equals("string")) {
        error("expecting string in stoi", getFirstToken(e));
      }
      currType = "int";
    }
    else if (funName.equals("stod")) {
      // one string argument
      if(node.args.size() != 1) {
        error("stod expects one argument", node.funName);
      }
      Expr e = node.args.get(0);
      e.accept(this);
      if (!currType.equals("string")) {
        error("expecting string in stod", getFirstToken(e));
      }
      currType = "double";
    }
    else if (funName.equals("itos")) {
      // one int argument
      if(node.args.size() != 1) {
        error("stoi expects one argument", node.funName);
      }
      Expr e = node.args.get(0);
      e.accept(this);
      if (!currType.equals("int")) {
        error("expecting int in itos", getFirstToken(e));
      }
      currType = "string";
    }
    else if (funName.equals("itod")) {
      // one int argument
      if(node.args.size() != 1) {
        error("itod expects one argument", node.funName);
      }
      Expr e = node.args.get(0);
      e.accept(this);
      if (!currType.equals("int")) {
        error("expecting int in itod", getFirstToken(e));
      }
      currType = "double";
    }
    else if (funName.equals("dtos")) {
      // one double argument
      if(node.args.size() != 1) {
        error("dtos expects one argument", node.funName);
      }
      Expr e = node.args.get(0);
      e.accept(this);
      if (!currType.equals("double")) {
        error("expecting double in dtos", getFirstToken(e));
      }
      currType = "string";
    }
    else if (funName.equals("dtoi")) {
      // one double argument
      if(node.args.size() != 1) {
        error("dtoi expects one argument", node.funName);
      }
      Expr e = node.args.get(0);
      e.accept(this);
      if (!currType.equals("double")) {
        error("expecting double in dtoi", getFirstToken(e));
      }
      currType = "int";
    }
  }

  
  public void visit(CallExpr node) throws MyPLException {
    // check built in first
    if(getBuiltinFunctions().contains(node.funName.lexeme())) {
      checkBuiltIn(node);
    }
    else {
      // check if user defined is declared
      String funName = node.funName.lexeme();
      if(!symbolTable.nameExists(funName)) {
        error("function " + funName + " was not defined", node.funName);
      }

      // check that params have correct types
      List<String> components = new ArrayList<>(typeInfo.components(funName));
      String paramName = "";
      String typeName = "";
      if(node.args.size() != components.size() - 1) {
        error("incompatible number of arg types in function call", node.funName);
      }
      for(int i = 0; i < node.args.size(); ++i) {
        Expr e = node.args.get(i);
        e.accept(this);
        paramName = components.get(i);
        typeName = typeInfo.get(funName, paramName);
        if(!currType.equals(typeName) && !currType.equals("void")) {
          String m = "incompatible parameter type in " + funName + " function";
          error(m, getFirstToken(node.args.get(i)));
        }
      }
      // set currType to return type
      paramName = components.get(components.size() - 1);
      currType = typeInfo.get(funName, paramName);
    }
  }
  

  //----------------------------------------------------------------------
  // rvalue nodes
  //----------------------------------------------------------------------
  
  public void visit(SimpleRValue node) throws MyPLException {
    TokenType tokenType = node.value.type();
    if (tokenType == TokenType.INT_VAL)
      currType = "int";
    else if (tokenType == TokenType.DOUBLE_VAL)
      currType = "double";
    else if (tokenType == TokenType.BOOL_VAL)
      currType = "bool";
    else if (tokenType == TokenType.CHAR_VAL)    
      currType = "char";
    else if (tokenType == TokenType.STRING_VAL)
      currType = "string";
    else if (tokenType == TokenType.NIL)
      currType = "void";
  }
  
    
  public void visit(NewRValue node) throws MyPLException {
    // need to check that new var is a UDT
    String varName = node.typeName.lexeme();
    // check varName has been defined
    if(symbolTable.get(varName) == null) {
      String m = varName + " has not been defined as a type";
      error(m, node.typeName);
    }
    // check varName is a UDT and not a fun
    if(!symbolTable.get(varName).equals("type")) {
      String m = varName + " is not an object variable";
      error(m, node.typeName);
    }
    // no errors so set currType to UDT
    currType = varName;
  }
  
      
  public void visit(IDRValue node) throws MyPLException {
    // get the first var
    String varName = node.path.get(0).lexeme();
    //check that the variable is defined
    if (!symbolTable.nameExists(varName)) {
      String m = varName + " is not defined";
      error(m, node.path.get(0));
    }
    // get the left-hand side type
    String typeName = symbolTable.get(varName);

    // check for more complex paths
    if(node.path.size() > 1) {
      for(int i = 1; i < node.path.size(); ++i) {
        // check that the variable is a UDT
        if(!symbolTable.get(typeName).equals("type")) {
          String m = typeName + " is not an object variable";
          error(m, node.path.get(i - 1));
        }
        // get components of current lhsType
        Set<String> components = typeInfo.components(typeName);

        // check it's a valid field
        varName = node.path.get(i).lexeme();
        if(!components.contains(varName)) {
          String m = "objects of type " + typeName + " do not have field " + varName;
          error(m, node.path.get(i - 1));
        }
        else {
          typeName = typeInfo.get(typeName, varName);
        }
      }
    }
    // if no errors set currType to typeName
    currType = typeName;
  }
  
      
  public void visit(NegatedRValue node) throws MyPLException {
    // negated rvalues can only be ints or doubles
    node.expr.accept(this);
    if(!(currType.equals("int") || currType.equals("double"))) {
      error("negated values must be ints or doubles", getFirstToken(node.expr));
    }
  }
  

  //----------------------------------------------------------------------
  // expression node
  //----------------------------------------------------------------------
  
  public void visit(Expr node) throws MyPLException {
    // grab the types of both sides
    String lhsType = null;
    String rhsType = null;
    String operator = null;
    if(node.first != null) {
      node.first.accept(this);
      lhsType = currType;
    }
    if(node.rest != null) {
      node.rest.accept(this);
      rhsType = currType;
    }
    if(node.op != null) {
      operator = node.op.lexeme();
    }

    // type checking if operator is involved
    if(operator != null) {
      // if there is an operator, rest should also be there
      if(node.rest == null) {
        error("expression is missing right-hand side", getFirstToken(node.first));
      }
      // check mod first, both sides should be ints
      if(operator.equals("%")) {
        if(!(lhsType.equals("int") && rhsType.equals("int"))) {
          error("modulus operator can only be used with two ints", getFirstToken(node.first));
        }
        currType = "int";
      }
      // and and or next, both sides should be booleans
      else if(operator.equals("and") || operator.equals("or")) {
        if(!lhsType.equals("bool") && !rhsType.equals("bool")) {
          error("and/or operators can only be used with two bools", getFirstToken(node.first));
        }
        currType = "bool";
      }
      // arithmetic operators
      else if(operator.equals("+") || operator.equals("-") || operator.equals("*") || operator.equals("/")) {
        // check for strings/chars using plus
        if((lhsType.equals("string") || lhsType.equals("char")) && (rhsType.equals("string") || rhsType.equals("char"))) {
          if(!operator.equals("+")) {
            error("only + arithmetic operator can be used with strings and chars", getFirstToken(node.first));
          }
          // cannot be double chars
          else if(lhsType.equals("char") && lhsType.equals(rhsType)) {
            error("+ can be used on two strings or one string and one char", getFirstToken(node.first));
          }
          
          lhsType = "string";
        }
        else if(!(lhsType.equals("int") && lhsType.equals(rhsType)) && !(lhsType.equals("double") && lhsType.equals(rhsType))) {
          error("arithmetic operators must be used with two ints or two doubles", getFirstToken(node.first));
        }
        currType = lhsType;
      }
      // logical operators still left
      else {
        // equals/not equals
        if(operator.equals("==") || operator.equals("!=")) {
          // only one can be void or both must be the same
          if(!lhsType.equals(rhsType) && !(lhsType.equals("void") || rhsType.equals("void"))) {
            error("equals/not equals must be used with two identical types", getFirstToken(node.first));
          }
          /*
          else if(lhsType.equals("void") || lhsType.equals(rhsType)) {
            error("equals/not equals cannot be used two void types", getFirstToken(node.first));
          }
          */
        }
        // less than, less equal, greater than, greater equal only left
        else {
          if(!lhsType.equals(rhsType)) {
            error("operator requires two of the same type", getFirstToken(node.first));
          }
          else if(!(lhsType.equals("int") || lhsType.equals("double") || lhsType.equals("char") || lhsType.equals("string"))) {
            String m = operator + " operator most be used with types int, double, char, or string";
            error(m, getFirstToken(node.first));
          }
        }
        currType = "bool";
      }
    }
    // first exists but rest doesn't, so type is lhsType
    else if(node.first != null && node.rest == null) {
      currType = lhsType;
    }
    // first doesn't exist but rest does, so type is rhsType
    else if(node.first == null && node.rest != null) {
      currType = rhsType;
    }
    // if first, op, and rest are null set it to void
    else {
      currType = "void";
    }

    // finally check for logical negation
    if(node.logicallyNegated && !currType.equals("bool")) {
      error("logical negation can only be used with type bool", getFirstToken(node.first));
    }
  }


  //----------------------------------------------------------------------
  // terms
  //----------------------------------------------------------------------
  
  public void visit(SimpleTerm node) throws MyPLException {
    node.rvalue.accept(this);
  }
  

  public void visit(ComplexTerm node) throws MyPLException {
    node.expr.accept(this);
  }


}
