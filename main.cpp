/*Процент размер поля и процент мины запрашивать у 
пользователя, и размещать мины на поля в соответсвии
с этим коэффициентом(x = rand; if (rand < 20) mines[0] = True;)*/

// ? - unknown
// # - excharged
// * - mine



#include "iostream"
#include "lib.h"
#include <limits>
using namespace std;
int main(){
    Coords input; 
    Field pole;

    int flag;
    int height,width;
    float procentage;

    cout<<"Welcom to mines\n ? - unknown\n\
 # - excharged\n 0..8 - mine quantity\n * - mine"<< endl;

    cout << "Height: "; cin >> height; 
    cout << "Width: "; cin >> width;
    pole.set_size(width, height);

    cout << "Percent mines: "; cin >> procentage;
    pole.set_mine_prtg(procentage);

    pole.make_pole(height, width, procentage);
    pole.print_pole(0);
    while (pole.game_running()){
        cout<<"coords(x, y): ";
        if (cin >> input.x >> input.y >> flag){
            if (input.x > pole.get_width() || input.y > pole.get_height() || input.x == 0 || input.y == 0){
                cout << "Index out of range\n";
            }
            else {
                int env = pole.count_env(input.y, input.x);
                if (flag == 1)
                    pole.set_status(input.y, input.x, Cell::STATUS::excharged);
                else
                    pole.set_status(input.y, input.x, Cell::STATUS::open);
                pole.print_pole(env);
                /* TODO: обработка ввода, в начале
                открывается sqrt(height*width) ящеек,
                затем по одной, до тех пор пока не
                откроется мина, тогда вызывается метод
                game_run();
                */
            }
        } 
        else {
            cout << "Invalid input\n";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }



    }
    return 0;
}

