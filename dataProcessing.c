#include <stdio.h>
#include <math.h>

typedef struct
{
  int x, y, c;
} P;

void myFunction(P *arr, int lineas, P *puntos)
{
  // int puntoComparacion_x = 1; // coordenada de prueba
  // int puntoComparacion_y = 2; // coordenada de prueba

  for (int i = 0; i < lineas; i++)
  { // agregar double para obtener resultados correctos
    int x = arr[i].x - puntos[i].x;
    int y = arr[i].y - puntos[i].x;

    int distancia = hypot(x, y);

    printf("suma de las x y %d\n", distancia);
  }
}

int main()
{
  P arr[1];
  // Selección de archivo de CLASES
  FILE *f = fopen("clases.txt", "r");
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
    printf("Datos leidos, %d coordenadas\n\n", a);
  }

  // numero de líneas en el archivo
  int lineas = a;

  // Imprimir coordenadas y clase
  for (int i = 0; i < a; ++i)
  {
    printf("%d %d %d \n", arr[i].x, arr[i].y, arr[i].c);
  }

  //-------------------------------------------------------

  P puntos[1];
  // Selección de archivo de PUNTOS
  FILE *g = fopen("puntos.txt", "r");
  if (!g)
  {
    printf("Archivo no existe o la dirección es incorrecta");
    return 1;
  }

  // Lectura de datos
  int b = 0;
  while (fscanf(g, "%d %d ", &puntos[b].x, &puntos[b].y) == 2)
  {
    b++;
  }
  {
    printf("Datos leidos, %d coordenadas\n\n", b);
  }

  // numero de líneas en el archivo
  int lines = b;

  // Imprimir coordenadas y clase
  for (int j = 0; j < b; ++j)
  {
    printf("%d %d \n", puntos[j].x, puntos[j].y);
  }

  myFunction(arr, lineas, puntos);

  return 0;
}