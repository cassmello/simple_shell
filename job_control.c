#include "job_control.h"

Job jobs[MAX_JOBS];

// Function to add a job to the job list
void add_job(pid_t pid, const char *command) {
    for (int i = 0; i < MAX_JOBS; i++) {
        if (jobs[i].pid == 0) {
            jobs[i].pid = pid;
            strncpy(jobs[i].command, command, sizeof(jobs[i].command));
            jobs[i].status = 1;  // Set the status to running
            return;
        }
    }

    fprintf(stderr, "Error: Maximum number of jobs reached.\n");
}

// Function to remove a job from the job list
void remove_job(pid_t pid) {
    for (int i = 0; i < MAX_JOBS; i++) {
        if (jobs[i].pid == pid) {
            jobs[i].pid = 0;
            jobs[i].command[0] = '\0';
            jobs[i].status = 0;
            return;
        }
    }
}

// Function to update the status of a job
void update_job_status() {
    int status;
    pid_t pid;
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        for (int i = 0; i < MAX_JOBS; i++) {
            if (jobs[i].pid == pid) {
                if (WIFEXITED(status) || WIFSIGNALED(status)) {
                    // Job has exited or terminated by signal
                    printf("[%d] %s\tDone\n", i + 1, jobs[i].command);
                    remove_job(pid);
                } else if (WIFSTOPPED(status)) {
                    // Job has been stopped by signal
                    printf("[%d] %s\tStopped\n", i + 1, jobs[i].command);
                    jobs[i].status = 0;
                } else if (WIFCONTINUED(status)) {
                    // Job has been resumed
                    printf("[%d] %s\tResumed\n", i + 1, jobs[i].command);
                    jobs[i].status = 1;
                }
            }
        }
    }
}

// Function to display the list of background jobs
void display_jobs() {
    for (int i = 0; i < MAX_JOBS; i++) {
        if (jobs[i].pid != 0) {
            printf("[%d] %s\t%s\n", i + 1, jobs[i].status ? "Running" : "Stopped", jobs[i].command);
        }
    }
}

// Function to bring a background job to the foreground
void bring_to_foreground(int job_number) {
    if (job_number > 0 && job_number <= MAX_JOBS && jobs[job_number - 1].pid != 0) {
        // Send the SIGCONT signal to resume the job
        kill(jobs[job_number - 1].pid, SIGCONT);

        // Wait for the job to finish
        waitpid(jobs[job_number - 1].pid, NULL, WUNTRACED);

        // Remove the job from the list after it has finished
        remove_job(jobs[job_number - 1].pid);
    } else {
        fprintf(stderr, "Error: Invalid job number.\n");
    }
}

// Function to send a signal to a background job
void send_signal_to_job(int job_number, int signal) {
    if (job_number > 0 && job_number <= MAX_JOBS && jobs[job_number - 1].pid != 0) {
        // Send the specified signal to the job
        kill(jobs[job_number - 1].pid, signal);
    } else {
        fprintf(stderr, "Error: Invalid job number.\n");
    }
}

