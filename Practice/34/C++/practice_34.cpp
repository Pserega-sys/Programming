
#include <iostream>


using namespace std;

int* create(int a, int b = 0, int c = 0) {
    int* array = new int[a];
    array[0] = b;
    for (int i = 1; i < a; i++)
    {
        array[i] = b + c;
        b += c;
    }
    return array;
}
    
    void create(int** array, int a, int b, int c) {
     *array = create(a, b, c);
}

void destroy(int** array) {
    if (array == nullptr) {
        return;
    }
     *array = nullptr;
}

void sort(int* array, int a) {
    int i = 0; int j = 0; int key = 0; int temp = 0;
    for (i = 0; i < a - 1; i++)
    {
        key = i + 1;
        temp = array[key];
        for (j = i + 1; j > 0; j--)
        {
            if (temp < array[j - 1])
            {
                array[j] = array[j - 1];
                key = j - 1;
            }
        }
        array[key] = temp;
    }
}
int* print(int* array, int a) {
    cout << '[';
    for (int i = 0; i < a; i++)
    {
        cout << array[i];
        if (i < a - 1)
        {
            cout << ", ";
        }
    }

    cout << ']' << endl;

    return array;
}

int main() {
    int a; int b = 0; int c = 0;
    setlocale(LC_ALL, "rus");
    cout << "Введите длину массива\n";
    cin >> a;
    cout << "Введите начальный член массива\n";
    cin >> b;
    cout << "Введите шаг арифметической прогрессии\n";
    cin >> c;
    int* array;
    create(&array, a, b, c);
    sort(array, a);
    print(array, a);
    destroy(&array);
    delete[] array;
    return 0;
}
