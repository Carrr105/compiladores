# Proyecto final de Diseño de Compiladores (gpo 2)

## Avance actual

Quinto avance al martes 9 de noviembre de 2021: Se han incluido avances en la máquina virtual y en el manejo de operaciones. Aún falta integrarlo todo ya que se mantienen en partes separadas.

### Avances anteriores

Cuarto avance al lunes 25 de octubre de 2021: Se ha avanzado en la parte de generación de código

Primer avance al viernes 1 de octubre de 2021: análisis de léxico y sintaxis (scanner y parser). Implementado con flex&bison. Por el momento, si no hay errores en el archivo de prueba, no muestra errores en terminal.

Segundo avance al sábado 9 de octubre de 2021: la tabla de simbolos ha sido implementada (SymbolTable.h). Por el momento se hizo una implementación con una hashing table.

Tercer avance al sábado 16 de octubre de 2021: Se ha añadido código para expresiones aritméticas

## Comandos

```
flex scanner.l
```
```
bison -dy parser.y 
```
```
g++ lex.yy.c y.tab.c -o mycompiler
```
```
./mycompiler
```

Carlos Gerardo Herrera Cortina - A00821946