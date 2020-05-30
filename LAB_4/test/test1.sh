#!/usr/bin/env bash

echo "Test.1 - NO ARGUMENT"
if ! ./serverLINUX/server
then 
echo -e "[TEST COMPLITE]\n"
else 
echo -e "[TEST FAILED]\n"
exit 1
fi
