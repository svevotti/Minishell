test cases failing so far
syntax tokens
"|" -> should print command not found, instead it prints nothing. I checked and the input i |

(=^･^=) |
bash: syntax error near unexpected token `|'
(=^･^=) ||
bash: syntax error near unexpected token `||'
(=^･^=) |||
bash: syntax error near unexpected token `||'
(=^･^=) |ls
bash: syntax error near unexpected token `|'
(=^･^=) ||ls
bash: syntax error near unexpected token `||'
(=^･^=) |||ls
bash: syntax error near unexpected token `||'
(=^･^=) | ls
bash: syntax error near unexpected token `|'
(=^･^=) || ls
bash: syntax error near unexpected token `||'
(=^･^=) ||| ls
bash: syntax error near unexpected token `||'
(=^･^=) ls |
bash: syntax error near unexpected token `|'
(=^･^=) ls ||
bash: syntax error near unexpected token `||'
(=^･^=) ls |||
bash: syntax error near unexpected token `||'
(=^･^=) ls|||
bash: syntax error near unexpected token `||'
(=^･^=) ls||
bash: syntax error near unexpected token `||'
(=^･^=) ls|
bash: syntax error near unexpected token `|'

(=^･^=) '|'
(=^･^=) '||'
||: command not found
(=^･^=) '|||'
|||: command not found
(=^･^=) "|"
(=^･^=) "||"
||: command not found
(=^･^=) "|||"
|||: command not found

(=^･^=) echo "|"
(=^･^=) echo "||"
(=^･^=) echo "|||"
(=^･^=) echo "||||"
(=^･^=) echo "ciao|"
ciao|
(=^･^=) echo 'ciao|'
ciao|

(=^･^=) ciao >>> test
bash: syntax error near unexpected token `>'
(=^･^=) ciao >>>> test
bash: syntax error near unexpected token `>>'
(=^･^=) >>test
(=^･^=) ciao<<<test
bash: syntax error near unexpected token `<'
(=^･^=) ciao<<<<test
bash: syntax error near unexpected token `<<'
(=^･^=) >>>
bash: syntax error near unexpected token `>'
(=^･^=) >>>>
bash: syntax error near unexpected token `>>'
(=^･^=) echo >>>
bash: syntax error near unexpected token `>'
(=^･^=) echo >>>>
bash: syntax error near unexpected token `>>'
(=^･^=) >>>echo
bash: syntax error near unexpected token `>'
(=^･^=) >>>>echo
bash: syntax error near unexpected token `>>'
(=^･^=) <<<echo
bash: syntax error near unexpected token `<'
(=^･^=) <<<<echo
bash: syntax error near unexpected token `<<'

echo "exit_code ->$? user ->$USER home -> $HOME" 
mini output = (exit_code ->0 user ->/home/smazzari home -> /home/smazzari)
bash output = (exit_code ->0 user ->smazzari home -> /home/smazzari)

if there are only whites spaces, it returns the prompt


6 8 9 
8