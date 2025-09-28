#include <stdio.h>
#include <math.h>
typedef struct
{
  int x, y, c;
} P;

int main()
{
  P arr[4];

  // Selección de archivo de datos
  FILE *f = fopen("data.txt", "r");
  if (!f)
  {
    printf("Archivo no existe o la dirección es incorrecta");
    return 1;
  }

  // Lectura de datos
  int a = 0;
  while (fscanf(f, "%d %d %d ", &arr[a].x, &arr[a].y, &arr[a].c) == 3)
  {
    a++;
  }
  {
    printf("Datos leidos\n\n");
  }

  // Imprimir coordenadas y clase

  for (int i = 0; i < a; ++i)
  {
    printf("%d %d %d \n", arr[i].x, arr[i].y, arr[i].c);
  }

  return 0;
}