#include <SFML/Graphics.hpp>
#include <string>
#include <thread>
#include <vector>

using namespace sf;



class Form {
public:
    int x;
    int y;
    Color color;
    std::string shapka;
    std::string massenge;
    std::string file;
    Text text;
    Font font;
    RectangleShape background;
    bool backgroundFlag;
    int fontSize;
    int backgroundXCoord;
    int backgroundWidth;
    Form(int _x, int _y, std::string _file, Color _color,int _fontSize, int _backgroundXCoord, int _backgroundWidth) : x(_x), y(_y) {
        backgroundXCoord = _backgroundXCoord;
        backgroundWidth = _backgroundWidth;
        fontSize = _fontSize;
        color = _color;
        file = _file;
        massenge = "";
        shapka = "Entered text: ";
        font.loadFromFile(file);
        text = Text(shapka,font, fontSize);
        text.setFillColor(color);        
        text.setPosition(x, y);
        background = RectangleShape(Vector2f(backgroundWidth, fontSize + 5));
        background.setFillColor(Color::White);
        background.setPosition(x + backgroundXCoord, y );
    }
    void active(sf::RenderWindow& win) {
        if (IntRect(x, y, 200, fontSize).contains(Mouse::getPosition(win)) && Mouse::isButtonPressed(Mouse::Left)) backgroundFlag = true;
        if (!IntRect(x, y, 200, fontSize).contains(Mouse::getPosition(win)) && Mouse::isButtonPressed(Mouse::Left)) backgroundFlag = false;

        
    }
};


class Button {
public:
    int x;
    int y;
    int fontSize;
    int backgroundSize;
    sf::Color color;
    sf::Text text;
    bool condition;
    std::string file;
    std::string messange;
    sf::Font font;
    RectangleShape shape;
    Button(int _x, int _y, std::string _file, int _fontSize, std::string _messange, sf::Color _color, int _backgroundSize) : x(_x), y(_y) {
        backgroundSize = _backgroundSize;
        condition = false;
        color = _color;
        fontSize = _fontSize;
        messange = _messange;
        file = _file;
        font.loadFromFile(file);
        text = sf::Text(messange, font, fontSize);
        text.setFillColor(color);
        text.setPosition(x, y);
    }
    void active(sf::RenderWindow &win) {
        if (IntRect(x, y, 130, fontSize).contains(Mouse::getPosition(win))) text.setFillColor(Color::White);
        else text.setFillColor(color);

        if ( (IntRect(x, y, 130, fontSize).contains(Mouse::getPosition(win))) && Mouse::isButtonPressed(Mouse::Left)) condition=true;
    }
};

class colorButton {
public:
    int x;
    int y;
    int w;
    int h;
    sf::Color color;
    bool condition;
    RectangleShape shape, background;
    bool BackGroundFlag;
    bool familyFlag;
    colorButton(int _x, int _y, int _w, int _h, Color _color) : x(_x), y(_y), w(_w), h(_h) {
        familyFlag = false;
        color = _color;
        condition = false;
        BackGroundFlag = false;
        shape = RectangleShape(Vector2f(w, h));
        background = RectangleShape(Vector2f(w + 10, h + 10));
        shape.setFillColor(color);
        background.setFillColor(Color::White);
        shape.setPosition(x, y);
        background.setPosition(x - 5, y - 5);

    }

    void active(sf::RenderWindow& win) {
        if (IntRect(x, y, w, h).contains(Mouse::getPosition(win))) BackGroundFlag = true;
        else BackGroundFlag = false;

        if (BackGroundFlag && Mouse::isButtonPressed(Mouse::Left)) condition = true;
        if (!BackGroundFlag && Mouse::isButtonPressed(Mouse::Left) && !familyFlag) condition = false;
    }

    void familyActive(RenderWindow& win, std::vector<colorButton> vec) {
        for (int i = 0; i < vec.size(); i++) {
            if (vec[i].BackGroundFlag) {
                this->familyFlag = true;
                break;
            }
            else familyFlag = false;

        }
    }
};

