#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <clocale>

using namespace std;

// Класс стек для хранения бочек
class BarrelStack {
private:
    struct Node; // Узел стека
    Node* Top;
public:
    BarrelStack();      // Конструктор
    ~BarrelStack();     // Деструктор
    void Push(int Fuel); // Положить бочку
    bool Pop(int& FuelValue); // Вынуть бочку
    bool Peek(int& FuelValue) const; // Посмотреть верхнюю бочку
    bool IsEmpty() const; // Проверка на пустоту
};

// Класс баржа с несколькими отсеками
class Barge {
private:
    vector<BarrelStack> Compartments; // Отсеки
public:
    Barge(int CompartmentCount); // Конструктор
    bool IsValidIndex(int index) const; // Проверка индекса
    bool Load(int Index, int Fuel); // Погрузка
    bool Unload(int Index, int ExpectedFuel); // Выгрузка
    bool IsFullyEmpty() const; // Баржа пуста?
};

// Класс для обработки логики задачи
class BargeProcessor {
public:
    void Run(); // Запуск программы
    void PrintTaskInfo(); // Вывод информации о задаче
};
