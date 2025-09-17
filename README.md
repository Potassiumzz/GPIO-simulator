# GPIO-simulator

A GPIO-simulator with a simple traffic-light FSM

# About

This project simulates **GPIO pin behaviour** without an actual microcontroller.

The purpose is to demonstrate how software (libraries) might be written for a microcontroller so that developers can interact with hardware.

> [!NOTE]
> This is not a perfect GPIO simulator. There are many ways to achieve the same goal. This implementation uses threads to mimic hardware concurrency.

### Threads usage

On real hardware:

- The CPU keeps executing instructions.
- The timer counts independently.
- Interrupts are triggered asynchronously.

In this simulation:

- Threads are used so the timer, interrupt, and CPU appear to run independently, like in bare-metal systems.

# Project Structure

```
/include  - Header files
/src      - Source files
```

- **gpio.c / gpio.h** - Functions to manipulate GPIO pins.

    - Write to a pin (turn on/off)
    - Clear pin
    - Toggle pin
    - Show pin status in console

    > [!NOTE]
    > Input/Output configuration is not included, though it exists in real hardware GPIO.

- **interrupt.c / interrupt.h** - Functions to simulate interrupts.

    - Timer interrupt (updates a time variable when compare match occurs)
    - Button press simulation (via Enter key)

    On real hardware, interrupts run asynchronously when peripherals fire IRQs.
    In this simulation, they run in their own threads to mimic that behaviour.

- **traffic_light.c / traffic_light.h** - Finite State Machine (FSM) for a traffic light.

    - Updates GPIO pins
    - Changes light states (RED -> RED+YELLOW -> GREEN -> GREEN+YELLOW -> RED.. and so on)
    - Represents CPU-driven logic, running in its own thread

    Note that when the enter key is pressed while on normal traffic light cycle, the system does not immediately switch to yellow but will let the traffic light cycle complete once before switching to yellow. This is known as deferred or delayed transition (event queuing).

- **main.c**

    - Initialises and starts threads
    - Coordinates simulation

# Compile and Run

Make sure you have `gcc` and `make` installed.

Using `make`
```
make run
```
This will compile the sources and automatically run the program.

If you prefer to compile manually, run:
```
mkdir -p bin
gcc -Iinclude src/*.c -o bin/GPIO-simulator
bin/GPIO-simulator
```
You can change the output directory/location accordingly.

# Platform Support

This simulation is designed for Linux. It uses Linux-specific functions such as `clock_nanosleep()` and `clock_gettime()`, which may not be available or behave differently on other operating systems.

> [!IMPORTANT]
> - The timer is simulated in software using threads.
> - This project is mainly for educational purposes (not a real-time accurate simulation).
> - In real hardware, an RTOS or bare-metal firmware would handle scheduling and timing instead of threads.
