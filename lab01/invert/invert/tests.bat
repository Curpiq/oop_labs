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
%MyProgram% matrix.txt InvalidMatrix.txt && goto err
echo Test 2 passed

REM Файл с некорректной матрицей
%MyProgram% InvalidMatrix.txt && goto err
echo Test 3 passed

REM Матрица, для которой нельзя найти обратную
%MyProgram% NonInvertMatrix.txt && goto err
echo Test 4 passed

REM Тесты проши успешно
echo All tests passed successfuly
exit /B 0

REM В случае ошибки
:err
echo Test failed
exit /B 1