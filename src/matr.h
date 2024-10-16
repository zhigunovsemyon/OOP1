#pragma once
#include <iostream> /*std::size_t*/

class Matrix {
      private:
	int **ptr;		   // Указатель на непосредственно матрицу
	std::size_t column_count;  // Вектор размеров строк
	std::size_t line_count;	   // Число строк

      public:
	// Конструктор квадратной матрицы, либо пустой
	Matrix(std::size_t size = 0);

	// Конструктор прямоугольной матрицы матрицы
	Matrix(std::size_t lines, std::size_t rows);

	// Деструктор
	~Matrix();

	// Получение числа строк матрицы
	std::size_t Get_line_count();
	
	// Получение числа строк матрицы
	std::size_t Get_column_count();

	// Вывод матрицы в stdout
	void Print() const;

	/*Метод для заполнения матрицы случайными числами*/
	void Randomise(int max, int min);

	/*Метод зануления матрицы*/
	void Zero();

	/*Доступ к определённой строке line матрицы*/
	int *operator[](long line);
};
