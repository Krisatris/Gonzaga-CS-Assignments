/*
 * File: CodeGenerator.java
 * Date: Spring 2022
 * Auth: Linden Beemer
 * Desc: 
 */

import java.util.ArrayList;
import java.util.List;
import java.util.HashMap;
import java.util.Map;


public class CodeGenerator implements Visitor {

  // the user-defined type and function type information
  private TypeInfo typeInfo = null;

  // the virtual machine to add the code to
  private VM vm = null;

  // the current frame
  private VMFrame currFrame = null;

  // mapping from variables to their indices (in the frame)
  private Map<String,Integer> varMap = null;

  // the current variable index (in the frame)
  private int currVarIndex = 0;

  // to keep track of the typedecl objects for initialization
  Map<String,TypeDecl> typeDecls = new HashMap<>();


  //----------------------------------------------------------------------
  // HELPER FUNCTIONS
  //----------------------------------------------------------------------
  
  // helper function to clean up uneeded NOP instructions
  private void fixNoOp() {
    int nextIndex = currFrame.instructions.size();
    // check if there are any instructions
    if (nextIndex == 0)
      return;
    // get the last instuction added
    VMInstr instr = currFrame.instructions.get(nextIndex - 1);
    // check if it is a NOP
    if (instr.opcode() == OpCode.NOP)
      currFrame.instructions.remove(nextIndex - 1);
  }

  private void fixCallStmt(Stmt s) {
    // get the last instuction added
    if (s instanceof CallExpr) {
      VMInstr instr = VMInstr.POP();
      instr.addComment("clean up call return value");
      currFrame.instructions.add(instr);
    }

  }
  
  //----------------------------------------------------------------------  
  // Constructor
  //----------------------------------------------------------------------

  public CodeGenerator(TypeInfo typeInfo, VM vm) {
    this.typeInfo = typeInfo;
    this.vm = vm;
  }

  
  //----------------------------------------------------------------------
  // VISITOR FUNCTIONS
  //----------------------------------------------------------------------
  
  public void visit(Program node) throws MyPLException {

    // store UDTs for later
    for (TypeDecl tdecl : node.tdecls) {
      // add a mapping from type name to the TypeDecl
      typeDecls.put(tdecl.typeName.lexeme(), tdecl);
    }
    // only need to translate the function declarations
    for (FunDecl fdecl : node.fdecls)
      fdecl.accept(this);
  }

  public void visit(TypeDecl node) throws MyPLException {
    // Intentionally left blank -- nothing to do here
  }
  
  public void visit(FunDecl node) throws MyPLException {
    // create a new frame for the function
    VMFrame newFrame = new VMFrame(node.funName.lexeme(), node.params.size());
    currFrame = newFrame;
    vm.add(currFrame);
    // 2. create a variable mapping for the frame
    currVarIndex = 0;
    varMap = new HashMap<String,Integer>();
    // 3. store args
    for(FunParam paramNode : node.params) {
      varMap.put(paramNode.paramName.lexeme(), currVarIndex);
      currFrame.instructions.add(VMInstr.STORE(currVarIndex));
      ++currVarIndex;
    }
    // 4. visit statement nodes
    Boolean hasReturnStmt = false;
    for(Stmt stmtNode : node.stmts) {
      stmtNode.accept(this);
      if(stmtNode instanceof ReturnStmt) {
        hasReturnStmt = true;
      }
      fixCallStmt(stmtNode);
    }
    // 5. check to see if the last statement was a return (if not, add
    //    return nil)
    if(!hasReturnStmt) {
      currFrame.instructions.add(VMInstr.PUSH(VM.NIL_OBJ));
      currFrame.instructions.add(VMInstr.VRET());
    }
  }
  
  public void visit(VarDeclStmt node) throws MyPLException {
    // generate the code for the first part of the stmt
    node.expr.accept(this);
    currFrame.instructions.add(VMInstr.STORE(currVarIndex));
    varMap.put(node.varName.lexeme(), currVarIndex);
    ++currVarIndex;
  }
  
