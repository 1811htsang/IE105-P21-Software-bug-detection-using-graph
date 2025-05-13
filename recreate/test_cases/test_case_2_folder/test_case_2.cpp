#include <stdio.h>
int main() {

  int x = 0;

  scanf("%d", x);
  if (x >= 1 && x <= 100) {
    printf("%d\\n", x * x * x);
  }

  return 0;
}
