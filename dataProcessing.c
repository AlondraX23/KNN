#include <stdio.h>
#include <math.h>
// IMPORTANTE: hacer que los arrays aumenten de tamaño según la cantidad de líneas en los txt
typedef struct
{
  int x, y;
  char c;
} P;

void myFunction(P *arr, int lineas, P *puntos, int lines)
{
  printf("\n*******************************************************************\n\n");
  for (int n = 0; n < lineas; n++)
  {
    if (n != 0)
    {
      printf("\n");
    }

    for (int m = 0; m < lines; m++)
    {
      double x = arr[n].x - puntos[m].x;
      double y = arr[n].y - puntos[m].y;

      double distancia = hypot(x, y);

      printf("  La distancia entre los puntos (%d, %d) y (%d, %d) es %lf\n", arr[n].x, arr[n].y, puntos[m].x, puntos[m].y, distancia);
    }
  }
  printf("\n*******************************************************************\n");
}

int main()
{
  P arr[10];
  // Selección de archivo de CLASES
  FILE *f = fopen("clases.txt", "r");
  if (!f)
  {
    printf("El archivo de COORDENADAS no existe o la dirección es incorrecta");
    return 1;
  }
  printf("________________________________________\n\n");
  // Lectura de coordenadas
  int a = 0;
  while (fscanf(f, "%d %d %c ", &arr[a].x, &arr[a].y, &arr[a].c) == 3)
  {
    a++;
  }
  {
    printf("  COORDENADAS: %d datos leidos \n\n", a);
  }

  // Numero de líneas en el archivo
  int lineas = a;

  // Imprimir coordenadas y clase
  for (int i = 0; i < a; ++i)
  {
    printf("\t(%d, %d) \tclase: %c \n", arr[i].x, arr[i].y, arr[i].c);
  }
  printf("\n________________________________________\n");

  //--------------------------------------------------------------------------------------

  P puntos[4];
  // Selección de archivo de PUNTOS
  FILE *g = fopen("puntos.txt", "r");
  if (!g)
  {
    printf("Archivo de PUNTOS DE COMPARACIÓN no existe o la dirección es incorrecta");
    return 1;
  }

  // Lectura de punto
  int b = 0;
  while (fscanf(g, "%d %d ", &puntos[b].x, &puntos[b].y) == 2)
  {
    b++;
  }
  {
    printf("\n  PUNTOS: %d datos leidos\n\n", b);
  }

  // Numero de líneas en el archivo
  int lines = b;

  // Imprimir coordenadas y clase
  for (int j = 0; j < b; ++j)
  {
    printf("\t(%d, %d) \n", puntos[j].x, puntos[j].y);
  }
  printf("________________________________________\n");

  myFunction(arr, lineas, puntos, lines);

  return 0;
}