class markButton {
public:
    int x;
    int y;
    int w;
    int h;
    sf::Color color;
    bool condition;
    RectangleShape shape;
    CircleShape mark;
    bool BackGroundFlag;
    bool familyFlag;
    markButton(int _x, int _y, int _w, int _h, Color _color) : x(_x), y(_y), w(_w), h(_h) {
        familyFlag = false;
        color = _color;
        condition = false;
        BackGroundFlag = false;
        shape = RectangleShape(Vector2f(w, h));
        mark = CircleShape(w/2 - 5);
        shape.setFillColor(color);
        mark.setFillColor(Color::Magenta);
        shape.setPosition(x, y);
        mark.setPosition(x + 5 , y + 5);
        
    }
    void active(sf::RenderWindow& win) {
        if (IntRect(x, y, w, h).contains(Mouse::getPosition(win))) BackGroundFlag = true;
        else BackGroundFlag = false;

        if (BackGroundFlag && Mouse::isButtonPressed(Mouse::Left)) condition = true;
        if (!BackGroundFlag && Mouse::isButtonPressed(Mouse::Left) && !familyFlag) condition = false;
    }

    void familyActive(RenderWindow& win, std::vector<markButton> vec) {
            for (int i = 0; i < vec.size(); i++) {
                if (vec[i].BackGroundFlag) {
                    this->familyFlag = true;
                    break;
                }
                else familyFlag = false;
            
        }
    }

};

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

//class exitClass {
//public:
//    RenderWindow* win;
//    bool flag;
//    exitClass(RenderWindow* _win) {
//        win = _win;
//        flag = false;
//
//    }
//};

void exitMenu(bool* flag) {
    sf::RenderWindow exitWin(sf::VideoMode(300, 200), "Exit");

    exitWin.setActive(true);

    Font font;
    font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-B.ttf");
    Text text("Exit?", font, 25);
    text.setPosition(50, 0);
    text.setFillColor(Color::Blue);

    Button yesButton(20, 50, "/usr/share/fonts/truetype/ubuntu/Ubuntu-B.ttf", 35, "Yes", sf::Color::Blue, 20);
    Button noButton(160, 50, "/usr/share/fonts/truetype/ubuntu/Ubuntu-B.ttf", 35, "No", sf::Color::Blue, 20);


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

        if (yesButton.condition) *flag = true;
        if (noButton.condition) *flag = false;


        exitWin.clear();

        exitWin.draw(yesButton.text);
        exitWin.draw(noButton.text);
        exitWin.draw(text);
        
        // ����� ���������

        exitWin.display();
    }



}

void settingFun(RenderWindow& win) {
    sf::RenderWindow settingWin(sf::VideoMode(300, 200), "Settings");

    settingWin.setActive(true);

    RectangleShape keyULRD(Vector2f(60,47));
    Image image;
    Texture texture;
    image.loadFromFile("/home/lev/CLionProjects/tron/menu/ULRD(2).jpg");
    texture.loadFromImage(image);
    keyULRD.setTexture(&texture);
    keyULRD.setPosition(193, 110);
    

    Font font;
    font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-B.ttf");
    Text text("Choose the size of the window", font, 15), smallText("480:620", font, 12), middleText("800:680", font, 12), bigText("full", font, 12), keyboardText("Choose a layot:", font, 15), keyTypeWASD("WASD", font, 12);
    text.setPosition(0, 0);
    smallText.setPosition(0, 25);
    middleText.setPosition(100, 25);
    bigText.setPosition(195, 25);
    keyboardText.setPosition(0, 55);
    keyTypeWASD.setPosition(108, 115);
    text.setFillColor(Color::Blue);
    smallText.setFillColor(Color::Blue);
    middleText.setFillColor(Color::Blue);
    bigText.setFillColor(Color::Blue);
    keyboardText.setFillColor(Color::Blue);
    keyTypeWASD.setFillColor(Color::Blue);

    markButton smallButton(65, 20, 30, 30, Color::White);
    markButton middleButton(160, 20, 30, 30, Color::White);
    markButton bigButton(255, 20, 30, 30, Color::White);

    markButton test1Button(112, 80, 30, 30, Color::White);
    markButton test2Button(207, 80, 30, 30, Color::White);
    
   
    

 

    while (settingWin.isOpen())
    {
        std::vector<markButton> firstVec = { smallButton ,middleButton,bigButton }, secondVec = { test1Button,test2Button };

        sf::Event event;
        while (settingWin.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                settingWin.close();
        }

        test1Button.familyActive(settingWin, firstVec);
        test2Button.familyActive(settingWin, firstVec);
        smallButton.familyActive(settingWin, secondVec);
        middleButton.familyActive(settingWin, secondVec);
        bigButton.familyActive(settingWin, secondVec);

        smallButton.active(settingWin);
        middleButton.active(settingWin);
        bigButton.active(settingWin);
        test1Button.active(settingWin);
        test2Button.active(settingWin);
       
       

        settingWin.clear();
                
        settingWin.draw(smallButton.shape);
        if (smallButton.BackGroundFlag || smallButton.condition) settingWin.draw(smallButton.mark);
        settingWin.draw(middleButton.shape);
        if (middleButton.BackGroundFlag || middleButton.condition) settingWin.draw(middleButton.mark);
        settingWin.draw(bigButton.shape);
        if (bigButton.BackGroundFlag || bigButton.condition) settingWin.draw(bigButton.mark);

        settingWin.draw(test1Button.shape);
        if (test1Button.BackGroundFlag || test1Button.condition) settingWin.draw(test1Button.mark);
        settingWin.draw(test2Button.shape);
        if (test2Button.BackGroundFlag || test2Button.condition) settingWin.draw(test2Button.mark);
        

        settingWin.draw(text);
        settingWin.draw(smallText);
        settingWin.draw(middleText);
        settingWin.draw(bigText);
        settingWin.draw(keyboardText);
        settingWin.draw(keyTypeWASD);
        settingWin.draw(keyULRD);

        settingWin.display();
    }
    
}

