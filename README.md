# minishell
This project is about creating a simple shell. Yes, the own little bash :)

If you have things setup different you can find the path to readline with this:

brew --prefix readline

Check if readline is installed with this:

brew info readline

Edge cases:
- **cd**
    - [x]  cd
    - [x]  cd ..
    - [x]  cd .
    - [x]  cd /Users
    - [x]  cd //
    - [x]  cd '//'
    - [x]  cd //////
    - [x]  cd ./././
    - [x]  cd '/etc'
    - [x]  cd '/var'
    - [x]  cd "$PWD/prompt"
    - [x]  cd "doesntexist"
    - [x]  cd "doesntexist" 2>/dev/null
    - [x]  cd ../../..
    - [x]  cd ?
    - [x]  cd '/'
    - [x]  cd $PWD/file_tests
    - [x]  cd $OLDPWD/builtins
    - [x]  cd .. | echo "something"
    - [x]  cd / | echo "something"
    - [x]  cd .. | pwd

- **echo**
    - [x]  echo $ $
    - [x]  ECHO
    - [x]  echo rhobebou
    - [x]  echo "bonjour"
    - [x]  echo -n bonjour
    - [x]  echo -nn bonjour
    - [x]  echo -n -n -n bonjour
    - [x]  echo "-n" bonjour
	- [x]  echo text"$USER"
	- [x]  echo text"'$USER'" ' $USER '
	- [x]  echo "text"   "$USER"    "$USER"
	- [x]  echo               text "$USER"            "$USER"text
	- [x]  echo ''''''''''$USER''''''''''
	- [x]  echo """"""""$USER""""""""
	- [x]  echo $USER'$USER'text oui oui     oui  oui $USER oui      $USER '
	- [x]  echo "$USER""$USER""$USER"
	- [x]  echo text"$USER"test
	- [x]  echo '$USER' "$USER" "text \' text"
	- [x]  echo '$USER'
	- [x]  echo $USER " "
	- [x]  echo "$USER""Users/$USER/file""'$USER'"'$USER'
	- [x]  echo "$USER$USER$USER"
	- [x]  echo '$USER'"$USER"'$USER'
	- [x]  echo '"$USER"''$USER'"""$USER"
	- [x]  echo $USER
	- [x]  echo $?
	- [x]  echo $PWD/file
	- [x]  echo "$PWD/file"
	- [x]  echo "text" "text$USER" ... "$USER"
	- [x]  echo $PWD

- **exit**
    - [x]  exit 0 0
    - [x]  exit 42 42
    - [x]  exit -42 -24
    - [x]  exit 42
    - [x]  exit 259
    - [x]  exit -12030
    - [x]  exit --1239312
    - [x]  exit ++++1203020103
    - [x]  exit +0
    - [x]  exit ++++++0
    - [x]  exit -----0
    - [x]  exit azerty
    - [x]  exit "1"
    - [x]  exit "+102"
    - [x]  exit "1230"
    - [x]  exit "+++1230"
    - [x]  exit "1"23
    - [x]  exit "2"32"32"
    - [x]  exit "'42'"
    - [x]  exit +'42'"42"42
    - [x]  exit -'42'"42"42
    - [x]  exit 9223372036854775807
    - [x]  exit 9223372036854775808
    - [x]  exit echo something
    - [x]  exit exit

- **export**
    - [x]  env | grep "_="
    - [x]  export | grep "SHLVL"
    - [x]  export | grep "OLDPWD"
    - [x]  export | grep "PWD"
    - [x]  export $?
    - [x]  export TEST
    - [x]  export TEST=
    - [x]  export TEST=123
    - [x]  export ___TEST=123
    - [x]  export --TEST=123
    - [x]  export ""=""
    - [x]  export ''=''
    - [x]  export "="="="
    - [x]  export '='='='
    - [x]  export TE\\\ST=100
    - [x]  export TE-ST=100
    - [x]  export -TEST=100
    - [x]  export TEST-=100
    - [x]  export _TEST=100
    - [x]  export TES=T=""
    - [x]  export export
    - [x]  export TES^T=123
    - [x]  export TEST A=5 B= A+=7

- **pipes**
    - [x]  env | grep "_="
    - [x]  env | grep "SHLVL"
    - [x]  echo oui | cat -e
    - [x]  echo oui | echo non | echo something | grep oui
    - [x]  echo oui | echo non | echo something | grep non
    - [x]  echo oui | echo non | echo something | grep something
    - [x]  ifconfig | grep ":"
    - [x]  ifconfig | grep nothing
    - [x]  whoami | grep $USER
    - [x]  whoami | grep $USER > tmp/file
    - [x]  whoami | cat -e | cat -e > tmp/file
    - [x]  cat Makefile | grep "FLAGS"
    - [x]  cat Makefile | cat -e | cat -e
    - [x]  cat Makefile | grep "FLAGS" | grep "FLAGS" | cat -e
    - [x]  export TEST=123 | cat -e | cat -e
    - [x]  unset TEST | cat -e
    - [x]  whereis ls | cat -e | cat -e > test
    - [x]  echo test | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | ls -la | grep "."

- **unset**
    - [x]  unset
    - [x]  unset doesntexist
    - [x]  unset PWD
    - [x]  unset OLDPWD
    - [x]  unset PATH
    - [x]  unset TES.T
    - [x]  unset TES+T
    - [x]  unset TES=T
    - [x]  unset -TEST
    - [x]  unset _TEST
    - [x]  unset TES_T
    - [x]  unset TES$?T
    - [x]  unset +++++++
    - [x]  unset ________
    - [x]  unset export

- **other**
    - [x]  echo $PWD
    - [x]  echo $PWD|cat -e
    - [x]  echo $PWD hallo | cat -e
    - [x]  echo '$PWD hallo | cat -e'
	- [x]  export TEST=1 test=2 sup= | env
	- [x]  wc < Makefile -l | cat -e > outfile | echo hello | rev > outfile2
	- [x]  < test.txt < Makefile<README.md wc -l|cat -e | rev
	- [x]  < Makefile cat > out | < README.md cat -e
	- [x]  < README.md cat -e | <Makefile cat
	- [x]  < in1 cat -e | < in2 cat
	- [x]  < in1 cat -e > out1 | < in2
	- [x]  env | rev | head -5 | cat -e | rev
	- [x]  echo ok"hello"ok1"mfg" == echo ok'hello'ok1'mfg' -- okhellook1mfg
	- [x]  echo okhellook1"mfg" == echo okhellook1'mfg' -- okhellook1mfg
	- [x]  echo "o""k       "hellook1 == echo 'o''k       'hellook1 -- ok       hellook1
	- [x]  echo '"***hello***"'
	- [x]  "***hello***"
	- [x]  echo "'***hello***'"
	- [x]  "***hello***'
	- [x]  echo ok"'hello'"ok1"hello1"ok2
	- [x]  echo "text"   "$USER"    "$USER"
	- [x]  echo """"""""$USER""""""""
	- [x]  echo "'$USER'"


	- **Expansions and redirections to test:**
    
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