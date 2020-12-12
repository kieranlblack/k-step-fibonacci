#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

u_int64_t *dp = NULL;

bool init_dp(u_int64_t n) {
    if (n < 3) {
        n = 3;
    }

    if (!(dp = calloc(n + 1, sizeof(u_int64_t)))) {
        return false;
    }

    dp[0] = 0;
    dp[1] = 1;
    dp[2] = 1;
    return true;
}

u_int64_t k_step_fibonacci(u_int64_t n, u_int64_t k) {
    if (!dp) {
        if (!init_dp(n)) {
            return -1;
        }
    }

    if (dp[n]) {
        return dp[n];
    }

    u_int64_t lower_bound = 0;
    if (k < n) {
        lower_bound = n - k;
    }

    u_int64_t sol = 0;
    for (u_int64_t i = lower_bound; i < n; i++) {
        sol += k_step_fibonacci(i, k);
    }

    dp[n] = sol;
    return sol;
}

void print_help(void) {
    puts("Error! Please use the command as: ");
    puts("./k-step-fib <term> <step>");
}

int main(int argc, char *argv[]) {
    u_int64_t n = 0;
    u_int64_t k = 0;

    bool error = false;
    if (argc != 3) {
        error = true;
    }

    n = atoi(argv[1]);
    if (!(k = atoi(argv[2]))) {
        error = true;
    }

    if (error) {
        print_help();
        return EXIT_FAILURE;
    }

    u_int64_t result = k_step_fibonacci(n, k);
    if (result < 0) {
        puts("Something went wrong.");
        return EXIT_FAILURE;
    }
    printf(" -> %lu\n", result);
    return EXIT_SUCCESS;
}
