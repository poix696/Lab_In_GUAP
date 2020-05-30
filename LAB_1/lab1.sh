#!/bin/bash
#place your code here
#поместите сюда код
file="dns-tunneling.log"
IFS=$'\n'
expand -t 4 results.json > results.json
echo "{" >> results.json
var1=$(sed -n '100p' $file)
for var in $(cat $file | sed -n 51,100p)
do
THREE=`echo ${var} | awk '{print $3}'`
FOUR=`echo ${var} | awk '{print $4}'`
FIVE=`echo ${var} | awk '{print $5}'`
SIX=`echo ${var} |awk '{print $6}'`
if [ "$var" == "$var1" ]; then
    echo  -e "\t\"$THREE\": {\n\t\t\"timestamp\": $FOUR,\n\t\t\"client ip\": \"$FIVE\",\n\t\t\"client port\": $SIX\n\t}">>results.json
else
   echo -e "\t\"$THREE\": {\n\t\t\"timestamp\": $FOUR,\n\t\t\"client ip\": \"$FIVE\",\n\t\t\"client port\": $SIX\n\t},">>results.json
fi
done
echo "}">>results.json
