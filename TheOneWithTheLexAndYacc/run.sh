echo "Today: " `date`
# echo "Enter file path: "
# read 
file_path="input.txt"
echo -e "You entered" $file_path

flex lexer.l
bison parse.y

gcc lex.yy.c parse.tab.c 

# clear
echo "File content: "
strings $file_path
echo "-----------------------"

./a.out < $file_path