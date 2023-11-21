
#define MyWidth 1200
#define MyHeight 800
#define TailLen 19200

enum TDirection { TLeft, TRight, TUp, TDown };

enum TEvent { TKill, TGaming };

enum TColor { TGreen, TREd, TBlue, TWelloy };



class POINT { 
public:
    int x;
    int y;
//public:
//    POINT(int _x = 0, int _y = 0) : x(_x), y(_y) {}
//    int x() { return x; }
//    int y() { return y; }
//    void setX(int _x) {x = _x;}
//    void setY(int _y) { y = _y; }

};


class Player {
public:
    float x, y, w, h, dx, dy = 0;
    float speed = 0.1;
    TEvent MyEvent = TGaming;
    TDirection dir = TLeft;
    TColor EnumColor = TGreen;
    Color color = Color::Green;
    RectangleShape heroShape;
    //POINT tail[TailLen];
    POINT tail[TailLen];
    int len;
    std::string file = "";
    Image image;
    Texture texture;
    std::string name = "";
    Player(std::string _file, float X, float Y, float W, float H, Color _color, TDirection _dir) {
        dir = _dir;
        file = _file;
        len = 0;
        w = W;
        h = H;
        color = _color;

        heroShape = RectangleShape(Vector2f(w, h));
        image.loadFromFile("snake.Head_2.png");
        texture.loadFromImage(image);
        heroShape.setTexture(&texture);

        x = X;
        y = Y;

        heroShape.setPosition(Vector2f(x, y));
    }

    void update(float time) {
        POINT old;
        old.x = x;
        old.y = y;
        switch (dir)
        {
        case TRight:
            dx = speed; dy = 0; break;
        case TLeft:
            dx = -speed; dy = 0; break;
        case TDown:
            dx = 0; dy = speed; break;
        case TUp:
            dx = 0; dy = -speed; break;
        default:
            break;
        }

        x += dx * time;
        y += dy * time;

        //speed = 0;
        heroShape.setPosition(x, y);

        AddTail(old.x, old.y);


    }

    void AddTail(int _x, int _y);
    void AddTailCnt(int _x, int _y, int cnt);
    void MoveTail(int _x, int _y);
    void clean() {
        for (int i = 0; i < len; i++) tail[i].x = 0, tail[i].y = 0;
    }
    
    
};

//void Player::MoveTail(int _x, int _y) {
//    //for (int i = len - 1; i >= 0; i--) tail[i + 1] = tail[i];
//    // заполняем оставшееся нулевое место
//    tail[len].x = _x;
//    tail[0].y = _y;
//}

void Player::AddTail(int _x, int _y) {
    //MoveTail(_x, _y);
    /*len++;
    if (len >= 1000) len = 1000 - 1;*/
    tail[len].x = _x;
    tail[len].y = _y;
    len++;
}

void Player::AddTailCnt(int _x, int _y, int cnt)
{
    for (int i = 0; i < cnt; i++) AddTail(_x, _y);
}
//----------------------------------------------------------------

void Control(Player& p) {

    if (Keyboard::isKeyPressed(Keyboard::Left)) {
        p.dir = TLeft, p.speed = 0.1;
    }
    if (Keyboard::isKeyPressed(Keyboard::Right)) {
        p.dir = TRight, p.speed = 0.1;
    }
    if (Keyboard::isKeyPressed(Keyboard::Up)) {
        p.dir = TUp, p.speed = 0.1;
    }  // у класса sprite  есть метод setRotation с помощью которого можно отразить изображение, поэтому можно не ипользовать полосу движения влево на картинке
    if (Keyboard::isKeyPressed(Keyboard::Down)) {
        p.dir = TDown, p.speed = 0.1;
    }

    for (int i = 0; i < p.len; i++) {

        switch (p.dir)
        {
        case TRight:
            for (int i = 0; i < p.len; i++) {
                //if (((p.x <= p.tail[i].x) && (p.tail[i].x <= p.x + p.w)) && ((p.y - p.h <= p.tail[i].y) && (p.tail[i].y <= p.y + p.h)) && ((p.x != p.tail[i].x) || (p.y != p.tail[i].y))) p.MyEvent = TKill;
                if (IntRect(p.x + 1 , p.y, p.w , p.h).contains(Vector2i(p.tail[i].x,p.tail[i].y ) )) p.MyEvent = TKill;
            }
            break;
        case TLeft:
            for (int i = 0; i < p.len; i++) {
                //if (((p.x - p.w <= p.tail[i].x) && (p.tail[i].x + 1 < p.x)) && ((p.y - p.h <= p.tail[i].y) && (p.tail[i].y <= p.y + p.h)) && ((p.x != p.tail[i].x) || (p.y != p.tail[i].y))) p.MyEvent = TKill;
                if (IntRect(p.x - 1, p.y, -p.w , p.h).contains(Vector2i(p.tail[i].x, p.tail[i].y))) p.MyEvent = TKill;
            }
            break;
        case TUp:
            for (int i = 0; i < p.len; i++) {
                //if ((p.x - p.w <= p.tail[i].x) && (p.tail[i].x <= p.x + p.w) && (p.y - p.h <= p.tail[i].y) && (p.tail[i].y + 1 < p.y) && ((p.x != p.tail[i].x) || (p.y != p.tail[i].y))) p.MyEvent = TKill;
                if (IntRect(p.x, p.y - 1, p.w, -p.h).contains(Vector2i(p.tail[i].x, p.tail[i].y))) p.MyEvent = TKill;
            }
            break;
        case TDown:
            for (int i = 0; i < p.len; i++) {
                //if ((p.x - p.w < p.tail[i].x) && (p.tail[i].x < p.x + p.w) && (p.y < p.tail[i].y) && (p.tail[i].y < p.y + p.h)) p.MyEvent = TKill;
                if (IntRect(p.x, p.y+1, p.w, p.h).contains(Vector2i(p.tail[i].x, p.tail[i].y))) p.MyEvent = TKill;
            }
            break;
        default:
            break;
        }

    }

    if (!( (p.x <= MyWidth - p.w) && (p.y <= MyHeight - p.h) && (0 <= p.x) && (0 <= p.y))) p.MyEvent = TKill;
}

//------------------------------------------------------------------

class barier {
public:
    int x;
    int y;
    int w;
    int h;
    Image image;
    Texture texture;
    RectangleShape shape;
    std::string file;
    Color color;
    barier(int _w, int _h, Color _color) :  w(_w), h(_h) {

        color = _color;
        shape = RectangleShape(Vector2f(w, h));
        shape.setFillColor(color);

        srand(time(NULL));
        x = rand() % (MyWidth - w);
        y = rand() % (MyHeight - h);

        shape.setPosition(x, y);

    }
};