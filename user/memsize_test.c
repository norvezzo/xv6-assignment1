#include "kernel/types.h"
#include "user/user.h"

int main() {
  printf("Memory size: %d bytes\n", memsize());

  void *p = malloc(20000);
  if(p == 0){
    printf("Failed to allocate memory\n");
    exit(1, "");
  }

  printf("After malloc: %d bytes\n", memsize());

  free(p);

  printf("After free: %d bytes\n", memsize());

  exit(0, "");
}