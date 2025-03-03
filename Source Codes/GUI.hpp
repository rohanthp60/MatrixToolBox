#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Matrix.hpp"
#ifndef GUI_ONE_H
#define GUI_ONE_H
enum class ButtonLable {            
    MAT_BEGIN,           //Solve button of Homepage, for matrix
    LNEQ_BEGIN,
    DIM_ENTERED,             //Dimensions entered, to confirm the entry of row and column
    BACK,                    //Back button for row and col page
    BACK_MAT2,
    MAT_ENTER,               //To confirm the matrix after entering elements
    DET_CALC,
    DEFAULT,
    LIN_EQ_ENTER,
    ENTER_ARITH,
    BACK_L 
}; 

enum class TextBoxLabel {
    DEFAULT,
    ROW_GETTER,
    COLUMN_GETTER,
    MATRIX,
    POW,
    UNKNOW_TAKER
};

class HomePage;
class MatInPg1;
class LinearPage;
class OutputMatrix;
class ArithmaticPage;

class MasterPage {  
    public:
    static std::shared_ptr<MasterPage> currentPage;
    static std::vector <std::shared_ptr<MasterPage>> pages;
    static Matrix matr;
    virtual void setPage(){}
    virtual void respond(sf::Event& event, sf::RenderWindow& window) {}
    virtual void draw(sf::RenderWindow& window) {}
    virtual OutputMatrix* getOutputMat() {return nullptr;}

    template <typename T>
    static void add(const std::shared_ptr<T>& page) {
        pages.push_back(page);
    }
};
std::shared_ptr<MasterPage> MasterPage::currentPage = nullptr;        //name suggests,
std::vector<std::shared_ptr<MasterPage>> MasterPage::pages;   //array of pointers to the pages exisiting
Matrix MasterPage::matr;             //the matrix is stored in this object

class BackGround {
    private:
    sf::Texture texture;
    sf::Sprite sprite;

    public:
    BackGround() {}
    BackGround(const std::string& bgr) {
        texture.loadFromFile(bgr);
        sprite.setTexture(texture);
    }
   void setTexture(const std::string& imagePath) {
        if (texture.loadFromFile(imagePath)) {
            sprite.setTexture(texture);
        } 
    }
    void operator=(const BackGround& b) {
        texture.create(b.texture.getSize().x, b.texture.getSize().y);
        texture.update(b.texture.copyToImage());
        sprite.setTexture(texture);
    }
    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }

};


class TextEl{
    private:
    sf::Text text;
    sf::Font font;
    public:
    TextEl() {
    }
    TextEl(const std::string& f, const int& size, const std::string& content, const sf::Vector2f &position,const sf::Color& fillCol) {
        font.loadFromFile(f);
        text.setFont(font);
        text.setCharacterSize(size);
        text.setString(content);
        text.setPosition(position);
        text.setFillColor(fillCol);
    }
    void operator=(const TextEl& txt) {
        text.setFont(txt.font);
        text.setString(txt.text.getString());
        text.setCharacterSize(txt.text.getCharacterSize());
        text.setFillColor(txt.text.getFillColor());
        text.setPosition(txt.text.getPosition());
    }

    void setStr(const std::string& content) {
        text.setString(content);
    }

    void setSize(int s) {
        text.setCharacterSize(s);
    }
    void setColor(const sf::Color& color) {
        text.setFillColor(color);
    }
    void draw(sf::RenderWindow &window) {
        window.draw(text);
    }
};

