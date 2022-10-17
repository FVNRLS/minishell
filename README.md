# minishell
**About the project**

This project is about creating a simple shell. Yes, the own little bash :)
 
The program is capable of parsing a prompt and launching executables with arguments, along with its own 7 built-in functions.

As the project name implies, this is a mandatory-parted project - therefore it does not contain a bonus part.

So many wildcards and special characters, like ';' or '\' are not supported.

<br>

__This minishell is able to interpret the following elements:__

1. [x] a working history is setup and updates after every input. Delimiter is seen. However, it doesn’t have to update the history!
2. [x] single quotes are handled, which should prevent the shell from interpreting the metacharacters in the quoted sequence.
3. [x] double quotes are handled, which should prevent the shell from interpreting the metacharacters in the quoted sequence except for $ (dollar sign).

5. [x] redirections:

	(<) - should redirect input.
	
	(>)- should redirect output.
	
	(<<) - should be given a delimiter, then read the input until a line containing the
	
	(>>) - should redirect output in append mode.


10. [x] pipes are implemented (| character). The output of each command in the pipeline is connected to the input of the next command via a pipe.
12. [x] environment variables are handled ($ followed by a sequence of characters) which should expand to their values.
14. [x] $? is handled which should expand to the exit status of the most recently executed foreground pipeline.
16. [x] ctrl-C, and ctrl-\ signals as well as ctrl-D key input are handled, which should behave like in bash.


18. [x] In interactive mode:
    18. [x] ctrl-C displays a new prompt on a new line.
    19. [x] ctrl-D exits the shell.
    20. [x] ctrl-\ does nothing.

21. [x] builtins:
    22. [x] echo with option -n
    23. [x] cd with only a relative or absolute path
    24. [x] pwd with no options
    25. [x] export with no options
    26. [x] unset with no options
    27. [x] env with no options or arguments
    28. [x] exit with no options


<br>

**Getting started**

If you have things setup different you can find the path to readline with this:

	`brew --prefix readline`
Check if readline is installed with this:

	`brew info readline`

Install with:

	`brew install readline`
<br>

**Usage**

`make`

`./minishell`

<br><br>
**Edge cases for testing purposes**

<details>
 <summary> cd </summary>

	cd
	cd ..
	cd
    cd ..
    cd .
    cd /Users
    cd //
    cd '//'
    cd //////
    cd ./././
	cd '/etc'
	cd '/var'
	cd "$PWD/prompt"
	cd "doesntexist"
	cd "doesntexist" 2>/dev/null
	cd ../../..
	cd ?
	cd '/'
	cd $PWD/file_tests
	cd $OLDPWD/builtins
	cd .. | echo "something"
	cd / | echo "something"
	cd .. | pwd
</details>


