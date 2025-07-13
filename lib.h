#include "spec-ation.cpp"
#include <ctime>
#include <stdlib.h>
#include <iostream>
#include <iomanip>

using namespace std;

void Field::make_pole(){
    srand(time(NULL));
    int x; 
    for (int i = 1; i <= height; ++i)
        for (int j = 1; j <= width; ++j){
            x = rand() % 101;
            pole[i][j].set_coords(j,i);
            if (x < mine_prtg && i != height && j != width){
                pole[i][j].set_condition_status(STATUS::close);
                pole[i][j].set_condition_mined(MINED::yes);
            }
            else {
                pole[i][j].set_condition_status(STATUS::close);
                pole[i][j].set_condition_mined(Cell::MINED::no);
            }
        }
}

void Field::print_pole(){
    int num;
    cout << "\n\n";
    for (int i = 0; i <= height; ++i){
        for (int j = 0; j <= width; ++j){
            if (i == 0 && j == 0) cout << "    ";
            else if (i == 0 && j == width) cout << setw(3) << j << "\n";
            else if (i == 0) cout << setw(3) << j;
            else if (j == 0) cout << setw(3) << i << "  ";
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
    int num = (pole[i-1][j-1].get_condition_mined()) +
        (pole[i-1][j].get_condition_mined()) +
        (pole[i-1][j+1].get_condition_mined()) +
        (pole[i][j-1].get_condition_mined()) +
        (pole[i][j+1].get_condition_mined()) +
        (pole[i+1][j-1].get_condition_mined()) +
        (pole[i+1][j].get_condition_mined()) +
        (pole[i+1][j+1].get_condition_mined());
    
    return num;
}

void Cell::print_cell(int num){
    if (this->condition.status == Cell::STATUS::close){
        cout << setw(3) << "? "; 
    }
    else if (this->condition.status == Cell::STATUS::excharged){
        cout << setw(3) << "# ";
    }
    else if (this->condition.status == Cell::STATUS::open && this->condition.mined == Cell::MINED::yes){
        cout << setw(3) << "* ";
    }
    else if (this->condition.status == Cell::STATUS::open && this->condition.mined == Cell::MINED::no){
        cout << setw(2) << num << ' ';
    }
    else {std::cout << "print_cell failier" << std::endl; exit(1);}
}

void Field::set_status(int y, int x, int flag){
    if (flag == 1)
        pole[y][x].set_condition_status(excharged);
    else{
        if (pole[y][x].get_condition_status() == open) return;
        pole[y][x].set_condition_status(open);
        if (pole[y-1][x-1].get_condition_mined() == no)
            pole[y-1][x-1].set_condition_status(Cell::STATUS::open);
        if (pole[y-1][x].get_condition_mined() == no)
            pole[y-1][x].set_condition_status(Cell::STATUS::open);
        if (pole[y-1][x+1].get_condition_mined() == no)
            pole[y-1][x+1].set_condition_status(Cell::STATUS::open);
        if (pole[y][x-1].get_condition_mined() == no)
            pole[y][x-1].set_condition_status(Cell::STATUS::open);
        if (pole[y][x+1].get_condition_mined() == no)
            pole[y][x+1].set_condition_status(Cell::STATUS::open);
        if (pole[y+1][x-1].get_condition_mined() == no)
            pole[y+1][x-1].set_condition_status(Cell::STATUS::open);
        if (pole[y+1][x].get_condition_mined() == no)
            pole[y+1][x].set_condition_status(Cell::STATUS::open);
        if (pole[y+1][x+1].get_condition_mined() == no)
            pole[y+1][x+1].set_condition_status(Cell::STATUS::open);
    }
}

bool Field::game_running(int game_end = 1){
    if (game_end == 0){
        game_run = game_end;
    } 
    return game_run;
}

bool Field::loos(){
    bool flag = false;
    for (int i = 1; i <= height; ++i)
        for (int j = 1; j <= width; ++j)
            if (pole[i][j].get_condition_mined() == yes &&
                pole[i][j].get_condition_status() == open){
                flag = true;
                print_pole();
                for (int i = 1; i <= height; ++i)
                    for (int j = 1; j <= width; ++j)
                        pole[i][j].set_condition_status(open);
                std::cout << "\n\n\t**BOOM**\n\tYou  loos\n\n";
                print_pole();
                return flag;
                }
    return flag;
}
bool Field::win(){
    bool flag = true;
    for (int i = 1; i <= height; ++i)
        for (int j = 1; j <= width; ++j)
            if ((pole[i][j].get_condition_mined() == yes &&
                pole[i][j].get_condition_status() != excharged) ||
                (pole[i][j].get_condition_mined() == no &&
                pole[i][j].get_condition_status() != open))
                {flag = false;}
    if (flag){
        std::cout << "\n\n\t**YOU WIN**\n\n";
    }
    return flag;
}

// TODO: нельзя нажимать на открытые клетки