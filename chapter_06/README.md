### 1.

added in `Parser#comma`

### 2.

added in `Parser#expression`. added tokens for QUESTION_MARK and COLON in `TokenType` and `Scanner`

#### answers differences

- using a separate conditional
- creating a new Expr.Conditional is probs a good idea. i did `new Expr.Binary(conditional, "?", new Binary(expr, ":", expr))`. i think that could still work, but unclear what problems i've introduced there.

### 3.

added in `Parser#ep_unmatched_binary`

- adding them to the primary rule seems better than adding a whole new rule. not sure how that affects the precedence. seems to handle `+ a - b + c - d` them same.
