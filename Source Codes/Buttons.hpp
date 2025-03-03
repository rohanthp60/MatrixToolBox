#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <iostream>
#include "Matrix.hpp"
#include "GUI.hpp"

#ifndef BUTTON_H
#define BUTTON_H

sf::Color dark = sf::Color(200, 200, 200);
class Button: public MasterPage {
    private:
    sf::Texture texture;
    sf::Vector2f Position;
    sf::Vector2f Pressed;
 
    protected:
    sf::Sprite sprite;
    ButtonLable lable;
    sf::Vector2i pixPostion;
    sf::Vector2f CordPosition;
    bool active;

    public:
    Button() {}
    Button(const std::string &a, const sf::Vector2f &postion, ButtonLable l) {
        texture.loadFromFile(a);
        sprite.setTexture(texture);
        Position = postion;
        sprite.setPosition(Position);
        lable = l;
        active = false;
    }
    void operator=(const Button& btn) {                 //To copy button to button
        texture.create(btn.texture.getSize().x, btn.texture.getSize().y);
        texture.update(btn.texture.copyToImage());
        lable = btn.lable;
        sprite.setTexture(texture);
        sprite.setPosition(btn.Position);
    }
    void changeColor(const sf::Color color) {
        sprite.setColor(color);
    }
    void respond(sf::Event &event, sf::RenderWindow &window, bool* rctaken = nullptr, bool* matmade = nullptr) {   //rctaken means row's value taken at "Enter the rows" similarly column
        pixPostion = sf::Mouse::getPosition(window);                                                               //Enter pressed means the row's value recorder, similarly column
        Pressed = CordPosition = window.mapPixelToCoords(pixPostion);
        if(event.type == sf::Event::MouseMoved) {
            if(sprite.getGlobalBounds().contains(CordPosition)) {
                sf::Color rang(100,100,100);
                sprite.setColor(rang);                   //Change button color while hovering
            }
            else {
                sprite.setColor(sf::Color::White);
            }
        }
        else if(event.type == sf::Event::MouseButtonPressed) {
            if(sprite.getGlobalBounds().contains(CordPosition)) {
                sf::Color rang(102, 255, 178);
                sprite.setColor(rang);
            }
            else {
                sprite.setColor(sf::Color::White);
            }
        }
        else if(event.type == sf::Event::MouseButtonReleased) {
            if(sprite.getGlobalBounds().contains(CordPosition) and sprite.getGlobalBounds().contains(Pressed)) {
                sf::Color rang(100,100, 100);
                sprite.setColor(rang);
                switch(lable) {
                    case ButtonLable::MAT_BEGIN:
                    currentPage = pages[1];
                    currentPage->setPage();            //switch page and then reinitialize it
                    break;

                    case ButtonLable::LNEQ_BEGIN:
                    currentPage = pages[3];
                    currentPage->setPage();
                    break;

                    case ButtonLable::ENTER_ARITH:
                    currentPage = pages[5];
                    currentPage->setPage();
                    break;

                    case ButtonLable::DIM_ENTERED:         //pages[0] for Homepage, 1 for row and column enter page, 2 to show entered matrix
                    *rctaken = true;
                    break;
                    
                    case ButtonLable::BACK:                //Back will switch to previous page,
                    if(currentPage != pages[3]) {
                        if(!*rctaken) {
                        currentPage = pages[0];
                        }
                        else {
                            *rctaken = false;
                            *matmade = false;
                        }
                    }
                    else {
                        currentPage = pages[0];
                    } 
                    break;

                    case ButtonLable::BACK_L:
                    currentPage = pages[0];
                    break;

                    case ButtonLable::BACK_MAT2:                       //MAT2 is label for back button for MatPage2(this page displays entered matrix)
                    MasterPage::currentPage = MasterPage::pages[0];
                    break;

                    case ButtonLable::MAT_ENTER:                         //here rctaken stores actually adress of mat made, now to display the entered mat 
                    *rctaken = true;
                    MasterPage::currentPage = MasterPage::pages[2];
                    MasterPage::currentPage->getOutputMat()->setMat(sf::Vector2f(200, 50));
                    MasterPage::currentPage->setPage();       //before displaying, will set up that page
                    break;

                    case ButtonLable::LIN_EQ_ENTER:
                    *rctaken = true;
                    MasterPage::currentPage = MasterPage::pages[4];
                    MasterPage::currentPage->setPage();
                    break;
                }
            }
            else {
                sprite.setColor(sf::Color::White);                 //white doesn't change the image
            }
        }
    }
    virtual void activate(TextEl& result, OutputMatrix& matrix){}
    virtual void deactivate(TextEl& result, OutputMatrix& matrix){}
    void draw(sf::RenderWindow &window) {
        window.draw(sprite);
    }
};

class Det: public Button {
    private:
    bool responsive;

