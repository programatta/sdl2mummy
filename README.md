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
## 20200723.
Se añade -DCMAKE_BUILD_TYPE=Debug para depuración de la app.
Se añade funcionalidad para obtener objetos de juego (llave, papiro y pocion).

Se crea la clase **ItemObject** que gestiona los objetos de juego.

Se añade funcionalidad para que el juego cree esos objetos y el player los pueda recoger.


## 20200722.
Se añade una clase para el contexto del juego **GameContext**.

Se hace uso de **SDL_RenderSetLogicalSize** y se elimina toda la funcionalidad relacionada con la escala **SDL_RenderSetScale**, **SDL_RenderGetScale** y **SDL_GetRendererOutputSize** para ajustar el juego a diferentes resoluciones.

Se añade funcionalidad para el movimiento del player en los dispositivos tactiles (mediante swipes).

Se añade funcionalidad para abrir las tumbas y la puerta de final de nivel.

## 20200720.
Se añade la clase **Stage** que se encarga de pintar el escenario y los pasos del jugador.
Se añade funcionalidad para notificar de cambios en el mapa.
Los eventos de juego (teclado) se recogen a través de **SDL_KeyboardState()** en vez de usar el pool de eventos.

## 20200714.
* Refactorización del código definiendo las primeras clases de juego. 

## 20200713.
* Creación del proyecto a partir de **sdl2anddesk**.