int Menu(RenderWindow& win) {
    win.setActive();

    Button button1(280, 150, "/usr/share/fonts/truetype/ubuntu/Ubuntu-B.ttf", 25, "player 1", sf::Color::Blue, 100);
    Button button2(280, 200, "/usr/share/fonts/truetype/ubuntu/Ubuntu-B.ttf", 25, "player 1", sf::Color::Blue, 100);
    Button exitButton(280, 250, "/usr/share/fonts/truetype/ubuntu/Ubuntu-B.ttf", 25, "exit", sf::Color::Blue, 100);

    imageButton  imageBat(550, 10, 100, 100, "/home/lev/CLionProjects/tron/menu/setImage.jpg", "/home/lev/CLionProjects/tron/menu/bigImage.jpg");

    bool flag = false;

    int count = 0;

    while (win.isOpen() && !(button1.condition || button2.condition ))
    {
        sf::Event event;
        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || exitButton.condition || Keyboard::isKeyPressed(Keyboard::Escape))
                win.close();            
        }


        button1.active(win);
        button2.active(win);
        exitButton.active(win);
        imageBat.active(win);

        win.clear();
        win.draw(button1.text);
        win.draw(button2.text);
        win.draw(exitButton.text);
        if (!imageBat.BackGroundFlag) win.draw(imageBat.shape);
        if (imageBat.BackGroundFlag) win.draw(imageBat.activeShape);
        win.display();

        if (imageBat.condition) {
            win.setActive(false);// ������ ���� ��������� ��� �������� ������

            sf::Thread newPollThread(settingFun, std::ref(win));
            newPollThread.launch();
            newPollThread.wait();
            imageBat.condition = false;
            win.setActive();
        }

        if (exitButton.condition && (count < 1)) {
            win.setActive(false);

            sf::Thread exitThread(exitMenu, &flag);
            exitThread.launch();
            exitThread.wait();

             if (flag) exitButton.condition = true, count++;
             else exitButton.condition = false;

            win.setActive();

            
        }
    }

    if (button1.condition) return 2;
    if (button2.condition) return 3;
    return 0;

}

