/*
 * File: TryStmt.java
 * Date: Spring 2022
 * Auth: Linden Beemer
 * Desc: Try statement AST Node
 */

import java.util.ArrayList;
import java.util.List;

public class TryStmt implements Stmt {
    
    public List<Stmt> stmts = new ArrayList<>();
    public CatchStmt catchStmt = new CatchStmt();

    @Override
    public void accept(Visitor visitor) throws MyPLException {
        visitor.visit(this);
    }
}
