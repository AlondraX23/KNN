#include <stdio.h>
#include <math.h>
#include <stdlib.h>
// IMPORTANTE: hacer que los arrays aumenten de tamaño según la cantidad de líneas en los txt
typedef struct
{
  int x, y;
  char c;
} P;

typedef struct
{
  double distanciaComparada;
  char clase;
} D;

void evaluarDistancias(P *arr, int lineas, P *puntos, int lines, D *distanciasClases, int cantidadDistancias)
{
  double distancia;
  // int cantidadDistancias = lines * lineas;
  // D distanciasClases[cantidadDistancias];
  printf("\n*******************************************************************\n\n");
  for (int n = 0; n < lineas; n++)
  {
    if (n != 0) // Espacio entre coordenadas con un punto
    {
      printf("\n");
    }
    distanciasClases[n].clase = arr[n].c;
    for (int m = 0; m < lines; m++)
    {
      double x = arr[n].x - puntos[m].x;
      double y = arr[n].y - puntos[m].y;

      distancia = hypot(x, y);
      distanciasClases[m].distanciaComparada = distancia;

      printf("  La distancia entre los puntos (%d, %d) y (%d, %d) es %lf\n", arr[n].x, arr[n].y, puntos[m].x, puntos[m].y, distancia);
      printf("  Arreglo de distancias (%lf, %c)  \n", distanciasClases[m].distanciaComparada, distanciasClases[n].clase);
    }
  }
  // int i = lineas * lines;
  // do
  // {
  //   distanciasClases[i].distanciaComparada = distancia;
  //   i--;
  // } while (i = 0);
  printf("\n*******************************************************************\n");
}

void knn(D *distanciasClases, int lineas, int lines)
{
  double temp;
  for (int n = 0; n < lineas; n++)
  {
    // printf("%lf, %c \n", distanciasClases[n].distanciaComparada, distanciasClases[n].clase);

    for (int m = 0; m < lines; m++)
    {
      printf("%lf, %c \n", distanciasClases[m].distanciaComparada, distanciasClases[m].clase);
      // if (distanciasClases[m].distanciaComparada > distanciasClases[m + 1].distanciaComparada)
      // {
      //   temp = distanciasClases[m].distanciaComparada;
      //   distanciasClases[m].distanciaComparada = distanciasClases[m + 1].distanciaComparada;
      //   distanciasClases[m + 1].distanciaComparada = temp;
      // }

      // printf("\n  distancia mayor es (%lf, %c)  \n\n", distanciasClases[m].distanciaComparada, distanciasClases[m].clase);
    }
  }
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

  // Tamaño de arreglo para distancia y clases
  int cantidadDistancias = lines * lineas;
  D distanciasClases[cantidadDistancias];

  evaluarDistancias(arr, lineas, puntos, lines, distanciasClases, cantidadDistancias);
  knn(distanciasClases, lineas, lines);

  return 0;
}