    public:
    Det(const std::string &a, const sf::Vector2f &postion, ButtonLable l = ButtonLable::DEFAULT): Button(a, postion, l) {
        responsive = true;
        sprite.setColor(dark);
    }
    void respond(const sf::Event& event, sf::RenderWindow& window, int& id) {
        if(responsive) {
            pixPostion = sf::Mouse::getPosition(window);                                                               //Enter pressed means the row's value recorder, similarly column
            CordPosition = window.mapPixelToCoords(pixPostion);
            if(event.type == sf::Event::MouseButtonPressed) {
                if(sprite.getGlobalBounds().contains(CordPosition)) {
                    id = 0;
                }
            }
        }
    }

    void setDetResponse() {
        responsive = matr.isSquare();
        if(!responsive) {
            sprite.setColor(sf::Color(255, 255, 0, 80));
        }
    }
    void activate(TextEl& result, OutputMatrix& matrix) {             //set the result in that page to this value
        result.setStr("Determinant = " + matr.Det().ToString());
        sprite.setColor(sf::Color::White);
    }
    void deactivate(TextEl& result, OutputMatrix& matrix) {
        if(responsive) {
            result.setStr("");
            sprite.setColor(dark);
        }
    }
};

class Rnk: public Button {
    public:
    Rnk(const std::string &a, const sf::Vector2f &postion, ButtonLable l = ButtonLable::DEFAULT): Button(a, postion, l) {
        sprite.setColor(dark);
    }
    void respond(const sf::Event& event, sf::RenderWindow& window, int& id) {
        pixPostion = sf::Mouse::getPosition(window);                                                               //Enter pressed means the row's value recorder, similarly column
        CordPosition = window.mapPixelToCoords(pixPostion);
        if(event.type == sf::Event::MouseButtonPressed) {
            if(sprite.getGlobalBounds().contains(CordPosition)) {
                id = 1;
            }
        }
    }
    void activate(TextEl& result, OutputMatrix& matrix) {
        result.setStr("Rank = " + std::to_string(matr.Rank()));
        sprite.setColor(sf::Color::White);
    }
    void deactivate(TextEl& result, OutputMatrix& matrix) {
        result.setStr("");
        sprite.setColor(dark);
    }
};

class Trnspose: public Button {
    private:
    Matrix trp;
    public:
    Trnspose(const std::string &a, const sf::Vector2f &postion, ButtonLable l = ButtonLable::DEFAULT): Button(a, postion, l) {
        sprite.setColor(dark);
    }
    void respond(const sf::Event& event, sf::RenderWindow& window, int& id) {
        pixPostion = sf::Mouse::getPosition(window);                                                               //Enter pressed means the row's value recorder, similarly column
        CordPosition = window.mapPixelToCoords(pixPostion);
        if(event.type == sf::Event::MouseButtonPressed) {
            if(sprite.getGlobalBounds().contains(CordPosition)) {
                id = 3;
            }
        }
    }
    void activate(TextEl& result, OutputMatrix& matrix) {
        trp = matr.Transpose();
        matrix.setMat(sf::Vector2f(200, 600), trp);
        sprite.setColor(sf::Color::White);
    }
    void deactivate(TextEl& result, OutputMatrix& matrix) {
        matrix.emptyMat();
        sprite.setColor(dark);
    }
};

class Invrse: public Button {
    private:
    Matrix inv;
    bool responsive;

    public:
    Invrse(const std::string &a, const sf::Vector2f &postion, ButtonLable l = ButtonLable::DEFAULT): Button(a, postion, l) {
        responsive = false;
    }
    void respond(const sf::Event& event, sf::RenderWindow& window, int& id) {
        if(responsive) {
            pixPostion = sf::Mouse::getPosition(window);                                                               //Enter pressed means the row's value recorder, similarly column
            CordPosition = window.mapPixelToCoords(pixPostion);
            if(event.type == sf::Event::MouseButtonPressed) {
                if(sprite.getGlobalBounds().contains(CordPosition)) {
                    id = 2;
                }
            }
        }
    }
    void setResponse() {
        responsive = !matr.isSingular();
        if(!responsive) {
            sprite.setColor(sf::Color(255, 255, 0, 80));
        }
    }

    void activate(TextEl& result, OutputMatrix& matrix) {
        inv = matr.Invert();
        matrix.setMat(sf::Vector2f(200, 600), inv);
        sprite.setColor(sf::Color::White);
    }
    void deactivate(TextEl& result, OutputMatrix& matrix) {
        
        if(responsive) {
            matrix.emptyMat();
            sprite.setColor(dark);
        }
    }
};

class Adjoint: public Button {
    private:
    Matrix adj;
    bool responsive;

