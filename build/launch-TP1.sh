#!/bin/sh
bindir=$(pwd)
cd /home/galax/Desktop/Projet-Moteur-de-Jeux/TP1/
export 

if test "x$1" = "x--debugger"; then
	shift
	if test "xYES" = "xYES"; then
		echo "r  " > $bindir/gdbscript
		echo "bt" >> $bindir/gdbscript
		/usr/bin/gdb -batch -command=$bindir/gdbscript --return-child-result /home/galax/Desktop/Projet-Moteur-de-Jeux/build/TP1 
	else
		"/home/galax/Desktop/Projet-Moteur-de-Jeux/build/TP1"  
	fi
else
	"/home/galax/Desktop/Projet-Moteur-de-Jeux/build/TP1"  
fi
