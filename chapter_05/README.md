### 1.

grammar for method calls

```
expr → expr ( "(" ( expr ( "," expr )* )? ")" | "." IDENTIFIER )+
     | IDENTIFIER
     | NUMBER
```

```
expr → mcall | identifier | number

mcall → mcall identifier invocation
mcall → identifier invocation

invocation        → invocation_parens | invocation_dot
invocation_parens → "(" ")" | "(" arguments ")"
invocation_dot    → "." identifier

arguments → expr
arguments → expr ", " arguments
```

### 2.

```rb
Binary = Struct.new(:left, :operator, :right) do
  def print
    "(#{operator} #{left.print} #{right.print})"
  end
end

Literal = Struct.new(:value) do
  def print
    "#{value}"
  end
end

Binary.new(Literal.new(1), "+", Literal.new(2)).print
```

```js
function build_binary(left, operator, right) {
  return {
    type: "binary",
    left,
    operator,
    right,
    print: function() {
      return `(${this.operator} ${this.left.print()} ${this.right.print()})`
    }
  }
}

function build_literal(value) {
  return {
    type: "literal",
    value
    print: function() {
      return `${this.value}`
    }
  }
}

build_binary(build_literal(1), "+", build_literal(2)).print()
```

### 3.

added in `com/craftinginterpreters/lox/RpnPrinter.java`
