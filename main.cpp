// ? - unknown
// # - excharged
// * - mine

#include "lib.h"
#include <limits>

int main(){
    Field pole;
    Coords input; 

    int height, width, flag;
    float procentage;

    std::cout <<
        "****************************************\n"
        "*                                      *\n"
        "*       Welcome to Minesweeper!        *\n"
        "*                                      *\n"
        "*  LEGEND:                             *\n"
        "*  ? - Unknown cell                    *\n"
        "*  # - Flagged (possible mine)         *\n"
        "*  1-8 - Number of nearby mines        *\n"
        "*  * - Mine (you lose if you reveal it)*\n"
        "*                                      *\n"
        "****************************************\n\n";
    cout << "Select you difficuty\n";
    cout << "Height: "; cin >> height; 
    cout << "Width: "; cin >> width;
    cout << "Percent mines: "; cin >> procentage;

    pole.set_difficulty(height, width, procentage);
    pole.make_pole();
    pole.print_pole();

    while (pole.game_running()){
        cout<<"coords(x, y): ";
        if (cin >> input.x >> input.y >> flag){
            if (input.x > pole.get_width() || input.y > pole.get_height() || input.x <= 0 || input.y <= 0){
                cout << "Index out of range\n";
            }
            else {
                pole.set_status(input.y, input.x, flag);
                if (pole.lose())
                    pole.game_running(0);
                else if (pole.win())
                    pole.game_running(0);
                else pole.print_pole();
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