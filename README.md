# Philosophers

# Philosophy Assignment: Dining Philosophers

## Usage

This assignment involves simulating a scenario where philosophers sit around a round table, engaging in activities like eating, thinking, and sleeping. The simulation aims to ensure that philosophers can eat without starvation while avoiding potential hazards like deadlocks.

## Features

- Simulation of philosophers sitting at a round table.
- Philosopher alternates between eating, thinking, and sleeping.
- Utilization of forks placed on the table for eating.
- Prevention of philosopher starvation.
- Thread-based implementation with mutexes for the mandatory part (philo).
- Process-based implementation with semaphores for the bonus part (philo_bonus).
- Implementation of logging program states with timestamps.

## Parameters

- **number_of_philosophers**: Number of philosophers participating in the simulation.
- **time_to_die**: Time in milliseconds indicating the maximum duration a philosopher can go without eating.
- **time_to_eat**: Time in milliseconds required for a philosopher to finish eating.
- **time_to_sleep**: Time in milliseconds indicating the duration a philosopher spends sleeping.
- **[number_of_times_each_philosopher_must_eat]**: Optional parameter indicating the number of times each philosopher must eat before the simulation stops.

## Usage

```
  git clone git@github.com:AhlyelAmine/Philosophers.git
```
- For thread-based implementation 
```
  make
  ./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> <number_of_times_each_philosopher_must_eat>
```
- For process-based implementation 
```
  ./philo_bonus <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> <number_of_times_each_philosopher_must_eat>
```
## Description

### Mandatory Part (philo)

- Each philosopher is represented as a thread.
- One fork is placed between each pair of adjacent philosophers.
- Fork states are protected by mutexes to prevent duplication.
- Philosophers alternate between eating, thinking, and sleeping, adhering to specific rules to avoid starvation and deadlocks.
- The simulation logs state changes of each philosopher with timestamps.

### Bonus Part (philo_bonus)

- Similar to the mandatory part but with additional features.
- All forks are placed in the middle of the table.
- Fork availability is managed using semaphores instead of maintaining fork states in memory.
- Each philosopher is a separate process, with the main process overseeing the simulation.
- Utilizes processes and semaphores for efficient resource management.
