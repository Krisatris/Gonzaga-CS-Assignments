/*
 * File: MyPL.java
 * Date: Spring 2022
 * Auth: Linden Beemer
 * Desc: This file implements rudimentary option flags for the MyPL langauge.
 */

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.IOException;


public class MyPL {

  public static void main(String[] args) {

    if (args.length > 2) {
      // too many args given
      displayUsageInfo();
      System.exit(1);
    }  
    else if(args.length == 0) {
      normalMode(args);
    }
    else if (args[0].equals("--lex")) {
      // print first char of input
      System.out.println("[Lex Mode]");
      BufferedReader r = getInputInfo(args.length - 1, true, args);
      try {
        int currChar = r.read();
        boolean printedChar = false;
        while(currChar != -1) {
          if(!printedChar) {
            System.out.println((char)currChar);
            printedChar = true;
          }
          if((char)currChar == '\n' && args.length == 1) {
            printedChar = false;
          }
          currChar = r.read();
        }
      } catch (IOException e) {
        System.out.println("ERROR: input could not be read");
      }
    } 
    else if (args[0].equals("--parse")) {
      // print first two chars of input
      System.out.println("[Parse Mode]");
      BufferedReader r = getInputInfo(args.length - 1, true, args);
      try {
        int currChar = r.read();
        boolean printedChars = false;
        while(currChar != -1) {
          if(!printedChars) {
            for(int i = 0; i < 2; ++i) {
              System.out.print((char)currChar);
              currChar = r.read();
            }
            System.out.println();
            printedChars = true;
          }
          if((char)currChar == '\n' && args.length == 1) {
            printedChars = false;
          }
          currChar = r.read();
        }
      } catch (IOException e) {
        System.out.println("ERROR: input could not be read");
      }
    } 
    else if (args[0].equals("--print")) {
      // print first word of input
      System.out.println("[Print Mode]");
      BufferedReader r = getInputInfo(args.length - 1, true, args);
      try {
        int currChar = r.read();
        boolean printedWord = false;
        while(currChar != -1) {
          if(!printedWord) {
            while((char)currChar != ' ' && (char)currChar != '\n') {
              System.out.print((char)currChar);
              currChar = r.read();
            }
            printedWord = true;
            System.out.println();
          }
          if((char)currChar == '\n' && args.length == 1) {
            printedWord = false;
          }
          currChar = r.read();
        }
      } catch (IOException e) {
        System.out.println("ERROR: input could not be read");
      }
    } 
    else if (args[0].equals("--check")) {
      // print first line
      System.out.println("[Check Mode]");
      BufferedReader r = getInputInfo(args.length - 1, true, args);
      try {
        int currChar = r.read();
        boolean printedLine = false;
        while(currChar != -1) {
          if(!printedLine) {
            while((char)currChar != '\n') {
              System.out.print((char)currChar);
              currChar = r.read();
            }
            printedLine = true;
            System.out.println();
          }
          if((char)currChar == '\n' && args.length == 1) {
            printedLine = false;
          }
          currChar = r.read();
        }
      } catch (IOException e) {
        System.out.println("ERROR: input could not be read");
      }
    } 
    else if (args[0].equals("--ir")) {
      // print entire file
      System.out.println("[IR Mode]");
      BufferedReader r = getInputInfo(args.length - 1, true, args);
      try {
        int currChar = r.read();
        while(currChar != -1) {
          System.out.print((char)currChar);
          currChar = r.read();
        }
        System.out.println();
      } catch (IOException e) {
        System.out.println("ERROR: input could not be read");
      }
    } 
    else {
      normalMode(args);
    }
  }

  private static void displayUsageInfo() {
    System.out.println("Usage: ./mypl [option] [script-file]");
    System.out.println("Options:");
    System.out.println("  --lex      Display token information.");
    System.out.println("  --parse    Check for valid syntax.");
    System.out.println("  --print    Pretty print the program.");
    System.out.println("  --check    Statically check program.");
    System.out.println("  --ir       Print intermediate code.");
  }

  private static BufferedReader getInputInfo(int argLength, boolean hasFlag, String[] args) {
    BufferedReader r = null;
    if((argLength == 0 && hasFlag) || argLength == -1) {
      try {
        InputStream input = System.in;
        r = new BufferedReader(new InputStreamReader(input));
      } catch (Exception e) {
        System.out.println("ERROR: Unable to read text.");
        System.exit(1);
      }
    }
    else {
      try {
        InputStream input = new FileInputStream(args[argLength]);
        r = new BufferedReader(new InputStreamReader(input));
      } catch (FileNotFoundException e) {
        System.out.println("ERROR: Unable to open file  \'" + args[argLength] + "\'");
        System.exit(1);
      }
    }
    return r;
  }

  private static void normalMode(String[] args) {
    // print every other word
    System.out.println("[Normal Mode]");

    // initalize the bufferedreader
    BufferedReader r = null;
    r = getInputInfo(args.length - 1, false, args);

    // print the output
    try {
      int currChar = r.read();
      boolean currWord = true;
      while(currChar != -1) {
        if(currWord || (char)currChar == '\n') {
          System.out.print((char)currChar);
        }
        if((char)currChar == ' ' || (char)currChar == '\n') {
          currWord = !currWord;
        }
        currChar = r.read();
      }
      System.out.println();
    } catch (IOException e) {
      System.out.println("ERROR: input could not be read");
    }
  }
  
}
