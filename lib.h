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
    int x; 
    for (int i = 1; i <= height; ++i)
        for (int j = 1; j <= width; ++j){
            x = rand() % 101;
            pole[i][j].set_coords(j,i);
            if (x < procentage && i != height && j != width){
                pole[i][j].set_status_status(STATUS::close);
                pole[i][j].set_status_mined(MINED::yes);
            }
            else {
                pole[i][j].set_status_status(STATUS::close);
                pole[i][j].set_status_mined(Cell::MINED::no);
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
                pole[i][j].print_cell(num);
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

void Cell::print_cell(int num){
    if (this->status.status == Cell::STATUS::close){
        cout << setw(3) << "? "; 
    }
    else if (this->status.status == Cell::STATUS::excharged){
        cout << setw(3) << "# ";
    }
    else if (this->status.status == Cell::STATUS::open && this->status.mined == Cell::MINED::yes){
        cout << setw(3) << "* ";
    }
    else if (this->status.status == Cell::STATUS::open && this->status.mined == Cell::MINED::no){
        cout << setw(2) << num << ' ';
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
    exit(1);// Если в массиве нет элемента с такими индексами
}   