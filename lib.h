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

int Field::count_env(int i, int j){ // считает количество мин вокруг
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

void Cell::print_cell(int num){ // распечатывает содержимое ячейки
    if (condition.status == close){
        cout << setw(3) << "? "; 
    }
    else if (condition.status == excharged){
        cout << setw(3) << "# ";
    }
    else if (condition.status == open && condition.mined == yes){
        cout << setw(3) << "* ";
    }
    else if (condition.status == open && condition.mined == no){
        cout << setw(2) << num << ' ';
    }
    else {cout << "print_cell failier" << endl; exit(1);}
}

void Field::set_status(int y, int x, int flag){ // открыват ячейку с инпута и поле 3х3 вокруг кроме мин
    if (flag == 1)
        pole[y][x].set_condition_status(excharged);
    else{
        if (pole[y][x].get_condition_status() == open && count_env(y, x) != 0) return; // игнорирует ввод при попытке повторно открыть клетку
        pole[y][x].set_condition_status(open);
        if (pole[y-1][x-1].get_condition_mined() == no)
            pole[y-1][x-1].set_condition_status(open);
        if (pole[y-1][x].get_condition_mined() == no)
            pole[y-1][x].set_condition_status(open);
        if (pole[y-1][x+1].get_condition_mined() == no)
            pole[y-1][x+1].set_condition_status(open);
        if (pole[y][x-1].get_condition_mined() == no)
            pole[y][x-1].set_condition_status(open);
        if (pole[y][x+1].get_condition_mined() == no)
            pole[y][x+1].set_condition_status(open);
        if (pole[y+1][x-1].get_condition_mined() == no)
            pole[y+1][x-1].set_condition_status(open);
        if (pole[y+1][x].get_condition_mined() == no)
            pole[y+1][x].set_condition_status(open);
        if (pole[y+1][x+1].get_condition_mined() == no)
            pole[y+1][x+1].set_condition_status(open);
    }
}

bool Field::game_running(int game_end = 1){ /* выключатель, при вызове с аргументом
                                         game_end = 0 завершает цикл while() в основной функции main()*/
    if (game_end == 0){
        game_run = game_end;
    } 
    return game_run;
}

bool Field::lose(){ // взрыв. провоцирует вызов game_running() через main()
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
bool Field::win(){ // победа. провоцирует вызов game_running() через main()
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