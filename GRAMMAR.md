# Grammar

<br>switch_statement:
<br>    SWITCH '(' expression ')' '{' labeled_statement_list '}'
<br>
<br>labeled_statement_list:
<br>    labeled_statement_list labeled_statement
<br>    | labeled_statement
<br>
<br>labeled_statement:
<br>    CASE constant ':' statement
<br>    | DEFAULT ':' statement
<br>
<br>expression:
<br>    additive_expression
<br>
<br>additive_expression:
<br>    multiplicative_expression
<br>    | additive_expression '+' multiplicative_expression
<br>    | additive_expression '-' multiplicative_expression
<br>
<br>multiplicative_expression:
<br>    primary_expression
<br>    | multiplicative_expression '*' primary_expression
<br>    | multiplicative_expression '/' primary_expression
<br>
<br>primary_expression:
<br>    identifier
<br>    | constant
<br>    | '(' expression ')'

---