int onePlayerMenu(RenderWindow& win) {
    win.setActive();

    RectangleShape shape(Vector2f(0, 0));
    shape.setFillColor(Color::Green);

    bool flag = false;

    int count = 0;

    
    Button backButton(0, 0, "/usr/share/fonts/truetype/ubuntu/Ubuntu-B.ttf", 25, "Main menu", sf::Color::Blue, 200);
    Button exitButton(0, 50, "/usr/share/fonts/truetype/ubuntu/Ubuntu-B.ttf", 25, "exit", sf::Color::Blue, 100);
    Button beginButton(0, 300, "/usr/share/fonts/truetype/ubuntu/Ubuntu-B.ttf", 25, "begin game", sf::Color::Blue, 170);
    colorButton colorBlueButton(90,200,50,50, Color::Blue);
    colorButton colorRedButton(190, 200, 50, 50, Color::Red);
    colorButton colorGreenButton(290, 200, 50, 50, Color::Green);

    Form form(0, 100, "/usr/share/fonts/truetype/ubuntu/Ubuntu-B.ttf", Color::Blue, 25, 207, 200);// 205

   
    while (win.isOpen() && !backButton.condition)
    {
        sf::Event event;
        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape) || exitButton.condition)
                win.close();
            if (event.type == sf::Event::TextEntered && form.backgroundFlag && event.text.unicode == 8) {
                
                if (!form.massenge.empty()) form.massenge.pop_back();
                    //form.massenge[form.massenge.size() - 1] = ' ';
                
                form.text.setString(form.shapka + form.massenge);
            }
            if (event.type == sf::Event::TextEntered && form.backgroundFlag && event.text.unicode != 8) {
                form.massenge.push_back(event.text.unicode);
                form.text.setString(form.shapka + form.massenge);
            }
            
            
        }

        

        backButton.active(win);
        exitButton.active(win);
        beginButton.active(win);
        colorBlueButton.active(win);
        colorRedButton.active(win);
        colorGreenButton.active(win);
        form.active(win);


        win.clear();
        win.draw(backButton.text);
        win.draw(exitButton.text);
        win.draw(beginButton.text);
        if (colorBlueButton.BackGroundFlag || colorBlueButton.condition) win.draw(colorBlueButton.background);
        if (colorRedButton.BackGroundFlag || colorRedButton.condition) win.draw(colorRedButton.background);
        if (colorGreenButton.BackGroundFlag || colorGreenButton.condition) win.draw(colorGreenButton.background);
        if (form.backgroundFlag) win.draw(form.background);
        win.draw(colorBlueButton.shape);    
        win.draw(colorRedButton.shape);
        win.draw(colorGreenButton.shape);
        win.draw(form.text);
        win.display();

        if (exitButton.condition && (count < 1)) {
            win.setActive(false);

            sf::Thread exitThread(exitMenu, &flag);
            exitThread.launch();
            exitThread.wait();

            if (flag) exitButton.condition = true, count++;
            else exitButton.condition = false;

            win.setActive();

            
        }

    }

    if (backButton.condition) return 1;
    return 0;
}

