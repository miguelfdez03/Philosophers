# 🍽️ Philosophers

<h3 align="center">Simulación del problema clásico de la cena de los filósofos en C</h3>

<p align="center">
  <img src="https://img.shields.io/badge/Lenguaje-C-blue" alt="Lenguaje">
  <img src="https://img.shields.io/badge/Proyecto-42-lightgrey" alt="Proyecto">
  <img src="https://img.shields.io/badge/Estado-Completado-success" alt="Estado">
  <img src="https://img.shields.io/badge/Threads-pthread-orange" alt="Threads">
</p>

---

## 📝 Descripción

Philosophers es un proyecto de la escuela 42 que implementa una solución al clásico problema de sincronización conocido como "La Cena de los Filósofos". El programa simula filósofos sentados alrededor de una mesa circular que alternan entre **pensar**, **comer** y **dormir**, utilizando programación multihilo y técnicas de sincronización para evitar condiciones de carrera y deadlocks.

El desafío principal consiste en coordinar el acceso a recursos compartidos (tenedores) entre múltiples hilos sin que ningún filósofo muera de hambre y evitando bloqueos mutuos.

---

## 🎯 Objetivos del Proyecto

- Dominar la programación con hilos (pthreads) en C
- Implementar sincronización thread-safe utilizando mutexes
- Prevenir y resolver deadlocks en sistemas concurrentes
- Gestionar recursos compartidos de forma eficiente
- Evitar condiciones de carrera (race conditions)
- Optimizar el rendimiento en entornos multihilo

---

## 🧠 Implementación del Algoritmo

Mi implementación utiliza estrategias avanzadas para garantizar una simulación robusta y libre de deadlocks:

### Prevención de Deadlocks
- **Ordenación de recursos**: Los filósofos impares toman primero el tenedor izquierdo, los pares el derecho
- **Caso especial**: Un solo filósofo no puede comer (solo tiene un tenedor disponible)
- **Sincronización inicial**: Los filósofos pares inician con un pequeño delay para reducir competencia

### Arquitectura Thread-Safe
- **Mutex por tenedor**: Cada tenedor está protegido por su propio mutex
- **Mutex de impresión**: Evita que los mensajes se superpongan en la salida
- **Mutex de comidas**: Protege el acceso a `last_meal_time` y `meals_eaten`
- **Mutex de finalización**: Controla de forma segura el estado de la simulación

### Optimizaciones Clave
- **Monitoreo eficiente**: Hilo separado supervisa muertes y cumplimiento de comidas
- **Timing preciso**: Función `ft_usleep` personalizada para mayor precisión
- **Gestión de memoria**: Liberación correcta de todos los recursos al finalizar

---

## ⚙️ Estados y Acciones

Los filósofos pueden realizar las siguientes acciones durante la simulación:

| Acción | Descripción | Color de Salida |
|---------|-------------|-----------------|
| 🟡 **Tomar tenedor** | El filósofo toma un tenedor de la mesa | Amarillo |
| 🟢 **Comer** | El filósofo come con ambos tenedores | Verde |
| 🔵 **Dormir** | El filósofo duerme después de comer | Azul |
| 🔷 **Pensar** | El filósofo piensa mientras espera | Cian |
| 🔴 **Morir** | El filósofo muere por falta de comida | Rojo |

---

## 🔧 Uso

### Compilación
```bash
cd philo
make
```

### Comandos de Makefile
```bash
make clean    # Limpiar archivos objeto
make fclean   # Limpiar todo (incluyendo ejecutable)
make re       # Recompilar desde cero
```

### Ejecución del Programa
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Parámetros de Entrada

| Parámetro | Descripción | Tipo |
|-----------|-------------|------|
| `number_of_philosophers` | Número de filósofos (y tenedores) | Entero positivo |
| `time_to_die` | Tiempo en ms sin comer antes de morir | Milisegundos |
| `time_to_eat` | Tiempo en ms que tarda en comer | Milisegundos |
| `time_to_sleep` | Tiempo en ms que duerme | Milisegundos |
| `[number_of_times_each_philosopher_must_eat]` | Comidas requeridas (opcional) | Entero positivo |

---

## 📊 Ejemplos de Uso

### Simulación Básica (Sin Muertes)
```bash
./philo 5 800 200 200
# 5 filósofos, mueren en 800ms, comen en 200ms, duermen 200ms
```

### Caso con Muerte Esperada
```bash
./philo 4 310 200 100
# Configuración donde un filósofo debería morir
```

### Simulación con Límite de Comidas
```bash
./philo 5 800 200 200 7
# Termina cuando cada filósofo haya comido 7 veces
```

### Casos Especiales
```bash
# Un solo filósofo (muerte inevitable)
./philo 1 800 200 200

# Test de estrés
./philo 10 410 200 200

# Caso límite extremo
./philo 4 410 200 200
```

---

## 📁 Estructura del Proyecto

