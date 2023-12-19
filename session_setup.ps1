$path = Resolve-Path .

Function compile {gcc .\src\main.c .\include\glad\glad.c -I".\include" -L".\lib" -lglfw3}
