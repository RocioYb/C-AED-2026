#  Simulador Artemis - Ascenso con el SLS (Laboratorio de C)

>Simulación física en lenguaje C de la primera fase de ascenso de la nave Orion propulsada por el sistema SLS.

---

##  Datos del Grupo
* **Grupo:** 11
* **Comisión:** B
* **Integrantes:**
  * Amadeo Agustin Benitez
  * Ezequiel Fernández
  * Lautaro Daniel Mendieta
  * Gabriel Omar Vallejos Sanchez
  * Rocío del Cielo Ybars Gomez de la fuente

---

##  Descripción del Proyecto
El objetivo de este proyecto es simular de forma computacional el despegue de la nave **Orion** desde el Centro Espacial Kennedy impulsada por el cohete **Space Launch System (SLS)**. El programa calcula el movimiento rectilíneo uniformemente variado (MRUV), el desprendimiento de los propulsores de combustible sólido (SRB), el apagado de motores a los $160\text{ km}$ de altitud y la fase de caída libre analizando la altitud máxima alcanzada.

###  Características principales:
1. **Carga de parámetros:** Permite utilizar los valores por defecto de la misión o ingresar parámetros físicos de forma manual.
2. **Motor de cálculo físico (`simulacion.c`):** Resuelve las ecuaciones de velocidad, altitud y aceleración para cada etapa del vuelo.
3. **Validación robusta (`validaciones.c`):** Controla errores de entradas y desbordamientos en la terminal.
4. **Reporte detallado:** Muestra un informe estructurado de la simulación con control de decimales.

---

##  Situación Problemática Resuelta
El programa está diseñado para dar respuesta analítica y numérica a las siguientes incógnitas físicas del ascenso:
* **a)** Rapidez $v_1$ y altitud $y_1$ al momento del desacople de los cohetes SRB ($t = 120,0\text{ s}$).
* **b)** Rapidez máxima $v_2$ al apagar motores a $h = 160.000,0\text{ m}$ de altitud.
* **c)** Altitud máxima $h_{máx}$ alcanzada en caso de una caída libre imprevista tras el apagado de motores ($g = 9,80\text{ m/s}^2$).
* **d)** Aceleración máxima experimentada por la tripulación expresada como múltiplo de la gravedad terrestre ($g$).

---

##  Requisitos y Compilación

Para compilar y ejecutar este proyecto desde la terminal, asegúrese de tener instalado un compilador de C (como MinGW).

### 1. Compilación y ejecución
```bash
gcc main.c Artemis.c simulacion.c validaciones.c -o artemis -lm

./artemis

---

##  Uso de inteligencia Artificial 


Durante el desarrollo del proyecto se utilizó ChatGPT como herramienta de apoyo para el aprendizaje de sintaxis de lenguaje C y la programación.
Herramienta utilizada: ChatGPT, de OpenAI.
Claude, de Anthropic
Organizar un programa en C y generacion de la estructura básica del programa
Solucionar errores de compilación y enlazado.
Asistencia en la depuración de funciones y revisión de la organización modular.
Orientación para diseñar casos de prueba y mejorar las validaciones.