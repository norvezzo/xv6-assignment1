#include "kernel/types.h"
#include "user/user.h"

#define SIZE 65536
#define PARTS 4
#define CHUNK (SIZE / PARTS)

int array[SIZE];

int main() {
  int pids[PARTS];
  int statuses[PARTS];
  int n = -1;

  for (int i = 0; i < SIZE; i++) {
    array[i] = i;
  }

  int ret = forkn(PARTS, pids);

  if (ret == 0) {
    // Parent process
    if (waitall((int *)&n, statuses) < 0) {
      exit(1, "waitall failed");
    }
     // Check if number of children created from forkn is equal to the number of children that waitall returns
     if (n != PARTS) {
        exit(1, "child count mismatch, calculation failed");
    }

    int total = 0;
    for (int i = 0; i < n; i++) {
      total += statuses[i];
    }

    printf("Total sum: %d\n", total);
    exit(0, "calculation completed");

  } else {
    // Child process
    int index = ret - 1;
    int start = index * CHUNK;
    int end = start + CHUNK;
    int sum = 0;

    for (int i = start; i < end; i++) {
      sum += array[i];
    }
    sleep(index * 10); // Printing the children in order
    printf("Child #%d (PID = %d) sum: %d\n", ret, getpid(), sum);
    exit(sum, "");
  }
}