class Box {
protected:
    sf::RectangleShape shape;
    sf::Vector2f position;
    sf::Vector2f size;
    sf::Color fillColor;
    float borderWidth;
    sf::Color borderColor;

public:
    Box(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& fillColor,
               float borderWidth = 0.f, const sf::Color& borderColor = sf::Color::Black) {
        this->position = position;
        this->size = size;
        this->fillColor = fillColor;
        this->borderWidth = borderWidth;
        this->borderColor = borderColor;

        shape.setPosition(position);
        shape.setSize(size);
        shape.setFillColor(fillColor);
        shape.setOutlineThickness(borderWidth);
        shape.setOutlineColor(borderColor);
    }
    Box(const sf::Vector2f& position, const sf::Vector2f& size) {
        this->position = position;
        this->size = size;
        this->fillColor = sf::Color::White;
        this->borderWidth = 3;
        this->borderColor = sf::Color::Black;

        shape.setPosition(position);
        shape.setSize(size);
        shape.setFillColor(fillColor);
        shape.setOutlineThickness(borderWidth);
        shape.setOutlineColor(borderColor);
    }
    void operator=(const Box& box) {
        this->position = box.position;
        this->size = box.size;
        this->fillColor = box.fillColor;
        this->borderWidth = box.borderWidth;
        this->borderColor = box.borderColor;

        shape.setPosition(position);
        shape.setSize(size);
        shape.setFillColor(fillColor);
        shape.setOutlineThickness(borderWidth);
        shape.setOutlineColor(borderColor);
    }

    void setPosition(const sf::Vector2f& position) {
        this->position = position;
        shape.setPosition(position);
    }

    void setSize(const sf::Vector2f& size) {
        this->size = size;
        shape.setSize(size);
    }

    void setFillColor(const sf::Color& fillColor) {
        this->fillColor = fillColor;
        shape.setFillColor(fillColor);
    }

    void setBorderWidth(float borderWidth) {
        this->borderWidth = borderWidth;
        shape.setOutlineThickness(borderWidth);
    }

    void setBorderColor(const sf::Color& borderColor) {
        this->borderColor = borderColor;
        shape.setOutlineColor(borderColor);
    }

    sf::RectangleShape getShape() {
        return shape;
    }

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
    }
};
class TextBox {
    private:
    sf::Text text;
    sf::Font font;
    std::string txtString;
    Box box;
    bool editing;
    TextBoxLabel label;
    sf::Vector2i index;
    sf::Vector2f place;
    sf::Vector2f size;
    bool isEmpty;
    bool clicked;
    int data;

    public:
    static sf::Vector2i textboxclicked;
    TextBox(): box(sf::Vector2f(0, 0), sf::Vector2f(0, 0), sf::Color::White) {
        editing = false;
    }
    TextBox(const sf::Vector2f& position, const sf::Vector2f& size, const int& chSize, TextBoxLabel label = TextBoxLabel::DEFAULT, sf::Vector2i index = sf::Vector2i(-1, -1))
        : box(position, size, sf::Color::White, 3, sf::Color::Black) {
            font.loadFromFile("COMIC.ttf");
            text.setFont(font);
            text.setCharacterSize(chSize);
            text.setFillColor(sf::Color::Black);
            text.setPosition(sf::Vector2f(box.getShape().getPosition().x + 2, box.getShape().getPosition().y + 3));
            txtString = "";
            text.setString(txtString);
            editing = false;
            this->label = label;
            this->index = index;
            place = position;
            this->size = size;
            isEmpty = true;
            clicked = false;
    }
    std::string String() {
        return txtString;
    }

