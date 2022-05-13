/*
 * File: CatchStmt.java
 * Date: Spring 2022
 * Auth: Linden Beemer
 * Desc: Catch statement AST Node
 */

import java.util.ArrayList;
import java.util.List;

public class CatchStmt implements Stmt {
    
    public Token typeName = null;
    public Token varName = null;
    public List<Stmt> stmts = new ArrayList<>();
    public CatchStmt otherCatch = null;

    @Override
    public void accept(Visitor visitor) throws MyPLException {
        visitor.visit(this);
    }
}
