# 🏰 The Haunted Castle

> Dungeon crawler textual por turnos desarrollado en C (ANSI/C89) para la asignatura **PPROG** — Grado en Ingeniería Informática, **Universidad Autónoma de Madrid**.

**Iteración:** I3 · **Versión del ejecutable:** `castle`
**Autores:** Violeta · Rafael · Salvador · Javier
**Licencia:** GNU Public License

---

## Índice

1. [Descripción del juego](#descripción-del-juego)
2. [Estructura del repositorio](#estructura-del-repositorio)
3. [Arquitectura del sistema](#arquitectura-del-sistema)
4. [Compilación](#compilación)
5. [Ejecución](#ejecución)
6. [Targets del Makefile](#targets-del-makefile)
7. [Comandos disponibles](#comandos-disponibles)
8. [Reglas de las acciones](#reglas-de-las-acciones)
9. [Sistema multijugador por turnos](#sistema-multijugador-por-turnos)
10. [Motor gráfico](#motor-gráfico)
11. [Formato de los ficheros `.dat`](#formato-de-los-ficheros-dat)
12. [Tests unitarios](#tests-unitarios)
13. [Comprobación de memoria](#comprobación-de-memoria)
14. [Documentación Doxygen](#documentación-doxygen)
15. [Herramienta Ingit](#herramienta-ingit)
16. [Notas de diseño](#notas-de-diseño)

---

## Descripción del juego

**The Haunted Castle** es un videojuego de exploración tipo dungeon crawler que funciona íntegramente en terminal. El jugador (o jugadores, en modo multijugador por turnos) explora habitaciones interconectadas, recoge objetos, interactúa con personajes NPC y combate contra enemigos. El objetivo es sobrevivir y explorar el castillo antes de que la salud llegue a cero.

---

## Estructura del repositorio

```
.
├── src/                  # Ficheros fuente (.c)
│   ├── game_loop.c       # Bucle principal del juego
│   ├── game.c            # Estado global del juego
│   ├── game_actions.c    # Lógica de acciones/comandos
│   ├── game_reader.c     # Carga del mundo desde .dat
│   ├── graphic_engine.c  # Motor gráfico ASCII
│   ├── space.c           # Salas del mapa
│   ├── player.c          # Jugador
│   ├── object.c          # Objetos
│   ├── character.c       # Personajes NPC
│   ├── inventory.c       # Inventario del jugador
│   ├── set.c             # Conjunto de IDs
│   ├── entity.c          # Entidad base (id + nombre)
│   ├── links.c           # Conexiones entre salas
│   └── command.c         # Lectura y parseo de comandos
├── headers/              # Ficheros de cabecera (.h)
├── obj/                  # Objetos compilados (generado por make)
├── doc/                  # Documentación Doxygen (generada por make doc)
├── tests/                # Tests unitarios por módulo
│   ├── Makefile
│   ├── set_test.c / set_test.h
│   ├── entity_test.c / entity_test.h
│   ├── space_test.c / space_test.h
│   ├── player_test.c / player_test.h
│   ├── character_test.c / character_test.h
│   ├── game_test.c / game_test.h
│   ├── command_test.c / command_test.h
│   ├── links_test.c / links_test.h
│   └── object_test.c / object_test.h
├── otros/                # Logs, memoria de Ingit
│   ├── output.log
│   └── memoria_ingit.txt
├── castle.dat            # Mapa principal (el castillo)
├── anthill.dat           # Mapa alternativo (el hormiguero)
├── *.cmd                 # Ficheros de comandos para pruebas de integración
├── libscreen.a           # Librería de pantalla (proporcionada)
├── Makefile
├── Doxyfile
├── Ingit.sh              # Asistente de Git del equipo
└── README.md
```

---

## Arquitectura del sistema

### Entidades principales

| Entidad | Descripción |
|---|---|
| **Space** | Sala del mapa: hasta 4 conexiones (N/S/E/W via Links), objetos y personajes |
| **Player** | Jugador con posición, salud e inventario de múltiples objetos |
| **Object** | Objeto que puede estar en un espacio o en el inventario de un jugador |
| **Character** | Personaje NPC con salud, mensaje y atributo `friendly` (amistoso/enemigo) |
| **Links** | Conexión **bidireccional** entre dos espacios con estado abierto/cerrado independiente por sentido |

### Módulos (TADs)

| Módulo | Responsabilidad |
|---|---|
| `game` | Estado global: arrays de espacios, objetos, personajes, jugadores y links; turno actual; flag de fin de partida |
| `space` | Sala: gdesc (3 líneas ASCII), conjunto de objetos, conjunto de personajes, flag de descubierta |
| `player` | Jugador: posición, salud, ataque, inventario (`Inventory`), nombre |
| `object` | Objeto: id y nombre (extiende `entity`) |
| `character` | NPC: id, nombre, salud, ataque, `friendly`, mensaje |
| `inventory` | Inventario basado en `Set`; admite límite configurable de objetos |
| `set` | Conjunto de `Id` sin duplicados; base de `inventory` y listas de objetos/personajes en espacios |
| `entity` | Base común (id + nombre) reutilizada por `player`, `object` y `character` |
| `links` | Enlace: id, nombre, espacios origen/destino, dirección, flags `open_orig_to_dest` y `open_dest_to_orig` |
| `command` | Parseo de la entrada del usuario; guarda el código de comando y el argumento de objeto/personaje |
| `game_actions` | Dispatcher de acciones: MOVE, TAKE, DROP, ATTACK, CHAT, INSPECT, EXIT |
| `game_reader` | Carga completa desde fichero `.dat` (5 loaders: spaces, objects, characters, players, links) |
| `game_loop` | Bucle principal: init → `command_get_user_input` → `game_actions_update` → `graphic_engine_paint_game` |
| `graphic_engine` | Renderizado ASCII con `libscreen`: mapa (sala actual + 4 vecinas), panel de descripción, banner, ayuda y feedback |
| `libscreen` | Librería de pintado de pantalla en terminal (proporcionada por los profesores) |

### Decisiones de diseño destacadas

- **Enfoque B:** se exponen punteros directamente (`Player*`, `Space*`, etc.) en lugar de operar siempre con IDs, lo que simplifica las llamadas entre módulos.
- **Links bidireccionales:** cada `Links` almacena `open_orig_to_dest` y `open_dest_to_orig` separadamente, permitiendo pasillos de un solo sentido. Es una extensión sobre el enunciado unidireccional.
- **`calloc` sobre `malloc`:** todos los contadores y arrays de punteros se inicializan a cero en la creación para evitar valores basura.
- **`Set` como base de `Inventory` y de objetos/personajes en `Space`:** desacopla la gestión de colecciones del resto de módulos.
- **Descubrimiento de espacios (F12):** una sala sólo muestra su `gdesc`, objetos y personajes si el jugador la ha visitado alguna vez.

---

## Compilación

**Requisitos previos:** `gcc`, `make`, `valgrind` (opcional), `doxygen` (opcional).

```bash
# Compilación estándar
make

# Limpiar objetos y ejecutable
make clean

# Limpiar también obj/ y doc/
make clean_all
```

> El Makefile compila con `-Wall -Wextra -Wpedantic -ansi -g -O0`. Se espera **0 warnings** en compilación limpia.

---

## Ejecución

```bash
# Directamente con el mapa del castillo
./castle castle.dat

# Con el mapa del hormiguero
./castle anthill.dat

# Con LOG activado
./castle castle.dat -l otros/output.log
```

---

## Targets del Makefile

### Compilación

| Target | Descripción |
|---|---|
| `make` / `make all` | Compila el proyecto completo en `obj/` → ejecutable `castle` |
| `make clean` | Elimina objetos, ejecutable y logs |
| `make clean_all` | Ídem + elimina `obj/` y `doc/` |

### Ejecución

| Target | Descripción |
|---|---|
| `make run` | Ejecuta `castle.dat` sin log |
| `make runv` | Ejecuta `castle.dat` bajo **Valgrind** |
| `make run_log` | Ejecuta `castle.dat` con log en `otros/output.log` |
| `make runv_log` | Ejecuta `castle.dat` con Valgrind + log |
| `make run_custom BD=anthill.dat` | Ejecuta el `.dat` indicado |
| `make run_custom_log BD=anthill.dat` | Ídem con log |
| `make play` | **Interactivo:** lista los `.dat` disponibles, pide elección y opcionalmente activa log |
| `make playv` | Igual que `play` pero bajo **Valgrind** |

### Tests de integración

```bash
# Redirige un fichero .cmd como entrada estándar y genera el LOG
make test_cmd CMD=game1.cmd
```

### Utilidades

| Target | Descripción |
|---|---|
| `make doc` | Genera documentación Doxygen en `doc/` (requiere `Doxyfile`) |
| `make mandar` | Empaqueta el proyecto en `Game_mandar_RaVi.zip` para entrega |
| `make mandar_rm` | Elimina el zip de entrega |
| `make rm_log` | Elimina todos los ficheros `.log` |
| `make Ingit` | Lanza el asistente de Git del equipo |

---

## Comandos disponibles

| Comando | Abreviatura | Descripción |
|---|---|---|
| `next` | `n` | Mover al **sur** |
| `back` | `b` | Mover al **norte** |
| `left` | `l` | Mover al **oeste** |
| `right` | `r` | Mover al **este** |
| `take <objeto>` | `t <objeto>` | Recoger un objeto de la sala actual |
| `drop <objeto>` | `d <objeto>` | Soltar un objeto del inventario |
| `attack <objetivo>` | `a <objetivo>` | Atacar a un personaje enemigo o a otro jugador |
| `chat <personaje>` | `c <personaje>` | Hablar con un personaje amistoso |
| `inspect <objetivo>` | `i <objetivo>` | Inspeccionar un objeto en la sala o en el inventario |
| `exit` | `e` | Salir del juego |

---

## Reglas de las acciones

- **move (next/back/left/right):** el link en esa dirección debe existir y estar **abierto**. Al entrar en una sala por primera vez se marca como descubierta.
- **take:** el objeto debe estar en la sala actual. El inventario admite múltiples objetos (hasta el límite configurado en el `.dat`).
- **drop:** el jugador debe tener el objeto; se coloca en la sala actual.
- **attack (NPC):** el personaje debe estar en la misma sala, ser **enemigo** (`friendly = FALSE`) y estar vivo. Se lanza un dado 0–9: valores 0–4 el enemigo gana (jugador −1 HP); valores 5–9 el jugador gana (enemigo −1 HP). Si la salud del jugador llega a 0, la partida termina.
- **attack (PvP):** se puede atacar a otro jugador que esté en la misma sala. No se puede atacar a uno mismo.
- **chat:** el personaje debe estar en la misma sala y ser **amistoso** (`friendly = TRUE`). El motor gráfico muestra su mensaje.
- **inspect:** comprueba primero el inventario y después la sala actual; muestra la descripción del objeto.
- **Links cerrados:** bloquean el movimiento en esa dirección; se informa al jugador.

---

## Sistema multijugador por turnos

El juego soporta varios jugadores cargados desde el fichero `.dat`. Cada turno pertenece a un jugador distinto, rotando en orden circular. La función `game_turn_update` avanza al siguiente jugador tras cada acción. El motor gráfico resalta al jugador activo con un color de borde distinto para cada jugador (hasta 6 colores: azul, verde, rojo, amarillo, morado, cian).

Los personajes en la sala se etiquetan como `[ALLY]` o `[ENEMY]` en función de su atributo `friendly`.

---

## Motor gráfico

El motor gráfico renderiza el estado completo en cada turno mediante `libscreen`:

```
┌──────────────────────────────────────────────────────────────┐  ┌────────────────────┐
│  [NORTE]          [ACTUAL]           [SUR]       [ESTE/OESTE] │  │ Descripción        │
│  +-------+       +-------+       +-------+                    │  │ Objetos en sala    │
│  |  ...  |       |  ...  |       |  ...  |                    │  │ Personajes         │
│  +-------+       +-------+       +-------+                    │  │ Jugadores          │
└──────────────────────────────────────────────────────────────┘  └────────────────────┘
                   [ Turno: Jugador1 ]
  next back left right take drop attack chat inspect exit
  Resultado: OK
```

- Sólo se muestran `gdesc`, objetos y personajes de las salas **descubiertas**.
- Las barras de salud son ASCII puro: `[###--] 3 !` (compatible con `libscreen`, sin Unicode).
- Cada jugador tiene un color de borde distinto en la sala actual.

---

## Formato de los ficheros `.dat`

```
#s:<id>|<nombre>|<gdesc1>|<gdesc2>|<gdesc3>
#o:<id>|<nombre>|<space_id>
#l:<id>|<nombre>|<origin_id>|<destiny_id>|<direction>|<open_orig_to_dest>|<open_dest_to_orig>
#c:<id>|<nombre>|<space_id>|<health>|<friendly>|<message>
#p:<id>|<nombre>|<space_id>|<health>
```

- `<direction>`: `N`, `S`, `E` o `W`.
- `<open_…>`: `1` (abierto) o `0` (cerrado).
- El loader de links acepta también el formato **unidireccional** de 6 campos (compatibilidad con el enunciado base): en ese caso `open_dest_to_orig` toma el mismo valor que `open_orig_to_dest`.

---

## Tests unitarios

El directorio `tests/` contiene tests unitarios para cada módulo principal.

```bash
cd tests/

# Compilar todos los tests
make

# Ejecutar un test concreto
./set_test
./player_test
./game_test
# ... etc.

# Ejecutar con Valgrind
make vset
make vply
make vgam
# ... etc.

# Limpiar
make clean
```

### Módulos con tests

| Binario de test | Módulos cubiertos |
|---|---|
| `set_test` | `set` |
| `entity_test` | `entity`, `set` |
| `space_test` | `space`, `set` |
| `player_test` | `player`, `entity`, `inventory`, `set` |
| `character_test` | `character`, `entity` |
| `game_test` | `game` completo |
| `command_test` | `command` |
| `links_test` | `links` |
| `object_test` | `object` |

---

## Comprobación de memoria

```bash
# Con el target de make
make runv

# Manualmente con todas las opciones
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./castle castle.dat
```

> **Estado actual:** 0 fugas y 0 errores confirmados con Valgrind en I3.

---

## Documentación Doxygen

```bash
make doc
# La documentación HTML se genera en doc/
```

Todos los módulos están documentados con Doxygen (`@brief`, `@param`, `@return`, `@author`, `@version`, `@date`).

---

## Herramienta Ingit

`Ingit.sh` es el asistente de Git del equipo. Automatiza las operaciones habituales (login, push con rebase, gestión de conflictos) y mantiene estadísticas de uso en `otros/memoria_ingit.txt`.

```bash
make Ingit
# o directamente:
./Ingit.sh
```

> ⚠️ No es necesario conocer los comandos de Git para usarla. Ingit guía el proceso paso a paso.

---

## Notas de diseño

- **`entity`** proporciona la base común (id + nombre) para `Player`, `Object` y `Character`, eliminando duplicación de código.
- **`Set` e `Inventory`** desacoplan la gestión de colecciones del resto de módulos; `space` los usa internamente para sus listas de objetos y personajes.
- **Links bidireccionales** separan la topología del mapa de los propios espacios y permiten pasillos con distintos estados de apertura según la dirección de tránsito.
- **`graphic_engine`** está deliberadamente desacoplado del estado del juego (`game`) para mantener la separación de responsabilidades (MVC-like).
- **`libscreen`** no admite códigos de escape ANSI dentro de `screen_area_puts` ni caracteres Unicode multibyte; todo el color se gestiona mediante `screen_paint(Frame_color)` y sólo se usan caracteres ASCII de un byte.

---

*PPROG — Programación — Grado en Ingeniería Informática, UAM — Curso 2025/2026*
