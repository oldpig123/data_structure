#include <algorithm>
#include <fstream>
#include <iomanip>

#include "SparseMatrix.h"

char compare(int a, int b) {
    if (a > b)
        return '>';
    else if (a < b)
        return '<';
    else if (a == b)
        return '=';
};

SparseMatrix SparseMatrix::Transpose() {
    SparseMatrix bt(this->Rows, this->Cols, this->Terms);
    // SparseMatrix* b = new SparseMatrix(this->Cols, this->Rows, this->Terms);
    //
    // DO IT BY YOURSELF
    for (int i = 0; i < bt.Terms && Terms > 0; i++) {
        /* code */
        bt.smArray[i].row = smArray[i].col;
        bt.smArray[i].col = smArray[i].row;
        bt.smArray[i].value = smArray[i].value;
    }
    sort(bt.smArray.begin(), bt.smArray.end(), [](const MatrixTerm& a, const MatrixTerm& b) { return pos_comp(a, b); });

    return bt;  // or return *b
}

// Fast Transpose
SparseMatrix SparseMatrix::FastTranspose() {  //  O(terms + cols) time complexity
    SparseMatrix b(Cols, Rows, Terms);

    // DO IT BY YOURSELF
    if (Terms > 0) {
        int* rowsize = new int[Cols];
        int* rowstart = new int[Cols];
        fill(rowsize, rowsize + Cols, 0);
        for (int i = 0; i < Terms; i++) {
            rowsize[smArray[i].col]++;
        }
        rowstart[0] = 0;
        for (int i = i; i < Cols; i++) {
            rowstart[i] = rowstart[i - 1] + rowsize[i - 1];
        }
        for (int i = 0; i < Terms; i++) {
            int j = rowstart[smArray[i].col];
            b.smArray[j].row = smArray[i].col;
            b.smArray[j].col = smArray[i].row;
            b.smArray[j].value = smArray[i].value;
            rowstart[smArray[i].col]++;
        }
        delete[] rowsize;
        delete[] rowstart;
    }

    return b;
}

istream& operator>>(istream& is, SparseMatrix& m)
// read in a matrix and set up its linked representation.
// An auxiliary array head is used
{
    is >> m.Rows >> m.Cols >> m.Terms;  // matrix dimensions
    m.smArray.resize(m.Terms);
    is.clear();
    is.ignore(100, '\n');
    int CurrentA = 0;
    for (int i = 0; i < m.Terms; i++) {
        is >> m.smArray[i].row >> m.smArray[i].col >> m.smArray[i].value;
        is.clear();
        is.ignore(100, '\n');
    }
    sort(m.smArray.begin(), m.smArray.end(), [](const MatrixTerm& a, const MatrixTerm& b) { return pos_comp(a, b); });
    return is;
}

ostream& operator<<(ostream& os, SparseMatrix& m) {
    if (m.Rows)
        if (m.Rows * m.Cols < 30) {
            int i, j;
            int** A = new int*[m.Rows];
            for (i = 0; i < m.Rows; i++)
                A[i] = new int[m.Cols];

            for (i = 0; i < m.Rows; i++)
                for (j = 0; j < m.Cols; j++)
                    A[i][j] = 0;
            //MatrixTerm* p = m.smArray;
            for (i = 0; i < m.Terms; i++)
                A[ m.smArray[i].row][m.smArray[i].col] =  m.smArray[i].value;
            for (i = 0; i < m.Rows; i++) {
                for (j = 0; j < m.Cols; j++)
                    os << setw(4) << A[i][j];
                os << endl;
            }
            os << endl;
        } else {
            for (int i = 0; i < m.Terms; i++)
                os << "(" << setw(4) << m.smArray[i].row << "," << setw(4) << m.smArray[i].col << "," << setw(4) << m.smArray[i].value << ")" << endl;
            os << endl;
        }
    return os;
}

bool pos_comp(const MatrixTerm& a, const MatrixTerm& b) {
    return (a.row < b.row) || ((a.row == b.row) && (a.col < b.col));
}

SparseMatrix& SparseMatrix::operator*(SparseMatrix& b) {
    SparseMatrix bt = b.Transpose();
    // cout<<bt<<endl;
    SparseMatrix* c = new SparseMatrix(b.Cols, Rows, 0);
    //cout<<c->Rows<<" "<<c->Cols;
    if (Cols != bt.Cols) {
        cout << " Can't Multiply, invalid Matrix dimensions ";
        c->Rows = 0;
        return *c;
    }
    int i = 0;
    for (int r = 0; r < c->Rows; r++) {
        while (smArray[i].row < r && i < Terms) {
            i++;
        }
        int j = 0;
        for (int co = 0; co < c->Cols; co++) {
            while (bt.smArray[j].row < co && j < bt.Terms) {
                j++;
            }
            int temp = 0, ti = i, tj = j;
            while ((ti < Terms || tj < bt.Terms) && smArray[ti].row == r && bt.smArray[tj].row == co) {
                if (smArray[ti].col == bt.smArray[tj].col) {
                    temp += smArray[ti].value * bt.smArray[tj].value;
                    ti++;
                    tj++;
                } else if (smArray[ti].col < bt.smArray[tj].col) {
                    ti++;
                } else if (smArray[ti].col > bt.smArray[tj].col) {
                    tj++;
                }
            }

            if (temp) {
                MatrixTerm tM;
                tM.set(r, co, temp);
                c->smArray.push_back(tM);
                c->Terms++;
            }
        }
    }

    return *c;
}

SparseMatrix& SparseMatrix::operator+(SparseMatrix& b) {
    if (Rows != b.Rows || Cols != b.Cols) {
        cout << " Can't Addition, invalid Matrix dimensions ";
        SparseMatrix* c = new SparseMatrix(0, 0, 0);
        return *c;
    }

    if (Rows == b.Rows && Cols == b.Cols) {
        SparseMatrix* c = new SparseMatrix(this->Rows, this->Cols, 0);
        int i = 0, j = 0;
        while (i < Terms || j < b.Terms) {
            if (pos_comp(smArray[i], b.smArray[j]) && i < Terms) {
                c->smArray.push_back(smArray[i]);
                c->Terms++;

                i++;
            } else if (pos_comp(b.smArray[j], smArray[i]) && j < b.Terms) {
                c->smArray.push_back(b.smArray[j]);
                c->Terms++;
                // cout<<"*"<<b.smArray[j].row<<" "<<b.smArray[i].col<<smArray[i].value<<endl;
                j++;

            } else if (smArray[i].col == b.smArray[j].col && smArray[i].row == b.smArray[j].row && i < Terms && j < b.Terms) {
                MatrixTerm temp;
                temp.set(smArray[i].row, smArray[i].col, smArray[i].value + b.smArray[j].value);
                c->smArray.push_back(temp);
                c->Terms++;
                j++;
                i++;
            } else if (i == Terms) {
                c->smArray.push_back(b.smArray[j]);
                c->Terms++;
                // cout<<"*"<<b.smArray[j].row<<" "<<b.smArray[i].col<<smArray[i].value<<endl;
                j++;
            } else if (j == b.Terms) {
                c->smArray.push_back(smArray[i]);
                c->Terms++;

                i++;
            }
        }
        return *c;
    }
}