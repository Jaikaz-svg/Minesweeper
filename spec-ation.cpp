// если игрок нажимает на поле у которой SATUS=charged
// идет вызов Field::end_game(0)

struct Coords{
    int x;
    int y;
};

class Mine{
    enum = {charged, explored, excharged} STATUS;

    Coords coordinates = {0, 0};
public:
};


class Field{
    bool game_run{1};
    int width{0};
    int height{0};
    float mine_prtg{0.0};
public:
    void set_size(int, int);
    void set_mine_prtg(float f){mine_prtg = f;}
    bool game_running(int game_end = 1){
        if (game_end == 0) game_run = game_end;
        return game_run;
    }
    void mine_pole();


};



