*This project has been created as part of the 42 curriculum by <cvillene\>*

# Codexion

## Description
Codexion simulates multiple coders sharing limited USB dongles to compile quantum code.  
Each coder cycles through compiling → debugging → refactoring and must compile before their burnout deadline.  
The program uses POSIX threads, mutexes, condition variables, and FIFO/EDF scheduling.

## Instructions
### Compile
```bash
make
```

### Run
```bash
./codexion number_of_coders time_to_burnout time_to_compile time_to_debug time_to_refactor number_of_compiles_required dongle_cooldown scheduler
```

`scheduler` must be `fifo` or `edf`.

## Blocking cases handled
- Deadlock prevention (ordered dongle access + scheduler queues)  
- Starvation prevention (FIFO fairness, EDF liveness)  
- Dongle cooldown enforcement  
- Accurate burnout detection (monitor thread, ≤10 ms precision)  
- Log serialization (mutex-protected output)

## Thread synchronization mechanisms
- `pthread_mutex_t` for dongles, logging, shared state  
- `pthread_cond_t` for dongle waiting queues (FIFO/EDF)  
- Custom priority queue for arbitration  
- Monitor thread checking deadlines with `gettimeofday()`

## Resources
- POSIX threads documentation  
- AI for mutex and deadlock understanding