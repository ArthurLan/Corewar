#!/bin/bash

######################### SCRIPT CORRECTION COREWAR ©alanter #########################

######################### COLOR #########################

BLUE="\033[1;34m"
RED="\033[8m\033[1;31m"
GREEN="\033[32m"
NORMAL="\033[0m"
LINE_ERASER="\n\033[1A\033[0K\r"

######################### EXTENSIONS #########################

EXT_S=.s
EXT_COR=.cor

######################### OPTIONS #########################

i_opt=false
s_opt=false
n_opt=false
a_opt=false
v_opt=false
d_opt=false
r_opt=false
u_opt="champs/*.s champs/*/*.s champs/*/*/*.s champs/*/*/*/*.s"
p=false

usage()
{
	printf "Usage: $0 [-i | -s | -a | -v | -d | -r | -u | -h] [-p path_to_directory]\noptions :
	i : initiate
	s : static analyzer
	n : name
	a : ./asm
	v : valgrind
	d : diff
	r : remove
	u : check in champs/tests_unitaires only
	p : choose path to directory to check
	h : help"
	exit 1
}
if [[ $1 == "" ]]; then
	usage
fi
while getopts 'isnavdrup:h' opt ;
do      case "$opt" in
	i)      i_opt=true;;
	s)      s_opt=true;;
	n)      n_opt=true;;
	a)      a_opt=true;;
	v)      v_opt=true;;
	d)      d_opt=true;;
	r)      r_opt=true;;
	u)		u_opt="champs/tests_unitaires/*.s";;
	p)		p="$OPTARG";;
	h|[?]|*)
		usage;;
	#        [?])    printf "no option"
	esac
done
if [ -a $p ]; then
	printf "\nPath selected  : $p\nIf path doesn't exist, path will be /champs\n\n"
	u_opt="$p/*.s $p/*/*.s $p/*/*/*.s"
fi
if $i_opt; then
	printf "Initiating ressources"
	if [ ! -a vm_champ.tar ]; then
		mv ~/Downloads/vm_champs.tar .
	fi
	tar -xvf vm_champs.tar
	mv asm zazasm
	mv corewar zazcorewar
	make re
fi
if $s_opt; then
	if [ -a ~/Downloads/checker-279/bin/scan-build ]; then
		printf "Compiling using static analyser"
		~/Downloads/checker-279/bin/scan-build make re
		printf "In case scan-build found bugs you can run the command ~/Downloads/checker-279/bin/scan-view /var/folders...... using the line above."
	else
		printf "You should download static analyzer : https://clang-analyzer.llvm.org/"
	fi
fi
if $a_opt || $d_opt || $r_opt || $v_opt; then
	if $a_opt; then
		if [ -f report.asm ]; then
			rm report.asm
		fi
		printf "\n\n                       <<<<~~~ ASM REPORT ~~~>>>>\n" >> report.asm
	fi
	if $v_opt; then
		if [ -f report.val ]; then
			rm report.val
		fi
		printf "\n\n                       <<<<~~~ VALGRIND REPORT ~~~>>>>\n" >> report.val
	fi
	if $d_opt; then
		if [ -f report.diff ]; then
			rm report.diff
		fi
		printf "\n\n                       <<<<~~~ DIFF REPORT ~~~>>>>\n" >> report.diff
	fi
	for file in $u_opt ;
	do
		echo $file | grep "*" > /dev/null
		if [ $? = 1 ]; then
			if $n_opt; then
				printf "<<<~~~ File : $file ~~~>>>\n"
			fi
		if $a_opt; then
			if [ ! -f asm ]; then
				make
			fi
#			printf "./asm $file"
			./asm $file 2>&1 | grep -q "Writing output"
			if [ $? = 0 ]; then
				printf "$GREEN"
				./asm $file
				printf "$NORMAL"
			else
				printf "$RED $file ~~> "
				./asm $file
				printf "$RED %.55s> " "$file -----------------------------------------"  >> report.asm
				./asm $file >> report.asm 2>&1
				printf "$NORMAL"
			fi
		fi
		if $v_opt; then
			valgrind ./asm $file > val 2>&1
			cat val | grep -q "definitely lost: 0" && cat val | grep -q "indirectly lost: 0"
			if [ $? = 1 ]; then
				printf "$RED $file has a leak :\n" >> report.val
				cat val | grep "definitely lost:" >> report.val
				cat val | grep "indirectly lost:" >> report.val
				printf "valgrind ./asm $file\n"
			else
				printf "$GREEN valgrind ./asm $file\n"
			fi
			printf "$NORMAL"
			rm val
		fi
		if $d_opt; then
			./asm $file > /dev/null 2>&1
			NEW_FILE=${file%$EXT_S}$EXT_COR
			if [ -a $NEW_FILE ]; then
				hexdump -C $NEW_FILE > 1
				./zazasm $file > /dev/null 2>&1
				hexdump -C $NEW_FILE > 2
				diff 1 2
				if [ $? = 0 ]; then
					printf "$GREEN No difference beetwen asm and zazasm on : $NORMAL$NEW_FILE\n"
				else
					printf "$RED A difference has been detected on file : $NORMAL
					$NEW_FILE\n" >> report.diff
				fi
				#printf "File cor : $NEW_FILE"
			else
				printf " $BLUE Couldn't compare because no .cor for : $NORMAL$file\n" >> report.diff
			fi
		fi
		if $r_opt; then
			NEW_FILE=${file%$EXT_S}$EXT_COR
			if [ -a $NEW_FILE ]; then
				printf "Removing $NEW_FILE\n"
				rm $NEW_FILE
			fi
		fi
	fi
	done
	if $a_opt; then
		cat report.asm
		ASM_LEN=$(cat report.ASM | wc -l)
		if [ "$ASM_LEN" == "       3" ]; then
			printf "\n$GREEN An output has been written for each file\n$NORMAL"
		fi
		rm report.asm
	fi
	if $v_opt; then
		cat report.val
		VAL_LEN=$(cat report.val | wc -l)
		if [ "$VAL_LEN" == "       3" ]; then
			printf "\n$GREEN No leak has been detected among files in /champs !\n$NORMAL"
		fi
		rm report.val
	fi
	if $d_opt; then
		cat report.diff
		cat report.diff | grep "A difference"
		if [ $? = 1 ]; then
			printf "\n$GREEN No difference has been detected between asm and zazasm on all compiled files in /champs !\n$NORMAL"
		fi
		if [ -a 1 ]; then
			rm 1 2
		fi
		rm report.diff
	fi
fi
