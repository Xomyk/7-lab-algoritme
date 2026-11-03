#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>

using namespace std;
using namespace chrono;

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high]; // Опорный элемент (последний)
    int i = (low - 1);     // Индекс для меньших элементов

    for (int j = low; j <= high - 1; j++) {
        // Если текущий элемент меньше или равен опорному
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

// Рекурсивная функция быстрой сортировки
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        // Индекс разделения
        int pi = partition(arr, low, high);

        // Рекурсивно сортируем левую и правую части
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Функция слияния двух подмассивов
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Создаем временные массивы
    vector<int> L(n1), R(n2);

    // Копируем данные во временные массивы
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    // Сливаем временные массивы обратно в arr
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Копируем оставшиеся элементы L (если есть)
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Копируем оставшиеся элементы R (если есть)
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Рекурсивная функция сортировки слиянием
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Сортируем первую и вторую половины
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Сливаем отсортированные половины
        merge(arr, left, mid, right);
    }
}
// Генерация случайного массива
vector<int> generateRandomArray(int size) {
    vector<int> arr(size);
    for (int i = 0; i < size; i++) {
        arr[i] = rand();
    }
    return arr;
}

// Замер времени выполнения сортировки
template <typename Func>
long long measureTime(Func sortFunction, vector<int> arr) {
    auto start = high_resolution_clock::now();
    sortFunction(arr, 0, arr.size() - 1); // Передаем копию массива
    auto end = high_resolution_clock::now();
    return duration_cast<microseconds>(end - start).count();
}


int main() {
    setlocale(LC_ALL, "ru");
    srand(time(0)); // Инициализация генератора случайных чисел

    cout << "=== СРАВНЕНИЕ БЫСТРОЙ СОРТИРОВКИ И СОРТИРОВКИ СЛИЯНИЕМ ===" << endl;
    cout << "Тест на случайных массивах" << endl;
    cout << "--------------------------------------------------------" << endl;
    cout << "Размер (N)\tБыстрая (мкс)\tСлиянием (мкс)" << endl;
    cout << "--------------------------------------------------------" << endl;

    vector<int> sizes = {10000, 50000, 100000};

    for (int n : sizes) {
        // Генерируем один и тот же случайный массив для обеих сортировок
        vector<int> original = generateRandomArray(n);

        // Замер для Быстрой сортировки
        long long timeQuick = measureTime(quickSort, original);

        // Замер для Сортировки слиянием
        long long timeMerge = measureTime(mergeSort, original);

        cout << n << "\t\t" << timeQuick << "\t\t" << timeMerge << endl;
    }

    cout << "--------------------------------------------------------" << endl;
    return 0;
}