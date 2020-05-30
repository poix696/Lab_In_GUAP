#!/usr/bin/env bash

echo "Test.2 - MORE THEN 1 ARGUMENT"
if ! ./serverLINUX/server 1234 1234
then
echo -e "[TEST COMPLITE]\n"
else
echo -e "[TEST FILED]\n"
exit 1
fi
