#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
using namespace std;

bool isPrime(int n)
{
    if (n <= 0) return false;
    if (n > 1 && n <= 3) return true;
    for (int i = 2; i <= n - 1; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}
int main() {
    cout << isPrime(23939);

    // create subprocess for test case
    __pid_t pid = fork();
    if (pid == 0) {
        // child process
        printf("Child process: %d\n", getpid());
        exit(0);
    } else if (pid < 0) {
        // fork failed
        cout << "Fork failed" << endl;
        return 1;
    } else {
        // parent process
        printf("Parent process: %d\n", getpid());
        wait(NULL); // wait for child process to finish
    }
    return 0;
}