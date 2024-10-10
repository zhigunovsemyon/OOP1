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
    int **ptr;
    std::size_t line_count;
    std::size_t *column_count;

  public:
    // Конструктор без параметров
    Matrix() {
        ::trace << "Адрес созданного объекта: " << this << '\n';
        this->ptr = nullptr;
        this->column_count = nullptr;
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
        this->column_count = new size_t[size];
        ::trace << "Адрес созданной памяти: " << this->ptr << '\n';

        for (std::size_t i = 0; i < size; i++) {
            this->column_count[i] = size;
            this->ptr[i] = new int[size];
            ::trace << "Выделение памяти под строку " << i
                    << " по адресу: " << this->ptr[i] << '\n';
        }

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
        delete[] this->column_count;
    }

    // Вывод матрицы в stdout
    void Print() const {
        for (std::size_t i = 0; i < this->line_count; i++) {
            for (std::size_t j = 0; j < this->column_count[i]; j++)
                std::cout << ptr[i][j] << ' ';

            std::cout << '\n';
        }
    }

    void Randomise(int const max = INT_MAX, int const min = INT_MIN) {
        for (std::size_t i = 0; i < this->line_count; i++) {
            for (std::size_t j = 0; j < this->column_count[i]; j++)
                this->ptr[i][j] = min + std::rand() % (max + 1 - min);
        }
    }

    void Zero() {
        for (std::size_t i = 0; i < this->line_count; i++) {
            for (std::size_t j = 0; j < this->column_count[i]; j++)
                ptr[i][j] = 0;
        }
    }
};

int main(void) {
    std::srand(static_cast<unsigned int>(std::time(NULL)));
    Matrix stackm(2);
    Matrix &heapm = *new Matrix;
    std::cout << "Матрица 1: \n";
    stackm.Print();
    std::cout << "Матрица 2: \n";
    heapm.Print();

    std::cout << "\nРандомизация:\n";
    stackm.Randomise(10, 0);
    heapm.Randomise();

    std::cout << "Матрица 1: \n";
    stackm.Print();
    std::cout << "Матрица 2: \n";
    heapm.Print();

    std::cout << '\n';
    delete &heapm;
    return EXIT_SUCCESS;
}
