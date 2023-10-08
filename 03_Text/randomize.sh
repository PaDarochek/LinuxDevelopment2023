#!/bin/bash

if [ -z $1 ]; then
    DELAY=0.005;
else
    DELAY=$1;
fi
SYMBOLS="";

LINE_NUM=1;
while IFS= read LINE; do
    COL_NUM=1;
    for ((I=0;I<${#LINE};I++)); do
        CHAR=${LINE:I:1};
        BYTE=$(IFS= /bin/echo -en "$CHAR" | od -An -tx1 -v | xargs);
        if [ "$BYTE" != "0a" ] & [ "$BYTE" != "20" ]; then
            SYMBOLS+="$LINE_NUM#$COL_NUM#$BYTE ";
        fi
        COL_NUM=$((COL_NUM+1));
    done
    LINE_NUM=$((LINE_NUM+1));
done

tput clear;
SYMBOLS=$(for SYM in $SYMBOLS; do
    echo $SYM;
done | shuf);

for SYM in $SYMBOLS; do
    CHAR=$(echo $SYM | cut -d "#" -f 3 | xxd -r -p);
    if [ "$CHAR" != "20" ]; then
        sleep $DELAY;
        LINE=$(echo $SYM | cut -d "#" -f 1);
        COL=$(echo $SYM | cut -d "#" -f 2);
        tput cup $LINE $COL;
        echo -n $CHAR;
    fi
done
tput cup $LINE_NUM 0;
