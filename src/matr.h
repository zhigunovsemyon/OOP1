#pragma once
#include <climits>
#include <iostream>

// Вывод трассировки
std::ostream &trace = std::cout;

class Matrix {
  private:
    int **ptr; // Указатель на непосредственно матрицу
    std::size_t *rows_in_line; // Вектор размеров строк
    std::size_t line_count;    // Число строк

  public:
    // Конструктор пустой матрицы без параметров
    Matrix() {
        ::trace << "Адрес созданного объекта: " << this << '\n';
        this->ptr = nullptr;
        this->rows_in_line = nullptr;
        this->line_count = 0;
        ::trace << "Адрес созданной памяти: " << this->ptr << '\n';
    }

    // Конструктор квадратной матрицы
    Matrix(std::size_t size) {
        ::trace << "Адрес созданного объекта: " << this << '\n';
        // Задание числа строк
        this->line_count = size;

        // Выделение памяти под вектор указателей и размеров
        this->ptr = new int *[size];
        this->rows_in_line = new size_t[size];
        ::trace << "Адрес созданной памяти: " << this->ptr << '\n';

        // Выделение памяти под каждую строку
        for (std::size_t i = 0; i < size; i++) {
            this->rows_in_line[i] = size;
            this->ptr[i] = new int[size];
            ::trace << "Выделение памяти под строку " << i
                    << " по адресу: " << this->ptr[i] << '\n';
        }

        // Зануление матрицы
        this->Zero();
    }

    // Конструктор прямоугольной матрицы матрицы
    Matrix(std::size_t lines, std::size_t rows) {
        ::trace << "Адрес созданного объекта: " << this << '\n';
        // Задание числа строк
        this->line_count = lines;

        // Выделение памяти под вектор указателей и размеров
        this->ptr = new int *[lines];
        this->rows_in_line = new size_t[lines];
        ::trace << "Адрес созданной памяти: " << this->ptr << '\n';

        // Выделение памяти под каждую строку
        for (std::size_t i = 0; i < lines; i++) {
            this->rows_in_line[i] = rows;
            this->ptr[i] = new int[rows];
            ::trace << "Выделение памяти под строку " << i
                    << " по адресу: " << this->ptr[i] << '\n';
        }

        // Зануление матрицы
        this->Zero();
    }

    // Деструктор
    ~Matrix() {
        while (this->line_count--) {
            // Трассировка каждой удаляемой строки
            ::trace << "Номер удаляемой строки: " //
                    << this->line_count           //
                    << ". Её адрес: " << this->ptr[this->line_count] << '\n';
            delete[] this->ptr[this->line_count];
        }

        // Трассировка удаляемой матрицы
        ::trace << "Адрес удаляемой памяти: " //
                << this->ptr                  //
                << " В объекте под адресом: " << this << '\n';
        delete[] this->ptr;
        delete[] this->rows_in_line;
    }

    // Вывод матрицы в stdout
    void Print() const {
        for (std::size_t i = 0; i < this->line_count; i++) {
            for (std::size_t j = 0; j < this->rows_in_line[i]; j++)
                std::cout << ptr[i][j] << ' ';

            std::cout << '\n';
        }
    }

    /*Метод для заполнения матрицы случайными числами*/
    void Randomise(int const max = INT_MAX, int const min = INT_MIN) {
        for (std::size_t i = 0; i < this->line_count; i++) {
            for (std::size_t j = 0; j < this->rows_in_line[i]; j++)
                this->ptr[i][j] = min + std::rand() % (max + 1 - min);
        }
    }

    /*Метод зануления матрицы*/
    void Zero() {
        for (std::size_t i = 0; i < this->line_count; i++) {
            for (std::size_t j = 0; j < this->rows_in_line[i]; j++)
                ptr[i][j] = 0;
        }
    }

    /*Доступ к определённой строке line матрицы*/
    int* operator[](std::size_t line){
        /*Если запрашиваемая строка находится за пределами матрицы,
         *возвращается null, что приведёт к падению программы*/
        return (line < this->line_count) ? this->ptr[line] : nullptr;
    }
};
