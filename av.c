int main(void) {
    char **arg = av;

    while (*arg != NULL) {
        printf("%s\n", *arg);
        arg++;
    }

    return 0;
}

