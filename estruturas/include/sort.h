#ifndef SORT_H
#define SORT_H

#include <chrono>
#include <iostream>
#include <vector>

#include "metrics.h"

using namespace std;


//função para movimentar dados 
template <typename T>
void troca(T& a, T& b) {
    T tmp = a;
    a     = b;
    b     = tmp;
}

template <typename T>
void insertion_sort_internal(T * array, int left, int right,  bool (*compare)(T&, T&), PerformanceMetrics *p) {
    // Implementação do Insert Sort
    for (int i = left + 1; i <= right; i++) {
        T key = array[i];
        int j = i - 1;

        while (j >= left && compare(key, array[j])) {
                p->n_comp++;
                array[j + 1] = array[j];
                p->n_mov++;
                j = j - 1;
        }

        array[j + 1] = key;
        p->n_mov++;
    }
}

template <typename T>
void insertion_sort(T* array, int left,  int right, bool (*compare)(T&, T&)) {
    PerformanceMetrics p;
    SetUpPerformanceMetrics(&p);
    auto t1 = Clock::now(); 
    insertion_sort_internal<T>(array, left, right, compare, &p);
     auto t2 = Clock::now();
    std::chrono::duration<double> diff = t2 - t1;
    PerformanceMetricsCPUTime(&p, diff.count());
    cout << "Insertion Sort:" << endl; 
    PerformanceMetricsPrint(&p);  
}

template <typename T>
void merge(T* array, int p, int q, int r, bool (*compare)(T&, T&), PerformanceMetrics *m) {
    //define o tamanho dos novos vetores
    int subArrayOne = q - p + 1;
    int subArrayTwo = r - q;

    T *leftArray = new T[subArrayOne], *rightArray = new T[subArrayTwo];

    //copia cada metade do vetor original para um vetor auxiliar
    for(int i = 0; i<subArrayOne; i++) {
        leftArray[i] = array[p + i];
        m->n_mov++;    
    }

    for(int j=0; j<subArrayTwo; j++) {
        rightArray[j] = array[q + j + 1];
        m->n_mov++;
    }

    int indexSubArrayOne = 0, indexSubArrayTwo = 0, indexOfMergedArray = p;

    while(indexSubArrayOne < subArrayOne && indexSubArrayTwo < subArrayTwo) {
        //compara os elementos dos vetores auxliares
        if(compare(leftArray[indexSubArrayOne], rightArray[indexSubArrayTwo])) {
            array[indexOfMergedArray] = leftArray[indexSubArrayOne];
            m->n_mov++;
            indexSubArrayOne++;
            m->n_comp++;
        } else {
            array[indexOfMergedArray] = rightArray[indexSubArrayTwo];
            m->n_mov++;
            indexSubArrayTwo++;
            m->n_comp++;
        }

        indexOfMergedArray++;
    }

    //copia o restante dos elementos dos vetores (caso hajam)
    while (indexSubArrayOne < subArrayOne) {
        array[indexOfMergedArray] = leftArray[indexSubArrayOne];
        m->n_mov++;
        m->n_comp++;
        indexSubArrayOne++;
        indexOfMergedArray++;
    }
   
    while (indexSubArrayTwo < subArrayTwo) {
        array[indexOfMergedArray] = rightArray[indexSubArrayTwo];
        m->n_mov++;
        m->n_comp++;
        indexSubArrayTwo++;
        indexOfMergedArray++;
    }

    delete [] leftArray;
    delete [] rightArray;
}

template <typename T>
void mergesort_internal(T* array, int start, int end, bool (*compare)(T&, T&), PerformanceMetrics *m) {
    if(start < end) {
        int q = (start+end)/2;
        mergesort_internal<T>(array, start, q, compare, m);
        mergesort_internal<T>(array, q+1, end,compare,m);
        merge<T>(array, start, q, end, compare,m);
    } else 
        return; 
}

