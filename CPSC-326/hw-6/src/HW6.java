/*
 * File: HW6.java
 * Date: Spring 2022
 * Auth: 
 * Desc: Example program to test the MyPL VM
 */


/*----------------------------------------------------------------------
   Your job for this part of the assignment is to imlement the
   following as a set of MyPL VM instructions and the VM. Note that
   you must implement the is_prime function and generally folow the
   approach laid out below. You can view the following as pseudocode
   (which could have been written in any procedural programming
   language). Note that since we don't have a square root function in
   MyPL, our naive primality tester is not very efficient.

    fun bool is_prime(int n) {
      var m = n / 2
      var v = 2
      while v <= m {
        var r = n / v
        var p = r * v
        if p == n {
          return false
        }
        v = v + 1
      }
      return true
    }

    fun void main() {
      print("Please enter integer values to sum (prime number to quit)\n")
      var sum = 0
      while true {
        print(">> Enter an int: ")
        var val = stoi(read())
        if is_prime(val) {
          print("The sum is: " + itos(sum) + "\n")
          print("Goodbye!\n")
          return
        }
        sum = sum + val
      }
    }
----------------------------------------------------------------------*/  

public class HW6 {

  public static void main(String[] args) throws Exception {
    VM vm = new VM();

    //main
    VMFrame main = new VMFrame("main", 0);
    vm.add(main);
    // print("Please enter integer values to sum (prime number to quit)\n")
    main.instructions.add(VMInstr.PUSH("Please enter integer values to sum (prime number to quit)\n"));
    main.instructions.add(VMInstr.WRITE());
    // var sum = 0
    main.instructions.add(VMInstr.PUSH(0));
    main.instructions.add(VMInstr.STORE(0)); // store sum @ 0
    // while true
    main.instructions.add(VMInstr.PUSH(true));
    main.instructions.add(VMInstr.JMPF(29));
    // print(">> Enter an int: ")
    main.instructions.add(VMInstr.PUSH(">> Enter an int: "));
    main.instructions.add(VMInstr.WRITE());
    // var val = stoi(read())
    main.instructions.add(VMInstr.READ());
    main.instructions.add(VMInstr.TOINT());
    main.instructions.add(VMInstr.STORE(1)); // store val @ 1
    // if is_prime(val)
    main.instructions.add(VMInstr.LOAD(1));
    main.instructions.add(VMInstr.CALL("isPrime")); // pushes t/f onto stack
    main.instructions.add(VMInstr.JMPF(24)); // comparison fails
    // print("The sum is: " + itos(sum) + "\n")
    main.instructions.add(VMInstr.PUSH("The sum is: "));
    main.instructions.add(VMInstr.LOAD(0));
    main.instructions.add(VMInstr.TOSTR());
    main.instructions.add(VMInstr.PUSH("\n"));
    main.instructions.add(VMInstr.ADD());
    main.instructions.add(VMInstr.ADD());
    main.instructions.add(VMInstr.WRITE());
    // print("Goodbye\n")
    main.instructions.add(VMInstr.PUSH("Goodbye!\n"));
    main.instructions.add(VMInstr.WRITE());
    // return
    main.instructions.add(VMInstr.JMP(29)); // aka break loop
    // sum = sum + val
    main.instructions.add(VMInstr.LOAD(0));
    main.instructions.add(VMInstr.LOAD(1));
    main.instructions.add(VMInstr.ADD());
    main.instructions.add(VMInstr.STORE(0));
    // return to top of loop
    main.instructions.add(VMInstr.JMP(6));
    // end of program
    main.instructions.add(VMInstr.NOP());
    
    //is_prime
    VMFrame isPrime = new VMFrame("isPrime", 1);
    vm.add(isPrime);
    isPrime.instructions.add(VMInstr.STORE(0)); // store param n @ 0
    // var m = n / 2
    isPrime.instructions.add(VMInstr.LOAD(0));
    isPrime.instructions.add(VMInstr.PUSH(2));
    isPrime.instructions.add(VMInstr.DIV());
    isPrime.instructions.add(VMInstr.STORE(1)); // store m @ 1
    // var v = 2
    isPrime.instructions.add(VMInstr.PUSH(2));
    isPrime.instructions.add(VMInstr.STORE(2)); // store v @ 2
    // while v <= m
    isPrime.instructions.add(VMInstr.LOAD(2)); // load v
    isPrime.instructions.add(VMInstr.LOAD(1)); // load m
    isPrime.instructions.add(VMInstr.CMPLE());
    isPrime.instructions.add(VMInstr.JMPF(30)); // comparison fails
    // var r = n / v
    isPrime.instructions.add(VMInstr.LOAD(0)); // load n
    isPrime.instructions.add(VMInstr.LOAD(2)); // load v
    isPrime.instructions.add(VMInstr.DIV());
    isPrime.instructions.add(VMInstr.STORE(3)); // store r @ 3
    // var p = r * v
    isPrime.instructions.add(VMInstr.LOAD(3));
    isPrime.instructions.add(VMInstr.LOAD(2));
    isPrime.instructions.add(VMInstr.MUL());
    isPrime.instructions.add(VMInstr.STORE(4)); // store p @ 4
    // if p == n
    isPrime.instructions.add(VMInstr.LOAD(4));
    isPrime.instructions.add(VMInstr.LOAD(0));
    isPrime.instructions.add(VMInstr.CMPEQ());
    isPrime.instructions.add(VMInstr.JMPF(25)); // comparison fails
    // return false
    isPrime.instructions.add(VMInstr.PUSH(false));
    isPrime.instructions.add(VMInstr.JMP(31)); // jump to vret
    // v = v + 1
    isPrime.instructions.add(VMInstr.LOAD(2));
    isPrime.instructions.add(VMInstr.PUSH(1));
    isPrime.instructions.add(VMInstr.ADD());
    isPrime.instructions.add(VMInstr.STORE(2));
    isPrime.instructions.add(VMInstr.JMP(7)); // restart while loop
    // return true
    isPrime.instructions.add(VMInstr.PUSH(true));
    isPrime.instructions.add(VMInstr.VRET());
    
    vm.run();
  }
}
