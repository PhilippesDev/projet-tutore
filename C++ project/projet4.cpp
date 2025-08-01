#include <iostream>
#include <vector>
#include <stdexcept>

// Classe template Matrix
template <typename T>
class Matrix {
private:
    std::vector<std::vector<T>> data;
    int rows, cols;

public:
    Matrix(int rows, int cols) : rows(rows), cols(cols) {
        data.resize(rows, std::vector<T>(cols, T()));
    }

    void setElement(int row, int col, T value) {
        if (row >= rows || col >= cols || row < 0 || col < 0)
            throw std::out_of_range("Indice hors limite");
        data[row][col] = value;
    }

    T getElement(int row, int col) const {
        if (row >= rows || col >= cols || row < 0 || col < 0)
            throw std::out_of_range("Indice hors limite");
        return data[row][col];
    }

    int getRows() const { return rows; }
    int getCols() const { return cols; }

    // Addition de matrices
    Matrix<T> operator+(const Matrix<T>& other) const {
        if (rows != other.rows || cols != other.cols)
            throw std::invalid_argument("Les dimensions ne correspondent pas pour l'addition");

        Matrix<T> result(rows, cols);
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                result.data[i][j] = data[i][j] + other.data[i][j];

        return result;
    }

    // Multiplication de matrices
    Matrix<T> operator*(const Matrix<T>& other) const {
        if (cols != other.rows)
            throw std::invalid_argument("Les dimensions ne correspondent pas pour la multiplication");

        Matrix<T> result(rows, other.cols);
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < other.cols; ++j)
                for (int k = 0; k < cols; ++k)
                    result.data[i][j] += data[i][k] * other.data[k][j];

        return result;
    }

    // Affichage de la matrice
    friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix) {
        for (int i = 0; i < matrix.rows; ++i) {
            for (int j = 0; j < matrix.cols; ++j)
                os << matrix.data[i][j] << " ";
            os << std::endl;
        }
        return os;
    }
};

// Programme principal
int main() {
    try {
        Matrix<int> mat1(2, 3);
        Matrix<int> mat2(3, 2);

        // Initialisation de mat1
        mat1.setElement(0, 0, 1);
        mat1.setElement(0, 1, 2);
        mat1.setElement(0, 2, 3);
        mat1.setElement(1, 0, 4);
        mat1.setElement(1, 1, 5);
        mat1.setElement(1, 2, 6);

        // Initialisation de mat2
        mat2.setElement(0, 0, 7);
        mat2.setElement(0, 1, 8);
        mat2.setElement(1, 0, 9);
        mat2.setElement(1, 1, 10);
        mat2.setElement(2, 0, 11);
        mat2.setElement(2, 1, 12);

        std::cout << "Matrice 1:\n" << mat1;
        std::cout << "Matrice 2:\n" << mat2;

        Matrix<int> produit = mat1 * mat2;
        std::cout << "Produit des matrices:\n" << produit;
    }
    catch (const std::exception& ex) {
        std::cerr << "Erreur: " << ex.what() << std::endl;
    }

    return 0;
}
