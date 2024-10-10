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

// Вывод трассировки
std::ostream &trace = std::cout;

/*Матрица переменной размерности, представленная динамическим массивом
указателей на строки матрицы (линейные динамические массивы)*/
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
};

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
