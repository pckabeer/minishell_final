# **************************************************************************** #
#   REDIRS                                                                     #
# **************************************************************************** #

### SIMPLE ###
/bin/echo 42 > tmp_redir_out
cat tmp_redir_out
rm tmp_redir_out

/bin/echo "cat this text\n" > tmp_redir_out
cat < tmp_redir_out
rm tmp_redir_out

cat < /dev/null

/bin/echo 42 > /dev/null

/bin/echo 42 >> /dev/null

### PERMISSION DENIED ###

/bin/grep 1 < inputfile

/bin/grep 1 < NO_SUCH_FILE

/bin/grep 1 < inputfile < inputfile

/bin/grep 1 < NO_SUCH_FILE < inputfile

tmp_std_outfile

rm -f tmp_std_outfile

rm -f tmp_std_outfile

/bin/echo 1 >/dev/null | /usr/bin/grep 1

/bin/echo 1 >/dev/null | /bin/echo 2

/bin/echo >/dev/null 1 | /usr/bin/grep 1

### HERE_DOC ###
cat << lim
 "lim"
HELLO
42
 lim
testing your minishell
limm
lim

cat << lim
test
lim

cat << EOF
"EOF"
!! HELLO
@42 !!
 EOF\t\b\n
testing your minishell :)
limm
EOF

cat << 'hello'
$USER
$NOVAR
$HOME
hello

cat << 'lim'
$USER
$NOVAR
$HOME
lim

cat << lim''
$USER
$NOVAR
$HOME
lim

cat << ''lim
$USER
$NOVAR
$HOME
lim

cat << 'lim'
$USER
$NOVAR
$HOME
lim
