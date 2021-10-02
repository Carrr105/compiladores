# Proyecto final de Diseño de Compiladores (gpo 2)

Primer avance al viernes 1 de octubre de 2021: análisis de léxico y sintaxis (scanner y parser). Implementado con flex&bison. Por el momento, si no hay errores en el archivo de prueba, no muestra errores en terminal.

```
flex scanner.l
```
```
bison -dy parser.y 
```
```
gcc lex.yy.c y.tab.c -o mycompiler
```
```
./mycompiler
```

Carlos Gerardo Herrera Cortina - A00821946