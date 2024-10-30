/*Разработать структуру элементов данных класса в виде дин.структуры данных.
Разработать:
    *конструкторы для различных типов входных данных (без параметров, параметр-
    строка, параметр-массив), конструктор копирования (объект из объекта) и
    деструктор;

    *методы ввода и вывода содержимого объекта в поток (на экран), в текстовую
    строку (из строки);

    *получения ссылки на внутренние данные объекта (например на коэффициент
    матрицы), либо чтение/запись отдельных компонент объекта.

    *разработать конструктор с указанием значений

    *разработать конструктор с указанием переменного числа значений и индексов

В конструкторе и деструкторе предусмотреть трассировку -- вывод адреса текущего
объекта и его содержимого. Проследить последовательность вызова конструкторов и
деструкторов при определении глобальных, локальных, динамических объектов, а
также их массивов, при передаче объекта в виде форм. пар-ра по умолчанию и
возврате его по зн. в качестве результата.*/

#include "matr.h"   /* Матрица */
#include <climits>  /*INT_MAX INT_MIN*/
#include <ctime>    /*time()*/
#include <iostream> /*cout*/

int main(void) {
	// Инициализация генератора случайных чисел
	std::srand(static_cast<unsigned int>(std::time(NULL)));

	// Создание прямоугольной матрицы
	int m, n;
	std::cout << "Число строк: ";
	std::cin >> m;
	std::cout << "Число столбцов: ";
	std::cin >> n;
	Matrix &heapm = *new Matrix(m, n);
	std::cout << "Конечные размеры матрицы: "
		<< heapm.get_line_count() << " на "
		<< heapm.get_column_count() << '\n';

	heapm.fill();

	std::cout << "Матрица:\n";
	heapm.print();

	Matrix *m2 = new Matrix(heapm);
	delete &heapm;

	std::cout << "Матрица 2:\n";
	m2->print();
	delete m2;

	return EXIT_SUCCESS;
}