    public:
    Adjoint(const std::string &a, const sf::Vector2f &postion, ButtonLable l = ButtonLable::DEFAULT): Button(a, postion, l) {
        responsive = false;
    }
    void respond(const sf::Event& event, sf::RenderWindow& window, int& id) {
        if(responsive) {
            pixPostion = sf::Mouse::getPosition(window);                                                               //Enter pressed means the row's value recorder, similarly column
            CordPosition = window.mapPixelToCoords(pixPostion);
            if(event.type == sf::Event::MouseButtonPressed) {
                if(sprite.getGlobalBounds().contains(CordPosition)) {
                    id = 4;
                }
            }
        }
    }
    void setResponse() {
        responsive = matr.isSquare();
        if(!responsive) {
            sprite.setColor(sf::Color(255, 255, 0, 80));
        }
    }

    void activate(TextEl& result, OutputMatrix& matrix) {
        adj = matr.Invert();
        adj = adj * matr.Det();
        matrix.setMat(sf::Vector2f(200, 600), adj);
        sprite.setColor(sf::Color::White);
    }
    void deactivate(TextEl& result, OutputMatrix& matrix) {
        
        if(responsive) {
            matrix.emptyMat();
            sprite.setColor(dark);
        }
    }
};

class Expo: public Button {
    private:
    Matrix exp;
    bool responsive;

    public:
    Expo(const std::string &a, const sf::Vector2f &postion, ButtonLable l = ButtonLable::DEFAULT): Button(a, postion, l) {
        responsive = false;
    }
    void respond(const sf::Event& event, sf::RenderWindow& window, int& id) {
        if(responsive) {
            pixPostion = sf::Mouse::getPosition(window);                                                               //Enter pressed means the row's value recorder, similarly column
            CordPosition = window.mapPixelToCoords(pixPostion);
            if(event.type == sf::Event::MouseButtonPressed) {
                if(sprite.getGlobalBounds().contains(CordPosition)) {
                    id = 5;
                }
            }
        }
    }
    void setResponse() {
        responsive = matr.isSquare();
        if(!responsive) {
            sprite.setColor(sf::Color(255, 255, 0, 80));
        }
    }

    void activate(TextEl& result, OutputMatrix& matrix) {
        result.setStr("");
        sprite.setColor(sf::Color::White);
    }
    void deactivate(TextEl& result, OutputMatrix& matrix) {
        
        if(responsive) {
            matrix.emptyMat();
            sprite.setColor(dark);
        }
    }
    void calc(OutputMatrix &matrix, int n) {
        exp = matr.pow(n);
        matrix.setMat(sf::Vector2f(200, 600), exp);
    }
};

class CoFact: public Button {
    private:
    bool responsive;

    public:
    CoFact(const std::string &a, const sf::Vector2f &postion, ButtonLable l = ButtonLable::DEFAULT): Button(a, postion, l) {}

    void respond(const sf::Event& event, sf::RenderWindow& window, int& id) {
        if(responsive) {
            pixPostion = sf::Mouse::getPosition(window);                                                               //Enter pressed means the row's value recorder, similarly column
            CordPosition = window.mapPixelToCoords(pixPostion);
            if(event.type == sf::Event::MouseButtonPressed) {
                if(sprite.getGlobalBounds().contains(CordPosition)) {
                    id = 6;
                }
            }
        }
    }

    void setResponse() {
        responsive = matr.isSquare() and matr.getRow() > 1;
        if(!responsive) {
            sprite.setColor(sf::Color(255, 255, 0, 80));
        }
    }
    void activate(TextEl& result, OutputMatrix& matrix) {
        sprite.setColor(sf::Color::White);
    }
    void deactivate(TextEl& result, OutputMatrix& matrix) {
        if(responsive) {
            result.setStr("");
            sprite.setColor(dark);
            matrix.deactivateAll();
        }
    }

};

class EigenV: public Button {
    private:
    bool responsive;

    public:
    EigenV(const std::string &a, const sf::Vector2f &postion, ButtonLable l = ButtonLable::DEFAULT): Button(a, postion, l) {
        responsive = true;
        sprite.setColor(dark);
    }
    void respond(const sf::Event& event, sf::RenderWindow& window, int& id) {
        if(responsive) {
            pixPostion = sf::Mouse::getPosition(window);                                                               //Enter pressed means the row's value recorder, similarly column
            CordPosition = window.mapPixelToCoords(pixPostion);
            if(event.type == sf::Event::MouseButtonPressed) {
                if(sprite.getGlobalBounds().contains(CordPosition)) {
                    id = 7;
                }
            }
        }
    }

    void setResponse() {
        responsive = matr.isSquare();
        if(!responsive) {
            sprite.setColor(sf::Color(255, 255, 0, 80));
        }
    }

    void activate(TextEl& result, OutputMatrix& matrix) {
        std::vector <Num> eValues = matr.eigen();
        std::string str = "Eigen values : \t";
        for(auto eign: eValues) {
            str = str + eign.ToString() + " , ";
        }
        result.setStr(str);
        result.setSize(30);
        sprite.setColor(sf::Color::White);
    }
    void deactivate(TextEl& result, OutputMatrix& matrix) {
        if(responsive) {
            result.setStr("");
            result.setSize(40);
            sprite.setColor(dark);
        }
    }
};

#endif