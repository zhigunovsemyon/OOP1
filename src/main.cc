/*Разработать структуру элементов данных класса в виде дин.структуры данных.
Разработать:
    *конструкторы для различных типов входных данных (без параметров, параметр-
    строка, параметр-массив), конструктор копирования (объект из объекта) и
    деструктор;

    *методы ввода и вывода содержимого объекта в поток (на экран), в текстовую
    строку (из строки);

    *получения ссылки на внутренние данные объекта (например на коэффициент
    матрицы), либо чтение/запись отдельных компонент объекта.

В конструкторе и деструкторе предусмотреть трассировку -- вывод адреса текущего
объекта и его содержимого. Проследить последовательность вызова конструкторов и
деструкторов при определении глобальных, локальных, динамических объектов, а
также их массивов, при передаче объекта в виде форм. пар-ра по умолчанию и
возврате его по зн. в качестве результата.*/

#include <climits>  /*INT_MAX INT_MIN*/
#include <ctime>    /*time()*/
#include <iostream> /*cout*/
#include "matr.h" /* Матрица */

int main(void) {
    // Инициализация генератора случайных чисел
    std::srand(static_cast<unsigned int>(std::time(NULL)));

    // Создание матриц на стеке и в куче
    Matrix stackm(2, 10);
    Matrix &heapm = *new Matrix;

    // Вывод только созданных матриц
    std::cout << "Матрица 1: \n";
    stackm.Print();
    std::cout << "Матрица 2: \n";
    heapm.Print();

    // Заполнение матриц случайными числами
    std::cout << "\nРандомизация:\n";
    stackm.Randomise(INT_MAX - 1488);
    heapm.Randomise();

    // Вывод матриц после изменения
    std::cout << "Матрица 1: \n";
    stackm.Print();
    std::cout << "Матрица 2: \n";
    heapm.Print();
    std::cout << '\n';

    // Очистка матрицы на куче из памяти
    delete &heapm;
    return EXIT_SUCCESS;
}