    void setStr(std::string content) {
        txtString = content;
        text.setString(txtString);
    }
    void operator=(const TextBox& t) {
        font.loadFromFile("COMIC.ttf");
        text.setFont(font);
        box.setPosition(t.place);
        box.setBorderColor(sf::Color::Black);
        box.setBorderWidth(3);
        box.setFillColor(sf::Color::White);
        box.setSize(t.size);
        editing = false;
        index = t.index;
        place = t.place;
        label = t.label;
        txtString = t.txtString;
        text.setCharacterSize(t.text.getCharacterSize());
        text.setString(txtString);
        text.setPosition(place.x + 3, place.y + 5);
        text.setFillColor(sf::Color::Black);
        isEmpty = t.isEmpty;
    }
    void respond(const sf::Event& event, sf::RenderWindow& window, int *row = nullptr, int *column = nullptr) {
        sf::Vector2i m = sf::Mouse::getPosition(window);
        sf::Vector2f p = window.mapPixelToCoords(m);

        if(event.type == sf::Event::MouseButtonPressed) {
            if(box.getShape().getGlobalBounds().contains(p)) {
                if(label == TextBoxLabel::ROW_GETTER) {
                    textboxclicked = sf::Vector2i(0, 0);
                }
                else if(label == TextBoxLabel::COLUMN_GETTER){
                    textboxclicked = sf::Vector2i(0, 1);
                }
                else if(label == TextBoxLabel::POW) {
                    if(!editing) {
                        activate();
                    }
                    else {
                        deactivate();
                    }
                }
                else if(label == TextBoxLabel::UNKNOW_TAKER) {
                    if(!editing) {
                        activate();
                    }
                    else {
                        deactivate();
                    }
                }
                if(index.x != -1) {
                    textboxclicked = index;
                }
            }
        }
        if(editing and event.type == sf::Event::KeyPressed) {
            if(event.key.code >= sf::Keyboard::Num0 and event.key.code <= sf::Keyboard::Num9) {
                int number = event.key.code - sf::Keyboard::Num0;
                txtString = txtString + std::to_string(number);
                text.setString(txtString);
            }
            else if(event.key.code == sf::Keyboard::Period and (label != TextBoxLabel::ROW_GETTER and label != TextBoxLabel::COLUMN_GETTER)){
                txtString = txtString + ".";
                text.setString(txtString);
            }
            else if(event.key.code == sf::Keyboard::Equal and (label != TextBoxLabel::ROW_GETTER and label != TextBoxLabel::COLUMN_GETTER)) {
                txtString = txtString + "+";
                text.setString(txtString);
            }
            else if(event.key.code == sf::Keyboard::I and (label != TextBoxLabel::ROW_GETTER and label != TextBoxLabel::COLUMN_GETTER)) {
                txtString = txtString + "i";
                text.setString(txtString);
            }
            else if(event.key.code == sf::Keyboard::Key::M and (label != TextBoxLabel::ROW_GETTER and label != TextBoxLabel::COLUMN_GETTER)) {
                txtString = txtString + "-";
                text.setString(txtString);
            }
            else if(event.key.code == sf::Keyboard::BackSpace) {
                if(txtString.length() > 0) {
                    txtString.pop_back();
                    text.setString(txtString);
                }
            }
            else if(event.key.code == sf::Keyboard::Enter) {
                
                box.setBorderWidth(3);
                switch(label) {
                    case TextBoxLabel::ROW_GETTER:
                    if(txtString.length() > 0) {
                        data = std::stoi(txtString);
                        *row = data;
                    }
                    else {
                        *row = 0;
                    }
                    break;

                    case TextBoxLabel::COLUMN_GETTER:
                    if(txtString.length() > 0) {
                        data = std::stoi(txtString);
                        *column = data;
                    }
                    else {
                        *column = 0;
                    }
                    break;

                    case TextBoxLabel::MATRIX:
                    if(txtString.length() > 0) {
                        MasterPage::matr.setElement(index.x, index.y, txtString);
                    }
                    else {
                       MasterPage::matr.setElement(index.x, index.y, "0");
                    }
                    break;

                    case TextBoxLabel::POW:
                    if(txtString.length() > 0) {
                        data = std::stoi(txtString);
                        *row = data;
                    }
                    else {
                        *row = 0;
                    }
                    break;

                    case TextBoxLabel::UNKNOW_TAKER:
                    if(txtString.length() > 0) {
                        data = std::stoi(txtString);
                        *row = data;
                    }
                    else {
                        *row = 0;
                    }
                    break;
                }
                editing = false;
            }
        }
    }
    bool isActive() {return editing;}
    void draw(sf::RenderWindow& window) {
        window.draw(box.getShape());
        window.draw(text);
    }
    void activate() {
        editing = true;
        box.setBorderWidth(5);
    }
    void deactivate() {
        editing = false;
        if(index.x != -1) {
            if(txtString.length() > 0) {
                MasterPage::matr.setElement(index.x, index.y, txtString);
            }
            else {
                MasterPage::matr.setElement(index.x, index.y, "0");
            }
        }
        box.setBorderWidth(3);
    }
};
sf::Vector2i TextBox::textboxclicked = sf::Vector2i(-1, -1);

