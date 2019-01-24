**************
Semaphore note
**************

.. cdoe-block:: c
    :caption: POSIX Semaphore APIs

    #include <semaphore.h>
    #include <fcntl.h>           /* For O_* constants */
    #include <sys/stat.h>

    // Link with -pthread.
    sem_t *sem_open(const char *name, int oflag);
    sem_t *sem_open(const char *name, int oflag, mode_t mode, unsigned int value);
    int sem_close(sem_t *sem);
    int sem_unlink(const char *name);
    
    int sem_post(sem_t *sem);
    int sem_wait(sem_t *sem);
    int sem_trywait(sem_t *sem);
    int sem_timedwait(sem_t *sem, const struct timespec *abs_timeout);
    
    int sem_getvalue(sem_t *sem, int *sem_val);

On success, sem_open() returns the address of the new semaphore; this address is used 
when calling other semaphore-related functions. On error, sem_open() returns ``SEM_FAILED``, 
with errno set to indicate the error.

All of these functions except ``sem_open()`` return 0 on success; on error, 
-1 is returned, and errno is set to indicate the error.

.. code-block:: c
    :caption: Taken from Linux Manual

    #include <unistd.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <semaphore.h>
    #include <time.h>
    #include <assert.h>
    #include <errno.h>
    #include <signal.h>
    
    sem_t sem;
    
    #define handle_error(msg) \
        do { perror(msg); exit(EXIT_FAILURE); } while (0)

    static void handler(int sig)
    {
        write(STDOUT_FILENO, "sem_post() from handler\n", 24);
        if (sem_post(&sem) == -1) {
            write(STDERR_FILENO, "sem_post() failed\n", 18);
            _exit(EXIT_FAILURE);
        }
    }

    int main(int argc, char *argv[])
    {
        if (argc != 3) 
        {
            fprintf(stderr, "Usage: %s <alarm-secs> <wait-secs>\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    
       if (sem_init(&sem, 0, 0) == -1)
            handle_error("sem_init");
    
        struct sigaction sa;
        sa.sa_handler = handler;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = 0;
        if (sigaction(SIGALRM, &sa, NULL) == -1)
            handle_error("sigaction");
    
        alarm(atoi(argv[1]));
    
        struct timespec ts;
        if (clock_gettime(CLOCK_REALTIME, &ts) == -1)
            handle_error("clock_gettime");
    
        ts.tv_sec += atoi(argv[2]);
    
        int s;
        printf("main() about to call sem_timedwait()\n");
        while ((s = sem_timedwait(&sem, &ts)) == -1 && errno == EINTR)
            continue;       /* Restart if interrupted by handler */
    
       if (s == -1) 
       {
            if (errno == ETIMEDOUT)
                printf("sem_timedwait() timed out\n");
            else
                perror("sem_timedwait");
        } 
        else
            printf("sem_timedwait() succeeded\n");
    
        exit((s == 0) ? EXIT_SUCCESS : EXIT_FAILURE);
    }   