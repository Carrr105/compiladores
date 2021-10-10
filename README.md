# Proyecto final de Diseño de Compiladores (gpo 2)

## Avance actual

Segundo avance al sábado 9 de octubre de 2021: La tabla de simbolos ha sido implementada (SymbolTable.h). Por el momento se hizo una implementación con una hashing table.

### Avances anteriores
Primer avance al viernes 1 de octubre de 2021: análisis de léxico y sintaxis (scanner y parser). Implementado con flex&bison. Por el momento, si no hay errores en el archivo de prueba, no muestra errores en terminal.

## Comandos

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