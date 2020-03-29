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

REM Несуществующий файл
%MyProgram% input.txt && goto err
echo Test 3 passed

REM Матрица 3х2
%MyProgram% Matrix3x2.txt && goto err
echo Test 4 passed

REM Матрица 2x3
%MyProgram% Matrix2x3.txt && goto err
echo Test 5 passed

REM Матрица 3х4
%MyProgram% Matrix3x4.txt && goto err
echo Test 6 passed

REM Матрица 4x3
%MyProgram% Matrix4x3.txt && goto err
echo Test 7 passed

REM Матрица содержит буквы
%MyProgram% MatrixWithLetters.txt && goto err
echo Test 8 passed

REM Матрица, для которой нельзя найти обратную
%MyProgram% NonInvertMatrix.txt && goto err
echo Test 9 passed

REM Корректная матрица 3х3
%MyProgram% Matrix.txt > %temp%/InvertMatrix.txt
fc InvertMatrix.txt %temp%/InvertMatrix.txt || goto err
echo Test 10 passed

REM Тесты проши успешно
echo All tests passed successfuly
exit /B 0

REM В случае ошибки
:err
echo Test failed
exit /B 1