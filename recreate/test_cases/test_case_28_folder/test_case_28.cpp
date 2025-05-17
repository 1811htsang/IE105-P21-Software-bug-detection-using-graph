// sample mutex error program
#include <pthread.h>
#include <stdio.h>

pthread_mutex_t lock;

void* thread_func(void* arg) {
    // Quên khóa mutex trước khi truy cập tài nguyên dùng chung
    printf("Thread %ld is running\n", (long)arg);
    // Không gọi pthread_mutex_lock(&lock);
    // Truy cập tài nguyên dùng chung ở đây (giả lập)
    printf("Thread %ld accessed shared resource\n", (long)arg);
    // Không gọi pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_mutex_init(&lock, NULL);

    pthread_create(&t1, NULL, thread_func, (void*)1);
    pthread_create(&t2, NULL, thread_func, (void*)2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&lock);
    return 0;
}

