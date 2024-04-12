ECHO off
SET program="%1"
if %program% == "" goto err

rem without arguments
%program%
IF NOT ERRORLEVEL 1 GOTO err

rem bad name of input and output file
%program% dsa dsa
IF NOT ERRORLEVEL 1 GOTO err

rem bad name of input file
%program% in_test321321321.txt output.txt 123 1
IF NOT ERRORLEVEL 1 GOTO err

rem good and simply replace 
%program% in_test1.txt output.txt unsuccessful successful
FC /b out_test1.txt output.txt
IF ERRORLEVEL 1 GOTO err

rem cycling test
%program% in_test2.txt output.txt ze zeze
FC /b out_test2.txt output.txt
IF ERRORLEVEL 1 GOTO err

rem empty input file
%program% in_test3.txt output.txt emptyIn emptyOut
FC /b out_test3.txt output.txt
IF ERRORLEVEL 1 GOTO err

rem good and simply replace to check cycling
%program% in_test4.txt output.txt ze zezezeze
FC /b out_test4.txt output.txt
IF ERRORLEVEL 1 GOTO err

rem check correct replace space
%program% in_test5.txt output.txt " " "  "
FC /b out_test5.txt output.txt
IF ERRORLEVEL 1 GOTO err

rem check correct processing empty find strings
%program% in_test6.txt output.txt "" "1"
FC /b out_test6.txt output.txt
IF ERRORLEVEL 1 GOTO err

rem check correct processing empty replacement strings
%program% in_test7.txt output.txt 5 ""
FC /b out_test7.txt output.txt
IF ERRORLEVEL 1 GOTO err

rem check correct processing empty find and replacement strings
%program% in_test8.txt output.txt "" ""
FC /b out_test8.txt output.txt
IF ERRORLEVEL 1 GOTO err

ECHO Tests are finished successfully.
EXIT /B
  
ECHO Tests are unsuccessful.
EXIT /B