<details>
 <summary> echo </summary>

	echo $ $
	ECHO
	echo rhobebou
	echo "bonjour"
	echo -n bonjour
	echo -nn bonjour
	echo -n -n -n bonjour
	echo "-n" bonjour
	echo text"$USER"
	echo text"'$USER'" ' $USER '
	echo "text"   "$USER"    "$USER"
	echo               text "$USER"            "$USER"text
	echo ''''''''''$USER''''''''''
	echo """"""""$USER""""""""
	echo $USER'$USER'text oui oui     oui  oui $USER oui      $USER '
	echo "$USER""$USER""$USER"
	echo text"$USER"test
	echo '$USER' "$USER" "text \' text"
	echo '$USER'
	echo $USER " "
	echo "$USER""Users/$USER/file""'$USER'"'$USER'
	echo "$USER$USER$USER"
	echo '$USER'"$USER"'$USER'
	echo '"$USER"''$USER'"""$USER"
	echo $USER
	echo $?
	echo $PWD/file
	echo "$PWD/file"
	echo "text" "text$USER" ... "$USER"
	echo $PWD
</details>

<details>
 <summary> exit </summary>

	exit 0 0
	exit 42 42
	exit -42 -24
	exit 42
	exit 259
	exit -12030
	exit --1239312
	exit ++++1203020103
	exit +0
	exit ++++++0
	exit -----0
	exit azerty
	exit "1"
	exit "+102"
	exit "1230"
	exit "+++1230"
	exit "1"23
	exit "2"32"32"
	exit "'42'"
	exit +'42'"42"42
	exit -'42'"42"42
	exit 9223372036854775807
	exit 9223372036854775808
	exit echo something
	exit exit
</details>

<details>
 <summary> export </summary>

	env | grep "_="
	export | grep "SHLVL"
	export | grep "OLDPWD"
	export | grep "PWD"
	export $?
	export TEST
	export TEST=
	export TEST=123
	export ___TEST=123
	export --TEST=123
	export ""=""
	export ''=''
	export "="="="
	export '='='='
	export TE\\\ST=100
	export TE-ST=100
	export -TEST=100
	export TEST-=100
	export _TEST=100
	export TES=T=""
	export export
	export TES^T=123
	export TEST A=5 B= A+=7
	export TEST A="5 B= A+=7"
</details>

<details>
 <summary> pipes </summary>

	env | grep "_="
	env | grep "SHLVL"
	echo oui | cat -e
	echo oui | echo non | echo something | grep oui
	echo oui | echo non | echo something | grep non
	echo oui | echo non | echo something | grep something
	ifconfig | grep ":"
	ifconfig | grep nothing
	whoami | grep $USER
	whoami | grep $USER > tmp/file
	whoami | cat -e | cat -e > tmp/file
	cat Makefile | grep "FLAGS"
	cat Makefile | cat -e | cat -e
	cat Makefile | grep "FLAGS" | grep "FLAGS" | cat -e
	export TEST=123 | cat -e | cat -e
	unset TEST | cat -e
	whereis ls | cat -e | cat -e > test
</details>

<details>
 <summary> unset </summary>

	unset
	unset doesntexist
	unset PWD
	unset OLDPWD
	unset PATH
	unset TES.T
	unset TES+T
	unset TES=T
	unset -TEST
	unset _TEST
	unset TES_T
	unset TES$?T
	unset +++++++
	unset ________
	unset export
</details>

<details>
 <summary> mixed </summary>

	echo $PWD
	echo $PWD|cat -e
	echo $PWD hallo | cat -e
	echo '$PWD hallo | cat -e'
	export TEST=1 test=2 sup= | env
	wc < Makefile -l | cat -e > outfile | echo hello | rev > outfile2
	< test.txt < Makefile<README.md wc -l|cat -e | rev
	< Makefile cat > out | < README.md cat -e
	< README.md cat -e | <Makefile cat
	< in1 cat -e | < in2 cat
	< in1 cat -e > out1 | < in2
	env | rev | head -5 | cat -e | rev
	echo ok"hello"ok1"mfg" == echo ok'hello'ok1'mfg' -- okhellook1mfg
	echo okhellook1"mfg" == echo okhellook1'mfg' -- okhellook1mfg
	echo "o""k       "hellook1 == echo 'o''k       'hellook1 -- ok       hellook1
	echo '"***hello***"'
	"***hello***"
	echo "'***hello***'"
	"***hello***'
	echo ok"'hello'"ok1"hello1"ok2
	echo "text"   "$USER"    "$USER"
	echo """"""""$USER""""""""
	echo "'$USER'"
</details>

<details>
 <summary> expansions and redirections </summary>

	```c
	echo '$PWD hallo | cat -e'
	```
	
	```c
	echo $"PWD$PATHaa"
	```
	
	```c
	echo '$"PWD$PATHaa"'
	```
	
	```c
	echo $PWD'echo'$ 123 $$$
	```
	
	```c
	echo $PWD'echo1231$$$$$$'$ 123 $$$
	```
	
	```c
	echo $PWD'$?'
	```
	
	```c
	echo $PWD $? $? $HOME$? $'12345'
	```
	
	```c
	echo **joinable_content_$PWD$PWD$PWD$**
	```
	
	```c
	echo '**joinable_content_'$PWD$PWD$PWD$**
	```
	
	```c
	echo "hello$"
	```
	
	```c
	echo "hello$$$"$PWD""$PWD
	```
	
	```c
	echo $HOME$? $'test'
	```
	
	```c
	echo $HOME$?$? $'test'
	```
	
	```c
	echo $PWD $pwd $CWD $$$ '@@"$PWD"'
	```
	
	```c
	echo $PWD'$?'"$???"
	```
	
	```c
	echo $PWD"$" $PWD$ $HOME"$"$HOME$
	```
	
	```c
	echo "$PWD" > out
	```
	
	```c
	echo $PWD $pwd $CWD $$$ '@@"$PWD"'"''"  $HOME   "''"
	```
	
	```c
	echo $PWD $pwd $CWD $$$ '@@"$PWD"'"''" aaa$HOMEaaa "''”
	```
	
	```c
	echo > merge_text dont_merge!
	```
	
	```c
	echo test > test | grep
	```
	
	```c
	>t1>t2>t3
	```
	
	```c
	< hello < hello2
	```
	
	```c
	<< 1 << 2 hello > t1 > t2 world | t3 >> shouldnt >> t4 open
	```
	
	```c
	< infile1 cat > out
	```
	
	```c
	< infile1 cat > out | < infile1 cat > out2
	```
	
	```c
	ls | ls -l | cat infile1
	```
	
	```c
	< infile1 cat | ls
	```
	
	```c
	< infile1 ls > out | < infile2 cat > out2 | echo "$PWD" > out3
	```
	
	```c
	< infile1 ls > out | < infile2 cat > out2 | echo $PWD > out3
	```
	
	```c
	echo "$PWD" > out1 | < infile1 cat > out2 | < out2 ls -l > out3
	```
	
	```c
	< infile1 ls > out -l
	```
	
	```c
	cat infile1 | cat
	```
	
	```c
	cat infile1 > out | cat | cat | ls > out2 | cat nofile | < infile2 cat > out3
	```
	
	```c
	cat infile1 > out | cat | cat | ls > out2 | cat nofile | < infile2 cat > out3 | echo SHOULD_PRINT
	```
	
	```c
	cat infile1 > out | echo SHOULD_PRINT
	```
	
	```c
	cat infile1 | echo bla
	```
	
	```c
	**echo bla > out | grep ls**
	```
	
	```c
	ls -la | cat > out | < infile | cat
	```
	
	```c
	**< infile | cat | < in**
	```
	
	```c
	**< infile cat > badfd**
	```
	
	```c
	cat badfd | /bin/ls | cat | cat > out1 | << stop cat > out2
	```
	
	```c
	<in cmd "str1 str2 str3" | cmd2 -arg | cmd3 >out >out2cmd "str1 str2 str3" >out | cmd2 -arg | cmd3 >out2 >out3
	```
	
	```c
	cmd "str1 str2 str3" >out | cmd2 -arg str | cmd3 str >out2 >out3
	```
	
	```c
	< in1 < in2
	```
	
	```c
	< in1 cat < in2
	```
	
	```c
	< Makefile > outfile > out
	```
	
	```c
	cat /dev/urandom | head -1 > out
	```
	
	```c
	echo $PWD"$" $PWD$ $HOME"$"$HOME$ '//( . )( . )\\'
	```

</details>

<br> <br>

**Contributing**

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement". Don't forget to give the project a star! Thanks again!

<br> <br>

**Acknowledgments**

Many thanks for useful advices, support and patience to:

Didar 😎 [https://github.com/4funoO/]

Heleen 💟 [https://github.com/heleenoomen]