# The Haunted Castle

> Dungeon crawler textual por turnos desarrollado en C (ANSI/C89) para la asignatura **PPROG** \u2014 Grado en Ingenier\u00eda Inform\u00e1tica, **Universidad Aut\u00f3noma de Madrid**.

**Iteraci\u00f3n:** I3 \u00b7 **Versi\u00f3n del ejecutable:** `castle`
**Autores:** Violeta \u00b7 Rafael \u00b7 Salvador \u00b7 Javier
**Licencia:** GNU Public License

---

## \u00cdndice

1. [Descripci\u00f3n del juego](#descripci\u00f3n-del-juego)
2. [Estructura del repositorio](#estructura-del-repositorio)
3. [Arquitectura del sistema](#arquitectura-del-sistema)
4. [Compilaci\u00f3n](#compilaci\u00f3n)
5. [Ejecuci\u00f3n](#ejecuci\u00f3n)
6. [Targets del Makefile](#targets-del-makefile)
7. [Comandos disponibles](#comandos-disponibles)
8. [Reglas de las acciones](#reglas-de-las-acciones)
9. [Sistema multijugador por turnos](#sistema-multijugador-por-turnos)
10. [Motor gr\u00e1fico](#motor-gr\u00e1fico)
11. [Formato de los ficheros `.dat`](#formato-de-los-ficheros-dat)
12. [Tests unitarios](#tests-unitarios)
13. [Comprobaci\u00f3n de memoria](#comprobaci\u00f3n-de-memoria)
14. [Documentaci\u00f3n Doxygen](#documentaci\u00f3n-doxygen)
15. [Herramienta Ingit](#herramienta-ingit)
16. [Notas de dise\u00f1o](#notas-de-dise\u00f1o)

---

## Descripci\u00f3n del juego

**The Haunted Castle** es un videojuego de exploraci\u00f3n tipo dungeon crawler que funciona \u00edntegramente en terminal. El jugador (o jugadores, en modo multijugador por turnos) explora habitaciones interconectadas, recoge objetos, interact\u00faa con personajes NPC y combate contra enemigos. El objetivo es sobrevivir y explorar el castillo antes de que la salud llegue a cero.

---

## Estructura del repositorio

```
.
\u251c\u2500\u2500 src/                  # Ficheros fuente (.c)
\u2502   \u251c\u2500\u2500 game_loop.c       # Bucle principal del juego
\u2502   \u251c\u2500\u2500 game.c            # Estado global del juego
\u2502   \u251c\u2500\u2500 game_actions.c    # L\u00f3gica de acciones/comandos
\u2502   \u251c\u2500\u2500 game_reader.c     # Carga del mundo desde .dat
\u2502   \u251c\u2500\u2500 graphic_engine.c  # Motor gr\u00e1fico ASCII
\u2502   \u251c\u2500\u2500 space.c           # Salas del mapa
\u2502   \u251c\u2500\u2500 player.c          # Jugador
\u2502   \u251c\u2500\u2500 object.c          # Objetos
\u2502   \u251c\u2500\u2500 character.c       # Personajes NPC
\u2502   \u251c\u2500\u2500 inventory.c       # Inventario del jugador
\u2502   \u251c\u2500\u2500 set.c             # Conjunto de IDs
\u2502   \u251c\u2500\u2500 entity.c          # Entidad base (id + nombre)
\u2502   \u251c\u2500\u2500 links.c           # Conexiones entre salas
\u2502   \u2514\u2500\u2500 command.c         # Lectura y parseo de comandos
\u251c\u2500\u2500 headers/              # Ficheros de cabecera (.h)
\u251c\u2500\u2500 obj/                  # Objetos compilados (generado por make)
\u251c\u2500\u2500 doc/                  # Documentaci\u00f3n Doxygen (generada por make doc)
\u251c\u2500\u2500 tests/                # Tests unitarios por m\u00f3dulo
\u2502   \u251c\u2500\u2500 Makefile
\u2502   \u251c\u2500\u2500 set_test.c / set_test.h
\u2502   \u251c\u2500\u2500 entity_test.c / entity_test.h
\u2502   \u251c\u2500\u2500 space_test.c / space_test.h
\u2502   \u251c\u2500\u2500 player_test.c / player_test.h
\u2502   \u251c\u2500\u2500 character_test.c / character_test.h
\u2502   \u251c\u2500\u2500 game_test.c / game_test.h
\u2502   \u251c\u2500\u2500 command_test.c / command_test.h
\u2502   \u251c\u2500\u2500 links_test.c / links_test.h
\u2502   \u2514\u2500\u2500 object_test.c / object_test.h
\u251c\u2500\u2500 otros/                # Logs, memoria de Ingit
\u2502   \u251c\u2500\u2500 output.log
\u2502   \u2514\u2500\u2500 memoria_ingit.txt
\u251c\u2500\u2500 castle.dat            # Mapa principal (el castillo)
\u251c\u2500\u2500 anthill.dat           # Mapa alternativo (el hormiguero)
\u251c\u2500\u2500 *.cmd                 # Ficheros de comandos para pruebas de integraci\u00f3n
\u251c\u2500\u2500 libscreen.a           # Librer\u00eda de pantalla (proporcionada)
\u251c\u2500\u2500 Makefile
\u251c\u2500\u2500 Doxyfile
\u251c\u2500\u2500 Ingit.sh              # Asistente de Git del equipo
\u2514\u2500\u2500 README.md
```

---

## Arquitectura del sistema

### Entidades principales

| Entidad | Descripci\u00f3n |
|---|---|
| **Space** | Sala del mapa: hasta 4 conexiones (N/S/E/W via Links), objetos y personajes |
| **Player** | Jugador con posici\u00f3n, salud e inventario de m\u00faltiples objetos |
| **Object** | Objeto que puede estar en un espacio o en el inventario de un jugador |
| **Character** | Personaje NPC con salud, mensaje y atributo `friendly` (amistoso/enemigo) |
| **Links** | Conexi\u00f3n **bidireccional** entre dos espacios con estado abierto/cerrado independiente por sentido |

### M\u00f3dulos (TADs)

| M\u00f3dulo | Responsabilidad |
|---|---|
| `game` | Estado global: arrays de espacios, objetos, personajes, jugadores y links