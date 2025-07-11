#include "spec-ation.cpp"
#include <ctime>
#include <stdlib.h>
#include <iostream>
#include <iomanip>

using namespace std;

int count_env(Cell (*pole)[50], int, int);
void print_cell(Cell, int);

void Field::set_size(int w, int h){
    this->width = w;
    this->height = h;
}

void Field::make_pole(int height, int width, float procentage){
    srand(time(NULL));
    int x = rand() % 101;
    for (int i = 1; i <= height+1; ++i)
        for (int j = 1; j <= width+1; ++j){
            pole[i][j].set_coords(j,i);
            if (x < procentage && i != height && j != width){
                pole[i][j].set_status(Cell::STATUS::close, Cell::MINED::yes);
            }
            else {
                pole[i][j].set_status(Cell::STATUS::close, Cell::MINED::no);
            }
        }
}

void Field::print_pole(int num){
    cout << endl;
    for (int i = 0; i <= height; ++i){
        for (int j = 0; j <= width; ++j){
            if (i == 0) cout << setw(3) << j;
            else if (j == 0) cout << setw(3) << i << " ";
            else {
                num = count_env(i, j);
                print_cell(pole[i][j], num);
            }
        }
        cout << endl;
    }
    cout << endl;
}

int Field::count_env(int i, int j){
    int num = (pole[i-1][j-1].get_mined()) +
        (pole[i-1][j].get_mined()) +
        (pole[i-1][j+1].get_mined()) +
        (pole[i][j-1].get_mined()) +
        (pole[i][j+1].get_mined()) +
        (pole[i+1][j-1].get_mined()) +
        (pole[i+1][j].get_mined()) +
        (pole[i+1][j+1].get_mined());
    
    return num;
}

void Cell::print_cell(const Cell obj, int num){
    if (obj.status.status == Cell::STATUS::close){
        cout << setw(3) << "? "; 
    }
    else if (obj.status.status == Cell::STATUS::excharged){
        cout << setw(3) << "# ";
    }
    else if (obj.status.status == Cell::STATUS::open && this->status.mined == Cell::MINED::yes){
        cout << setw(3) << "* ";
    }
    else if (obj.status.status == Cell::STATUS::open && this->status.mined == Cell::MINED::no){
        cout << setw(3) << num;
    }
    else {std::cout << "print_cell failier" << std::endl; exit(1);}
}

Cell::Status Field::cmp(Coords input){
    Coords cell;
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j){
            cell = pole[i][j].get_coords();
            if (cell.x == input.x && cell.y == input.y){
                return pole[i][j].get_status();
            }
        }
    exit(1);// Если в массиве не элемента с такими индексами
}   