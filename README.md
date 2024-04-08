# Grammar
You can find the <em>[`Grammar for C language here`](https://www.lysator.liu.se/c/ANSI-C-grammar-y.html)</em>.
<br>
<br>
I have attached the [reduced grammar](./GRAMMAR.md) that we worked on in this repo.

---

# How to run

1. While being in the <em>`curent repo`</em>, i.e., <em>`C-Parser`</em> use the folowing command in the terminal to run. 
```
./build <file_path_to_parse>
```
2. Output will be printed on the terminal.
3. If you do not wan't file contents to be printed, goto `src/parser.cpp` file and change `PRINT_FILE_CONTENTS` to anything other than 1.

---
## To Know
1. First and Follow Table has been given [here](./images/FirstAndFollowTable.png).
1. Predictive Parsing Table has been given [here](./images/PredictiveParsingTable.png).
1. We used the following syntax to print colored text in terminal.
```cpp
\e[<color code>m<text>\e[0m
```
<br>

| Color   | Code |
|---------|------|
| Black   | 30   |
| Red     | 31   |
| Green   | 32   |
| Yellow  | 33   |
| Blue    | 34   |
| Magenta | 35   |
| Cyan    | 36   |
| White   | 37   |