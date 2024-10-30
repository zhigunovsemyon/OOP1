#pragma once

class Matrix {
private:
	/*Сокрытые поля*/
	int **ptr_;	    // Указатель на непосредственно матрицу
	long column_count_; // Вектор размеров строк
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
	void fill(long line = 0, long column = 0);

	// Получение числа строк матрицы
	inline long get_line_count() const { return this->line_count_; }

	// Получение числа строк матрицы
	inline long get_column_count() const { return this->column_count_; }

	// Вывод матрицы в stdout
	void print() const;

	/*Метод для заполнения матрицы случайными числами*/
	void randomise(int max, int min);

	/*Метод зануления матрицы*/
	inline void zero() { this->fill_with(0); }

	/*Метод заполнения матрицы одним числом*/
	void fill_with(int);

	/*Изменение элемента строки line, колонки column матрицы
	 * Поддерживается индексация с конца через индексы <0.
	 * Возврат false при неудаче, true при успехе*/
	bool set_element(long line, long column, int num);

	/*Чтение элемента строки line, колонки column матрицы
	 * Поддерживается индексация с конца через индексы <0*/
	int &get_element(long line, long column) const;
};
