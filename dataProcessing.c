#include <stdio.h>
#include <math.h>
#include <stdlib.h> //malloc
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
  int a = 0;
  printf("\n*******************************************************************\n\n");
  for (int n = 0; n < lineas; n++)
  {
    if (n != 0) // Espacio entre coordenadas con un punto
    {
      printf("\n");
    }
    for (int m = 0; m < lines; m++)
    {
      double x = arr[n].x - puntos[m].x;
      double y = arr[n].y - puntos[m].y;

      distancia = hypot(x, y);

      distanciasClases[a].distanciaComparada = distancia;
      distanciasClases[a].clase = arr[n].c;

      printf("  La distancia entre los puntos (%d, %d) y (%d, %d) es %lf\n", arr[n].x, arr[n].y, puntos[m].x, puntos[m].y, distancia);
      // printf("  Arreglo de distancias (%lf, %c)  \n", distanciasClases[a].distanciaComparada, distanciasClases[n].clase);
      a++;
    }
  }

  printf("\n*******************************************************************\n");
}

void knn(D *distanciasClases, int lineas, int lines, int cantidadDistancias, D *porPunto, D *perteneceClase)
{

  printf("\n  Arreglo de distancia y su clase \n\n");

  for (int k = 0; k < cantidadDistancias; k++) // imprimir todo el arreglo
  {
    printf("\t(%lf, %c)\n", distanciasClases[k].distanciaComparada, distanciasClases[k].clase);
  }
  printf("\n");
  //-------------------------------------------------------------
  int evaluarPorClase = cantidadDistancias / lineas;
  // printf("%d\n", evaluarPorClase);

  int h;
  int a = 0;
  for (int k = 0; k < evaluarPorClase; k++)
  {
    h = k;
    printf("%i", h);
    for (h; h < cantidadDistancias; h += evaluarPorClase)
    {
      porPunto[a].distanciaComparada = distanciasClases[h].distanciaComparada;
      porPunto[a].clase = distanciasClases[h].clase;

      // printf("\t(%lf, %c)\n", distanciasClases[h].distanciaComparada, distanciasClases[h].clase);
      // printf("\t(%lf, %c)\n", porPunto[a].distanciaComparada, porPunto[a].clase);

      // if (distanciasClases[a].distanciaComparada > distanciasClases[a + 1].distanciaComparada)
      // {
      //   temp = distanciasClases[a].distanciaComparada;
      //   distanciasClases[a].distanciaComparada = distanciasClases[a + 1].distanciaComparada;
      //   distanciasClases[a + 1].distanciaComparada = temp;
      // }
      printf("\t(%lf, %c)\n", porPunto[a].distanciaComparada, porPunto[a].clase);
    }
    porPunto[a].distanciaComparada = 0;
    porPunto[a].clase = 0;

    a++;
    printf("\n");
  }
  //------------------------------------------------------------------------------------

  /*DIVIDIR por clase cada número de PUNTOs y elegir el número menor.
  Por ejemplo: cada 3 líneas con 0, elegir la distancia menor*/
  //---------------------------------------------------------

  // double temp;
  // for (int n = 0; n < lineas; n++)
  // {
  //   // printf("%lf, %c \n", distanciasClases[n].distanciaComparada, distanciasClases[n].clase);

  //   for (int m = 0; m < lines; m++)
  //   {
  //     printf("%lf, %c \n", distanciasClases[m].distanciaComparada, distanciasClases[m].clase);
  //     // if (distanciasClases[m].distanciaComparada > distanciasClases[m + 1].distanciaComparada)
  //     // {
  //     //   temp = distanciasClases[m].distanciaComparada;
  //     //   distanciasClases[m].distanciaComparada = distanciasClases[m + 1].distanciaComparada;
  //     //   distanciasClases[m + 1].distanciaComparada = temp;
  //     // }

  //     // printf("\n  distancia mayor es (%lf, %c)  \n\n", distanciasClases[m].distanciaComparada, distanciasClases[m].clase);
  //   }
  // }
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

  //______________________________________________________________________
  // Tamaño de arreglo para distancia y clases
  int cantidadDistancias = lines * lineas;
  D distanciasClases[cantidadDistancias];

  // Tamaño de arreglo para distancias a un punto
  D porPunto[lineas];      // 8 espacios (distancia, clase). La distancia menor e guarda en perteneceClase[lines]
  D perteneceClase[lines]; // 3 espacios. Se guarda la pura clase.

  evaluarDistancias(arr, lineas, puntos, lines, distanciasClases, cantidadDistancias);
  knn(distanciasClases, lineas, lines, cantidadDistancias, porPunto, perteneceClase);

  return 0;
}