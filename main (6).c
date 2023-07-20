#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Búsqueda Binaria
bool busqueda_binaria(const int arr[], int n, int objetivo) {
  int bajo = 0;
  int alto = n - 1;
  while (bajo <= alto) {
    int medio = (bajo + alto) / 2;
    if (arr[medio] == objetivo) {
      return true;
    } else if (arr[medio] < objetivo) {
      bajo = medio + 1;
    } else {
      alto = medio - 1;
    }
  }
  return false;
}
// Búsqueda Lineal por Saltos
bool busqueda_saltos(const int arr[], int n, int objetivo) {
  int paso = sqrt(n);
  int previo = 0;

  while (arr[(int)fmin(paso, n) - 1] < objetivo) {
    previo = paso;
    paso += sqrt(n);
    if (previo >= n) {
      return false;
    }
  }

  while (arr[previo] < objetivo) {
    previo++;
    if (previo == fmin(paso, n)) {
      return false;
    }
  }

  if (arr[previo] == objetivo) {
    return true;
  }

  return false;
}

// QuickSort
void quicksort(int arr[], int n) {
  if (n <= 1) {
    return;
  }

  int pivote = arr[n / 2];
  int *izquierda = malloc(sizeof(int) * n);
  int *medio = malloc(sizeof(int) * n);
  int *derecha = malloc(sizeof(int) * n);
  int izquierda_size = 0, medio_size = 0, derecha_size = 0;

  for (int i = 0; i < n; i++) {
    if (arr[i] < pivote) {
      izquierda[izquierda_size++] = arr[i];
    } else if (arr[i] == pivote) {
      medio[medio_size++] = arr[i];
    } else {
      derecha[derecha_size++] = arr[i];
    }
  }

  quicksort(izquierda, izquierda_size);
  quicksort(derecha, derecha_size);

  int i = 0;
  for (; i < izquierda_size; i++) {
    arr[i] = izquierda[i];
  }

  for (int j = 0; j < medio_size; j++) {
    arr[i++] = medio[j];
  }

  for (int k = 0; k < derecha_size; k++) {
    arr[i++] = derecha[k];
  }

  free(izquierda);
  free(medio);
  free(derecha);
}

// MergeSort
void merge(int izquierda[], int izquierda_n, int derecha[], int derecha_n,
           int resultado[]) {
  int i = 0, j = 0, k = 0;

  while (i < izquierda_n && j < derecha_n) {
    if (izquierda[i] < derecha[j]) {
      resultado[k++] = izquierda[i++];
    } else {
      resultado[k++] = derecha[j++];
    }
  }

  while (i < izquierda_n) {
    resultado[k++] = izquierda[i++];
  }

  while (j < derecha_n) {
    resultado[k++] = derecha[j++];
  }
}

void mergesort(int arr[], int n, int resultado[]) {
  if (n <= 1) {
    resultado[0] = arr[0];
    return;
  }

  int medio = n / 2;
  int *izquierda = malloc(sizeof(int) * medio);
  int *derecha = malloc(sizeof(int) * (n - medio));

  for (int i = 0; i < medio; i++) {
    izquierda[i] = arr[i];
  }

  for (int j = 0; j < n - medio; j++) {
    derecha[j] = arr[medio + j];
  }

  mergesort(izquierda, medio, resultado);
  mergesort(derecha, n - medio, resultado + medio);

  merge(izquierda, medio, derecha, n - medio, resultado);

  free(izquierda);
  free(derecha);
}

void generar_datos_prueba(int *datos, int tamano) {
  srand(time(NULL));
  for (int i = 0; i < tamano; i++) {
    datos[i] = rand() % 1000000;
  }
}

// Función de utilidad para imprimir los elementos de un arreglo
void imprimir_arreglo(int *arr, int n) {
  printf("[ ");
  for (int i = 0; i < n; i++) {
    printf("%d ", arr[i]);
  }
  printf("]\n");
}

