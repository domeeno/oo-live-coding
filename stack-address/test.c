#include <stdio.h>
#include <stdlib.h>
int main()
{
  int m;
  int n;
  int *p = malloc(sizeof(int));

  printf("%p, %p\n", &m, &n); 
  printf("%p\n", p);

  free(p);
  printf("-1000 aura");

  return 0;
}