class Variable {                      //for the variables x1, x2, etc. to be used to display linear equation
    private:
    sf::Text main, subscript, sign;
    sf::Font font;

    public:
    Variable() {
        font.loadFromFile("Arial.ttf");
        main.setFont(font);
        main.setFillColor(sf::Color::Black);
        main.setCharacterSize(20);
        main.setPosition(sf::Vector2f(0, 0));
        main.setString("");
        subscript.setFont(font);
        subscript.setFillColor(sf::Color::Black);
        subscript.setCharacterSize(10);
        subscript.setPosition(sf::Vector2f(0, 0));
        subscript.setString("");
        sign.setFont(font);
        sign.setFillColor(sf::Color::Black);
        sign.setCharacterSize(10);
        sign.setPosition(sf::Vector2f(0, 0));
        sign.setString("");
    }
    void setPara(const std::string& fnt, const sf::Vector2f &pos, const int& chsize) {
        sf::Vector2f ssPos = sf::Vector2f(pos.x + 0.6 * chsize, pos.y + 0.5 * chsize);
        sf::Vector2f sPos = sf::Vector2f(pos.x + chsize, pos.y);
        int subSize = 0.6 * chsize;
        font.loadFromFile(fnt);
        main.setFont(font);
        main.setPosition(pos);
        main.setFillColor(sf::Color::Black);
        main.setCharacterSize(chsize);
        subscript.setFont(font);
        subscript.setPosition(ssPos);
        subscript.setFillColor(sf::Color::Black);
        subscript.setCharacterSize(subSize);
        sign.setFont(font);
        sign.setPosition(sPos);
        sign.setFillColor(sf::Color::Black);
        sign.setCharacterSize(chsize);
    }
    void setVar(const std::string &str, int n) {
        main.setString("x");
        subscript.setString(std::to_string(n));
        sign.setString(str);
    }
    void draw(sf::RenderWindow &window) {
        window.draw(main);
        window.draw(subscript);
        window.draw(sign);
    }
};

class InputMatrix {                    //display a cell at a position, increase by 90 px, then display, box to box distance = 30px(each box size = 60 px)
    private:
    std::vector <std::vector <TextBox> > theMat;
    std::vector <std::vector <Variable>> variables;
    float x, y;
    sf::Vector2f pos;
    int rows, columns;
    bool buildingLinear;

