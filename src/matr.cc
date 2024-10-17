#include "matr.h"  
#include <iostream> /*std::size_t; std::rand(); std::cout*/
#include <utility> /*swap() */

// Вывод трассировки
std::ostream &trace = std::cout;

// Конструктор квадратной матрицы, либо пустой
Matrix::Matrix(long size) {
	::trace << "Адрес созданного объекта: " << this << '\n';
	// Задание числа строк
	this->line_count = size;

	// Выделение памяти под вектор указателей
	this->ptr =
		(size) ? new int *[static_cast<std::size_t>(size)] : nullptr;
	::trace << "Адрес созданной памяти: " << this->ptr << '\n';

	// Выделение памяти под каждую строку
	for (long i = 0; i < size; i++) {
		this->ptr[i] = new int[static_cast<std::size_t>(size)];
		::trace << "Выделение памяти под строку " << i
			<< " по адресу: " << this->ptr[i] << '\n';
	}

	// Зануление матрицы
	this->Zero();
}

// Конструктор прямоугольной матрицы матрицы
Matrix::Matrix(long lines, long columns) {
	::trace << "Адрес созданного объекта: " << this << '\n';
	// Задание числа строк
	this->line_count = lines;

	// Выделение памяти под вектор указателей
	this->ptr = new int *[static_cast<std::size_t>(lines)];
	::trace << "Адрес созданной памяти: " << this->ptr << '\n';

	// Выделение памяти под каждую строку
	for (long i = 0; i < lines; i++) {
		this->ptr[i] = new int[static_cast<std::size_t>(columns)];
		::trace << "Выделение памяти под строку " << i
			<< " по адресу: " << this->ptr[i] << '\n';
	}

	// Зануление матрицы
	this->Zero();
}

// Деструктор
Matrix::~Matrix() {
	while (this->line_count--) {
		// Трассировка каждой удаляемой строки
		::trace << "Номер удаляемой строки: " //
			<< this->line_count	      //
			<< ". Её адрес: " << this->ptr[this->line_count]
			<< '\n';
		delete[] this->ptr[this->line_count];
	}

	// Трассировка удаляемой матрицы
	::trace << "Адрес удаляемой памяти: " //
		<< this->ptr		      //
		<< " В объекте под адресом: " << this << '\n';
	delete[] this->ptr;
}

// Вывод матрицы в stdout
void Matrix::Print() const {
	for (long i = 0; i < this->line_count; i++) {
		for (long j = 0; j < this->column_count; j++)
			std::cout << ptr[i][j] << ' ';

		std::cout << '\n';
	}
}

/*Метод для заполнения матрицы случайными числами*/
void Matrix::Randomise(int max, int min) {
	/*Переворот значений min и max*/
	if (min > max)
		std::swap(max, min);

	for (long i = 0; i < this->line_count; i++) {
		for (long j = 0; j < this->column_count; j++)
			this->ptr[i][j] = min + std::rand() % (max + 1 - min);
	}
}

long Matrix::Get_column_count() {
	return this->column_count;
}

long Matrix::Get_line_count() {
	return this->line_count;
}

/*Метод зануления матрицы*/
void Matrix::Zero() {
	for (long i = 0; i < this->line_count; i++) {
		for (long j = 0; j < this->column_count; j++)
			ptr[i][j] = 0;
	}
}

/*Доступ к определённой строке line матрицы*/
int *Matrix::operator[](long line) {
	/*Если пользователь запросил отрицательный элемент, отсчитывается
	 *соответствующий элемент с конца*/
	if (line < 0)
		line = this->line_count + line;
	/*Если запрашиваемая строка находится за пределами матрицы,
	 *возвращается null, что приведёт к падению программы*/
	return (line < this->line_count && line >= 0) ? this->ptr[line]
						      : nullptr;
}
