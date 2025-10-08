#include <stdio.h>
#include <math.h>
#include <stdlib.h> //malloc
#include <string.h> //memcpy
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

double evaluarDistancias(P *arrClases, int lineasClases, P *arrPuntos, int lineasPuntos, D *arrDistancias, int tamanoDistancias)
{
  double distancia;
  int a = 0;
  printf("\n*******************************************************************\n\n");
  for (int n = 0; n < lineasClases; n++)
  {
    if (n != 0) // Espacio entre coordenadas con un punto
    {
      printf("\n");
    }
    for (int m = 0; m < lineasPuntos; m++)
    {
      double x = arrClases[n].x - arrPuntos[m].x;
      double y = arrClases[n].y - arrPuntos[m].y;

      distancia = hypot(x, y);

      arrDistancias[a].distanciaComparada = distancia;
      arrDistancias[a].clase = arrClases[n].c;

      printf("  La distancia entre los puntos (%d, %d) y (%d, %d) es %lf\n", arrClases[n].x, arrClases[n].y, arrPuntos[m].x, arrPuntos[m].y, distancia);
      a++;
    }
  }

  printf("\n*******************************************************************\n");
}

int numLineasClases(FILE *clases)
{
  clases = fopen("clases.txt", "r"); // Abrir archivo de CLASES
  int lineas;
  int saltoLinea;
  while ((saltoLinea = fgetc(clases)) != EOF) // Lectura de líenas en CLASES
  {
    if (saltoLinea == '\n')
    {
      lineas++;
    }
  }
  if (lineas == 0)
  {
    rewind(clases);
    if (fgetc(clases) != EOF)
    {
      lineas = 1;
    }
  }
  else
  {
    rewind(clases);
    while ((saltoLinea = fgetc(clases)) != EOF)
      ;
    if (saltoLinea != '\n' && lineas > 0)
    {
      lineas++;
    }
  }

  int totalLineas = lineas;
  return totalLineas;
  fclose(clases);
}

int numLineasPuntos(FILE *archivoPuntos)
{
  archivoPuntos = fopen("puntos.txt", "r");
  int lineas;
  int saltoLinea;
  while ((saltoLinea = fgetc(archivoPuntos)) != EOF)
  {
    if (saltoLinea == '\n')
    {
      lineas++;
    }
  }
  if (lineas == 0)
  {
    rewind(archivoPuntos);
    if (fgetc(archivoPuntos) != EOF)
    {
      lineas = 1;
    }
  }

  int totalLineas = lineas;
  return totalLineas;
  fclose(archivoPuntos);
}

double reordenamientoPorPunto(D *arrDistancias, int lineasClases, int lineasPuntos, int tamanoDistancias, D *porPunto, D *perteneceClase, D *arrDistReordenamiento, P *arrPuntos)
{
  //-------------------------------------------------------------
  printf("\n  Arreglo de distancia y su clase por punto evaluado \n\t____________________________\n\n        Punto     Distancia\n");

  int h;
  int a = 0;
  int b = 0;
  double temp;
  for (int k = 0; k < 3; k++)
  {
    h = k;
    printf("\t____________________________\n\n\t(%d %d)\n", arrPuntos[k].x, arrPuntos[k].y);
    for (h; h < tamanoDistancias; h += lineasPuntos)
    {
      porPunto[a].distanciaComparada = arrDistancias[h].distanciaComparada;
      porPunto[a].clase = arrDistancias[h].clase;
      printf("\t\t(%lf, %c)\n", porPunto[a].distanciaComparada, porPunto[a].clase);

      arrDistReordenamiento[b].distanciaComparada = arrDistancias[h].distanciaComparada; // Reordenar resoecto al punto evaludo
      arrDistReordenamiento[b].clase = arrDistancias[h].clase;
      b++;
    }
    a++;
  }
  printf("\n\t____________________________\n");
}

