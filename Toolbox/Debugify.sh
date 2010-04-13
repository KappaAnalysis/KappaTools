#!/bin/sh

[ ! -f "$2" ] && echo "Syntax: <on/off> <FILE>" && exit
if [ "$1" == "on" ]; then
sed -i -e "s@{@{DEBUGMSG();@" $2
sed -i -e "s@}@DEBUGMSG();}@" $2
else
sed -i -e "s@{DEBUGMSG();@{@" $2
sed -i -e "s@DEBUGMSG();}@}@" $2
fi
