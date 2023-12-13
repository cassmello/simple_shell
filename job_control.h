#ifndef JOB_CONTROL_H
#define JOB_CONTROL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_JOBS 50  // Adjust the maximum number of background jobs as needed

// Structure to represent a background job
typedef struct {
    pid_t pid;           // Process ID of the job
    char command[1024];  // Command associated with the job
    int status;          // Status of the job (running, stopped, terminated)
} Job;

// Array to store background jobs
extern Job jobs[MAX_JOBS];

// Function to add a job to the job list
void add_job(pid_t pid, const char *command);

// Function to remove a job from the job list
void remove_job(pid_t pid);

// Function to update the status of a job
void update_job_status();

// Function to display the list of background jobs
void display_jobs();

// Function to bring a background job to the foreground
void bring_to_foreground(int job_number);

// Function to send a signal to a background job
void send_signal_to_job(int job_number, int signal);

#endif /* JOB_CONTROL_H */

