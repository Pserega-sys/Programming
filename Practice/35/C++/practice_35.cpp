
#include <iostream>

using namespace std;


struct IntArray {
    int* data;
    int size;
};



void create(IntArray& arr, int size) {
    arr.data = new int[size];
    arr.size = size;
}



int get(IntArray& arr, int index) {
    if (index < 0 || index > arr.size){
        cout << "Ошибка. Индекс массива находится за его пределами. Размер массива равен [" << arr.size << "]";
        return 0;
    }
        return arr.data[index];
}




void set(IntArray& arr, int index, int value) {
    if (index < 0 || index > arr.size) {
        cout << "Ошибка. Индекс массива находится за его пределами. Размер массива равен [" << arr.size << "]";
        return;
    }
    arr.data[index] = value;
}



void print(IntArray& arr) {
    cout << '[';
    for (int i = 0; i < arr.size; i++)
    {
        cout << arr.data[i];
        if (i < arr.size - 1)
        {
            cout << ", ";
        }
    }

    cout << ']' << endl;
}



void resize(IntArray& arr, int newSize) {
    int* arr2 = new int[newSize];
    memcpy(arr2, arr.data, sizeof(int) * arr.size);

    for (int i = arr.size; i < newSize; ++i)
        arr2[i] = 0;

    delete[] arr.data;
    arr.data = arr2;
    arr.size = newSize;
    return;
}




void destroy(IntArray& arr) {
    if (!arr.data)
        return;
    arr.data = nullptr;
    arr.size = 0;
    delete[] arr.data;
}


int main() {
    setlocale(LC_ALL, "rus");
    int size = 30;
    IntArray arr;
    create(arr,size);
    for (int i = 0; i < size; i++)
        set(arr, i, i + 1);

    print(arr);
    resize(arr, 50);
    print(arr);
    resize(arr, 10);
    print(arr);
    destroy(arr);
    return 0;
}
