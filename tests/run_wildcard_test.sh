#!/bin/zsh

#function testing for minishell

source test_framework.sh

make -C ..

echo "\n${ITALIC}${YELLOW}Testing wildcard expansion ${RESET}"

touch	Afirst Zfirst Zafirstest apple apple1 apple2 apple3 papplez applebananna bannana \
		fapple drapple .hidden .hid.this not.hidden ..what aaaazzzzaaazz thisthatthis \

exec_stdout 0 \
'
echo *
'
exec_stdout 1 \
'
echo *.sh
'
exec_stdout 2 \
'
echo
'
#issue #110
touch simplified.c srcs ss__s__ ss_____ s__
exec_stdout 3 \
'
echo s*s*
'
rm simplified.c srcs ss__s__ ss_____ s__

#issue #109
exec_stdout 4 \
'
echo "*"
'
rm	Afirst Zfirst Zafirstest apple apple1 apple2 apple3 papplez applebananna bannana \
		fapple drapple .hidden .hid.this not.hidden ..what aaaazzzzaaazz thisthatthis \
