#include "Header.h"


// --- Реализация BarrelStack ---
// Узел стека для BarrelStack
struct BarrelStack::Node {
    int FuelType;
    Node* Next;
    Node(int fuel, Node* next) : FuelType(fuel), Next(next) {}
};

// Конструктор стека
BarrelStack::BarrelStack() : Top(nullptr) {}

// Деструктор стека
BarrelStack::~BarrelStack() {
    int dummy;
    while (Pop(dummy)) {}
}

// Поместить бочку в стек
void BarrelStack::Push(int Fuel) {
    Top = new Node(Fuel, Top);
}

// Вынуть бочку из стека
bool BarrelStack::Pop(int& FuelValue) {
    if (IsEmpty()) return false;
    Node* OldTop = Top;
    FuelValue = OldTop->FuelType;
    Top = Top->Next;
    delete OldTop;
    return true;
}

// Посмотреть тип топлива на вершине
bool BarrelStack::Peek(int& FuelValue) const {
    if (IsEmpty()) return false;
    FuelValue = Top->FuelType;
    return true;
}

// Проверка: стек пустой?
bool BarrelStack::IsEmpty() const {
    return Top == nullptr;
}


// --- Реализация Barge ---
// Конструктор баржи с K отсеками
Barge::Barge(int CompartmentCount) {
    if (CompartmentCount > 0) {
        Compartments.resize(CompartmentCount);
    }
}

// Проверка корректности индекса
bool Barge::IsValidIndex(int index) const {
    return index >= 0 && index < Compartments.size();
}

// Погрузка бочки в отсек
bool Barge::Load(int Index, int Fuel) {
    if (!IsValidIndex(Index)) return false;
    Compartments[Index].Push(Fuel);
    return true;
}

// Выгрузка бочки из отсека
bool Barge::Unload(int Index, int ExpectedFuel) {
    if (!IsValidIndex(Index)) return false;
    int ActualFuel;
    // Проверка типа топлива
    if (!Compartments[Index].Peek(ActualFuel) || ActualFuel != ExpectedFuel) {
        return false;
    }
    return Compartments[Index].Pop(ActualFuel);
}

// Проверка: баржа пуста?
bool Barge::IsFullyEmpty() const {
    for (const auto& compartment : Compartments) {
        if (!compartment.IsEmpty()) {
            return false;
        }
    }
    return true;
}

// Вывод информации о задаче
void BargeProcessor::PrintTaskInfo() {
    cout << "===============================================\n"
        << "           Индивидуальное задание\n"
        << "           Симулятор работы баржи\n"
        << "===============================================\n\n";

    cout << "На барже располагается K грузовых отсеков. В каждый отсек можно поместить некоторое количество\n"
        << "бочек с одним из 10 000 видов топлива. Извлечь бочку из отсека можно только, если все бочки,\n"
        << "помещённые после неё, уже были извлечены. В каждый момент времени в каждом непустом отсеке\n"
        << "есть ровно одна бочка, которую можно извлечь, не трогая остальные.\n\n";

    cout << "Баржа изначально пуста. Затем она последовательно проплывает через N доков. В каждом доке:\n"
        << "- либо погружается бочка с некоторым видом топлива в некоторый отсек,\n"
        << "- либо выгружается крайняя бочка из некоторого отсека.\n\n";

    cout << "Ошибка фиксируется, если:\n"
        << "- указанный отсек пуст при выгрузке,\n"
        << "- выгружена бочка не того вида, который ожидался,\n"
        << "- на барже оказалось более P бочек,\n"
        << "- после всех операций баржа не пуста.\n\n";

    cout << "Задача программы:\n"
        << "- Определить максимальное количество бочек, которые одновременно находились на барже,\n"
        << "- либо вывести Error, если была допущена ошибка.\n\n";

    cout << "Формат входных данных:\n"
        << "- В первой строке три целых числа: N (число операций), K (отсеков), P (максимум бочек)\n"
        << "- Далее N строк: '+ A B' (погрузка) или '- A B' (выгрузка)\n\n";

    cout << "Формат выходных данных:\n"
        << "- Одно число — максимум бочек на барже одновременно,\n"
        << "- или слово Error, если была ошибка.\n\n";
}



// --- Реализация BargeProcessor ---
// Основной цикл работы программы
void BargeProcessor::Run() {
    setlocale(LC_ALL, "RU");
    PrintTaskInfo();
    int N = 0, K = 0, P_capacity = 0;

    // Ввод параметров
    while (true) {
        cout << "Введите N (операций), K (отсеков), P (макс. вместимость):\n> ";
        cin >> N >> K >> P_capacity;
        if (cin.good() && N > 0 && K > 0 && P_capacity > 0 && cin.peek() == '\n') {
            break;
        }
        cout << "Ошибка: введите три положительных целых числа.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    Barge barge(K);
    int currentBarrelCount = 0;
    int maxBarrelCount = 0;
    bool errorOccurred = false;

    cout << "\nВведите " << N << " операций (+ A B или - A B):\n";

    // Обработка операций
    for (int i = 0; i < N; ++i) {
        char Op;
        int A_compartment, B_fuel_type;
        cin >> Op >> A_compartment >> B_fuel_type;

        // Проверка корректности ввода
        if (cin.fail() || (Op != '+' && Op != '-') || A_compartment < 1 || A_compartment > K || B_fuel_type < 1) {
            errorOccurred = true;
            break;
        }

        if (Op == '+') {
            // Проверка вместимости
            if (currentBarrelCount >= P_capacity) {
                errorOccurred = true;
                break;
            }
            if (barge.Load(A_compartment - 1, B_fuel_type)) {
                currentBarrelCount++;
                maxBarrelCount = max(maxBarrelCount, currentBarrelCount);
            }
            else {
                errorOccurred = true;
                break;
            }
        }
        else { // Выгрузка
            if (barge.Unload(A_compartment - 1, B_fuel_type)) {
                currentBarrelCount--;
            }
            else {
                errorOccurred = true;
                break;
            }
        }
    }

    // После всех операций баржа должна быть пуста
    if (!errorOccurred && !barge.IsFullyEmpty()) {
        errorOccurred = true;
    }

    // Вывод результата
    if (errorOccurred) {
        cout << "Error" << endl;
    }
    else {
        cout << maxBarrelCount << endl;
    }
}