    public:
    InputMatrix(const int &r, const int &c, const sf::Vector2f& position) {
        std::string content;
        rows = r;
        columns = c;
        pos = position;
        x = position.x;
        y = position.y;
        theMat.resize(r);
        for(int i = 0; i < r; i++) {
            theMat[i].resize(c);  
            x = position.x;
            for(int j = 0; j < c; j++) {
                content = (MasterPage::matr.getElement(i, j));
                theMat[i][j] = TextBox(sf::Vector2f(x, y), sf::Vector2f(60, 60), 30, TextBoxLabel::DEFAULT, sf::Vector2i(i, j));
                x += 90;
            }
            y += 90;
        }
        buildingLinear = false;
    }
    void createMatrix(const int& r, const int& c, const sf::Vector2f &position, bool linBuilder = false) {
        buildingLinear = linBuilder;
        if(linBuilder) {
            MasterPage::matr.setup(r, c);          
            rows = r, columns = c;
            variables.resize(r);
            theMat.resize(r);
            y = position.y;
            for(int i = 0; i < r; i++) {
                theMat[i].resize(c);  
                variables[i].resize(r);
                x = position.x;
                for(int j = 0; j < r; j++) {
                    variables[i][j].setPara("COMIC.ttf", sf::Vector2f(x + 80, y), 30);
                    if(j == r - 1) {
                        variables[i][j].setVar("=", j + 1);
                    }
                    else {
                        variables[i][j].setVar("+", j + 1);
                    }
                    x += 150;
                }
                x = position.x;
                for(int j = 0; j < c; j++) {
                    theMat[i][j] = TextBox(sf::Vector2f(x, y), sf::Vector2f(75, 45), 30, TextBoxLabel::MATRIX, sf::Vector2i(i, j));
                    x += 150;
                }
                y += 80;
            }
        }
        else {
            MasterPage::matr.setup(r, c);          
            rows = r, columns = c;
            theMat.resize(r);
            y = position.y;
            for(int i = 0; i < r; i++) {
                theMat[i].resize(c);  
                x = position.x;
                for(int j = 0; j < c; j++) {
                    theMat[i][j] = TextBox(sf::Vector2f(x, y), sf::Vector2f(130, 60), 30, TextBoxLabel::MATRIX, sf::Vector2i(i, j));
                    x += 160;
                }
                y += 90;
            }
        }
    }

    void respond(sf::Event& event, sf::RenderWindow& window, bool* matFull = nullptr) {
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < columns; j++) {
                theMat[i][j].respond(event, window);        
            }
        }
        *matFull = isFull();
    }
    void activateCell(sf::Vector2i& cell) {
       for(int i = 0; i < rows; i++) {
            for(int j = 0; j < columns; j++) {
                if(i == cell.x and j == cell.y) {
                    theMat[i][j].activate();
                }
                else {
                    theMat[i][j].deactivate();
                }
            }
        }
        cell = sf::Vector2i(-1, -1);
    }
    bool noCellActive() {
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < columns; j++) {
                if(theMat[i][j].isActive()) {return false;}
            }
        }
        return true;
    }
    bool isFull() {
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < columns; j++) {
                if(theMat[i][j].String().length() == 0) {
                    return false;
                }
            }
        }
        return true;
    }
    void draw(sf::RenderWindow& window) {
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < columns; j++) {
                theMat[i][j].draw(window);
            }
        }
        if(buildingLinear) {
            for(int i = 0; i < rows; i++) {
                for(int j = 0; j < rows; j++) {
                    variables[i][j].draw(window);
                }
            }
        }
    }
};

class OutputMatrix {
    private:
    std::vector <sf::Text> MatArray;
    std::vector <Variable> var;
    int r, c;
    float x, y;
    sf::Font f;
    bool LinEqBuilding;
    sf::Vector2i activeCell;
    sf::Vector2i pixPos;
    sf::Vector2f cordPos;

