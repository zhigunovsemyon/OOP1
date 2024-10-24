#pragma once

class Matrix {
private:
	int **ptr; // Указатель на непосредственно матрицу
	long column_count; // Вектор размеров строк
	long line_count;   // Число строк

public:
	// Конструктор квадратной матрицы, либо пустой
	Matrix(long size = 0);

	// Конструктор прямоугольной матрицы матрицы
	Matrix(long lines, long rows);

	// Деструктор
	~Matrix();

	// Заполнение матрицы из стандартного ввода
	void Fill(long line = 0, long column = 0);

	// Получение числа строк матрицы
	inline long Get_line_count() const {return this->line_count;}

	// Получение числа строк матрицы
	inline long Get_column_count() const { return this->column_count; }

	// Вывод матрицы в stdout
	void Print() const;

	/*Метод для заполнения матрицы случайными числами*/
	void Randomise(int max, int min);

	/*Метод зануления матрицы*/
	inline void Zero() { this->FillWith(0); }

	/*Метод заполнения матрицы одним числом*/
	void FillWith(int);

	/*Изменение элемента строки line, колонки column матрицы
	 * Поддерживается индексация с конца через индексы <0.
	 * Возврат false при неудаче, true при успехе*/
	bool SetElement(long line, long column, int num);

	/*Чтение элемента строки line, колонки column матрицы
	 * Поддерживается индексация с конца через индексы <0*/
	int &GetElement(long line, long column) const;
};
