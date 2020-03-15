@echo off

REM Путь к тестируемой программе передается через 1-ый параметр командной строки
SET MyProgram="%~1"

REM Защита от запуска без параметра - пути к программе
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM Запуск с недостаточным количеством параметров
%MyProgram% && goto err
echo Test 1 passed

REM Запуск с лишним количеством параметров
%MyProgram% 1 3 && goto err
echo Test 2 passed

REM Если аргумент - не число
%MyProgram% a && goto err
echo Test 3 passed

REM Если число находится вне диапазона функции stoi
%MyProgram% 99999999999999 && goto err
echo Test 4 passed

REM Если число > 255 
%MyProgram% 256 && goto err
echo Test 5 passed

REM Если число < 0
%MyProgram% -1 && goto err
echo Test 6 passed

REM Если число = 0
%MyProgram% 0 > %temp%/out0.txt
fc out0.txt %temp%/out0.txt || goto err
echo Test 7 passed

REM Если число = 255
%MyProgram% 255 > %temp%/out255.txt
fc out255.txt %temp%/out255.txt || goto err
echo Test 8 passed

REM Если число = 15 
%MyProgram% 15 > %temp%/out240.txt
fc out240.txt %temp%/out240.txt || goto err
echo Test 9 passed

REM Если число = 240
%MyProgram% 240 > %temp%/out15.txt
fc out15.txt %temp%/out15.txt || goto err
echo Test 10 passed

REM Тесты проши успешно
echo All tests passed successfuly
exit /B 0

REM В случае ошибки
:err
echo Test failed
exit /B 1