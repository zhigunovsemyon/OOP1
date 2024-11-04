#pragma once

class Matrix {
private:
	/*Сокрытые поля*/
	int **ptr_;	    // Указатель на непосредственно матрицу
	long row_count_; // Число столбцов
	long line_count_;   // Число строк

	/*Сокрытые методы*/
	void constructor_(long const lines,
			  long const rows); // Общий конструктор

public:
	// Конструктор квадратной матрицы, либо пустой
	Matrix(long const size = 0);

	// Конструктор прямоугольной матрицы матрицы
	Matrix(long const lines, long const rows);

	// Конструктор копирования
	Matrix(Matrix const &other);

	// Деструктор
	~Matrix();

	// Заполнение матрицы из стандартного ввода
	Matrix& fill(long line = 0, long column = 0);

	// Получение числа строк матрицы
	inline long get_line_count() const { return this->line_count_; }

	// Получение числа строк матрицы
	inline long get_row_count() const { return this->row_count_; }

	// Вывод матрицы в stdout
	void print() const;

	/*Метод для заполнения матрицы случайными числами*/
	Matrix& randomise(int max, int min);

	/*Метод зануления матрицы*/
	inline Matrix& zero() { return this->fill_with(0); }

	/*Метод заполнения матрицы одним числом*/
	Matrix& fill_with(int);

	/*Изменение элемента строки line, колонки column матрицы
	 * Поддерживается индексация с конца через индексы <0.
	 * Возврат false при неудаче, true при успехе*/
	bool set_element(long line, long column, int num);

	/*Чтение элемента строки line, колонки column матрицы
	 * Поддерживается индексация с конца через индексы <0*/
	int &get_element(long line, long column) const;
};
