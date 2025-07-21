# Philosophers - 42 School Project

## Descripción

El proyecto **Philosophers** simula el clásico problema de la cena de los filósofos. Varios filósofos se sientan alrededor de una mesa circular, alternando entre tres estados: **pensar**, **comer** y **dormir**. Para comer, cada filósofo necesita dos tenedores (uno a su izquierda y otro a su derecha).

### Objetivos del proyecto:
- Aprender sobre programación con hilos (threads)
- Entender la sincronización con mutexes
- Evitar condiciones de carrera (race conditions)
- Prevenir deadlocks
- Gestionar recursos compartidos

## Estructura del proyecto

```
philo/
├── Makefile
├── include/
│   └── philo.h
└── src/
    ├── main.c          # Validación de argumentos y función principal
    ├── init.c          # Inicialización de estructuras y mutexes
    ├── philosopher.c   # Lógica principal de los filósofos
    ├── monitor.c       # Monitorización de muerte y comidas
    ├── actions.c       # Acciones: tomar tenedores, comer, dormir
    └── utils.c         # Utilidades: tiempo, impresión, validación
```

## Compilación

```bash
make
```

Para limpiar archivos objeto:
```bash
make clean
```

Para limpiar todo (incluyendo el ejecutable):
```bash
make fclean
```

Para recompilar desde cero:
```bash
make re
```

## Uso

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Parámetros:

1. **number_of_philosophers**: Número de filósofos (y tenedores)
2. **time_to_die**: Tiempo en ms que un filósofo puede estar sin comer antes de morir
3. **time_to_eat**: Tiempo en ms que tarda un filósofo en comer
4. **time_to_sleep**: Tiempo en ms que un filósofo duerme
5. **[number_of_times_each_philosopher_must_eat]**: (Opcional) Número de veces que cada filósofo debe comer

## Ejemplos de uso

### Ejemplo básico (no debería morir ningún filósofo):
```bash
./philo 5 800 200 200
```

### Ejemplo con muerte (un filósofo debería morir):
```bash
./philo 4 310 200 100
```

### Ejemplo con número específico de comidas:
```bash
./philo 5 800 200 200 7
```

### Casos especiales:

#### Un solo filósofo (debería morir):
```bash
./philo 1 800 200 200
```

#### Caso extremo:
```bash
./philo 4 410 200 200
```

## Características técnicas

### Prevención de deadlocks:
- Los filósofos impares toman primero el tenedor izquierdo, luego el derecho
- Los filósofos pares toman primero el tenedor derecho, luego el izquierdo

### Sincronización:
- **Mutexes para tenedores**: Cada tenedor es protegido por un mutex
- **Mutex de impresión**: Evita que los mensajes se superpongan
- **Mutex de comidas**: Protege el acceso a `last_meal_time` y `meals_eaten`
- **Mutex de finalización**: Controla el estado de fin de simulación

### Optimizaciones:
- Los filósofos pares empiezan con un pequeño delay para reducir la competencia inicial
- Tiempo de pensamiento variable para evitar que los filósofos se sincronicen
- Verificación frecuente del estado de finalización para terminar rápidamente

## Códigos de color en la salida

- 🟡 **Amarillo**: Tomar tenedor
- 🟢 **Verde**: Comer
- 🔵 **Azul**: Dormir
- 🔷 **Cian**: Pensar
- 🔴 **Rojo**: Muerte

## Testing

Para probar el proyecto sistemáticamente:

```bash
# Test básico - debería ejecutarse indefinidamente sin muertes
./philo 5 800 200 200

# Test de muerte - debería haber una muerte
./philo 4 310 200 100

# Test con un filósofo - debería morir
./philo 1 800 200 200

# Test con número de comidas - debería terminar cuando todos hayan comido 7 veces
./philo 5 800 200 200 7

# Test de estrés
./philo 10 410 200 200
```

## Errores comunes y soluciones

1. **Deadlock**: Verificar el orden de toma de tenedores
2. **Data races**: Asegurar que todos los accesos a variables compartidas están protegidos
3. **Muerte no detectada**: Verificar la frecuencia del monitor
4. **Salida mezclada**: Asegurar que todas las impresiones usan el mutex de impresión

## Norma 42

El proyecto sigue estrictamente la Norma de 42:
- ✅ Máximo 25 líneas por función
- ✅ Máximo 5 funciones por archivo
- ✅ Sin variables globales
- ✅ Gestión correcta de memoria
- ✅ Compilación sin warnings con -Wall -Wextra -Werror
