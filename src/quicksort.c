#include "include/quicksort.h"
#include "include/build.h"
#include "include/generation.h"

void swap(struct Build* a, struct Build* b) {
    struct Build t = *a;
    *a = *b;
    *b = t;
}

int partition(struct Build *arr, int low, int high) {
    
    int pivot = arr[high].score;
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j].score < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    
    swap(&arr[i + 1], &arr[high]);  
    return i + 1;
}

// The QuickSort function implementation
void quickSort(struct Build *arr, int low, int high) {
    if (low < high) {
        
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}


void sortByScores(struct Generation *gen){
	quickSort(gen->builds, 0, 255);	
}
