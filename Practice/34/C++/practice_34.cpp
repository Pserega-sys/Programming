﻿// practice_34.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

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

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
