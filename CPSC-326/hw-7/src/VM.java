/*
 * File: VM.java
 * Date: Spring 2022
 * Auth: 
 * Desc: A bare-bones MyPL Virtual Machine. The architecture is based
 *       loosely on the architecture of the Java Virtual Machine
 *       (JVM).  Minimal error checking is done except for runtime
 *       program errors, which include: out of bound indexes,
 *       dereferencing a nil reference, and invalid value conversion
 *       (to int and double).
 */


import java.util.Collection;
import java.util.ArrayList;
import java.util.List;
import java.util.HashMap;
import java.util.Map;
import java.util.Deque;
import java.util.ArrayDeque;
import java.util.Scanner;


/*----------------------------------------------------------------------

  TODO: Your main job for HW-6 is to finish the VM implementation
        below by finishing the handling of each instruction.

        Note that PUSH, NOT, JMP, READ, FREE, and NOP (trivially) are
        completed already to help get you started. 

        Be sure to look through OpCode.java to get a basic idea of
        what each instruction should do as well as the unit tests for
        additional details regarding the instructions.

        Note that you only need to perform error checking if the
        result would lead to a MyPL runtime error (where all
        compile-time errors are assumed to be found already). This
        includes things like bad indexes (in GETCHR), dereferencing
        and/or using a NIL_OBJ (see the ensureNotNil() helper
        function), and converting from strings to ints and doubles. An
        error() function is provided to help generate a MyPLException
        for such cases.

----------------------------------------------------------------------*/ 


class VM {

  // set to true to print debugging information
  private boolean DEBUG = false;
  
  // the VM's heap (free store) accessible via object-id
  private Map<Integer,Map<String,Object>> heap = new HashMap<>();
  
  // next available object-id
  private int objectId = 1111;
  
  // the frames for the program (one frame per function)
  private Map<String,VMFrame> frames = new HashMap<>();

  // the VM call stack
  private Deque<VMFrame> frameStack = new ArrayDeque<>();

  
  /**
   * For representing "nil" as a value
   */
  public static String NIL_OBJ = new String("nil");
  

  /** 
   * Add a frame to the VM's list of known frames
   * @param frame the frame to add
   */
  public void add(VMFrame frame) {
    frames.put(frame.functionName(), frame);
  }

  /**
   * Turn on/off debugging, which prints out the state of the VM prior
   * to each instruction. 
   * @param debug set to true to turn on debugging (by default false)
   */
  public void setDebug(boolean debug) {
    DEBUG = debug;
  }