  public void visit(AssignStmt node) throws MyPLException {
    // generate the code for the first part of the stmt
    node.expr.accept(this);
    Token firstToken = node.lvalue.get(0);
    if(node.lvalue.size() > 1) {
      currFrame.instructions.add(VMInstr.LOAD(varMap.get(firstToken.lexeme())));
      for(Token currToken : node.lvalue.subList(1, node.lvalue.size() - 1)) {
        currFrame.instructions.add(VMInstr.GETFLD(currToken.lexeme()));
      }
      currFrame.instructions.add(VMInstr.SWAP());
      Token lastToken = node.lvalue.get(node.lvalue.size() - 1);
      currFrame.instructions.add(VMInstr.SETFLD(lastToken.lexeme()));
    }
    else {
      currFrame.instructions.add(VMInstr.STORE(varMap.get(firstToken.lexeme())));
    }
  }
  
  public void visit(CondStmt node) throws MyPLException {
    // if part
    BasicIf ifNode = node.ifPart;
    ifNode.cond.accept(this);
    currFrame.instructions.add(VMInstr.JMPF(0)); // 0 as placeholder
    int jmpfIndex = currFrame.instructions.size() - 1;
    for(Stmt stmtNode : ifNode.stmts) {
      stmtNode.accept(this);
      fixCallStmt(stmtNode);
    }
    List<Integer> jmpIndexes = new ArrayList<>();
    if(!node.elifs.isEmpty() || node.elseStmts != null) {
      currFrame.instructions.add(VMInstr.JMP(0));
      jmpIndexes.add(currFrame.instructions.size() - 1);
    }
    currFrame.instructions.set(jmpfIndex, VMInstr.JMPF(currFrame.instructions.size()));

    // else ifs
    for(BasicIf elifNode : node.elifs) {
      elifNode.cond.accept(this);
      currFrame.instructions.add(VMInstr.JMPF(0));
      jmpfIndex = currFrame.instructions.size() - 1;
      for(Stmt stmtNode : elifNode.stmts) {
        stmtNode.accept(this);
        fixCallStmt(stmtNode);
      }
      if(node.elseStmts != null) {
        currFrame.instructions.add(VMInstr.JMP(0));
        jmpIndexes.add(currFrame.instructions.size() - 1);
      }
      currFrame.instructions.set(jmpfIndex, VMInstr.JMPF(currFrame.instructions.size()));
    }

    // else
    if(node.elseStmts != null) {
      for(Stmt stmtNode : node.elseStmts) {
        stmtNode.accept(this);
        fixCallStmt(stmtNode);
      }
    }

    // set the jumps
    for(Integer index : jmpIndexes) {
      currFrame.instructions.set(index, VMInstr.JMP(currFrame.instructions.size()));
    }
  }

  public void visit(WhileStmt node) throws MyPLException {
    int jmpIndex = currFrame.instructions.size();
    node.cond.accept(this);
    currFrame.instructions.add(VMInstr.JMPF(0));
    int jmpfIndex = currFrame.instructions.size() - 1;
    for(Stmt stmtNode : node.stmts) {
      stmtNode.accept(this);
      fixCallStmt(stmtNode);
    }
    currFrame.instructions.add(VMInstr.JMP(jmpIndex));
    currFrame.instructions.set(jmpfIndex, VMInstr.JMPF(currFrame.instructions.size()));
  }

  public void visit(ForStmt node) throws MyPLException {
    // assign storage for varName
    varMap.put(node.varName.lexeme(), currVarIndex);
    ++currVarIndex;
    // write instructions for start expr
    node.start.accept(this);
    // store start in variable
    currFrame.instructions.add(VMInstr.STORE(currVarIndex - 1));
    // load and test against end condition
    currFrame.instructions.add(VMInstr.LOAD(currVarIndex - 1));
    int jmpIndex = currFrame.instructions.size() - 1;
    node.end.accept(this);
    if(node.upto)
      currFrame.instructions.add(VMInstr.CMPLE());
    else
      currFrame.instructions.add(VMInstr.CMPGE());
    currFrame.instructions.add(VMInstr.JMPF(0)); // placeholder 0
    int jmpfIndex = currFrame.instructions.size() - 1;
    // accept statements
    for(Stmt stmtNode : node.stmts) {
      stmtNode.accept(this);
      fixCallStmt(stmtNode);
    }
    // increment for loop var
    currFrame.instructions.add(VMInstr.LOAD(varMap.get(node.varName.lexeme())));
    currFrame.instructions.add(VMInstr.PUSH(1));
    if(node.upto)
      currFrame.instructions.add(VMInstr.ADD());
    else
      currFrame.instructions.add(VMInstr.SUB());
    currFrame.instructions.add(VMInstr.STORE(varMap.get(node.varName.lexeme())));
    currFrame.instructions.add(VMInstr.JMP(jmpIndex));
    currFrame.instructions.add(VMInstr.NOP());
    // fix jmpf
    currFrame.instructions.set(jmpfIndex, VMInstr.JMPF(currFrame.instructions.size()));
  }
  
