ECHO off
SET program="%1"
if %program% == "" goto err

rem empty arguments
%program%
IF NOT ERRORLEVEL 1 GOTO err

rem wrong arguments
%program% dsa
IF NOT ERRORLEVEL 1 GOTO err

rem wrong argument -fin
%program% -fin 21321
IF NOT ERRORLEVEL 1 GOTO err

rem these number is not allowed because is giant
%program% 21321111111111111111111122222222222222222222222222222222222222222222222222222222222222222222222222222221111111122222222222222222222222222222222222222222222222221111111
IF NOT ERRORLEVEL 1 GOTO err

rem correct number
%program% sad 21231123
IF NOT ERRORLEVEL 1 GOTO err

rem test with symbols after number
%program% 201 dsa 
FC /b out_test1.txt output.txt
IF ERRORLEVEL 1 GOTO err

rem common test
%program% 201 
FC /b out_test2.txt output.txt
IF ERRORLEVEL 1 GOTO err

rem test with arg -find
%program% -find 100321
FC /b out_test3.txt output.txt
IF ERRORLEVEL 1 GOTO err

rem test number with unary minus
%program% -100321
FC /b out_test4.txt output.txt
IF ERRORLEVEL 1 GOTO err

ECHO Tests are finished successfully.
EXIT /B
  
ECHO Tests are unsuccessful.
EXIT /B