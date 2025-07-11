// если игрок нажимает на поле у которой SATUS=charged
// идет вызов Field::end_game(0)

struct Coords{
    int x;
    int y;
};

class Cell{
public:
    enum STATUS {open, close, excharged};
    enum MINED {yes, no};
    struct status{
        STATUS status;
        MINED mined;
    };
private:
    status status{close, no};
    Coords coords;
    int env{0};
public:
    Cell() = default;
    explicit Cell(STATUS status, MINED mined):status{status, mined}{}
    void set_status(STATUS status, MINED mined){
        this->status.status = status;
        this->status.mined = mined;
    }
    void set_coords(int x, int y){
        coords.x = x;
        coords.y = y;
    }
    Cell::STATUS get_status(){return status.status;}
    Cell::MINED get_mined(){return status.mined;}
};


class Field{
    bool game_run{1};
    int width{0};
    int height{0};
    float mine_prtg{0.0};// no need
    Cell pole[50][50];
public:
    void set_size(int, int);
    void set_mine_prtg(float f){mine_prtg = f;}// no need
    int get_width(){return width;}
    int get_height(){return height;}
    bool game_running(int game_end = 1){
        if (game_end == 0) game_run = game_end;
        return game_run;
    }

    void make_pole(int, int, float);
    void print_pole();
};

