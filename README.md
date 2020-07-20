# SDL2MUMMY
Remake del juego *Oh! Mummy* desarrollado en C++ con la librería SDL2 y para las siguientes plataformas:
* Desktop  
    * OSX
    * Linux
* Android
* iOS (wip)

## Notas.
Basado en la estructura de proyecto [**sdl2anddesk**](https://github.com/programatta/sdl2anddesk.git).

# Progreso.
## 20200720.
Se añade la clase **Stage** que se encarga de pintar el escenario y los pasos del jugador.
Se añade funcionalidad para notificar de cambios en el mapa.
Los eventos de juego (teclado) se recogen a través de **SDL_KeyboardState()** en vez de usar el pool de eventos.

## 20200714.
* Refactorización del código definiendo las primeras clases de juego. 

## 20200713.
* Creación del proyecto a partir de **sdl2anddesk**.
