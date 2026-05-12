# Atlantic Quest — PPROG · Violeta, Rafael, Salva y Javier

> Juego de exploración y combate desarrollado en C con Raylib para la asignatura de PPROG (UAM · EPS).
> Versión I4 — Mayo 2026

---

## Descripción

**Atlantic Quest** es un juego de aventura donde controlas al explorador **Atlas** y a los **Numens**: entidades elementales que puedes reclutar, entrenar y usar en batalla. Explora un mundo compuesto por salas conectadas mediante enlaces bidireccionales, recoge objetos con efectos sobre tus Numens, combate contra criaturas corruptas y llega a la sala de los jefes finales.

El juego tiene dos modos de ejecución: **User** (con Raylib, teclado + ratón en la UI) y **test** (stdin puro, sin ventana, ideal para automatizar pruebas de integración recomendado usar -l para el log).

---

## Índice

1. [Compilación y ejecución](#compilación-y-ejecución)
2. [Modos de juego](#modos-de-juego)
3. [Comandos del juego](#comandos-del-juego)
4. [Mecánicas de juego](#mecánicas-de-juego)
5. [Los Numens](#los-numens)
6. [Objetos y efectos](#objetos-y-efectos)
7. [Pruebas de integración con .cmd](#pruebas-de-integración-con-cmd)
8. [Tests unitarios](#tests-unitarios)
9. [Formato del fichero .dat](#formato-del-fichero-dat)
10. [Guía para crear mapas y mods](#guía-para-crear-mapas-y-mods)
11. [Estructura del proyecto](#estructura-del-proyecto)
12. [Arquitectura del sistema](#arquitectura-del-sistema)

---

## Compilación y ejecución

**Requisitos:** `gcc`, `make`, `raylib` (incluida como librería estática).

```bash
make            # compila todo → ejecutable ./atlantic_quest
make clean      # elimina objetos y ejecutable
make clean_all  # elimina también logs y doc/
```

Flags de compilación: `-g -Wall -Wextra -Wpedantic -O0`

---

## Modos de juego

| Modo | Descripción |
|---|---|
| **User** | `./atlantic_quest` — menú Raylib; teclado + ratón. |
| **Test** | `./atlantic_quest -t <fichero.dat>` — lee comandos de stdin, sin ventana. |
| **Log** | Añade `-l <fichero.log>` — registra cada comando y su resultado. |
| **Determinista** | Añade `-d <semilla>` — fija `srand()` para reproducir comportamientos. |

**Targets del Makefile:**

| Target | Descripción |
|---|---|
| `make play` | Menú interactivo visual |
| `make playv` | Ídem bajo Valgrind |
| `make test_cmd CMD=<f.cmd> BD=<f.dat>` | Modo test con log en `otros/output.log` |
| `make run_text BD=<f.dat> CMD=<f.cmd>` | Modo test sin log |
| `make run_text_log` | Modo test con log |

```bash
# Ejemplos directos
./atlantic_quest -t new_game.dat                          # test básico
./atlantic_quest -t new_game.dat -l otros/out.log         # test con log
./atlantic_quest -t new_game.dat -l out.log < test_full.cmd  # CI total
```

---

## Comandos del juego

### Movimiento

| Largo | Corto | Argumento | Descripción |
|---|---|---|---|
| `move` | `m` | `north/south/east/west` | Mueve al jugador a la sala vecina si el enlace está abierto. |
| `walk` | `w` | `north/south/east/west` | Avanza una celda dentro de la sala (estilo Pokémon). Al llegar al borde, intenta cambio de sala. |

> Las abreviaturas de dirección también funcionan: `n`, `s`, `e`, `w`.

### Objetos

| Largo | Corto | Argumento | Descripción |
|---|---|---|---|
| `take` | `t` | — | Recoge el objeto en la celda que miras (visión). |
| `drop` | `d` | `[nombre]` | Suelta el objeto activo —o el nombrado— en la celda que miras. |
| `inspect` | `i` | — | Muestra la descripción del objeto en visión o del objeto activo. |
| `use` | `u` | `[nombre]` | Aplica el efecto del objeto activo (o nombrado) al Numen activo. |

### Numens

| Largo | Corto | Argumento | Descripción |
|---|---|---|---|
| `attack` | `a` | `<índice 0–3>` | Lanza la skill [0–3] del Numen activo contra enemigos en rango. |
| `chat` | `c` | — | Habla con el Numen en la celda que miras o con tu Numen activo. |
| `recruit` | `r` | — | Captura al Numen salvaje más cercano con HP <= 30% del máximo. |
| `kick` | `k` | `[nombre]` | Libera un Numen de tu equipo al mapa (en la celda que miras). |

### Sistema

| Largo | Corto | Descripción |
|---|---|---|
| `save` | `s` | Guarda la partida en `./Save_old_games/savefile.dat`. |
| `exit` | `e` | Termina la sesión. |

---

## Mecánicas de juego

### Visión y celda objetivo

El jugador siempre **mira** una celda adyacente (la **visión**). `walk` actualiza la visión automáticamente a la celda siguiente en la dirección de movimiento. `take`, `drop`, `inspect` y `chat` actúan sobre la celda de visión; si no hay nada allí, usan el objeto o Numen activo.

### Sistema de combate

Cada Numen tiene **4 skills** con radio y daño distintos. Al ejecutar `attack <índice>`:

1. Se localizan todos los Numens enemigos en el espacio actual dentro del radio de la skill.
2. Se aplica el daño a cada uno que esté en rango.
3. `FIRE_BALL` tiene además un efecto de **salpicadura** (splash) a Numens vecinos del impactado.
4. El Numen atacante **paga el coste de energía**; si no tiene energía suficiente, falla.
5. Si el HP de un enemigo cae a ≤ 0, es eliminado del mapa.

### Reclutamiento

Para reclutar un Numen salvaje (`recruit`):
- Debes tener un **Numen activo** con posición válida.
- El candidato debe ser **no corrupto**, **errante** (sin dueño) y tener **HP ≤ 30%** del máximo.
- El más cercano dentro de `4×SCALE = 160 píxeles` es capturado y pasa a tu equipo.

### Condición de victoria y derrota

- **Victoria:** derrotar al jefe final en Boss_e activa la pantalla de fin de juego.
- **Derrota:** si todos tus Numens caen a 0 HP, la partida termina.

### Regeneración

El juego aplica regeneración pasiva de energía cada cierto número de turnos gracias a `game_rules_regen`.

---

## Los Numens

Los Numens son las criaturas que puedes reclutar y usar en combate:

| Numen | Tipo | HP | Energía | Skills | Notas |
|---|---|---|---|---|---|
| Hydrolizard | Starter | 10 | 50 | 3,4,5,— | Arranque asequible |
| Faigreen | Starter | 10 | 50 | 5,2,3,1 | Velocidad alta |
| Fluffire | Starter | 10 | 50 | 2,1,2,6 | FIRE_BALL disponible |
| Lumen | Salvaje | 8 | 40 | 6,3,2,1 | En Corridor_r |
| Nemul | Salvaje | 8 | 40 | 1,5,3,2 | En End_l |
| Brocochacho | Salvaje | 7 | 50 | 1,3,4,6 | En End_r |
| Fertisand | Salvaje | 10 | 30 | 1,5,3,2 | En Corridor_l |
| Arisand | Corrupto | 20 | 25 | 1,6,7,4 | Jefe Boss_r |
| Pyjuggler | Corrupto | 20 | 50 | 1,3,6,5 | Jefe Boss_l |
| LavaBall | Corrupto | 30 | 10 | 1,6,7,3 | Jefe final Boss_e |

---

## Objetos y efectos

| Efecto (código) | Descripción |
|---|---|
| `NO_EFECT` (0) | Sin efecto; `use` siempre devuelve OK. |
| `HEALTH_PLUS` (1) | Restaura HP al Numen activo. |
| `HEALTH_LESS` (2) | Quita HP (objeto maldito). |
| `SPEED_PLUS` (3) | Aumenta velocidad del Numen activo. |
| `SPEED_LESS` (4) | Reduce velocidad. |
| `ATTACK_PLUS` (5) | Aumenta ataque del Numen activo. |
| `ATTACK_LESS` (6) | Reduce ataque. |
| `ENERGY_PLUS` (7) | Restaura energía del Numen activo. |
| `ENERGY_LESS` (8) | Reduce energía. |
| `OPEN` (9) | Abre un enlace bloqueado en el espacio actual. |
| `MULTI_EFFECT` (10) | Aplica HP + energía + ataque + velocidad a la vez. |

> Los objetos **consumibles** desaparecen al usarse, incluso si el efecto falla.

---

## Pruebas de integración con .cmd

### Cómo usar el modo test

```bash
# Compilar
make

# Ejecutar con test_full.cmd y generar log
./atlantic_quest -t new_game.dat -l otros/test_full.log < test_full.cmd

# Comparar con la salida esperada (ignorando líneas de comentario)
grep -v '^#' test_full.expected > /tmp/expected_clean.txt
diff /tmp/expected_clean.txt otros/test_full.log
```

Si `diff` no produce salida, **el juego funciona correctamente**.

### Ficheros incluidos

| Fichero | Descripción |
|---|---|
| `game1.cmd` | Secuencia original de prueba (ejemplo básico). |
| `test_full.cmd` | Prueba de integración completa — cubre todos los comandos con casos OK y ERROR. |
| `test_full.expected` | Salida de log ideal para `test_full.cmd`. Úsalo con `diff`. |

### Formato del log

Cada línea de log sigue el patrón:
```
<Comando>: <Objetivo> Result: <OK|ERROR>
```

Ejemplos:
```
Move: south Result: OK
Walk: north Result: OK
Take: UNKNOW Result: OK
Attack: 0 Result: ERROR
Exit: Generic Result: OK
UNKNOW: ??? Result: ERROR
```

### Comandos de Makefile para tests

```bash
make test_cmd                                          # usa game1.cmd + new_game.dat
make test_cmd CMD=test_full.cmd BD=new_game.dat        # usa test_full
make test_cmd CMD=test_full.cmd LOG_FILE=otros/my.log  # log personalizado
```

---

## Tests unitarios

El directorio `tests/` contiene pruebas unitarias para todos los módulos. El script `automatic_test.sh` simplifica su ejecución.

```bash
cd tests && make            # compila todos los binarios de test
cd tests && make run_all    # ejecuta todos los tests
./automatic_test.sh         # asistente interactivo (con/sin Valgrind)
make Tests                  # asistente interactivo (con/sin Valgrind)
```

Targets individuales:
```bash
cd tests && make run_game        # tests del módulo game
cd tests && make run_entity      # tests del módulo entity
cd tests && make run_player      # tests del módulo player
cd tests && make run_object      # tests del módulo object
cd tests && make run_space       # tests del módulo space
cd tests && make run_set         # tests del módulo set
cd tests && make run_links       # tests del módulo links
cd tests && make run_character   # tests del módulo character
cd tests && make run_command     # tests del módulo command
cd tests && make run_numen       # tests del módulo numen
```

---

## Formato del fichero .dat

Los ficheros `.dat` definen todo el estado inicial de una partida. Se leen con `game_management_create_from_file`.

### Espacios `#s:`

```
#s:<id>|<nombre>|<imagen.png>|<musica.mp3>|<fila0>|...|<fila11>
```

- `<imagen.png>` — ruta al PNG de fondo (relativa al ejecutable).
- `<musica.mp3>` — ruta al MP3 de ambiente. Escribe `none` para silencio.
- `<fila0>…<fila11>` — 12 cadenas de 12 caracteres. `'1'` = transitable, `'0'` = pared.

> La cuadrícula es de **12×12 celdas** de **40×40 px** (SCALE=40). El espacio total es **480×480 px**.

### Jugadores `#p:`

```
#p:<id>|<nombre>|<zona_id>|<pos_x>|<pos_y>|<vision_x>|<vision_y>|<ascii>|<max_bolsa>|<max_numens>|<numen_activo_id>|<objeto_activo_id>
```

- `<zona_id>` — espacio inicial.
- `<pos_x>/<pos_y>` — posición en píxeles (múltiplo de 40).
- `<vision_x>/<vision_y>` — celda que mira el jugador al iniciar.
- `<numen_activo_id>` — `-1` si aún no se eligió (lo asigna el menú al empezar).

### Objetos `#o:`

```
#o:<id>|<nombre>|<space_id>|<pos_x>|<pos_y>|<descripcion>|<gdesc>|<consumible>|<health>|<attack>|<energy>|<speed>|<dependency_id>|<movable>|<efecto>
```

- `<space_id>` — si coincide con el id de un jugador, el objeto va directo a su inventario.
- `<consumible>` — `1` = desaparece al usarse, `0` = permanente.
- `<dependency_id>` — id del objeto necesario para poder cogerlo (`-1` = ninguno).
- `<movable>` — `1` = siempre cogible, `0` = sólo si se tiene la dependencia.
- `<efecto>` — código de efecto (0–10, ver tabla de efectos).

### Numens `#n:`

```
#n:<id>|<nombre>|<space_id>|<pos_x>|<pos_y>|<gdesc>|<health>|<energy>|<attack>|<speed>|<skill0>|<skill1>|<skill2>|<skill3>|<following>|<corrupt>
```

- `<space_id>` — `-1` si no está en el mapa (starter o en inventario de jugador).
- `<following>` — id del jugador al que sigue; `-1` = errante (capturable).
- `<corrupt>` — `0` = amigo/capturable, `1` = enemigo permanente.

**IDs de skills disponibles:**

| ID | Nombre | Descripción |
|---|---|---|
| 1 | TAKLE | Ataque cuerpo a cuerpo básico |
| 2 | QUICK_ATTACK | Ataque rápido, radio corto |
| 3 | STEAM_ERUPTION | Explosión de vapor, daño alto |
| 4 | STAND_PLATINUM | Golpe definitivo, radio corto |
| 5 | THUNDER_SHOCK | Descarga eléctrica, radio largo |
| 6 | FIRE_BALL | Bola de fuego con splash en área |

### Enlaces `#l:`

```
#l:<id>|<nombre>|<origin_id>|<dest_id>|<direccion>|<abierto_orig_dest>|<abierto_dest_orig>
```

- `<direccion>` — `0`=Norte, `1`=Sur, `2`=Este, `3`=Oeste.
- `<abierto_orig_dest>/<abierto_dest_orig>` — `1` = abierto, `0` = cerrado (puerta bloqueada).

Los enlaces son **bidireccionales**: cada sentido puede abrirse independientemente con un objeto de efecto `OPEN`.

### Personajes NPC `#c:`

```
#c:<id>|<nombre>|<gdesc>|<space_id>|<health>|<friendly>|<mensaje>
```

- `<friendly>` — `1` = amistoso (responde a `chat`), `0` = enemigo.

---

## Guía para crear mapas y mods

¿Quieres diseñar tu propia aventura? Sólo necesitas un editor de texto y el formato `.dat` de arriba.

### Paso 1 — Planifica el mapa

Dibuja la red de espacios y conexiones en papel o en una hoja de cálculo. Ten en cuenta:

- Cada espacio es una cuadrícula de **12×12 celdas**.
- Los **bordes con enlaces** deben tener celdas transitables en las filas/columnas extremas.
- La posición de **entrada** en un espacio nuevo es siempre el borde opuesto al de salida:
  - Sales por el Este → entras en la columna 0 del espacio destino.
  - Sales por el Sur → entras en la fila 0 del espacio destino.
- El jugador empieza en `(240, 240)` de la sala inicial, mirando al sur → esa zona debe ser transitable.

### Paso 2 — Crea los ficheros de imagen y audio

- Fondos de sala: `./img_src/background/<nombre>.png` (resolución libre, se escala).
- Sprites de Numens: `./img_src/sprites/numens/<nombre>.png` (recomendado: `40×40 px`).
- Sprites de objetos: `./img_src/sprites/objects/<gdesc>.png`.
- Música: `msc_src/OST/<nombre>.mp3`.

Si no tienes assets propios, puedes reutilizar los existentes o usar `none` en el campo de música.

### Paso 3 — Escribe el fichero .dat

Usa IDs altos para no colisionar con el juego base:

```
# Nuevo espacio
#s:201|Mi_Caverna|./img_src/background/caverna.png|msc_src/OST/cueva.mp3|000011111100|000011111100|111111111111|111111111111|111111111111|111111111111|111111111111|111111111111|111111111111|111111111111|111111111111|000011111100|

# Enlace desde el Loby base (espacio 1) hacia mi caverna (espacio 201)
#l:601|Loby-Caverna|1|201|1|1|1

# Objeto nuevo
#o:301|Antorcha|201|200|200|Una antorcha que ilumina el camino.|Antorch|0|0|0|5|0|-1|1|7

# Numen nuevo (no corrupto, errante, capturable)
#n:101|Pyroserpent|201|240|320|Pyroserpent|8|45|3|2|6|3|2|1|-1|0
```

### Paso 4 — Prueba con el modo test

Crea un fichero `mi_mapa_test.cmd` y un `mi_mapa_expected.txt`, luego ejecuta:

```bash
./atlantic_quest -t mi_mapa.dat -l mi_mapa.log < mi_mapa_test.cmd
grep -v '^#' mi_mapa_expected.txt | diff - mi_mapa.log
```

### Consejos de diseño

- **Equilibra HP y skills** de los Numens enemigos en función de la dificultad esperada en cada zona.
- **Usa dependencias de objetos** para crear puzzles: el jugador necesita objeto A para poder recoger objeto B.
- **Crea puertas** con `abierto=0` en el enlace y un objeto de efecto `OPEN` que referencie el id del enlace.
- **Nombra los objetos** con una sola palabra si quieres poder referenciarlos por nombre en el modo test (`drop`, `use` sólo leen el primer token del argumento).
- **Prueba siempre en modo test** antes de lanzar el modo visual para verificar que todos los enlaces y posiciones son correctos.

---

> *"El universo de Atlantic Quest está abierto a quien se atreva a cartografiarlo.*
> *Si creas un mapa épico o un mod increíble, compártelo — siempre hay nuevas tierras que explorar."*
>
> — El equipo de desarrollo

---

## Estructura del proyecto

```
Atlantic_Quest/
├── src/                    # Código fuente (.c)
│   ├── game_loop.c         # Bucle principal y gestión de flags
│   ├── game.c              # Estado global: espacios, objetos, Numens, jugadores
│   ├── game_actions.c      # Dispatcher de comandos → handlers privados
│   ├── game_management.c   # Loaders/Savers del fichero .dat
│   ├── game_rules.c        # Reglas: move, walk, combate, regen, victoria/derrota
│   ├── graphic_engine.c    # Renderizado Raylib (modo visual)
│   ├── command.c           # Parser de stdin (modo test)
│   ├── command_raylib.c    # Parser de teclado (modo visual)
│   ├── space.c             # TAD Sala: grid, objetos, Numens, links
│   ├── player.c            # TAD Jugador: posición, inventario, Numens
│   ├── numen.c             # TAD Numen: stats, skills, estado
│   ├── object.c            # TAD Objeto: efectos, dependencias
│   ├── character.c         # TAD Personaje NPC
│   ├── links.c             # TAD Enlace bidireccional
│   ├── inventory.c         # Colección con límite de capacidad
│   ├── set.c               # Colección de IDs únicos
│   ├── entity.c            # Base común (id + nombre + stats)
│   ├── skills.c            # Tabla de skills y lógica de activación
│   └── types.c             # Utilidades de tipos (dirección, posición)
├── headers/                # Cabeceras (.h)
├── tests/                  # Tests unitarios por módulo
│   ├── Makefile
│   └── *_test.c / *_test.h
├── img_src/                # Assets gráficos (PNG)
│   ├── background/         # Fondos de sala
│   └── sprites/            # Sprites de Numens, objetos, jugador
├── msc_src/OST/            # Música del juego (MP3)
├── Save_old_games/         # Partidas guardadas
├── otros/                  # Logs de partida
├── new_game.dat            # Mapa principal (nuevo juego)
├── game1.cmd               # Ejemplo de fichero de comandos
├── test_full.cmd           # Prueba de integración completa
├── test_full.expected      # Salida esperada para diff
├── automatic_test.sh       # Asistente interactivo para tests unitarios
├── Makefile
├── Doxyfile                # Configuración de documentación Doxygen
└── README.md
```

---

## Arquitectura del sistema

### Módulos principales

| Módulo | Responsabilidad |
|---|---|
| `game` | Estado global: arrays de espacios, objetos, Numens, jugadores y links; turno activo; último comando y resultado |
| `game_management` | Seis loaders (`#s`,`#o`,`#c`,`#p`,`#l`,`#n`) que pueblan el estado desde ficheros `.dat`; función de guardado |
| `game_actions` | Dispatcher: mapea cada `CommandCode` a su handler privado |
| `game_rules` | Reglas del mundo: movimiento, condiciones de victoria/derrota, regeneración, IA de Numens enemigos |
| `game_loop` | Ciclo RENDER→INPUT→UPDATE→LOG; gestión de flags `-t`, `-l`, `-d` |
| `graphic_engine` | Renderizado Raylib: mapa, sprites, UI, menú, pantalla de game over |
| `command` | Parser de stdin para modo test: `<cmd> [<target>]` |
| `skills` | Tabla de skills y lógica de activación (daño, coste de energía, radio) |
| `numen` | TAD Numen: estadísticas, skills, estado corrupto/errante/siguiendo |
| `space` | TAD Sala: grid 12×12, sets de objetos y Numens, links, flag discovered |
| `player` | TAD Jugador: posición, visión, inventarios (objetos y Numens) |
| `entity` | Base común para Numen, Player, Object y Character |
| `set` | Colección de IDs únicos con operaciones CRUD |
| `inventory` | Wrapper de Set con límite máximo de capacidad |

### Flujo de ejecución (modo test)

```
main()
  └─ game_loop_init_test()          ← carga el .dat
       └─ game_management_create_from_file()
  └─ bucle while(!EXIT && !finished)
       ├─ command_get_user_input()  ← lee una línea de stdin
       ├─ game_actions_update()     ← ejecuta la acción
       └─ game_loop_print_log()     ← escribe en el fichero de log
```

---

## Comprobación de memoria

```bash
make runv                        # Valgrind sobre new_game.dat
make playv                       # Valgrind con menú interactivo
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./atlantic_quest -t new_game.dat < game1.cmd
```

Estado actual: **0 leaks, 0 errores** con todas las entidades cargadas.

---

## Ingit — Asistente Git del equipo

El repositorio incluye `Ingit.sh`, un asistente interactivo en Bash para simplificar el flujo de trabajo en ordenadores compartidos de la uni (donde las credenciales no persisten).

```bash
chmod +x Ingit.sh   # solo la primera vez
./Ingit.sh
```

Operaciones disponibles: Pull, Push, Status, Log, Checkout, Merge, Reset.

---

**Autores:** Violeta · Rafael · Salva · Javier
**Asignatura:** Programación (PPROG) — Grado en Ingeniería Informática, UAM
**Licencia:** GNU Public License
