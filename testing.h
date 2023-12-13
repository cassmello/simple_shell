#ifndef TESTING_H
#define TESTING_H

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

// Function to initialize the test suite
int init_suite(void);

// Function to clean up the test suite
int clean_suite(void);

// Function to add test cases to the suite
void add_test_cases(void);

#endif /* TESTING_H */

