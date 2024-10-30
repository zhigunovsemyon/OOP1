#include "matr.h"
#include <iostream> /*std::size_t; std::rand(); std::cout*/
#include <utility>  /*swap() */

// Вывод трассировки
std::ostream &trace = std::cout;

// Конструктор квадратной матрицы, либо пустой
Matrix::Matrix(long const size) {
	::trace << "Адрес созданного объекта: " << this << '\n';

	if (size <= 0) {
		this->column_count_ = this->line_count_ = 0;
		this->ptr_ = nullptr;
		return;
	}
	// Задание числа строк
	this->line_count_ = size;
	this->column_count_ = size;

	// Выделение памяти под вектор указателей
	this->ptr_ = new int *[static_cast<std::size_t>(size)];
	::trace << "Адрес созданной памяти: " << this->ptr_ << '\n';

	// Выделение памяти под каждую строку
	for (long i = 0; i < size; i++) {
		this->ptr_[i] = new int[static_cast<std::size_t>(size)];
		::trace << "Выделение памяти под строку " << i
			<< " по адресу: " << this->ptr_[i] << '\n';
	}

	// Зануление матрицы
	this->zero();
}

// Конструктор прямоугольной матрицы матрицы
Matrix::Matrix(long const lines, long const columns) {
	::trace << "Адрес созданного объекта: " << this << '\n';

	if (lines <= 0 || columns <= 0) {
		this->column_count_ = this->line_count_ = 0;
		this->ptr_ = nullptr;
		return;
	}

	// Задание числа строк
	this->line_count_ = lines;
	this->column_count_ = columns;

	// Выделение памяти под вектор указателей
	this->ptr_ = new int *[static_cast<std::size_t>(lines)];
	::trace << "Адрес созданной памяти: " << this->ptr_ << '\n';

	// Выделение памяти под каждую строку
	for (long i = 0; i < lines; i++) {
		this->ptr_[i] = new int[static_cast<std::size_t>(columns)];
		::trace << "Выделение памяти под строку " << i
			<< " по адресу: " << this->ptr_[i] << '\n';
	}

	// Зануление матрицы
	this->zero();
}

// Деструктор
Matrix::~Matrix() {
	while (this->line_count_--) {
		// Трассировка каждой удаляемой строки
		::trace << "Номер удаляемой строки: " //
			<< this->line_count_	      //
			<< "; Её адрес: " << this->ptr_[this->line_count_]
			<< '\n';
		delete[] this->ptr_[this->line_count_];
	}

	// Трассировка удаляемой матрицы
	::trace << "Адрес удаляемой памяти: " //
		<< this->ptr_ << ';'	      //
		<< " В объекте под адресом: " << this << '\n';
	delete[] this->ptr_;
}

// Вывод матрицы в stdout
void Matrix::print() const {
	for (long i = 0; i < this->line_count_; i++) {
		for (long j = 0; j < this->column_count_; j++)
			std::cout << ptr_[i][j] << ' ';

		std::cout << '\n';
	}
}

/*Метод для заполнения матрицы случайными числами*/
void Matrix::randomise(int max, int min) {
	/*Переворот значений min и max*/
	if (min > max)
		std::swap(max, min);

	for (long i = 0; i < this->line_count_; i++) {
		for (long j = 0; j < this->column_count_; j++)
			this->ptr_[i][j] = min + std::rand() % (max + 1 - min);
	}
}

/*Метод зануления матрицы*/
void Matrix::fill_with(int const num) {
	for (long i = 0; i < this->line_count_; i++) {
		for (long j = 0; j < this->column_count_; j++)
			ptr_[i][j] = num;
	}
}

/*Доступ к определённой строке line матрицы*/
int &Matrix::get_element(long line, long column) const {
	/*Если пользователь запросил отрицательный элемент, отсчитывается
	 *соответствующий элемент с конца*/
	if (column < 0)
		column = this->column_count_ + column;
	if (line < 0)
		line = this->line_count_ + line;

	// Возврат ссылки на соответствующую ячейку
	return this->ptr_[line][column];
}

// Возврат false при неудаче, true при успехе
bool Matrix::set_element(long line, long column, int num) {
	/*Если пользователь указал отрицательный элемент, отсчитывается
	 *соответствующий элемент с конца*/
	if (column < 0)
		column = this->column_count_ + column;
	if (line < 0)
		line = this->line_count_ + line;

	/*Если итоговый индекс отрицательный, запись не осуществляется*/
	if (line < 0 || column < 0)
		return false;

	/*Если итоговый индекс за пределами матрицы, запись не осуществляется*/
	if (line >= this->line_count_ || column >= this->column_count_)
		return false;

	/*Запись элемента, возврат флага успешной записи*/
	this->ptr_[line][column] = num;
	return true;
}

void Matrix::fill(long line, long column) {
	/*Если пользователь указал отрицательный элемент, отсчитывается
	 *соответствующий элемент с конца*/
	if (column < 0)
		column = this->column_count_ + column;
	if (line < 0)
		line = this->line_count_ + line;

	/*Если итоговый индекс отрицательный, запись не осуществляется*/
	if (line < 0 || column < 0)
		return;

	for (long i = line; i < this->line_count_; ++i) {
		for (long j = column; j < this->column_count_; ++j) {
			std::cout << '[' << i << "][" << j << "] = ";
			std::cin >> this->ptr_[i][j];
		}
	}
}
