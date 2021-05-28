# Operating System

<center>Assignment 3 : Synchronizing Threads with POSIX Semaphores</center>



<center>61519322 杨哲睿</center>

## Exercise 1

### Original Program with no protection

The program `badcnt.c` has no protection to the variable `cnt`:

```c
void * Count(void * a)
{
    int i, tmp;
    for(i = 0; i < NITER; i++)
    {
        tmp = cnt;      /* copy the global cnt locally */
        tmp = tmp+1;    /* increment the local copy */
        cnt = tmp;      /* store the local value into the global cnt */ 
    }
}
```

When two thread run concurrently , the operations can be shuffled (even inside the critical section). 

| Thread 1                    | Thread 2                    |
| --------------------------- | --------------------------- |
| `tmp = cnt` (`tmp = 0`)     |                             |
|                             | `tmp = cnt = 0` (`tmp = 0`) |
|                             | `tmp = tmp + 1` (`tmp = 1`) |
| `tmp = tmp + 1` (`tmp = 1`) |                             |
|                             | `cnt = tmp` (`cnt = 1`)     |
| `cnt = tmp` (`cnt = 1`)     |                             |

<center>Here we assume <code>cnt = 0</code> at the beginning: We expect <code>cnt = 2</code> After the thread1's and thread2's first loop is executed. But the output is 1, because two threads executes in the critical section at the same time (or executes these instructions in a randomly shuffled order)</center>

To fix this bug, we have to make the execution **mutual** in the critical section:

```c
        // wait(mutex)
		sem_wait(&mutex);
        tmp = cnt;      /* copy the global cnt locally */
        tmp = tmp+1;    /* increment the local copy */
        cnt = tmp;      /* store the local value into the global cnt */ 
        // signal(mutex)
        sem_post(&mutex);
```

and initialize the semaphore with `1`:

```c
sem_init(&mutex, 0, 1);
```

Then we can arrive at the correct answer.

