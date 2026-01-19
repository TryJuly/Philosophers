This project has been created as part of the 42 curriculum by strieste

## Description

The Philosophers project is an introduction to concurrent programming using threads and mutexes.  
The goal of the project is to simulate the Dining Philosophers problem while respecting strict timing constraints and avoiding data races and deadlocks. Each philosopher is represented by a thread and alternates between eating, sleeping, and thinking.  
To eat, a philosopher must acquire two forks, which are shared resources protected by mutexes.

This project focuses on correct thread synchronization, resource management, and precise time handling.

## Instructions

- Use git clone for clone the project where do you want, going inside philo directory.

Compilation

- Use make to compile the project. This will generate an executable named philo

- Run the program as follows:

./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

Arguments explanation:

- Number_of_philosophers: number of philosophers

- Time_to_die: time (in milliseconds) before a philosopher dies without eating

- Time_to_eat: time (in milliseconds) spent eating

- Time_to_sleep: time (in milliseconds) spent sleeping

- Number_of_times_each_philosopher_must_eat (optional): simulation ends when all philosophers have eaten this many times

## Ressources

- Dining Philosophers problem:

https://en.wikipedia.org/wiki/Dining_philosophers_problem

- POSIX Threads Programming:

https://man7.org/linux/man-pages/man7/pthreads.7.html

- Pthread_mutex_lock:

https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html

- pthread_create / pthread_join:

https://man7.org/linux/man-pages/man3/pthread_create.3.html

# Use of AI

AI tools were used only to clarify concepts related to concurrency (threads, mutexes, data races, deadlocks)
reason about synchronization and timing constraints.