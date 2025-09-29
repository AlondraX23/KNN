#include <stdio.h>
#include <math.h>

typedef struct
{
  int x, y;
  char c;
} P;

void myFunction(P *arr, int lineas, P *puntos) // Crear ciclo para que que se evalúe la distancia con los demás puntos. usar lines
{
  printf("\n*******************************************************************\n\n");
  for (int i = 0; i < lineas; i++)
  {

    double x = arr[i].x - puntos[0].x;
    double y = arr[i].y - puntos[0].y;

    double distancia = hypot(x, y);

    printf("  La distancia entre los puntos (%d, %d) y (%d, %d) es %lf\n", arr[i].x, arr[i].y, puntos[0].x, puntos[0].y, distancia);
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

  P puntos[1];
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

  myFunction(arr, lineas, puntos);

  return 0;
}