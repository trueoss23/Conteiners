# Conteiners
## Платформы(Mac OS, Linux)
## Среда разработки: Vs Code
## Язык : С++17
## Тесты: gtest

* для запуска проекта необходимо иметь:
1. Компилятор С++(при создании использовался g++)
2. Gtest, gcov и lcov библиотеки(для тестов)

* Находясь в папке "src" (Mac OS, Linux) в терминале вводим команду "make", запуститься вывод тестов.

* Данный проект реализует 8 контейнеров из стандартной библиотеки C++ STL:
    - Очередь (Queue)
    - Стэк (Stack)
    - Массив (Array)
    - Вектор (Vector)
    - Связный список (LinckedList)
    - Соварь (Map)
    - Множество (Set)
    - Мульти-Множество (MultiSet)
***
* Для контейнеров Set, MultiSet и Map была реализована структура данных красно-черное дерево.
* Для тестов используется библиотека Gtest. Gcov/Lcov библиотеки обеспечивают вывод покрытия тестов. Для этого вводим в терминале "make gcov_report", находясь в папке "src". Результаты храняться в папке "report" файле "index.html".
