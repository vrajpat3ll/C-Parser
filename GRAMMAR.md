# Grammar

<br>`switch_statement`:
<br> `SWITCH` `(` expression `)` `{` labeled_statement_list `}`
<br>

<br>`labeled_statement_list`
<br> : labeled_statement_list labeled_statement
<br> | labeled_statement
<br>;
<br>

<br>`labeled_statement`
<br> : `CASE` `CONSTANT` `:` statement
<br> | `DEFAULT` `:` statement
<br> ;
<br>

<br>`expression`
<br> : additive_expression
<br>;
<br>

<br>`additive_expression`
<br>: multiplicative_expression
<br>| additive_expression `+` multiplicative_expression
<br>| additive_expression `-` multiplicative_expression
<br>

<br>`multiplicative_expression`
<br>: primary_expression
<br>| multiplicative_expression `*` primary_expression
<br> | multiplicative_expression `/` primary_expression
<br>;
<br>

<br>`primary_expression`
<br> : `IDENTIFIER`
<br> | `CONSTANT`
<br> | `(` expression `)`
<br> ;

---