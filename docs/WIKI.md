# 📖 Project Emurald — Wiki

> Este documento resume todos los cambios, características y tareas pendientes del proyecto, organizados por categoría. Está generado a partir del historial de Issues y Pull Requests del repositorio.

---

## 📋 Tabla de Contenidos

1. [Sobre el Proyecto](#sobre-el-proyecto)
2. [Características Implementadas (QoL)](#características-implementadas-qol)
3. [Características Implementadas (Jugabilidad)](#características-implementadas-jugabilidad)
4. [Características Implementadas (Gráficos y Visuales)](#características-implementadas-gráficos-y-visuales)
5. [Sistema RTC y Estaciones](#sistema-rtc-y-estaciones)
6. [Sistemas de Entrenadores](#sistemas-de-entrenadores)
7. [Evoluciones Mejoradas](#evoluciones-mejoradas)
8. [Tareas en Desarrollo (Abiertas)](#tareas-en-desarrollo-abiertas)
9. [Bugs Conocidos](#bugs-conocidos)
10. [Actualizaciones del Upstream (RHH)](#actualizaciones-del-upstream-rhh)
11. [Historial de Pull Requests](#historial-de-pull-requests)

---

## Sobre el Proyecto

**Project Emurald** es un ROM hack de Pokémon Emerald basado en [pokeemerald-expansion](https://github.com/rh-hideout/pokeemerald-expansion) de RHH (Rom Hacking Hideout). El proyecto incorpora numerosas mejoras de calidad de vida, sistemas de jugabilidad nuevos y cambios visuales para ofrecer una experiencia más moderna y equilibrada.

---

## Características Implementadas (QoL)

Estas son las mejoras de calidad de vida que ya han sido integradas al proyecto:

| # | Característica | Descripción | Issue / PR |
|---|---------------|-------------|------------|
| 1 | **Guardar más rápido** | Al guardar, ya no pide confirmación si se sobreescribe la misma partida. Además agrega una animación de "throbber" mientras guarda. | [#1](https://github.com/DiegoPincheiraIb/project_emurald/issues/1) / [PR #68](https://github.com/DiegoPincheiraIb/project_emurald/pull/68) |
| 2 | **Texto más rápido y opciones por defecto** | Ajusta la velocidad del texto y cambia las opciones predeterminadas (`TextSpeed: HIGH`, `Sound: STEREO`). | [#2](https://github.com/DiegoPincheiraIb/project_emurald/issues/2) / [PR #12](https://github.com/DiegoPincheiraIb/project_emurald/pull/12) |
| 3 | **Auto-Run con tecla R** | Permite activar/desactivar la carrera automática presionando R. | [#16](https://github.com/DiegoPincheiraIb/project_emurald/issues/16) / [PR #29](https://github.com/DiegoPincheiraIb/project_emurald/pull/29) |
| 4 | **Bici en intro según género del jugador** | El personaje en la cinemática de intro ahora corresponde al género elegido del jugador. | [#17](https://github.com/DiegoPincheiraIb/project_emurald/issues/17) |
| 5 | **Nurse Joy más rápida** | Acorta la interacción con la Enfermera Joy: hablas, curas y te vas. | [#13](https://github.com/DiegoPincheiraIb/project_emurald/issues/13) |
| 6 | **Los entrenadores ya no giran para mirarte** | Los entrenadores no se giran abruptamente cuando pasas cerca de ellos. | [#20](https://github.com/DiegoPincheiraIb/project_emurald/issues/20) |
| 7 | **Nombres predeterminados mejorados** | Los nombres por defecto se limpiaron a: **Brendan/Ruby** y **Sapphy/May**. | [#19](https://github.com/DiegoPincheiraIb/project_emurald/issues/19) |
| 8 | **Pantalla de error "Wrong Save Type" mejorada** | En lugar de pantalla blanca, ahora muestra un mensaje de error descriptivo. | [#21](https://github.com/DiegoPincheiraIb/project_emurald/issues/21) |
| 9 | **Opción para saltar la intro** | Se puede omitir la introducción y la pantalla de copyright desde el menú. | [#22](https://github.com/DiegoPincheiraIb/project_emurald/issues/22) / [PR #56](https://github.com/DiegoPincheiraIb/project_emurald/pull/56) |
| 10 | **Diálogo de "olvidar movimiento" mejorado** | Al aprender un quinto movimiento, se elimina el paso de confirmación innecesario. Presionar B equivale a "No aprender". | [PR #70](https://github.com/DiegoPincheiraIb/project_emurald/pull/70) / [PR #42](https://github.com/DiegoPincheiraIb/project_emurald/pull/42) |

---

## Características Implementadas (Jugabilidad)

| # | Característica | Descripción | Issue / PR |
|---|---------------|-------------|------------|
| 1 | **Intercambio rápido en el equipo (SELECT)** | En el menú del equipo, se puede intercambiar la posición de los Pokémon presionando SELECT. | [#23](https://github.com/DiegoPincheiraIb/project_emurald/issues/23) / [PR #35](https://github.com/DiegoPincheiraIb/project_emurald/pull/35) |
| 2 | **Dar apodo desde el menú del equipo** | Se puede dar apodo a un Pokémon directamente desde el menú del equipo, sin visitar a un NPC. | [#24](https://github.com/DiegoPincheiraIb/project_emurald/issues/24) / [PR #34](https://github.com/DiegoPincheiraIb/project_emurald/pull/34) |
| 3 | **Recordar movimientos desde el menú del equipo** | Se puede reaprender movimientos olvidados desde el menú del equipo. | [#26](https://github.com/DiegoPincheiraIb/project_emurald/issues/26) / [PR #34](https://github.com/DiegoPincheiraIb/project_emurald/pull/34) |
| 4 | **Pantalla de resumen estilo B&W + Editor de EVs** | La pantalla de resumen de Pokémon ahora usa el estilo de Pokémon Negro/Blanco. Incluye un editor de EVs (no de IVs). | [#60](https://github.com/DiegoPincheiraIb/project_emurald/issues/60) / [PR #102](https://github.com/DiegoPincheiraIb/project_emurald/pull/102) |
| 5 | **Niveles de obediencia corregidos** | Los niveles de obediencia se ajustaron para reflejar la curva de niveles actual del proyecto (hasta nivel 100). | [#100](https://github.com/DiegoPincheiraIb/project_emurald/issues/100) / [PR #111](https://github.com/DiegoPincheiraIb/project_emurald/pull/111) |
| 6 | **Soft-cap de nivel con medallas** | Implementa un tope de nivel basado en la cantidad de medallas obtenidas por el jugador. | [#92](https://github.com/DiegoPincheiraIb/project_emurald/issues/92) / [PR #113](https://github.com/DiegoPincheiraIb/project_emurald/pull/113) |
| 7 | **Transiciones de batalla más rápidas** | Se aceleran las transiciones al entrar y salir de combate. | [#101](https://github.com/DiegoPincheiraIb/project_emurald/issues/101) / [PR #112](https://github.com/DiegoPincheiraIb/project_emurald/pull/112) |
| 8 | **Mejoras en las bayas** | Crecimiento más rápido, mayor rendimiento, diálogo más conciso, y las bayas no desaparecen hasta ser recogidas. | [#94](https://github.com/DiegoPincheiraIb/project_emurald/issues/94) / [PR #114](https://github.com/DiegoPincheiraIb/project_emurald/pull/114) |
| 9 | **Arreglo del clima Nieve** | Los copos de nieve ahora se muestran correctamente. Además, el clima nevado ahora activa el efecto de granizo en combate. | [#9](https://github.com/DiegoPincheiraIb/project_emurald/issues/9) |
| 10 | **Primeros pasos mejorados** | Desde el discurso de Birch hasta despedirse de mamá: el reloj se configura automáticamente, los Pokémon iniciales reciben apodo automáticamente, y se dan las zapatillas de correr en lugar del reloj. | [#72](https://github.com/DiegoPincheiraIb/project_emurald/issues/72) / [PR #83](https://github.com/DiegoPincheiraIb/project_emurald/pull/83) |

---

## Características Implementadas (Gráficos y Visuales)

| # | Característica | Descripción | Issue / PR |
|---|---------------|-------------|------------|
| 1 | **Throbber al guardar** | Animación visual que aparece al guardar la partida. | [#18](https://github.com/DiegoPincheiraIb/project_emurald/issues/18) |
| 2 | **Animaciones de caminar para NPCs** | Los NPCs del mapa ahora tienen animaciones de caminar (rama de Bivurnum). | [#25](https://github.com/DiegoPincheiraIb/project_emurald/issues/25) / [PR #33](https://github.com/DiegoPincheiraIb/project_emurald/pull/33) |
| 3 | **Iconos del equipo en la tarjeta de entrenador** | Se muestran los iconos de los Pokémon del equipo en la tarjeta del entrenador. | [#27](https://github.com/DiegoPincheiraIb/project_emurald/issues/27) / [PR #39](https://github.com/DiegoPincheiraIb/project_emurald/pull/39) |
| 4 | **Vista previa de mapas** | Al entrar en una zona nueva, se muestra una vista previa del mapa al estilo FRLG (rama de Bivurnum). | [#10](https://github.com/DiegoPincheiraIb/project_emurald/issues/10) / [PR #77](https://github.com/DiegoPincheiraIb/project_emurald/pull/77) |
| 5 | **Paletas de estaciones** | El juego cambia las paletas de color del entorno según la estación activa. | [#73](https://github.com/DiegoPincheiraIb/project_emurald/issues/73) / [PR #71](https://github.com/DiegoPincheiraIb/project_emurald/pull/71) |

---

## Sistema RTC y Estaciones

El sistema de **Real Time Clock (RTC)** y **Estaciones** es una de las características más importantes del proyecto:

- El reloj ya no se configura manualmente al inicio; el sistema utiliza la hora real del hardware.
- Se implementaron **4 estaciones** (Primavera, Verano, Otoño, Invierno) con paletas de color diferenciadas.
- Los **Pokémon disponibles en las rutas** cambian según el día, la hora y la estación activa.
- La hora se muestra en el **menú de inicio**.

**Issues relacionados:** [#28](https://github.com/DiegoPincheiraIb/project_emurald/issues/28), [#61](https://github.com/DiegoPincheiraIb/project_emurald/issues/61), [#65](https://github.com/DiegoPincheiraIb/project_emurald/issues/65), [#80](https://github.com/DiegoPincheiraIb/project_emurald/issues/80)  
**PRs relacionados:** [PR #37](https://github.com/DiegoPincheiraIb/project_emurald/pull/37), [PR #74](https://github.com/DiegoPincheiraIb/project_emurald/pull/74), [PR #88](https://github.com/DiegoPincheiraIb/project_emurald/pull/88), [PR #99](https://github.com/DiegoPincheiraIb/project_emurald/pull/99)

---

## Sistemas de Entrenadores

El proyecto introduce un sistema flexible y dinámico para el manejo de equipos de entrenadores:

### Entrenadores Comunes con Equipos Aleatorios
- Se añade soporte para reemplazar los Pokémon de entrenadores comunes con miembros aleatorios de un **pool de especies por clase de entrenador**.
- Distingue entre "miembros fijos" del equipo y "miembros variables".
- Los niveles de los Pokémon se escalan dinámicamente según la proximidad al jugador.

**Issue:** [#49](https://github.com/DiegoPincheiraIb/project_emurald/issues/49) | **PR:** [PR #115](https://github.com/DiegoPincheiraIb/project_emurald/pull/115)

### Equipos Aleatorios Preestablecidos para Líderes de Gimnasio / Elite 4
- Soporte para que Líderes y Miembros de la Elite 4 usen equipos predefinidos pero seleccionados aleatoriamente entre varias opciones.

**Issue:** [#117](https://github.com/DiegoPincheiraIb/project_emurald/issues/117) | **PR:** [PR #121](https://github.com/DiegoPincheiraIb/project_emurald/pull/121)

### Level Scaling para Entrenadores del Mapa
- Se está desarrollando un sistema para escalar los niveles de los entrenadores según el progreso del jugador.

**Issue:** [#91](https://github.com/DiegoPincheiraIb/project_emurald/issues/91) *(en desarrollo)*

---

## Evoluciones Mejoradas

El PR [#122](https://github.com/DiegoPincheiraIb/project_emurald/pull/122) introduce:

- **Nuevo método de evolución `EVO_LEVEL_HOLD_ITEM`**: permite que un Pokémon evolucione al alcanzar cierto nivel mientras sostiene un objeto específico.
- Actualizaciones en los datos de entrenadores para soportar los nuevos campos de composición de equipo.
- Mejoras en la configuración de pools de especies por clase.

---

## Pokéballs Rediseñadas

Se planea rediseñar varias Pokéballs para que tengan un **multiplicador de captura de 2.5x** contra ciertos tipos:

| Pokéball | Tipos efectivos |
|----------|----------------|
| Net Ball | VOLADOR + BICHO |
| Dive Ball | AGUA + HIELO |
| Moon Ball | SINIESTRO + FANTASMA |
| Fast Ball | NORMAL + ELÉCTRICO |
| Heavy Ball | ACERO + LUCHA |
| **Soil Ball** *(ex-Nest)* | TIERRA + PLANTA |
| **Scorched Ball** *(ex-Repeat)* | FUEGO + ROCA |
| **Suppressing Ball** *(ex-Lure)* | DRAGÓN + VENENO |
| **Ethereal Ball** *(ex-Love)* | PSÍQUICO + HADA |

**Issue:** [#93](https://github.com/DiegoPincheiraIb/project_emurald/issues/93) *(pendiente)*

---

## Tareas en Desarrollo (Abiertas)

Las siguientes características están actualmente planificadas o en progreso:

| # Issue | Título | Estado |
|---------|--------|--------|
| [#49](https://github.com/DiegoPincheiraIb/project_emurald/issues/49) | Equipos aleatorios para clases de entrenadores comunes | 🔄 WIP |
| [#63](https://github.com/DiegoPincheiraIb/project_emurald/issues/63) | Battle Speed Up | 🆓 Libre |
| [#62](https://github.com/DiegoPincheiraIb/project_emurald/issues/62) | Integrar expansión del Game Corner | 🆓 Libre |
| [#66](https://github.com/DiegoPincheiraIb/project_emurald/issues/66) | Base de datos de Pokémon por ruta | 🔄 WIP |
| [#90](https://github.com/DiegoPincheiraIb/project_emurald/issues/90) | Implementar Vs. Seeker | 🔄 WIP → [PR #120](https://github.com/DiegoPincheiraIb/project_emurald/pull/120) |
| [#91](https://github.com/DiegoPincheiraIb/project_emurald/issues/91) | Level Scaling para entrenadores del mapa | 🔄 WIP |
| [#93](https://github.com/DiegoPincheiraIb/project_emurald/issues/93) | Rediseño de Pokéballs | 🆓 Libre |
| [#95](https://github.com/DiegoPincheiraIb/project_emurald/issues/95) | Objetos de curación rediseñados | 🆓 Libre |
| [#116](https://github.com/DiegoPincheiraIb/project_emurald/issues/116) | Implementar Exp. Share en Rustboro | 🆓 Libre |
| [#117](https://github.com/DiegoPincheiraIb/project_emurald/issues/117) | Equipos preset aleatorios para Líderes/Elite 4 | 🔄 WIP |
| [#118](https://github.com/DiegoPincheiraIb/project_emurald/issues/118) | Balance del primer Tech Demo | 🔄 WIP |
| [#119](https://github.com/DiegoPincheiraIb/project_emurald/issues/119) | Pools de entrenadores comunes para Tech Demo | 📋 Planificado |

> **Leyenda:** 🔄 WIP = En progreso · 🆓 Libre = Disponible para contribuir · 📋 Planificado

---

## Bugs Conocidos

| # Issue | Descripción | Estado |
|---------|-------------|--------|
| [#98](https://github.com/DiegoPincheiraIb/project_emurald/issues/98) | Errores visuales en las paletas de estaciones (ej: flores de Evergrande City no cambian de color en otoño) | 🐛 Abierto |

---

## Actualizaciones del Upstream (RHH)

El proyecto se mantiene sincronizado con [pokeemerald-expansion](https://github.com/rh-hideout/pokeemerald-expansion). Historial de actualizaciones:

| PR | Versión / Descripción |
|----|-----------------------|
| [PR #3](https://github.com/DiegoPincheiraIb/project_emurald/pull/3) | Actualización a RHH v1.8.5 |
| [PR #4](https://github.com/DiegoPincheiraIb/project_emurald/pull/4) | Actualización a RHH v1.9.0 |
| [PR #5](https://github.com/DiegoPincheiraIb/project_emurald/pull/5) | Actualización a RHH v1.9.1 |
| [PR #85](https://github.com/DiegoPincheiraIb/project_emurald/pull/85) | Sincronización con upstream |
| [PR #103](https://github.com/DiegoPincheiraIb/project_emurald/pull/103) | Merge RHH — Octubre 2025 |
| [PR #108](https://github.com/DiegoPincheiraIb/project_emurald/pull/108) | Actualización a RHH v1.14.3 |
| [PR #109](https://github.com/DiegoPincheiraIb/project_emurald/pull/109) | Re-merge de v1.14.3 como commit de merge |

---

## Historial de Pull Requests

### PRs Abiertos (en revisión)

| PR | Título | Descripción |
|----|--------|-------------|
| [#120](https://github.com/DiegoPincheiraIb/project_emurald/pull/120) | Added VS SEEKER event | Agrega el evento del Vs. Seeker en Ciudad Petalia. |
| [#121](https://github.com/DiegoPincheiraIb/project_emurald/pull/121) | Adds mechanic for Random Preset Gym Leader teams | Equipos preset aleatorios para Líderes de Gimnasio. |
| [#122](https://github.com/DiegoPincheiraIb/project_emurald/pull/122) | Overhauled Evolutions | Nuevo método `EVO_LEVEL_HOLD_ITEM` y mejoras al sistema de evolución. |
| [#115](https://github.com/DiegoPincheiraIb/project_emurald/pull/115) | Adds Random Pool of Mons per Trainer Class | Infraestructura para pools de especies por clase de entrenador. |

### PRs Fusionados Destacados

| PR | Título |
|----|--------|
| [#99](https://github.com/DiegoPincheiraIb/project_emurald/pull/99) | RTC + Estaciones + Primeros Pasos mejorados |
| [#102](https://github.com/DiegoPincheiraIb/project_emurald/pull/102) | Menú B&W + Editor de EVs |
| [#111](https://github.com/DiegoPincheiraIb/project_emurald/pull/111) | Obediencia ajustada a curva de niveles actual |
| [#112](https://github.com/DiegoPincheiraIb/project_emurald/pull/112) | Transiciones de batalla más rápidas |
| [#113](https://github.com/DiegoPincheiraIb/project_emurald/pull/113) | Soft-cap de niveles con medallas |
| [#114](https://github.com/DiegoPincheiraIb/project_emurald/pull/114) | Mejoras en sistema de bayas |
| [#77](https://github.com/DiegoPincheiraIb/project_emurald/pull/77) | Vista previa de mapas (estilo FRLG) |
| [#70](https://github.com/DiegoPincheiraIb/project_emurald/pull/70) | Diálogo mejorado al olvidar movimientos |
| [#68](https://github.com/DiegoPincheiraIb/project_emurald/pull/68) | Mejoras al sistema de guardado |
| [#34](https://github.com/DiegoPincheiraIb/project_emurald/pull/34) | Menú del equipo mejorado (SELECT, apodos, recordar movs) |

---

*Última actualización: Julio 2026 — Generado automáticamente a partir de Issues y Pull Requests del repositorio.*
