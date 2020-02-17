@echo off

REM Путь к тестируемой программе передается через 1-ый параметр командной строки
SET MyProgram="%~1"

REM Защита от запуска без параметра - пути к программе
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM Сравнение пустых файлов
%MyProgram% empty1.txt empty2.txt || goto err
echo Test 1 passed 

REM Сравнение файлов, отличающихся 1-ой строкой
%MyProgram% file1.txt file2.txt && goto err
echo Test 2 passed

REM Сравнение файлов, отличающихся 2-ой строкой
%MyProgram% dif1.txt dif2.txt && goto err
echo Test 3 passed

REM Сравнение несуществующих файлов
%MyProgram% text1.txt text2.txt && goto err
echo Test 4 passed

REM Сравнение несуществующего файла с существующим
%MyProgram% text1.txt file2.txt && goto err
echo Test 5 passed
%MyProgram% file1.txt text2.txt && goto err
echo Test 6 passed

REM Запуск с недостаточным количеством параметров командной строки
%MyProgram% file1.txt && goto err
echo Test 7 passed
%MyProgram% && goto err
echo Test 8 passed

REM Запуск с лишним количеством параметров командной строки
%MyProgram% file1.txt file2.txt empty1.txt && goto err
echo Test 9 passed

REM В случае успешного прохождения всех тестов
echo All tests passed successfuly
exit /B 0

REM В случае ошибки
:err
echo Test failed
exit /B 1