```
Philosophers/
├── Makefile
├── README.md
└── philo/
    ├── Makefile
    ├── include/
    │   └── philo.h              # Estructuras y prototipos principales
    └── src/
        ├── main.c               # Validación de argumentos y punto de entrada
        ├── init.c               # Inicialización de estructuras y mutexes
        ├── philosopher.c        # Rutina principal de cada filósofo
        ├── monitor.c            # Monitoreo de muertes y finalización
        ├── actions.c            # Implementación de acciones (comer, dormir)
        ├── utils_lib.c          # Funciones auxiliares (atoi, isdigit, strlen)
        ├── utils_time.c         # Gestión de tiempo y sincronización
        └── utils_print.c        # Funciones de impresión thread-safe
```

---

## 🧪 Testing y Validación

### Casos de Prueba Sistemáticos
```bash
# Test básico - ejecución indefinida sin muertes
./philo 5 800 200 200

# Test de detección de muerte
./philo 4 310 200 100

# Test de un solo filósofo
./philo 1 800 200 200

# Test con contador de comidas
./philo 5 800 200 200 7

# Test de estrés con muchos filósofos
./philo 10 410 200 200
```

### Verificaciones Importantes
- ✅ No debe haber deadlocks
- ✅ No debe haber data races
- ✅ Los mensajes deben aparecer en orden cronológico
- ✅ Las muertes deben detectarse inmediatamente
- ✅ La simulación debe terminar correctamente

---

## 🛠️ Manejo de Errores

El programa implementa validación robusta de entrada:

- **Validación de argumentos**: Verifica número correcto de parámetros
- **Validación numérica**: Asegura que todos los argumentos sean enteros positivos
- **Gestión de memoria**: Liberación correcta de todos los recursos asignados
- **Error de hilos**: Manejo apropiado de fallos en creación de threads
- **Inicialización de mutex**: Verificación de éxito en inicialización

---

## 📈 Rendimiento y Optimizaciones

### Estrategias de Optimización
- **Inicio escalonado**: Los filósofos pares inician con delay para reducir competencia
- **Monitor dedicado**: Hilo separado para supervisión evita overhead en filósofos
- **Verificación frecuente**: Checks regulares del estado de finalización para terminación rápida
- **Timing preciso**: Implementación custom de sleep para mayor precisión

### Métricas de Rendimiento
- **Latencia de detección**: Muerte detectada en < 10ms
- **Overhead de sincronización**: Mínimo impacto en performance
- **Escalabilidad**: Funciona eficientemente con 1-200 filósofos

---

## 🔍 Arquitectura Técnica

### Estructuras de Datos
```c
typedef struct s_philo {
    int             id;                 // Identificador único del filósofo
    int             meals_eaten;        // Contador de comidas realizadas
    long long       last_meal_time;     // Timestamp de última comida
    pthread_t       thread;             // Hilo del filósofo
    pthread_mutex_t *left_fork;         // Puntero al tenedor izquierdo
    pthread_mutex_t *right_fork;        // Puntero al tenedor derecho
    t_data          *data;              // Puntero a datos compartidos
} t_philo;
```

### Flujo de Ejecución
1. **Inicialización**: Configuración de estructuras y mutexes
2. **Creación de hilos**: Un hilo por filósofo + hilo monitor
3. **Simulación**: Ciclo continuo de acciones hasta finalización
4. **Limpieza**: Liberación de recursos y finalización ordenada

---

## 🚀 Norma 42

El proyecto cumple estrictamente con los estándares de la escuela 42:

- ✅ Máximo 25 líneas por función
- ✅ Máximo 5 funciones por archivo
- ✅ Sin variables globales
- ✅ Gestión correcta de memoria (sin leaks)
- ✅ Compilación sin warnings con `-Wall -Wextra -Werror`
- ✅ Uso correcto de pthreads y mutexes
- ✅ Documentación completa del código

---

## 🔗 Problemas Comunes y Soluciones

| Problema | Causa | Solución |
|----------|-------|----------|
| **Deadlock** | Orden incorrecto de mutexes | Implementar ordenación consistente de recursos |
| **Data Race** | Acceso no sincronizado | Proteger todas las variables compartidas con mutexes |
| **Muerte no detectada** | Monitor poco frecuente | Verificar estado cada 1-10ms |
| **Salida mezclada** | Impresión no sincronizada | Usar mutex de impresión en todos los prints |

---

## 📚 Aprendizajes Obtenidos

A través de este proyecto, he adquirido experiencia profunda en:

- **Programación concurrente**: Diseño y implementación de sistemas multihilo
- **Sincronización**: Uso avanzado de mutexes y primitivas de sincronización
- **Prevención de deadlocks**: Estrategias para evitar bloqueos mutuos
- **Debugging multihilo**: Técnicas para detectar y resolver race conditions
- **Optimización de rendimiento**: Minimización de overhead en sistemas concurrentes
- **Arquitectura de software**: Diseño modular y mantenible

---

## 👨‍💻 Autor

- [miguelfdez03](https://github.com/miguelfdez03)

---

- LinkedIn: https://www.linkedin.com/in/miguelfdezmunoz

---

Nota: Este repositorio se sube con el propósito de compartir mi progreso y ofrecer un recurso orientativo para aquellos que necesiten ayuda en su aprendizaje. Espero que se utilice como base de estudio y comprensión de conceptos, siempre respetando las políticas académicas de la institución.

<p align="center">🚀 Never stop learning!</p>
