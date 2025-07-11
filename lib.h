#include "spec-ation.cpp"
#include <ctime>
#include <stdlib.h>
#include <iostream>

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

void Field::print_pole(){
    int num = 0;
    for (int i = 1; i <= height; ++i){
        for (int j = 1; j <= width; ++j){
            num = count_env(this->pole, i, j);
            print_cell(pole[i][j], num);
        }
        std::cout << std::endl;
    }
}

int count_env(Cell (*pole)[50], int i, int j){
    int num = (pole[i-1][j-1].get_mined() == Cell::MINED::yes) +
        (pole[i-1][j].get_mined() == Cell::MINED::yes) +
        (pole[i-1][j+1].get_mined() == Cell::MINED::yes) +
        (pole[i][j-1].get_mined() == Cell::MINED::yes) +
        (pole[i][j+1].get_mined() == Cell::MINED::yes) +
        (pole[i+1][j-1].get_mined() == Cell::MINED::yes) +
        (pole[i+1][j].get_mined() == Cell::MINED::yes) +
        (pole[i+1][j+1].get_mined() == Cell::MINED::yes);
    
    return num;
}

void print_cell(Cell point, int num){
    Cell::STATUS status = point.get_status();
    Cell::MINED mined = point.get_mined();
    if (status == Cell::STATUS::close){
        std::cout << "? "; 
    }
    else if (status == Cell::STATUS::excharged){
        std::cout << "# ";
    }
    else if (status == Cell::STATUS::open && mined == Cell::MINED::yes){
        std::cout <<  "* ";
    }
    else if (status == Cell::STATUS::open && mined == Cell::MINED::no){
        std::cout << num << ' ';
    }
    else {std::cout << "print_cell failier" << std::endl; exit(1);}
}