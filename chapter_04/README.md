1. their significant indentation requires the parser to hold state about the level of indentation across lines

2. i know in ruby the lack of space is significant when calling methods -- i.e. `puts()` is ok, but `puts ()` is not. coffeescript had significant indentation for function bodies and other blocks curly braces would normally delimit. idk about c.

3. pragma / magic comments. documentation generation.

4. idk what nesting them means. c doesn't seem to support that...? but wrote an implementation that ignores nesting.
