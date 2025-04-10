## SISTEMA PARA GESTIONAR TICKETS DE SERVICIO TECNICO
=====

---
## Descripción

Este sistema permite a los usuarios gestionar los tickets de servicio tecnico de una tienda generica. Los usuarios pueden registrar nuevos tickets, asignar o modificar prioridades de los tickets, ver todos los tickets de la lista, procesar tickets y buscar tickets en especifico. Este programa busca apoyar el servicio tecnico de cualquier organizacion, con diversas alternativas para poder gestionar tickets con problematicas, clasificandolas mediante su prioridad de atencion.
---
## Cómo compilar y ejecutar

Este sistema ha sido desarrollado en lenguaje C y puede ejecutarse fácilmente utilizando **Visual Studio Code** junto con una extensión para C/C++, como **C/C++ Extension Pack** de Microsoft. Para comenzar a trabajar con el sistema en tu equipo local, sigue estos pasos:
---
### Requisitos previos:

- Tener instalado [Visual Studio Code](https://code.visualstudio.com/).
- Instalar la extensión **C/C++** (Microsoft).
- Tener instalado un compilador de C (como **gcc**). Si estás en Windows, se recomienda instalar [MinGW](https://www.mingw-w64.org/) o utilizar el entorno [WSL](https://learn.microsoft.com/en-us/windows/wsl/).

---
### Pasos para compilar y ejecutar:

- Descarga y descomprime el archivo .zip en una carpeta de tu elección.
- Abre el proyecto en Visual Studio Code
- Inicia Visual Studio Code.
    Selecciona **Archivo > Abrir carpeta...** y elige la carpeta donde descomprimiste el proyecto.
- Compila el código
    Abre el archivo principal (**tarea1.c**).
    Abre la terminal integrada (**Terminal > Nueva terminal**).
    En la terminal, compila el programa con el siguiente comando:
        ```
        gcc tarea1.c -o tarea1.exe
        ```
- Ejecuta el programa
    Una vez compilado, puedes ejecutar la aplicación con:
        ```
        ./tarea1.exe
        ```

---
## Funcionalidades

### Funcionando correctamente:

- Registrar tickets de servicio tecnico, cada ticket cuenta con **ID**,
una **Descripcion** de 1999 caracteres disponibles,
**Hora** de ingreso y una **Prioridad** (Baja, Media o Alta).
- Asignar o modificar la prioridad de un ticket en especifico.
- Mostrar la lista de tickets pendientes junto a todos sus datos, respetando la prioridad de los mismos.
- Procesar el primer ticket de la lista, mostrando primero sus datos y un sub-menú para confirmar el procesamiento.
- Buscar un ticket en especifico mediante la ID.
- Alternativa 'salir' para finalizar el funcionamiento del programa (eliminando todos los tickets ingresados).

### Problemas conocidos:

- Cuando en algún menú se ingresa un caracter distinto a un numero se cierra el programa indicando un error.
- Cuando en algun menú se ingresa un numero distinto a los de la lista se solicita que ingresen una opcion valida.
- Cuando se agrega una ID que ya existe se indica que no se pudo ingresar porque esta ID ya se encuentra enlistada.

### A mejorar:

- Que la ID la cree la computadora en vez de el cliente.
- Permitir registrar un ticket con prioridad Alta sin tener que cambiarla luego de registrar.


## Ejemplo de uso

**Paso 1: Registrar un Nuevo Ticket**

Se comienza registrando un nuevo ticket a la plataforma.

```
**Opción seleccionada: 1) Registrar Ticket**


Ingrese ID del ticket: 1A3B
Ingrese Descripcion del Problema: EJEMPLO DE DESCRIPCION

Ticket Ingresado con Exito!
```

El sistema registra al ticket '1A3B' con una prioridad inicial "BAJA" y guarda la hora actual de registro.

**Paso 2: Asignar Prioridad a un Ticket**
Tras una registrar el ticket, el cliente puede decidir si la descripcion de el ticket es muy urgente o no tan urgente, modificando su prioridad.
```
**Opción seleccionada: 2) Asignar Prioridad a ticket**


Ingrese la ID del ticket: 1A3B
=================================================
Indique nueva prioridad para el Ticket 1A3B:

1) BAJA
2) MEDIA
3) ALTA

>>>LA PRIORIDAD DE EL TICKET 1A3B SE ASIGNO COMO [PRIORIDAD]<<<
```

**Paso 3: Mostrar Lista de Tickets Pendientes**
El cliente puede revisar todos los tickets ingresados junto a sus respectivos datos.
```
**Opción seleccionada: 3) Mostrar Lista de Tickets Pendientes**


===========================
LISTA DE TICKETS INGRESADOS
===========================

ID: 1A3B
Descripcion: EJEMPLO DE DESCRIPCION
Prioridad: BAJA
Hora de Registro: HH:MM

===========================
```
La lista muestra todos los tickets con sus datos, organizados de prioridad mas alta a la mas baja y por orden de llegada.


**Paso 4: Procesar Siguiente Ticket**

El proximo ticket de la lista será procesado.

```
**Opción seleccionada: 4) Procesar Siguiente Ticket**


========================
SIGUIENTE TICKET EN COLA
========================

ID: 1A3B
Descripcion: EJEMPLO DE DESCRIPCION
Prioridad: BAJA
Hora de Registro: HH:MM

Seleccione la operacion:

1) Procesar
2) Regresar


[SI LA SELECCION FUE 1]

Ticket Procesado con Exito!

[SI LA SELECCION FUE 2]

**Vuelve al menu**

```
El sistema muestra el siguiente ticket a procesar y abre un sub-menu para determinar si se procesa
y se elimina de la lista o vuelve al menú principal.

**Paso 5: Buscar Ticket**

Se busca un ticket en especifico mediante su ID y se muestran todos sus datos.

```
**Opción seleccionada: 5) Buscar Ticket**

Ingrese la ID del ticket: 1A3B


======================
INFORMACION DEL TICKET
======================
ID: 1A3B
Descripcion: EJEMPLO DE DESCRIPCION
Prioridad: BAJA
Hora de Registro: HH:MM
```

**Paso 6: Salir del Programa**

El cliente cierra el programa, eliminando todos los tickets registrados.

```
**Opción seleccionada: 5) Buscar Ticket**

Vuelve Pronto!!
```

**CODIGO CREADO POR MATIAS ELIHU SALAS VALDIVIA**