void knn(D *arrDistReordenamiento, int tamanoDistancias, int lineasPuntos, int lineasClases)
{
  printf("\n  Reordenamiento de arrDistancias \n\n");

  for (int k = 0; k < tamanoDistancias; k++) // imprimir todo el arreglo
  {
    printf("\t(%lf, %c)\n", arrDistReordenamiento[k].distanciaComparada, arrDistReordenamiento[k].clase);
  }
  printf("\n");
  //---------------------------------------------------------------------------
  int numSubarrays = lineasPuntos; // número de subarrays

  for (int i = 0; i < numSubarrays; i++)
  {
    int *subarray = (int *)malloc(lineasClases * sizeof(int));
    if (subarray == NULL)
    {
      printf("Error al asignar memoria.\n");
      return;
    }

    memcpy(subarray, &arrDistReordenamiento[i * lineasPuntos], lineasPuntos * sizeof(int));

    // Imprime el sub-array (para demostrar que funcionó)
    printf("Sub-array %d: ", i + 1);

    for (int j = 0; j < lineasPuntos; j++)
    {
      printf("%d ", subarray[j]);
    }
    printf("\n");

    // Libera la memoria reservada para el sub-array
    free(subarray);
  }
}

int main() // gcc dataProcessing.c -o d -lm
{
  FILE *clases;
  clases = fopen("clases.txt", "r"); // Abrir archivo de CLASES

  if (!clases) // Mensaje de erro al leer el archivo CLASE
  {
    printf("El archivo de COORDENADAS no existe o la dirección es incorrecta");
    return 1;
  }

  int lineasClases = numLineasClases(clases); // Obtener el número de líneas en el archivo

  rewind(clases); // Para que leea desde el inicio del archivo CLASES

  P arrClases[lineasClases]; // Establecer el tamaño del array

  printf("________________________________________\n\n   COORDENADAS: %d datos leidos\n\n", lineasClases);
  for (int a = 0; a < lineasClases; a++) // Lectura y llenado del array
  {
    (fscanf(clases, "%d %d %c ", &arrClases[a].x, &arrClases[a].y, &arrClases[a].c)); // Agregar un if para que llene la línea si están los 3 valores
    printf("\t(%d, %d) \tclase: %c \n", arrClases[a].x, arrClases[a].y, arrClases[a].c);
  }
  printf("\n________________________________________\n");

  fclose(clases);
  //----------------------------------------------------------------------------------

  FILE *archivoPuntos; // Selección de archivo de PUNTOS

  archivoPuntos = fopen("puntos.txt", "r");
  if (!archivoPuntos)
  {
    printf("Archivo de PUNTOS DE COMPARACIÓN no existe o la dirección es incorrecta");
    return 1;
  }

  int lineasPuntos = numLineasPuntos(archivoPuntos); // Obtener el número de líneas en el archivo

  rewind(archivoPuntos);

  P arrPuntos[lineasPuntos]; // Establecer el tamaño del array

  printf("\n   PUNTOS: %d datos leidos\n\n", lineasPuntos);
  for (int a = 0; a < lineasPuntos; a++) // Lectura y llenado del array
  {
    (fscanf(archivoPuntos, "%d %d ", &arrPuntos[a].x, &arrPuntos[a].y));
    printf("\t(%d, %d)\n", arrPuntos[a].x, arrPuntos[a].y);
  }
  printf("\n________________________________________\n");

  fclose(archivoPuntos);

  //______________________________________________________________________
  // Tamaño de arreglo para distancia y clases
  int tamanoDistancias = lineasClases * lineasPuntos;
  D arrDistancias[tamanoDistancias];
  D arrDistReordenamiento[tamanoDistancias];

  // Tamaño de arreglo para distancias a un punto
  D porPunto[lineasClases];       // 8 espacios (distancia, clase)
  D perteneceClase[lineasPuntos]; // 3 espacios. Se guarda la pura clase.

  evaluarDistancias(arrClases, lineasClases, arrPuntos, lineasPuntos, arrDistancias, tamanoDistancias);
  reordenamientoPorPunto(arrDistancias, lineasClases, lineasPuntos, tamanoDistancias, porPunto, perteneceClase, arrDistReordenamiento, arrPuntos);
  knn(arrDistReordenamiento, tamanoDistancias, lineasPuntos, lineasClases);
  return 0;
}