  /**
   * Run the virtual machine
   */
  public void run() throws MyPLException {

    // grab the main stack frame
    if (!frames.containsKey("main"))
      throw MyPLException.VMError("No 'main' function");
    VMFrame frame = frames.get("main").instantiate();
    frameStack.push(frame);
    
    // run loop (keep going until we run out of frames or
    // instructions) note that we assume each function returns a
    // value, and so the second check below should never occur (but is
    // useful for testing, etc).
    while (frame != null && frame.pc < frame.instructions.size()) {
      // get next instruction
      VMInstr instr = frame.instructions.get(frame.pc);
      // increment instruction pointer
      ++frame.pc;

      // For debugging: to turn on the following, call setDebug(true)
      // on the VM.
      if (DEBUG) {
        System.out.println();
        System.out.println("\t FRAME........: " + frame.functionName());
        System.out.println("\t PC...........: " + (frame.pc - 1));
        System.out.println("\t INSTRUCTION..: " + instr);
        System.out.println("\t OPERAND STACK: " + frame.operandStack);
        System.out.println("\t HEAP ........: " + heap);
      }

      
      //------------------------------------------------------------
      // Consts/Vars
      //------------------------------------------------------------

      if (instr.opcode() == OpCode.PUSH) {
        frame.operandStack.push(instr.operand());
      }

      else if (instr.opcode() == OpCode.POP) {
        frame.operandStack.pop();
      }

      else if (instr.opcode() == OpCode.LOAD) {
        if(!(instr.operand() instanceof Integer)) {
          error("LOAD operand is not a valid integer", frame);
        }
        Object storedObject = frame.variables.get((Integer)instr.operand());
        frame.operandStack.push(storedObject);
      }
        
      else if (instr.opcode() == OpCode.STORE) {
        if(!(instr.operand() instanceof Integer)) {
          error("STORE operand is not a valid integer", frame);
        }
        Integer memAddress = (int)instr.operand();
        Object storedObject = frame.operandStack.pop();
        if(memAddress >= frame.variables.size()) {
          while(frame.variables.size() < memAddress + 1) {
            frame.variables.add(null);
          }
        }
        frame.variables.set(memAddress, storedObject);
      }

      
      //------------------------------------------------------------
      // Ops
      //------------------------------------------------------------
        
      else if (instr.opcode() == OpCode.ADD) {
        // integers
        if(frame.operandStack.peek() instanceof Integer) {
          Integer x = (Integer)frame.operandStack.pop();
          if(frame.operandStack.peek() instanceof Integer) {
            Integer y = (Integer)frame.operandStack.pop();
            ensureNotNil(frame, x);
            ensureNotNil(frame, y);
            frame.operandStack.push(y + x);
          } else {
            error("invalid operand with operation +", frame);
          }
        }
        // strings/chars
        else if(frame.operandStack.peek() instanceof String || frame.operandStack.peek() instanceof Character) {
          String x = (String)frame.operandStack.pop();
          if(frame.operandStack.peek() instanceof String || frame.operandStack.peek() instanceof Character) {
            String y = (String)frame.operandStack.pop();
            ensureNotNil(frame, x);
            ensureNotNil(frame, y);
            frame.operandStack.push(y + x);
          } else {
            error("invalid operand with operation +", frame);
          }
        }
        else if(frame.operandStack.peek() instanceof Double) {
          Double x = (Double)frame.operandStack.pop();
          if(frame.operandStack.peek() instanceof Double) {
            Double y = (Double)frame.operandStack.pop();
            ensureNotNil(frame, x);
            ensureNotNil(frame, y);
            frame.operandStack.push(y + x);
          } else {
            error("invalid operand with operation +", frame);
          }
        }
        else {
          error("invalid operand with operation +", frame);
        }
      }

      else if (instr.opcode() == OpCode.SUB) {
        if(frame.operandStack.peek() instanceof Integer) {
          Integer x = (Integer)frame.operandStack.pop();
          if(frame.operandStack.peek() instanceof Integer) {
            Integer y = (Integer)frame.operandStack.pop();
            ensureNotNil(frame, x);
            ensureNotNil(frame, y);
            frame.operandStack.push(y - x);
          } else {
            error("invalid operand with operation -", frame);
          }
        } else if(frame.operandStack.peek() instanceof Double) {
          Double x = (Double)frame.operandStack.pop();
          if(frame.operandStack.peek() instanceof Double) {
            Double y = (Double)frame.operandStack.pop();
            ensureNotNil(frame, x);
            ensureNotNil(frame, y);
            frame.operandStack.push(y - x);
          } else {
            error("invalid operand with operation -", frame);
          }
        } else {
          error("invalid operand with operation -", frame);
        }
      }

      else if (instr.opcode() == OpCode.MUL) {
        if(frame.operandStack.peek() instanceof Integer) {
          Integer x = (Integer)frame.operandStack.pop();
          if(frame.operandStack.peek() instanceof Integer) {
            Integer y = (Integer)frame.operandStack.pop();
            ensureNotNil(frame, x);
            ensureNotNil(frame, y);
            frame.operandStack.push(y * x);
          } else {
            error("invalid operand with operation *", frame);
          }
        } else if(frame.operandStack.peek() instanceof Double) {
          Double x = (Double)frame.operandStack.pop();
          if(frame.operandStack.peek() instanceof Double) {
            Double y = (Double)frame.operandStack.pop();
            ensureNotNil(frame, x);
            ensureNotNil(frame, y);
            frame.operandStack.push(y * x);
          } else {
            error("invalid operand with operation *", frame);
          }
        } else {
          error("invalid operand with operation *", frame);
        }
      }

      else if (instr.opcode() == OpCode.DIV) {
        if(frame.operandStack.peek() instanceof Integer) {
          Integer x = (Integer)frame.operandStack.pop();
          if(frame.operandStack.peek() instanceof Integer) {
            Integer y = (Integer)frame.operandStack.pop();
            ensureNotNil(frame, x);
            ensureNotNil(frame, y);
            frame.operandStack.push(y / x);
          } else {
            //System.out.println(frame.operandStack.peek().toString());
            error("invalid operand with operation /", frame);
          }
        } else if(frame.operandStack.peek() instanceof Double) {
          Double x = (Double)frame.operandStack.pop();
          if(frame.operandStack.peek() instanceof Double) {
            Double y = (Double)frame.operandStack.pop();
            ensureNotNil(frame, x);
            ensureNotNil(frame, y);
            frame.operandStack.push(y / x);
          } else {
            error("invalid operand with operation /", frame);
          }
        } else {
          error("invalid operand with operation /", frame);
        }
      }

      else if (instr.opcode() == OpCode.MOD) {
        if(frame.operandStack.peek() instanceof Integer) {
          Integer x = (Integer)frame.operandStack.pop();
          if(frame.operandStack.peek() instanceof Integer) {
            Integer y = (Integer)frame.operandStack.pop();
            ensureNotNil(frame, x);
            ensureNotNil(frame, y);
            frame.operandStack.push(y % x);
          } else {
            error("invalid operand with operation %", frame);
          }
        } else {
          error("invalid operand with operation %", frame);
        }
      }

      else if (instr.opcode() == OpCode.AND) {
        if(frame.operandStack.peek() instanceof Boolean) {
          Boolean x = (Boolean)frame.operandStack.pop();
          if(frame.operandStack.peek() instanceof Boolean) {
            Boolean y = (Boolean)frame.operandStack.pop();
            ensureNotNil(frame, x);
            ensureNotNil(frame, y);
            frame.operandStack.push(y && x);
          } else {
            error("invalid operand with operation AND", frame);
          }
        } else {
          error("invalid operand with operation AND", frame);
        }
      }

      else if (instr.opcode() == OpCode.OR) {
        if(frame.operandStack.peek() instanceof Boolean) {
          Boolean x = (Boolean)frame.operandStack.pop();
          if(frame.operandStack.peek() instanceof Boolean) {
            Boolean y = (Boolean)frame.operandStack.pop();
            ensureNotNil(frame, x);
            ensureNotNil(frame, y);
            frame.operandStack.push(y || x);
          } else {
            error("invalid operand with operation OR", frame);
          }
        } else {
          error("invalid operand with operation OR", frame);
        }
      }

      else if (instr.opcode() == OpCode.NOT) {
        Object operand = frame.operandStack.pop();
        ensureNotNil(frame, operand);
        frame.operandStack.push(!(boolean)operand);
      }

      else if (instr.opcode() == OpCode.CMPLT) {
        if(frame.operandStack.peek() instanceof Integer) {
          Integer x = (Integer)frame.operandStack.pop();
          if(frame.operandStack.peek() instanceof Integer) {
            Integer y = (Integer)frame.operandStack.pop();
            ensureNotNil(frame, x);
            ensureNotNil(frame, y);
            frame.operandStack.push(y < x);
          } else {
            error("invalid operand with operation <", frame);
          }
        } else if(frame.operandStack.peek() instanceof Double) {
          Double x = (Double)frame.operandStack.pop();
          if(frame.operandStack.peek() instanceof Double) {
            Double y = (Double)frame.operandStack.pop();
            ensureNotNil(frame, x);
            ensureNotNil(frame, y);
            frame.operandStack.push(y < x);
          } else {
            error("invalid operand with operation <", frame);
          }
        } else if(frame.operandStack.peek() instanceof String || frame.operandStack.peek() instanceof Character) {
          String x = (String)frame.operandStack.pop();
          if(frame.operandStack.peek() instanceof String || frame.operandStack.peek() instanceof Character) {
            String y = (String)frame.operandStack.pop();
            ensureNotNil(frame, x);
            ensureNotNil(frame, y);
            Boolean result = y.compareTo(x) < 0;
            frame.operandStack.push(result);
          }
        } else {
          error("invalid operand with operation <", frame);
        }
      }

      else if (instr.opcode() == OpCode.CMPLE) {
        if(frame.operandStack.peek() instanceof Integer) {
          Integer x = (Integer)frame.operandStack.pop();
          if(frame.operandStack.peek() instanceof Integer) {
            Integer y = (Integer)frame.operandStack.pop();
            ensureNotNil(frame, x);
            ensureNotNil(frame, y);
            frame.operandStack.push(y <= x);
          } else {
            error("invalid operand with operation <", frame);
          }
        } else if(frame.operandStack.peek() instanceof Double) {
          Double x = (Double)frame.operandStack.pop();
          if(frame.operandStack.peek() instanceof Double) {
            Double y = (Double)frame.operandStack.pop();
            ensureNotNil(frame, x);
            ensureNotNil(frame, y);
            frame.operandStack.push(y <= x);
          } else {
            error("invalid operand with operation <", frame);
          }
        } else if(frame.operandStack.peek() instanceof String || frame.operandStack.peek() instanceof Character) {
          String x = (String)frame.operandStack.pop();
          if(frame.operandStack.peek() instanceof String || frame.operandStack.peek() instanceof Character) {
            String y = (String)frame.operandStack.pop();
            ensureNotNil(frame, x);
            ensureNotNil(frame, y);
            Boolean result = y.compareTo(x) <= 0;
            frame.operandStack.push(result);
          }
        } else {
          error("invalid operand with operation <=", frame);
        }
      }

      else if (instr.opcode() == OpCode.CMPGT) {
        if(frame.operandStack.peek() instanceof Integer) {
          Integer x = (Integer)frame.operandStack.pop();
          if(frame.operandStack.peek() instanceof Integer) {
            Integer y = (Integer)frame.operandStack.pop();
            ensureNotNil(frame, x);
            ensureNotNil(frame, y);
            frame.operandStack.push(y > x);
          } else {
            error("invalid operand with operation >", frame);
          }
        } else if(frame.operandStack.peek() instanceof Double) {
          Double x = (Double)frame.operandStack.pop();
          if(frame.operandStack.peek() instanceof Double) {
            Double y = (Double)frame.operandStack.pop();
            ensureNotNil(frame, x);
            ensureNotNil(frame, y);
            frame.operandStack.push(y > x);
          } else {
            error("invalid operand with operation >", frame);
          }
        } else if(frame.operandStack.peek() instanceof String || frame.operandStack.peek() instanceof Character) {
          String x = (String)frame.operandStack.pop();
          if(frame.operandStack.peek() instanceof String || frame.operandStack.peek() instanceof Character) {
            String y = (String)frame.operandStack.pop();
            ensureNotNil(frame, x);
            ensureNotNil(frame, y);
            Boolean result = y.compareTo(x) > 0;
            frame.operandStack.push(result);
          }
        } else {
          error("invalid operand with operation >", frame);
        }
      }

      else if (instr.opcode() == OpCode.CMPGE) {
        if(frame.operandStack.peek() instanceof Integer) {
          Integer x = (Integer)frame.operandStack.pop();
          if(frame.operandStack.peek() instanceof Integer) {
            Integer y = (Integer)frame.operandStack.pop();
            ensureNotNil(frame, x);
            ensureNotNil(frame, y);
            frame.operandStack.push(y >= x);
          } else {
            error("invalid operand with operation >=", frame);
          }
        } else if(frame.operandStack.peek() instanceof Double) {
          Double x = (Double)frame.operandStack.pop();
          if(frame.operandStack.peek() instanceof Double) {
            Double y = (Double)frame.operandStack.pop();
            ensureNotNil(frame, x);
            ensureNotNil(frame, y);
            frame.operandStack.push(y >= x);
          } else {
            error("invalid operand with operation >=", frame);
          }
        } else if(frame.operandStack.peek() instanceof String || frame.operandStack.peek() instanceof Character) {
          String x = (String)frame.operandStack.pop();
          if(frame.operandStack.peek() instanceof String || frame.operandStack.peek() instanceof Character) {
            String y = (String)frame.operandStack.pop();
            ensureNotNil(frame, x);
            ensureNotNil(frame, y);
            Boolean result = y.compareTo(x) >= 0;
            frame.operandStack.push(result);
          }
        } else {
          error("invalid operand with operation >=", frame);
        }
      }

      else if (instr.opcode() == OpCode.CMPEQ) {
        Object x = frame.operandStack.pop();
        Object y = frame.operandStack.pop();
        if(x.equals(NIL_OBJ) && y.equals(NIL_OBJ)) {
          frame.operandStack.push(true);
        }
        else if(x.equals(NIL_OBJ) || y.equals(NIL_OBJ)) {
          frame.operandStack.push(false);
        }
        else if(x instanceof Integer) {
          frame.operandStack.push(((int)y) == (int)x);
        }
        else if(x instanceof Double) {
          frame.operandStack.push(((double)y) == (double)x);
        }
        else if(x instanceof Character || x instanceof String) {
          String yStr = (String)y;
          Boolean result = yStr.compareTo((String)x) == 0;
          frame.operandStack.push(result);
        }
      }

      else if (instr.opcode() == OpCode.CMPNE) {
        Object x = frame.operandStack.pop();
        Object y = frame.operandStack.pop();
        if(x.equals(NIL_OBJ) && y.equals(NIL_OBJ)) {
          frame.operandStack.push(false);
        }
        else if(x.equals(NIL_OBJ) || y.equals(NIL_OBJ)) {
          frame.operandStack.push(true);
        }
        else if(x instanceof Integer) {
          frame.operandStack.push(!(((int)y) == (int)x));
        }
        else if(x instanceof Double) {
          frame.operandStack.push(!(((double)y) == (double)x));
        }
        else if(x instanceof Character || x instanceof String) {
          String yStr = (String)y;
          Boolean result = yStr.compareTo((String)x) != 0;
          frame.operandStack.push(result);
        }
      }

      else if (instr.opcode() == OpCode.NEG) {
        if(frame.operandStack.peek() instanceof Integer) {
          Integer operand = (Integer)frame.operandStack.pop();
          ensureNotNil(frame, operand);
          frame.operandStack.push(operand * -1);
        } else if(frame.operandStack.peek() instanceof Double) {
          Double operand = (Double)frame.operandStack.pop();
          ensureNotNil(frame, operand);
          frame.operandStack.push(operand * -1.0);
        } else {
          error("invalid operand used with operator neg", frame);
        }
      }

      
      //------------------------------------------------------------
      // Jumps
      //------------------------------------------------------------
        
      else if (instr.opcode() == OpCode.JMP) {
        frame.pc = (int)instr.operand();
      }

      else if (instr.opcode() == OpCode.JMPF) {
        Object operand = frame.operandStack.pop();
        ensureNotNil(frame, operand);
        if(!(boolean)operand) {
          frame.pc = (int)instr.operand();
        }
      }
        
      //------------------------------------------------------------
      // Functions
      //------------------------------------------------------------

      else if (instr.opcode() == OpCode.CALL) {
        // get frame and instantiate a new copy
        String funName = (String)instr.operand();
        VMFrame functionFrame = frames.get(funName);
        VMFrame instantiateFunction = functionFrame.instantiate();
        // copy args over
        for(int i = 0; i < instantiateFunction.argCount(); ++i) {
          Object arg = frame.operandStack.pop();
          instantiateFunction.operandStack.push(arg);
        }
        // push new frame and set to current frame
        frameStack.push(instantiateFunction);
        frame = instantiateFunction;
      }
        
      else if (instr.opcode() == OpCode.VRET) {
        if(!frame.functionName().equals("main")) {
          //System.out.println("exiting " + frame.functionName());
          Object returnVal = frame.operandStack.pop();
          frameStack.pop();
          frame = frameStack.peek();
          frame.operandStack.push(returnVal);
        }
        else {
          System.exit(0);
        }
      }
        
      //------------------------------------------------------------
      // Built-ins
      //------------------------------------------------------------
        
      else if (instr.opcode() == OpCode.WRITE) {
        System.out.print(frame.operandStack.pop());
      }

      else if (instr.opcode() == OpCode.READ) {
        Scanner s = new Scanner(System.in);
        frame.operandStack.push(s.nextLine());
      }

      else if (instr.opcode() == OpCode.LEN) {
        if(frame.operandStack.peek() instanceof String) {
          String operand = (String)frame.operandStack.pop();
          ensureNotNil(frame, operand);
          frame.operandStack.push(operand.length());
        } else {
          error("incompatible type used with operator LEN", frame);
        }
      }

      else if (instr.opcode() == OpCode.GETCHR) {
        if(frame.operandStack.peek() instanceof String) {
          String stringArg = (String)frame.operandStack.pop();
          if(frame.operandStack.peek() instanceof Integer) {
            Integer intArg = (Integer)frame.operandStack.pop();
            ensureNotNil(frame, stringArg);
            ensureNotNil(frame, intArg);
            if(intArg >= stringArg.length() || intArg < 0) {
              error("illegal int arg (out of scope) for getchar method", frame);
            }
            frame.operandStack.push(stringArg.substring(intArg, intArg + 1));
          } else {
            error("expecting int as second operand for LEN", frame);
          }
        } else {
          error("expected string as first operand for LEN", frame);
        }
      }

      else if (instr.opcode() == OpCode.TOINT) {
        Object operand = frame.operandStack.pop();
        ensureNotNil(frame, operand);
        if(operand instanceof Double) {
          frame.operandStack.push(((Double)operand).intValue());
        }
        else if(operand instanceof String) {
          if(((String)operand).matches("[0-9]+")) {
            frame.operandStack.push((Integer.parseInt(operand.toString())));
          }
          else {
            error("string contains characters that cannot be converted to ints", frame);
          }
        }
        else {
          error("cannot convert given type to integer", frame);
        }
      }

      else if (instr.opcode() == OpCode.TODBL) {
        Object operand = frame.operandStack.pop();
        ensureNotNil(frame, operand);
        if(operand instanceof Integer) {
          frame.operandStack.push(Double.valueOf((int)operand));
        }
        else if(operand instanceof String) {
          if(((String)operand).matches("([0-9]*)\\.([0-9]*)")) {
            frame.operandStack.push(Double.parseDouble(operand.toString()));
          }
          else {
            error("string contains characters that cannot be converted to doubles", frame);
          }
        }
        else {
          error("unable to convert to double", frame);
        }
      }

      else if (instr.opcode() == OpCode.TOSTR) {
        Object operand = frame.operandStack.pop();
        ensureNotNil(frame, operand);
        frame.operandStack.push(operand.toString());
      }

      //------------------------------------------------------------
      // Heap related
      //------------------------------------------------------------

      else if (instr.opcode() == OpCode.ALLOC) {      
        List<String> fields = new ArrayList<>();
        fields.addAll((List<String>)instr.operand());
        Map<String, Object> temp = new HashMap<>();
        for(String field : fields) {
          temp.put(field, null);
        }
        heap.put(objectId, temp);
        frame.operandStack.push(objectId);
        ++this.objectId;
      }

      else if (instr.opcode() == OpCode.FREE) {
        // pop the oid to 
        Object oid = frame.operandStack.pop();
        ensureNotNil(frame, oid);
        // remove the object with oid from the heap
        heap.remove((int)oid);
      }

      else if (instr.opcode() == OpCode.SETFLD) {
        String fieldName = (String)instr.operand();
        Object top = frame.operandStack.pop();
        Integer oid = (int)frame.operandStack.pop();
        Map<String, Object> field = heap.get(oid);
        if(field == null) {
          error("object id not valid", frame);
        }
        field.replace(fieldName, top);
      }

      else if (instr.opcode() == OpCode.GETFLD) {      
        String fieldName = (String)instr.operand();
        Integer oid = (int)frame.operandStack.pop();
        Map<String, Object> field = heap.get(oid);
        if(field == null) {
          error("object id not valid", frame);
        }
        frame.operandStack.push(field.get(fieldName));
      }

      //------------------------------------------------------------
      // Special instructions
      //------------------------------------------------------------
        
      else if (instr.opcode() == OpCode.DUP) {
        Object dup = frame.operandStack.pop();
        frame.operandStack.push(dup);
        frame.operandStack.push(dup);
      }

      else if (instr.opcode() == OpCode.SWAP) {
        Object operand1 = frame.operandStack.pop();
        Object operand2 = frame.operandStack.pop();
        frame.operandStack.push(operand1);
        frame.operandStack.push(operand2);
      }

      else if (instr.opcode() == OpCode.NOP) {
        // do nothing
      }

    }
  }

  
  // to print the lists of instructions for each VM Frame
  @Override
  public String toString() {
    String s = "";
    for (Map.Entry<String,VMFrame> e : frames.entrySet()) {
      String funName = e.getKey();
      s += "Frame '" + funName + "'\n";
      List<VMInstr> instructions = e.getValue().instructions;      
      for (int i = 0; i < instructions.size(); ++i) {
        VMInstr instr = instructions.get(i);
        s += "  " + i + ": " + instr + "\n";
      }
      // s += "\n";
    }
    return s;
  }

  
  //----------------------------------------------------------------------
  // HELPER FUNCTIONS
  //----------------------------------------------------------------------

  // error
  private void error(String m, VMFrame f) throws MyPLException {
    int pc = f.pc - 1;
    VMInstr i = f.instructions.get(pc);
    String name = f.functionName();
    m += " (in " + name + " at " + pc + ": " + i + ")";
    throw MyPLException.VMError(m);
  }

  // error if given value is nil
  private void ensureNotNil(VMFrame f, Object v) throws MyPLException {
    if (v == NIL_OBJ)
      error("Nil reference", f);
  }
  
  
}
