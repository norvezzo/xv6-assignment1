#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int n = 4;
  int pids[16];
  int statuses[64]; // must be at least NPROC
  int count = -1;

  int ret = forkn(n, pids);

  if (ret == 0) {
    // Parent process
    int wait_result = waitall((int *)&count, statuses);
    if (wait_result < 0) {
      printf("waitall failed\n");
      exit(1, "waitall failed");
    }

    printf("Parent: waitall completed. %d children exited.\n", count);
    for (int i = 0; i < count; i++) {
      printf("  Child[%d] exited with status = %d\n", i, statuses[i]);
    }

    exit(0, "waitall success");

  } else {
    // Child process: just exit with ret (1 to n)
    exit(ret, "");
  }
}