template <typename T>
void merge_sort(T* array, int size, bool (*compare)(T&, T&)) {
    PerformanceMetrics m;
    SetUpPerformanceMetrics(&m);
    auto t1 = Clock::now(); 
    mergesort_internal<T>(array, 0, size-1, compare, &m);
    auto t2 = Clock::now();
    std::chrono::duration<double> diff = t2 - t1;
    PerformanceMetricsCPUTime(&m, diff.count());
    cout << "Merge Sort:" << endl; 
    PerformanceMetricsPrint(&m); 
}

template <typename T>
void quicksort_internal(T* array, int low, int high, bool (*compare)(T&, T&), PerformanceMetrics *p) {
    //escolhendo como pivo um elemento do meio do vetor
    T pivot = array[(low + high)/2];
    int i = low; 
    int j = high; 

    while(i<=j) {
        //pesquisa indices dos elementos que serão trocados
        while(compare(array[i], pivot) && i < high)
            i++;
        
        while(compare(pivot, array[j]) && j > low)
            j--;

        //troca os elementos i e j.
        if(i <= j ){
            troca(array[i], array[j]);
            p->n_mov+=3;
            i++;
            j--;
        }

        p->n_comp+=3;
    }

    //chama recursivamente para partir o vetor em um vetor menor (limitado pelo indice)
    if(low<j){
        p->n_comp++;
        quicksort_internal<T>(array, low, j, compare,p);
    }
        

    if(i<high){
        p->n_comp++;
        quicksort_internal<T>(array, i, high, compare,p);
    }
        

    //p->n_comp+=2;
}

template <typename T>
void quick_sort(T* array, int size, bool (*compare)(T&, T&))  {
    PerformanceMetrics p;
    SetUpPerformanceMetrics(&p);
    auto t1 = Clock::now(); 
    quicksort_internal<T>(array, 0, size-1, compare,&p);
    auto t2 = Clock::now();
    std::chrono::duration<double> diff = t2 - t1;
    PerformanceMetricsCPUTime(&p, diff.count());
    cout << "Quick Sort:" << endl; 
    PerformanceMetricsPrint(&p); 
}

template <typename T>
void timSort(T* array, int n, bool (*compare)(T&, T&)){
    PerformanceMetrics p;
    SetUpPerformanceMetrics(&p);
    auto t1 = Clock::now(); 
    timsort_internal(array, n, compare,&p);
    auto t2 = Clock::now();
    std::chrono::duration<double> diff = t2 - t1;
    PerformanceMetricsCPUTime(&p, diff.count());
    cout << "Tim Sort:" << endl; 
    PerformanceMetricsPrint(&p); 
}

template <typename T>
void timsort_internal(T* array, int n, bool (*compare)(T&, T&), PerformanceMetrics *p){
    const int RUN = 64;
    for (int i = 0; i < n; i+=RUN)
        insertion_sort_internal<T>(array, i, min((i+RUN-1),(n-1)), compare, p);
 
    for (int size = RUN; size < n; size = 2*size) {
        for (int left = 0; left < n; left += 2*size) {
            int mid = left + size - 1;
            int right = min((left + 2*size - 1), (n-1));

            if(mid < right)
                merge(array, left, mid, right, compare, p);
        }
    }
}

void SetUpPerformanceMetrics(PerformanceMetrics* pm){
    pm->n_comp = 0;
    pm->n_mov = 0;
    pm->time   = 0.0;
}


void PerformanceMetricsPrint(PerformanceMetrics* pm){   
#ifdef CPU_TIME
    cout << " Tempo de execução: "     << pm->time    << " segundos" << endl;
#endif
    cout << " Comparacoes: " << pm->n_comp << endl;
    cout << " Movimentacoes: "      << pm->n_mov << endl; 
}

void PerformanceMetricsCPUTime(PerformanceMetrics* pm, double time){
    pm->time = time;
}

#endif /* SORT_H */