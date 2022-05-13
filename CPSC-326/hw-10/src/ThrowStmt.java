/*
 * File: ThrowStmt.java
 * Date: Spring 2022
 * Auth: Linden Beemer
 * Desc: An AST node for representing a throw statement
 */

public class ThrowStmt implements Stmt {
    
    public Token varName = null;
    public String typeName = null;

    @Override
    public void accept(Visitor visitor) throws MyPLException {
        visitor.visit(this);
    }
}
