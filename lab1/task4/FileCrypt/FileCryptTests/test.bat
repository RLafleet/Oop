ECHO off
SET program="%1"
if %program% == "" goto err

rem without arguments
%program%
IF NOT ERRORLEVEL 1 GOTO err

rem bad arguments
%program% dsa dsa
IF NOT ERRORLEVEL 1 GOTO err

rem bad name of input file
%program% decrypt in_test321321321.txt output.txt 123 
IF NOT ERRORLEVEL 1 GOTO err

rem bad key
%program% crypt in_test3.txt output.txt 256
IF NOT ERRORLEVEL 1 GOTO err

rem bad mode
%program% scrypt in_test1.txt output.txt 256
IF NOT ERRORLEVEL 1 GOTO err

rem simply crypt
%program% crypt in_test1.txt output.txt 123
FC /b out_test1.txt output.txt
IF ERRORLEVEL 1 GOTO err

rem check if is correct data after crypt
%program% decrypt out_test1.txt output.txt 123
FC /b in_test1.txt output.txt
IF ERRORLEVEL 1 GOTO err

rem simply crypt file with big data
%program% crypt in_test2.txt output.txt 123
FC /b out_test2.txt output.txt
IF ERRORLEVEL 1 GOTO err

rem check if is correct data after crypt
%program% decrypt out_test2.txt output.txt 123
FC /b in_test2.txt output.txt
IF ERRORLEVEL 1 GOTO err

rem empty files
%program% crypt in_test3.txt output.txt 123
FC /b out_test3.txt output.txt
IF ERRORLEVEL 1 GOTO err

ECHO Tests are finished successfully.
EXIT /B
  
ECHO Tests are unsuccessful.
EXIT /B