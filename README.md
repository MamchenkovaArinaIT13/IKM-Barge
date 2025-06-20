Моделирование погрузки и разгрузки баржи

Описание

Программа на C++ симулирует процесс погрузки и разгрузки бочек с топливом на барже, состоящей из нескольких отсеков. Каждый отсек работает по принципу стека (LIFO: последняя загруженная бочка выгружается первой). Программа проверяет корректность операций, фиксирует ошибки и определяет максимальное количество бочек, одновременно находящихся на барже.

Основные возможности

1) Поддержка до 100 000 отсеков и операций.
2) Обработка двух типов операций:
  - Погрузка (+ A B) — добавление бочки типа B в отсек A.
  - Разгрузка (- A B) — извлечение бочки из отсека A с проверкой типа B.
3) Проверка ошибок:
  - Попытка разгрузки из пустого отсека.
  - Несоответствие типа топлива при разгрузке.
  - Превышение максимальной вместимости баржи (P).
  - Баржа не пуста после выполнения всех операций.
4) Эффективное использование структур данных (std::vector и стеков).

Входные данные

Программа принимает:
1) Три числа:
   N — количество операций (1 ≤ N ≤ 100 000).
   K — количество отсеков (1 ≤ K ≤ 100 000).
   P — максимальное число бочек на барже (1 ≤ P ≤ 100 000).
2) N строк с операциями (+ A B или - A B), где:
   A — номер отсека (1 ≤ A ≤ K).
   B — тип топлива (1 ≤ B ≤ 10 000).

Выходные данные

-Максимальное количество бочек на барже в процессе работы.
-Error, если обнаружена любая ошибка.

Алгоритм

1) Инициализация:
  - Создается баржа с K отсеками (стеками).
  - Счетчики: текущее количество бочек (current), максимум (max), флаг ошибки (error).
2) Обработка операций:
  - Для погрузки проверяется, что current < P, затем бочка добавляется в отсек.
  - Для разгрузки проверяется, что отсек не пуст и тип бочки совпадает.
3) Финализация:
  - Если после всех операций баржа не пуста или была ошибка — вывод Error.
  - Иначе — вывод max.

Как запустить?

1) Клонируйте репозиторий: git clone https://github.com/MamchenkovaArinaIT13/IKM-Barge.git
2) Соберите программу: g++ main.cpp -o barge_simulation
3) Запустите: ./barge_simulation

Структура проекта

- main.cpp — точка входа, обработка ввода/вывода.
- Header.h / modul.cpp — класс баржи с методами погрузки/разгрузки.
- README.md — документация.

Автор

Мамченкова Арина Дмитриевна (Группа ИТ-13)
Пермский государственный национальный исследовательский университет.


