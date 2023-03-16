package com.craftinginterpreters.lox;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

class RpnPrinter implements Expr.Visitor<Void> {
  private static final Map<String, Integer> precedence;

  static {
    precedence = new HashMap<>();
    precedence.put("(", 0);
    precedence.put(")", 0);
    precedence.put("+", 1);
    precedence.put("-", 1);
    precedence.put("*", 2);
    precedence.put("/", 2);
  }

  private final List<String> out = new ArrayList<>();
  private final List<String> stack = new ArrayList<>();

  String print(Expr expr) {
    expr.accept(this);

    while (!stack.isEmpty()) {
      out.add(pop());
    }

    return String.join(" ", out);
  }

  @Override
  public Void visitBinaryExpr(Expr.Binary expr) {
    expr.left.accept(this);
    expr.right.accept(this);
    stackable(expr.operator.lexeme);

    return null;
  }

  @Override
  public Void visitGroupingExpr(Expr.Grouping expr) {
    stackable("(");
    expr.expression.accept(this);
    stackable(")");

    return null;
  }

  @Override
  public Void visitLiteralExpr(Expr.Literal expr) {
    if (expr.value == null) {
      out.add("nil");
    }

    out.add(expr.value.toString());

    return null;
  }

  @Override
  public Void visitUnaryExpr(Expr.Unary expr) {
    // TODO - skipped (my simple test uses no unaryExpr)
    return null;
  }

  private void stackable(String operator) {
    if (operator == "(") {
      stack.add("(");
    }
    else if (operator == ")") {
      while (!stack.isEmpty() && peek() != "(") {
        out.add(pop());
      }
      pop();
    }
    else {
      while (!stack.isEmpty() && precedence.get(operator) <= precedence.get(peek())) {
        out.add(pop());
      }
      stack.add(operator);
    }
  }

  private String peek() {
    return stack.get(stack.size() - 1);
  }

  private String pop() {
    return stack.remove(stack.size() - 1);
  }

  public static void main(String[] args) {
    System.out.println("(1 + 2) * (4 - 3)");

    Expr expression = new Expr.Binary(
      new Expr.Grouping(
        new Expr.Binary(new Expr.Literal(1), new Token(TokenType.PLUS, "+", null, 1), new Expr.Literal(2))
      ),

      new Token(TokenType.STAR, "*", null, 1),

      new Expr.Grouping(
        new Expr.Binary(new Expr.Literal(4), new Token(TokenType.MINUS, "-", null, 1), new Expr.Literal(3))
      )
    );

    System.out.println("ast: " + new AstPrinter().print(expression));
    System.out.println("rpn: " + new RpnPrinter().print(expression));
  }
}