int tamanos[] = {30000, 60000, 90000, 120000, 150000, 180000, 210000, 240000,
                 270000, 300000, 330000, 360000, 390000, 420000, 450000, 480000,
                 510000, 540000, 570000, 600000, 630000, 660000, 690000, 720000,
                 750000, 780000, 810000, 840000, 870000, 900000, 930000, 960000,
                 990000, 1020000, 1050000, 1080000, 1110000, 1140000, 1170000,
                 1200000, 1230000, 1260000, 1290000, 1320000, 1350000, 1380000,
                 1410000, 1440000, 1470000, 1500000, 1530000, 1560000, 1590000,
                 1620000, 1650000, 1680000, 1710000, 1740000, 1770000, 1800000,
                 1830000, 1860000, 1890000, 1920000, 1950000, 1980000, 2010000,
                 2040000, 2070000, 2100000, 2130000, 2160000, 2190000, 2220000,
                 2250000, 2280000, 2310000, 2340000, 2370000, 2400000, 2430000,
                 2460000, 2490000, 2520000, 2550000, 2580000, 2610000, 2640000,
                 2670000, 2700000, 2730000, 2760000, 2790000, 2820000, 2850000,
                 2880000, 2910000, 2940000, 2970000, 3000000, 3300000, 3600000,
                 3900000, 4200000, 4500000, 4800000, 5100000, 5400000, 5700000,
                 6000000, 6300000, 6600000, 6900000, 7200000, 7500000, 7800000,
                 8100000, 8400000, 8700000, 9000000, 9300000, 9600000, 9900000,
                 10000000};
int cant_tamanos = sizeof(tamanos) / sizeof(tamanos[0]);

int main() {
  clock_t start_time;
  clock_t end_time;
  double time_taken;

  while (true) {
    int op = 0;
    printf("1.Busqueda Binaria\n");
    printf("2.Busqueda Lineal por saltos\n");
    printf("3.MergeSort\n");
    printf("4.QuickSort\n");
    printf("Digite su opcion: ");
    scanf("%d", &op);
    printf("\n\n");

    switch (op) {
      case 1:
        for (int i = 0; i < cant_tamanos; i++) {
          int tamano = tamanos[i];
          int *datos = malloc(sizeof(int) * tamano);
          generar_datos_prueba(datos, tamano);

          start_time = clock();
          quicksort(datos, tamano);
          int objetivo = datos[rand() % tamano];
          bool encontrado = busqueda_binaria(datos, tamano, objetivo);
          end_time = clock();
          time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
          printf("Búsqueda Binaria (Tamaño %d):\n", tamano);
          printf("Tiempo de ejecución: %f segundos\n", time_taken);
          printf("-------------------------------------------------------------\n");

          free(datos);
        }
        break;

      case 2:
        for (int i = 0; i < cant_tamanos; i++) {
          int tamano = tamanos[i];
          int *datos = malloc(sizeof(int) * tamano);
          generar_datos_prueba(datos, tamano);

          start_time = clock();
          int objetivo = datos[rand() % tamano];
          bool encontrado = busqueda_saltos(datos, tamano, objetivo);
          end_time = clock();
          time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
          printf("Búsqueda Lineal por Saltos (Tamaño %d):\n", tamano);
          printf("Tiempo de ejecución: %f segundos\n", time_taken);
          printf("-------------------------------------------------------------\n");

          free(datos);
        }
        break;

      case 3:
        for (int i = 0; i < cant_tamanos; i++) {
          int tamano = tamanos[i];
          int *datos = malloc(sizeof(int) * tamano);
          int *resultado = malloc(sizeof(int) * tamano);
          generar_datos_prueba(datos, tamano);

          start_time = clock();
          mergesort(datos, tamano, resultado);
          end_time = clock();
          time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
          printf("MergeSort (Tamaño %d):\n", tamano);
          printf("Tiempo de ejecución: %f segundos\n", time_taken);
          printf("-------------------------------------------------------------\n");

          free(datos);
          free(resultado);
        }
        break;

      case 4:
        for (int i = 0; i < cant_tamanos; i++) {
          int tamano = tamanos[i];
          int *datos = malloc(sizeof(int) * tamano);
          int *datos2 = malloc(sizeof(int) * tamano);
          generar_datos_prueba(datos, tamano);

          start_time = clock();
          quicksort(datos2, tamano);
          end_time = clock();
          time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
          printf("QuickSort (Tamaño %d):\n", tamano);
          printf("Tiempo de ejecución: %f segundos\n", time_taken);
          printf("-------------------------------------------------------------\n");

          free(datos);
          free(datos2);
        }
        break;
    }
  }

  return 0;
}
