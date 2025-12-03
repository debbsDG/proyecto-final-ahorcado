# Documentación del Juego del Ahorcado en C

Este es un juego del ahorcado implementado en C utilizando la biblioteca ncurses para la interfaz gráfica en terminal.

## Estructura del Proyecto

```
ahorcado/
├── Makefile                    # Sistema de compilación
├── ahorcado                    # Ejecutable binario
├── crear_ahorcado.sh.save      # Script de creación
├── assets/
│   └── palabras.txt           # Lista de palabras para el juego
├── include/                   # Archivos de cabecera
│   ├── interfaz.h
│   ├── logica.h
│   ├── palabras.h
│   └── utilidades.h
└── src/                       # Código fuente
    ├── interfaz.c
    ├── logica.c
    ├── main.c
    ├── palabras.c
    └── utilidades.c
```

## Componentes Principales

### 1. Lógica del Juego (`logica.h`/`logica.c`)
- **EstadoJuego**: Estructura que almacena:
  - Palabra secreta y representación oculta
  - Letras usadas
  - Contador de fallos
- Funciones principales:
  - `inicializar_juego()`: Prepara un nuevo juego
  - `verificar_letra()`: Verifica si una letra está en la palabra
  - `es_ganador()`/`es_perdedor()`: Determinan el estado del juego

### 2. Gestión de Palabras (`palabras.h`/`palabras.c`)
- Carga palabras desde archivo de texto
- Selecciona palabras según nivel de dificultad:
  - **Nivel 1 (Fácil)**: 3-5 letras
  - **Nivel 2 (Medio)**: 6-8 letras  
  - **Nivel 3 (Difícil)**: 9+ letras
- Manejo dinámico de memoria para la lista de palabras

### 3. Interfaz de Usuario (`interfaz.h`/`interfaz.c`)
- Usa ncurses para interfaz gráfica en terminal
- Funciones de dibujo:
  - Horca con animación progresiva (6 etapas)
  - Tablero con información del juego
  - Menús y pantallas de presentación
- Control de entrada del usuario

### 4. Programa Principal (`main.c`)
- Flujo del juego:
  1. Inicialización y carga de palabras
  2. Presentación y entrada del nombre
  3. Menú principal (Jugar, Opciones, Salir)
  4. Bucle de juego con sistema de puntos
  5. Pantalla final

## Características del Juego

### Sistema de Puntos
- **Nivel Fácil**: +20 puntos por victoria
- **Nivel Medio**: +30 puntos por victoria  
- **Nivel Difícil**: +50 puntos por victoria

### Interfaz Visual
- Horca dibujada con caracteres ASCII
- Colores para diferentes elementos
- Animaciones de presentación
- Mensajes informativos

### Gestión de Entrada
- Solo acepta letras válidas
- Detecta letras repetidas
- Conversión automática a minúsculas

## Compilación y Ejecución

### Requisitos
- Compilador GCC
- Biblioteca ncurses

### Compilación
```bash
make        # Compilar
make clean  # Limpiar archivos generados
make run    # Compilar y ejecutar
```

### Opciones de Makefile
- `CC = gcc`: Compilador
- `CFLAGS = -std=c11 -Wall -Wextra -Iinclude`: Opciones de compilación
- `LDFLAGS = -lncurses`: Enlazador con ncurses

## Lista de Palabras
El archivo `assets/palabras.txt` contiene 20 palabras en español relacionadas con:
- Tecnología (computadora, programa, microcontrolador)
- Electrónica (arduino, raspberry)
- Programación (algoritmo, función, variable)
- Objetos comunes (casa, trenes, ejemplo)

## Flujo del Juego
1. Pantalla de inicio animada
2. Entrada del nombre del jugador
3. Menú principal
4. Selección de dificultad (en opciones)
5. Juego principal con horca visual
6. Opción de jugar otra vez o salir
7. Pantalla final

## Detalles Técnicos

### Manejo de Memoria
- Uso de `malloc`/`realloc`/`free` para lista dinámica de palabras
- Limpieza adecuada al finalizar

### Validaciones
- Comprobación de errores en apertura de archivos
- Verificación de índices y buffers
- Sanitización de entrada del usuario

### Portabilidad
- Código C11 estándar
- Uso de ncurses para compatibilidad multiplataforma en terminal

### Ejemplos de uso
- pruebas:


<img width="1920" height="1080" alt="image" src="https://github.com/user-attachments/assets/18265832-0bb7-4a2e-9aa0-f35e24382322" />
<img width="1920" height="1080" alt="image" src="https://github.com/user-attachments/assets/da6cba32-148d-4a04-9d79-a4c498bcbbe4" />
<img width="1920" height="1080" alt="image" src="https://github.com/user-attachments/assets/832fe0fc-485a-4811-ab89-570a555af0ee" />
<img width="1920" height="1080" alt="image" src="https://github.com/user-attachments/assets/63f6dfcf-954d-402d-b7a2-f94de1bc3e64" />
<img width="1920" height="1080" alt="image" src="https://github.com/user-attachments/assets/aaa8d31c-550d-49f8-92ec-d2dc3776da0b" />