    public:
    OutputMatrix() {
        LinEqBuilding = false;
    }
    void setMat(const sf::Vector2f& position, bool LinEq = false) {
        LinEqBuilding = LinEq;
        if(LinEq) {
            r = MasterPage::matr.getRow();
            c = MasterPage::matr.getColumn(); 
            MatArray.resize(r * c);
            var.resize(r * r);
            y = position.y;
            f.loadFromFile("comici.ttf");
            bool complexMat = MasterPage::matr.isComplex();
            for(int i = 0; i < r; i++) {
                x = position.x;
                
                for(int j = 0; j < r; j++) {
                    if(!complexMat) {var[i * r + j].setPara("comici.ttf", sf::Vector2f(x+90, y), 30);}
                    else {var[i * r + j].setPara("comici.ttf", sf::Vector2f(x+190, y), 30);}
                    if(j == r - 1) {
                        var[i * r + j].setVar("  =", j + 1);
                    }
                    else {
                        var[i * r + j].setVar("  +", j + 1);
                    }
                    if(complexMat) {x += 280;}
                    else {x += 180;}
                }
                x = position.x;
                for(int j = 0; j < c; j++) {
                    MatArray[i * c + j].setCharacterSize(30);
                    MatArray[i * c + j].setFillColor(sf::Color::Black);
                    MatArray[i * c + j].setFont(f);
                    MatArray[i * c + j].setPosition(sf::Vector2f(x, y));
                    MatArray[i * c + j].setString((MasterPage::matr.getOri(i, j)));
                    if(complexMat) {x += 280;}
                    else {x += 180;}
                }
                y += 75;
            }
        }
        else {
            r = MasterPage::matr.getRow();
            c = MasterPage::matr.getColumn(); 
            MatArray.resize(r * c);
            y = position.y;
            f.loadFromFile("comici.ttf");
 
            for(int i = 0; i < r; i++) {
                x = position.x;
                for(int j = 0; j < c; j++) {
                    MatArray[i * c + j].setCharacterSize(25);
                    MatArray[i * c + j].setFillColor(sf::Color::Black);
                    MatArray[i * c + j].setFont(f);
                    MatArray[i * c + j].setPosition(sf::Vector2f(x, y));
                    MatArray[i * c + j].setString((MasterPage::matr.getOri(i, j)));
                    x += 165;
                }
                y += 50;
            }
        }
    }
    void setMat(const sf::Vector2f& position, Matrix& mat) {
        r = mat.getRow();
        c = mat.getColumn();
        MatArray.resize(r * c);
        y = position.y;
        f.loadFromFile("COMIC.ttf");
 
        for(int i = 0; i < r; i++) {
            x = position.x;
            for(int j = 0; j < c; j++) {
                MatArray[i * c + j].setCharacterSize(25);
                MatArray[i * c + j].setFillColor(sf::Color::Black);
                MatArray[i * c + j].setFont(f);
                MatArray[i * c + j].setPosition(sf::Vector2f(x, y));
                MatArray[i * c + j].setString((mat.getElement(i, j)));
                x += 180;
            }
            y += 50;
        }
    }
    void emptyMat() {
        if(!MatArray.empty()) {
            MatArray.clear();
        }
    }
    void respond(const sf::Event &event, sf::RenderWindow &window, TextEl &result) {
        if(event.type == sf::Event::MouseButtonPressed) {
            pixPos = sf::Mouse::getPosition(window);
            cordPos = window.mapPixelToCoords(pixPos);

            for(int i = 0; i < r; i++) {
                for(int j = 0; j < c; j++) {
                    if(MatArray[i*c + j].getGlobalBounds().contains(cordPos)) {
                        Num CoFact, Minor;
                        MatArray[i * c + j].setFillColor(sf::Color::Blue);
                        Minor = MasterPage::matr.CoFactor(i, j);
                        if((i + j + 2) % 2 == 0) {
                            result.setStr("Cofactor and minor = " + Minor.ToString());
                        }
                        else {
                            CoFact = Minor * Num(-1);
                            result.setStr("Minor = " + Minor.ToString() + "\nCoFactor = " + CoFact.ToString());
                        }
                    }
                    else {
                        MatArray[i * c + j].setFillColor(sf::Color::Black);
                    }
                }
            }
        }
    }
    void deactivateAll() {
        for(int i = 0; i < r; i++) {
            for(int j = 0; j < c; j++) {
                MatArray[i*c+j].setFillColor(sf::Color::Black);
            }
        }
    }
    void draw(sf::RenderWindow& window) {
        if(!MatArray.empty()) {
            if(LinEqBuilding) {
                for(int i = 0; i < r; i++) {
                    for(int j = 0; j < r; j++) {
                        var[i * r + j].draw(window);
                    }
                    for(int j = 0; j < c; j++) {
                        window.draw(MatArray[i * c + j]);
                    }
                }
            }
            else {
                for(int i = 0; i < r; i++) {
                    for(int j = 0; j < c; j++) {
                        window.draw(MatArray[i * c + j]);
                    }
                }
            }
        }
    }
};

#endif