  public void visit(ReturnStmt node) throws MyPLException {
    if(node.expr == null)
      currFrame.instructions.add(VMInstr.PUSH(VM.NIL_OBJ));
    else
      node.expr.accept(this);
    currFrame.instructions.add(VMInstr.VRET());
  }
  
  
  public void visit(DeleteStmt node) throws MyPLException {
    int index = varMap.get(node.varName.lexeme());
    currFrame.instructions.add(VMInstr.LOAD(index));
    currFrame.instructions.add(VMInstr.FREE());
  }

  public void visit(CallExpr node) throws MyPLException {
    // TODO: Finish the following (partially completed)

    // push args (in order)
    for (Expr arg : node.args)
      arg.accept(this);
    // built-in functions:
    if (node.funName.lexeme().equals("print")) {
      currFrame.instructions.add(VMInstr.WRITE());
      currFrame.instructions.add(VMInstr.PUSH(VM.NIL_OBJ));
    }
    else if (node.funName.lexeme().equals("read")) {
      currFrame.instructions.add(VMInstr.READ());
    }
    else if (node.funName.lexeme().equals("length")) {
      currFrame.instructions.add(VMInstr.LEN());
    }
    else if(node.funName.lexeme().equals("get")) {
      currFrame.instructions.add(VMInstr.GETCHR());
    }
    else if(node.funName.lexeme().equals("stoi") || node.funName.lexeme().equals("dtoi")) {
      currFrame.instructions.add(VMInstr.TOINT());
    }
    else if(node.funName.lexeme().equals("stod") || node.funName.lexeme().equals("itod")) {
      currFrame.instructions.add(VMInstr.TODBL());
    }
    else if(node.funName.lexeme().equals("itos") || node.funName.lexeme().equals("dtos")) {
      currFrame.instructions.add(VMInstr.TOSTR());
    }

    // user-defined functions
    else {
      currFrame.instructions.add(VMInstr.CALL(node.funName.lexeme()));
    }
  }
  
  public void visit(SimpleRValue node) throws MyPLException {
    if (node.value.type() == TokenType.INT_VAL) {
      int val = Integer.parseInt(node.value.lexeme());
      currFrame.instructions.add(VMInstr.PUSH(val));
    }
    else if (node.value.type() == TokenType.DOUBLE_VAL) {
      double val = Double.parseDouble(node.value.lexeme());
      currFrame.instructions.add(VMInstr.PUSH(val));
    }
    else if (node.value.type() == TokenType.BOOL_VAL) {
      if (node.value.lexeme().equals("true"))
        currFrame.instructions.add(VMInstr.PUSH(true));
      else
        currFrame.instructions.add(VMInstr.PUSH(false));        
    }
    else if (node.value.type() == TokenType.CHAR_VAL) {
      String s = node.value.lexeme();
      s = s.replace("\\n", "\n");
      s = s.replace("\\t", "\t");
      s = s.replace("\\r", "\r");
      s = s.replace("\\\\", "\\");
      currFrame.instructions.add(VMInstr.PUSH(s));
    }
    else if (node.value.type() == TokenType.STRING_VAL) {
      String s = node.value.lexeme();
      s = s.replace("\\n", "\n");
      s = s.replace("\\t", "\t");
      s = s.replace("\\r", "\r");
      s = s.replace("\\\\", "\\");
      currFrame.instructions.add(VMInstr.PUSH(s));
    }
    else if (node.value.type() == TokenType.NIL) {
      currFrame.instructions.add(VMInstr.PUSH(VM.NIL_OBJ));
    }
  }
  
