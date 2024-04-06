`SWITCH` `(` `expression` `)` statement;
<br>
<br>`expression`
<br>	: assignment_expression
<br>	| expression ',' assignment_expression
<br>	;
<br>
<br>
<br>`statement`
<br>	: labeled_statement
<br>	| expression_statement
<br>	;
<br>
<br>`expression_statement`
<br>	: `;`
<br>	| expression `;`
<br>	;
<br>
<br>`labeled_statement`
<br>	: `IDENTIFIER` `:` statement
<br>	| `CASE` constant_expression `:` statement
<br>	| `DEFAULT` `:` statement
<br>	;
<br>