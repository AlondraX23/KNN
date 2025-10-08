int main()
{
    P *arr = NULL;     // Arreglo dinámico, inicialmente vacío
    int capacidad = 0; // Capacidad inicial
    int a = 0;         // Número de elementos leídos

    // Selección de archivo de CLASES
    FILE *f = fopen("clases.txt", "r");
    if (!f)
    {
        printf("El archivo de COORDENADAS no existe o la dirección es incorrecta");
        return 1;
    }

    printf("________________________________________\n\n");

    // Lectura de coordenadas
    while (1)
    {
        // Si se necesita más espacio, aumentar capacidad
        if (a >= capacidad)
        {
            capacidad = (capacidad == 0) ? 1 : capacidad * 2;
            P *tmp = realloc(arr, capacidad * sizeof(P));
            if (!tmp)
            {
                printf("Error al asignar memoria\n");
                free(arr);
                fclose(f);
                return 1;
            }
            arr = tmp;
        }

        // lectura de una coordenada
        if (fscanf(f, "%d %d %c ", &arr[a].x, &arr[a].y, &arr[a].c) != 3)
            break;

        a++;
    }
    fclose(f);

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

    free(arr); // Liberar memoria al final
    return 0;
}
