#include "Header.h"

#include "Player.h"

class imageButton {
public:
    int x;
    int y;
    int w;
    int h;
    bool condition;
    RectangleShape shape, activeShape;
    bool BackGroundFlag;
    std::string file;
    Image image;
    Texture texture;
    std::string activeFile;
    Image bigImage;
    Texture bigTexture;
    imageButton(int _x, int _y, int _w, int _h, std::string _file, std::string _activeFile) : x(_x), y(_y), w(_w), h(_h) {
        file = _file;
        activeFile = _activeFile;
        condition = false;
        BackGroundFlag = false;

        image.loadFromFile(file);
        texture.loadFromImage(image);
        bigImage.loadFromFile(activeFile);
        bigTexture.loadFromImage(bigImage);
        shape = RectangleShape(Vector2f(w, h));
        activeShape = RectangleShape(Vector2f(w + 10, h + 10));
        shape.setTexture(&texture);
        activeShape.setTexture(&bigTexture);
        shape.setPosition(x, y);
        activeShape.setPosition(x - 3, y - 3);

    }
    void active(sf::RenderWindow& win) {
        if (IntRect(x, y, w, h).contains(Mouse::getPosition(win))) BackGroundFlag = true;
        else BackGroundFlag = false;

        if (BackGroundFlag && Mouse::isButtonPressed(Mouse::Left)) condition = true;
        if (!BackGroundFlag && Mouse::isButtonPressed(Mouse::Left)) condition = false;
    }
};


void exitMenu(bool* flag) {
    sf::RenderWindow exitWin(sf::VideoMode(400, 300), "Exit");

    exitWin.setActive(true);

    imageButton yesButton(0, 0,150,150, "/home/lev/CLionProjects/tron/tronData/photo_2023-11-19_13-47-16.jpg","/home/lev/CLionProjects/tron/tronData/bigRestart.jpg");
    imageButton noButton(170, 0,150,150, "/home/lev/CLionProjects/tron/tronData/photo_2023-11-19_13-47-26.jpg","/home/lev/CLionProjects/tron/tronData/bigPresent.jpg");


    while (exitWin.isOpen() && !yesButton.condition && !noButton.condition)
    {
        sf::Event event;
        while (exitWin.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                exitWin.close();
        }

        yesButton.active(exitWin);
        noButton.active(exitWin);

       


        exitWin.clear();

        
        if (!yesButton.BackGroundFlag) exitWin.draw(yesButton.shape);
        if (yesButton.BackGroundFlag) exitWin.draw(yesButton.activeShape);
        if (!noButton.BackGroundFlag) exitWin.draw(noButton.shape);
        if (noButton.BackGroundFlag) exitWin.draw(noButton.activeShape);

        if (yesButton.condition) *flag = true;
        if (noButton.condition) *flag = false;

        // ����� ���������

        exitWin.display();
    }



}


int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 800), "SFML works!"/*, sf::Style::Fullscreen*/);

    Player p("/home/lev/CLionProjects/tron/tronData/snake_Head_2.jpg",250, 250, 35, 35, Color::Blue, TUp);

    barier firstBar(100, 100, Color::Cyan);

    float CurrentFrame = 0;
    Clock clock;

    int count = 0;
    bool flag = true;

       
    while (window.isOpen() && (p.MyEvent == TGaming))
    {
        std::cout << "Hello \n";
        //p.AddTail(p.x, p.y);
        float time = clock.getElapsedTime().asMicroseconds(); //��������� ������� �����
        clock.restart();
        time = time / 800;// �������� ����
        

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //���������� ������ p --------------------------------
             
        Control(p);

        if (p.MyEvent == TKill ) {
            window.setActive(false);

            sf::Thread exitThread(exitMenu, &flag);
            exitThread.launch();
            exitThread.wait();

            if (flag) {
                p.MyEvent = TGaming, count++;
                p.clean();
                /*p.x = 250, p.y = 250;
                p.len = 0;
                p.dir = TUp;*/
                p = Player("/home/lev/CLionProjects/tron/tronData/snake_Head_2.jpg", 250, 250, 35, 35, Color::Blue, TUp);
                clock.restart();
                
            }
            else p.MyEvent = TKill;            

           

            window.setActive();
        }
        
        
        //---------------------------------------

        p.update(time);
        window.clear();
        
        for (int i = 0; i < p.len; i++) {
            RectangleShape tailShape(Vector2f(p.w, p.h));
            tailShape.setFillColor(p.color);
            tailShape.setPosition(Vector2f(p.tail[i].x, p.tail[i].y));
            window.draw(tailShape);
        }
        //window.draw(firstBar.shape);

        window.draw(p.heroShape);     
        window.display();
       
       
       
    }

    return 0;
}