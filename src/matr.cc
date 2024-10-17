#include "matr.h"
#include <iostream> /*std::size_t; std::rand(); std::cout*/
#include <utility>  /*swap() */

// Вывод трассировки
std::ostream &trace = std::cout;

// Конструктор квадратной матрицы, либо пустой
Matrix::Matrix(long size) {
	::trace << "Адрес созданного объекта: " << this << '\n';

	if (size <= 0) {
		this->column_count = this->line_count = 0;
		this->ptr = nullptr;
		return;
	}
	// Задание числа строк
	this->line_count = size;
	this->column_count = size;

	// Выделение памяти под вектор указателей
	this->ptr = new int *[static_cast<std::size_t>(size)];
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

	if (lines <= 0 || columns <= 0) {
		this->column_count = this->line_count = 0;
		this->ptr = nullptr;
		return;
	}

	// Задание числа строк
	this->line_count = lines;
	this->column_count = columns;

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
			<< "; Её адрес: " << this->ptr[this->line_count]
			<< '\n';
		delete[] this->ptr[this->line_count];
	}

	// Трассировка удаляемой матрицы
	::trace << "Адрес удаляемой памяти: " //
		<< this->ptr << ';'	      //
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
void Matrix::FillWith(int num) {
	for (long i = 0; i < this->line_count; i++) {
		for (long j = 0; j < this->column_count; j++)
			ptr[i][j] = num;
	}
}

/*Доступ к определённой строке line матрицы*/
int &Matrix::GetElement(long line, long column) {
	/*Если пользователь запросил отрицательный элемент, отсчитывается
	 *соответствующий элемент с конца*/
	if (column < 0)
		column = this->column_count + column;
	if (line < 0)
		line = this->line_count + line;

	// Возврат ссылки на соответствующую ячейку
	return this->ptr[line][column];
}

// Возврат false при неудаче, true при успехе
bool Matrix::SetElement(long line, long column, int num) {
	/*Если пользователь указал отрицательный элемент, отсчитывается
	 *соответствующий элемент с конца*/
	if (column < 0)
		column = this->column_count + column;
	if (line < 0)
		line = this->line_count + line;

	/*Если итоговый индекс отрицательный, запись не осуществляется*/
	if (line < 0 || column < 0)
		return false;

	/*Если итоговый индекс за пределами матрицы, запись не осуществляется*/
	if (line >= this->line_count || column >= this->column_count)
		return false;

	/*Запись элемента, возврат флага успешной записи*/
	this->ptr[line][column] = num;
	return true;
}