int twoPlayersMenu(RenderWindow& win) {
    win.setActive();

    Font font;
    font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-B.ttf");
    Text pl1Text("player 1", font, 20), pl2Text("player 2", font, 20);
    pl1Text.setPosition(50, 0), pl2Text.setPosition(win.getPosition().x+100 + 300, 0);
    pl1Text.setFillColor(Color::Blue), pl2Text.setFillColor(Color::Blue);

    Button backButton(win.getPosition().x-100, win.getPosition().y*2 , "/usr/share/fonts/truetype/ubuntu/Ubuntu-B.ttf", 25, "Main menu", sf::Color::Blue, 170);
    Button exitButton(win.getPosition().x-100, win.getPosition().y * 2 +30, "/usr/share/fonts/truetype/ubuntu/Ubuntu-B.ttf", 25, "Exit", sf::Color::Blue, 70);

    colorButton color_PL1_BlueButton(0, 200, 50, 50, Color::Blue);
    colorButton color_PL1_RedButton(70, 200, 50, 50, Color::Red);
    colorButton color_PL1_GreenButton(140, 200, 50, 50, Color::Green);

    colorButton color_PL2_BlueButton(win.getPosition().x + 300, 200, 50, 50, Color::Blue);
    colorButton color_PL2_RedButton(win.getPosition().x + 70 + 300 ,200, 50, 50, Color::Red);
    colorButton color_PL2_GreenButton(win.getPosition().x + 140 + 300, 200, 50, 50, Color::Green);

    Form firstForm(0, 50, "/usr/share/fonts/truetype/ubuntu/Ubuntu-B.ttf", Color::Blue, 20, 170, 150);
    Form secondForm(win.getPosition().x + 300, 50, "/usr/share/fonts/truetype/ubuntu/Ubuntu-B.ttf", Color::Blue, 20, 170, 150);

    bool flag = false;
    int count = 0;


    while (win.isOpen() && !backButton.condition)
    {
        std::vector<colorButton> firstVec = { color_PL2_BlueButton  , color_PL2_RedButton, color_PL2_GreenButton },
            secondVec = { color_PL1_BlueButton  , color_PL1_RedButton, color_PL1_GreenButton };

        sf::Event event;
        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape) || exitButton.condition)
                win.close();
            if (event.type == sf::Event::TextEntered  && event.text.unicode == 8) {

                if (!firstForm.massenge.empty() && firstForm.backgroundFlag ) firstForm.massenge.pop_back();
                //form.massenge[form.massenge.size() - 1] = ' ';
                if (!secondForm.massenge.empty() && secondForm.backgroundFlag) secondForm.massenge.pop_back();

                firstForm.text.setString(firstForm.shapka + firstForm.massenge);
                secondForm.text.setString(secondForm.shapka + secondForm.massenge);

            }
            if (event.type == sf::Event::TextEntered  && event.text.unicode != 8) {
                if (firstForm.backgroundFlag) {
                    firstForm.massenge.push_back(event.text.unicode);
                    firstForm.text.setString(firstForm.shapka + firstForm.massenge);
                }
                if (secondForm.backgroundFlag) {
                    secondForm.massenge.push_back(event.text.unicode);
                    secondForm.text.setString(secondForm.shapka + secondForm.massenge);
                }
            }
        }

        backButton.active(win);
        exitButton.active(win);
        firstForm.active(win);
        secondForm.active(win);

        color_PL1_BlueButton.familyActive(win, firstVec);
        color_PL1_RedButton.familyActive(win, firstVec);
        color_PL1_GreenButton.familyActive(win, firstVec);

        color_PL2_BlueButton.familyActive(win, secondVec);
        color_PL2_RedButton.familyActive(win, secondVec);
        color_PL2_GreenButton.familyActive(win, secondVec);

        color_PL1_BlueButton.active(win);
        color_PL1_RedButton.active(win);
        color_PL1_GreenButton.active(win);
        color_PL2_BlueButton.active(win);
        color_PL2_RedButton.active(win);
        color_PL2_GreenButton.active(win);

        win.clear();


        win.draw(backButton.text);
        win.draw(exitButton.text);
        win.draw(pl1Text);
        win.draw(pl2Text);

        if (color_PL1_BlueButton.BackGroundFlag || color_PL1_BlueButton.condition) win.draw(color_PL1_BlueButton.background);
        if (color_PL1_RedButton.BackGroundFlag || color_PL1_RedButton.condition) win.draw(color_PL1_RedButton.background);
        if (color_PL1_GreenButton.BackGroundFlag || color_PL1_GreenButton.condition) win.draw(color_PL1_GreenButton.background);
        if (color_PL2_BlueButton.BackGroundFlag || color_PL2_BlueButton.condition) win.draw(color_PL2_BlueButton.background);
        if (color_PL2_RedButton.BackGroundFlag || color_PL2_RedButton.condition) win.draw(color_PL2_RedButton.background);
        if (color_PL2_GreenButton.BackGroundFlag || color_PL2_GreenButton.condition) win.draw(color_PL2_GreenButton.background);

        if (firstForm.backgroundFlag) win.draw(firstForm.background);
        if (secondForm.backgroundFlag) win.draw(secondForm.background);

        win.draw(color_PL1_BlueButton.shape);
        win.draw(color_PL1_RedButton.shape);
        win.draw(color_PL1_GreenButton.shape);
        win.draw(color_PL2_BlueButton.shape);
        win.draw(color_PL2_RedButton.shape);
        win.draw(color_PL2_GreenButton.shape);

        win.draw(firstForm.text);
        win.draw(secondForm.text);

        win.display();

        if (exitButton.condition && (count < 1)) {
            win.setActive(false);

            sf::Thread exitThread(exitMenu, &flag);
            exitThread.launch();
            exitThread.wait();

            if (flag) exitButton.condition = true, count++;
            else exitButton.condition = false;

            win.setActive();

            
        }
    }

    if (backButton.condition) return 1;
    return 0;
}

int main()
{

    
    sf::RenderWindow window(sf::VideoMode(680, 420), "SFML works!");
   
    int MenuNum = 1;
    while (MenuNum != 0 && window.isOpen()) {
        switch (MenuNum)
        {
        case 1:
            MenuNum = Menu(window);
            break;
        case 2:
            MenuNum = onePlayerMenu(window);
            break;
        case 3:
            MenuNum = twoPlayersMenu(window);
            break;
        default:
            break;
        }
    }

    return 0;
}