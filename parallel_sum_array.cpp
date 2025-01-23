#include <iostream>
#include <iomanip>
#include <random>

#ifdef _OPENMP
#include <omp.h>
#else
#define omp_get_thread_num() 0
#endif

// Definiciones
#define N 1000
#define chunk 100
#define mostrar 10

void imprimeArreglo(float *d);
void imprimeTodosLosElementos(float *a, float *b, float *c);

// Usar namespace para evitar escribir std::
using namespace std;

int main() {
  // Inicializar generador de numeros aleatorios
  // Se generaran numeros reales X tal que 1 <= X < 100
  random_device rd;
  mt19937 gen(rd());
  uniform_real_distribution<float> dis(1, 100);

  cout << "Sumando arreglos en paralelo\n";

  // Declarar los arreglos con la cantidad deseada de elementos (N)
  float a[N], b[N], c[N];
  int i;

  // Inicializar arrays de manera secuencial
  for (i = 0; i < N; i++) 
  {
    a[i] = dis(gen); 
    b[i] = dis(gen);
  }

  int pedazos = chunk;

    // INICIA CODIGO PARALELO
    #pragma omp parallel for shared(a, b, c, pedazos) private(i) schedule(static, pedazos)
    for (i = 0; i < N; i++)
      {
        c[i] = a[i] + b[i];
      }
    // TERMINA CODIGO PARALELO
  
    // Imprimir secuencialmente los elementos y el resultado
    cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo a: " << endl;
    imprimeArreglo(a);
    cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo b: " << endl;
    imprimeArreglo(b);
    cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo c: " << endl;
    imprimeArreglo(c);

    // Imprimir todos los elementos y sus resultados
    cout << "\nImprimiendo los elementos y sus sumas:\n";
    imprimeTodosLosElementos(a, b, c);
}

void imprimeArreglo(float *d)
{
  for (int x = 0; x < mostrar; x++)
    cout << d[x] << " - ";
  cout << endl;
}

void imprimeTodosLosElementos(float *a, float *b, float *c)
{
  // Imprimir encabezados
  cout << left << setw(10) << "Índice" 
       << left << setw(15) << "Arreglo a" 
       << left << setw(15) << "Arreglo b" 
       << left << setw(15) << "Arreglo c" << endl;
  cout << string(55, '-') << endl;

  // Imprimir cada elemento
  for(int i = 0; i < mostrar; i++)
  {
    cout << left << setw(10) << i
         << left << setw(15) << a[i]
         << left << setw(15) << b[i]
         << left << setw(15) << c[i] << endl;
  }
}
