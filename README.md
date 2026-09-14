_This project has been created as part of the 42 curriculum by sjolliet_

# Philosophers - 42 Common Core

## Description

**Philosophers** is a project where we learn about threads, mutexes and race conditions, based on the classic [dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem).

A number of philosophers sit around a round table. Each one alternates between three states: **eating**, **sleeping** and **thinking**. To eat, a philosopher needs to pick up the two forks placed on their left and right, but each fork is shared with a neighbor and can only be held by one philosopher at a time. If a philosopher doesn't manage to start eating before `time_to_die` milliseconds have passed since their last meal, they die and the simulation stops.

An optional argument can also set the number of times each philosopher must eat; the simulation then stops as soon as every philosopher has reached that count.

The goal is to implement this simulation using threads (one per philosopher, plus one that monitors philosopher deaths) and mutexes, while avoiding:
- **race conditions**, by protecting every shared resource (forks, last meal time, simulation state) with a mutex
- **deadlocks**, where every philosopher waits forever for a fork that will never be released
- **starvation**, where a philosopher never manages to eat because others always take the forks first

## Instructions

### Compilation

Clone the repository and compile the project using make:
```sh
git clone <repository_url>
cd philo/philo
make
```

This builds the `philo` executable. Other available Makefile rules:
- `make clean` — remove object files
- `make fclean` — remove object files and the executable
- `make re` — `fclean` then `all`

### Usage

```sh
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

| Argument | Description |
|---|---|
| `number_of_philosophers` | Number of philosophers and forks at the table |
| `time_to_die` | Time in milliseconds since a philosopher's last meal after which they die if they haven't started eating again |
| `time_to_eat` | Time in milliseconds a philosopher takes to eat (holding both forks) |
| `time_to_sleep` | Time in milliseconds a philosopher spends sleeping |
| `number_of_times_each_philosopher_must_eat` *(optional)* | If given, the simulation stops as soon as every philosopher has eaten at least this many times |

Example:

```sh
./philo 5 800 200 200
./philo 4 410 200 200 7
```

While running, the simulation logs a timestamped status for each philosopher (`has taken a fork`, `is eating`, `is sleeping`, `is thinking`, `died`) and stops as soon as a philosopher dies or, if provided, once every philosopher has eaten `number_of_times_each_philosopher_must_eat` times.

## Resources

### References
- **Article on the project itself and how to start it**  
https://medium.com/@denaelgammal/dining-philosophers-problem-42-project-guide-mandatory-part-a20fb8dc530e
- **Multiple videos on threads from Youtube channel CodeVault**  
https://www.youtube.com/@CodeVault
- **Wikipedia page on threads**  
https://en.wikipedia.org/wiki/Thread_(computing)
- **Wikipedia page on multithreading**  
https://en.wikipedia.org/wiki/Multithreading_(computer_architecture)

### AI Usage
AI tools were used as learning and productivity aids for :
- asking questions about threads, race conditions and mutex
- helping me understand how to handle errors (like what happens if a thread creation failed)
- tell me how the order works inside the thread creation and join (when and where do you join the watcher thread for eg.)
