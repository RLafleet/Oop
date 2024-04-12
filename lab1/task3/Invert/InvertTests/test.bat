ECHO off
SET program="%1"
if %program% == "" goto err

rem without arguments
%program%
IF NOT ERRORLEVEL 1 GOTO err

rem bad name of input file
%program% dsa
IF NOT ERRORLEVEL 1 GOTO err

rem good and simply matrix
%program% in_test1.txt
FC /b out_test1.txt output.txt
IF ERRORLEVEL 1 GOTO err

rem determinant is 0 with matrix contain almost only 0 in values
%program% in_test2.txt
FC /b out_test2.txt output.txt
IF ERRORLEVEL 1 GOTO err

rem determinant is 0 in normal matrix
%program% in_test3.txt
FC /b out_test3.txt output.txt
IF ERRORLEVEL 1 GOTO err

rem good and bad for calculate matrix
%program% in_test4.txt
FC /b out_test4.txt output.txt
IF ERRORLEVEL 1 GOTO err

rem char symbol in matrix values
%program% in_test5.txt
IF NOT ERRORLEVEL 1 GOTO err

rem giant number which not allowed
%program% in_test6.txt
IF NOT ERRORLEVEL 1 GOTO err

ECHO Tests are finished successfully.
EXIT /B
  
ECHO Tests are unsuccessful.
EXIT /B