  public void visit(NewRValue node) throws MyPLException {
    TypeDecl tdeclNode = typeDecls.get(node.typeName.lexeme());
    List<String> fields = new ArrayList<>();
    for(VarDeclStmt fieldStmt : tdeclNode.vdecls) {
      fields.add(fieldStmt.varName.lexeme());
    }
    currFrame.instructions.add(VMInstr.ALLOC(fields));
    currFrame.instructions.add(VMInstr.DUP());
    for(int i = 0; i < tdeclNode.vdecls.size(); ++i) {
      VarDeclStmt fieldStmt = tdeclNode.vdecls.get(i);
      fieldStmt.expr.accept(this);
      currFrame.instructions.add(VMInstr.SETFLD(fieldStmt.varName.lexeme()));
      if(i < tdeclNode.vdecls.size() - 1) {
        currFrame.instructions.add(VMInstr.DUP());
      }
    }
  }
  
  public void visit(IDRValue node) throws MyPLException {
    Token firstVar = node.path.get(0);
    int index = varMap.get(firstVar.lexeme());
    currFrame.instructions.add(VMInstr.LOAD(index));
    for(int i = 1; i < node.path.size(); ++i) {
      Token currVar = node.path.get(i);
      currFrame.instructions.add(VMInstr.GETFLD(currVar.lexeme()));
    }
  }
      
  public void visit(NegatedRValue node) throws MyPLException {
    node.expr.accept(this);
    currFrame.instructions.add(VMInstr.NEG());
  }

  public void visit(Expr node) throws MyPLException {
    // first
    if(node.first != null) 
      node.first.accept(this);
    // rest
    if(node.rest == null) {
      if(node.logicallyNegated) {
        currFrame.instructions.add(VMInstr.NOT());
      }
      return;
    }
    if(node.rest != null) {
      node.rest.accept(this);
    }
    // op
    if(node.op != null) {
      if(node.op.type() == TokenType.PLUS) {
        currFrame.instructions.add(VMInstr.ADD());
      }
      else if(node.op.type() == TokenType.MINUS) {
        currFrame.instructions.add(VMInstr.SUB());
      }
      else if(node.op.type() == TokenType.MULTIPLY) {
        currFrame.instructions.add(VMInstr.MUL());
      }
      else if(node.op.type() == TokenType.DIVIDE) {
        currFrame.instructions.add(VMInstr.DIV());
      }
      else if(node.op.type() == TokenType.MODULO) {
        currFrame.instructions.add(VMInstr.MOD());
      }
      else if(node.op.type() == TokenType.AND) {
        currFrame.instructions.add(VMInstr.AND());
      }
      else if(node.op.type() == TokenType.OR) {
        currFrame.instructions.add(VMInstr.OR());
      }
      else if(node.op.type() == TokenType.LESS_THAN) {
        currFrame.instructions.add(VMInstr.CMPLT());
      }
      else if(node.op.type() == TokenType.LESS_THAN_EQUAL) {
        currFrame.instructions.add(VMInstr.CMPLE());
      }
      else if(node.op.type() == TokenType.GREATER_THAN) {
        currFrame.instructions.add(VMInstr.CMPGT());
      }
      else if(node.op.type() == TokenType.GREATER_THAN_EQUAL) {
        currFrame.instructions.add(VMInstr.CMPGE());
      }
      else if(node.op.type() == TokenType.EQUAL) {
        currFrame.instructions.add(VMInstr.CMPEQ());
      }
      else if(node.op.type() == TokenType.NOT_EQUAL) {
        currFrame.instructions.add(VMInstr.CMPNE());
      }
    }
    // logically negated
    if(node.logicallyNegated) {
      currFrame.instructions.add(VMInstr.NOT());
    }
  }

  public void visit(SimpleTerm node) throws MyPLException {
    // defer to contained rvalue
    node.rvalue.accept(this);
  }
  
  public void visit(ComplexTerm node) throws MyPLException {
    // defer to contained expression
    node.expr.accept(this);
  }

}
