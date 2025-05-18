#include <iostream>
#include <thread>

int x = 0;

void print_x() {
  std::cerr << "x is " << x << std::endl;
}

void set_x(int new_x) {
  x = new_x;
}

void thread1() {
  print_x();
}

void thread2() {
  set_x(1);
}

int main() {
  std::thread t1(thread1);
  std::thread t2(thread2);

  t1.join();
  t2.join();

  return 0;
}