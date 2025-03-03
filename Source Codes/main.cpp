#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <iostream>
#include "Buttons.hpp"

//Every page has setPage() function to set it's elements before diplaying
class HomePage: public MasterPage {
    private:
    Button StartMat, StartEq;
    TextEl MatHead, MatDes, LEHead, LEDes;
    sf::Texture texture;
    sf::Sprite Divider;
    BackGround BG;

    public:
    HomePage():
        StartMat("solve.png", sf::Vector2f(800.f,360.f), ButtonLable::MAT_BEGIN),
        StartEq("solve.png", sf::Vector2f(800.f,680.f), ButtonLable::LNEQ_BEGIN),
        MatHead("COMIC.ttf", 60, "Matrices", sf::Vector2f(190, 260), sf::Color (0, 0, 0)),
        MatDes("comici.ttf", 25, "Defines a matrix and can perform any operation\nlike calculation of determinants, inverse, rank,\neigen values etc..", sf::Vector2f(200, 360), sf::Color (0, 0, 0)),
        LEDes("comici.ttf", 25, "Solves system of simultaneous linear equations \n with any number of unknowns.", sf::Vector2f(200.f, 680.f), sf::Color (0, 0, 0)),
        LEHead("COMIC.ttf", 60, "Linear Equation", sf::Vector2f(190.f, 570.f), sf::Color (0, 0, 0)),
        BG("Background.jpg")
    {
        texture.loadFromFile("Line.png");
        Divider.setTexture(texture);
        Divider.setPosition(sf::Vector2f(120, 520));
    }

    void respond(sf::Event& event, sf::RenderWindow& window) {
        StartMat.respond(event, window);
        StartEq.respond(event, window);
    }

    void draw(sf::RenderWindow& window) {
        BG.draw(window);
        StartMat.draw(window);
        StartEq.draw(window);
        MatHead.draw(window);
        MatDes.draw(window);
        LEDes.draw(window);
        LEHead.draw(window);
        window.draw(Divider);
    }
};


class MatInPg1: public MasterPage {          //This page takes matrix input 
    private:                                 //boolean flags and variables are used to manage the state
    BackGround bg;
    TextBox RowIn, ColIn;
    TextEl RowEnter, ColEnter, message, caution;
    Button Enter, Back, MatEnt;
    InputMatrix Mat;
    bool rctaken, matmade, matdefined, matFull;     //rctaken = "row and column value taken", matmade = "matrix made to take input",  matdefined = "Matrix matr is set"
    sf::Texture texturemat;
    sf::Sprite Dividermat;
    int a;

    public:
    int row, column;
    MatInPg1(): bg("Background.jpg"), 
    RowIn(sf::Vector2f(610, 400), sf::Vector2f(100, 70), 45, TextBoxLabel::ROW_GETTER),
    RowEnter("COMIC.ttf", 55, "Enter Number Of Rows  ", sf::Vector2f(320,285), sf::Color::Black),
    ColIn(sf::Vector2f(610, 650), sf::Vector2f(100, 70), 45, TextBoxLabel::COLUMN_GETTER),
    ColEnter("COMIC.ttf", 55, "Enter Number Of Columns  ", sf::Vector2f(320, 525), sf::Color::Black),
    Enter("enterrc.png", sf::Vector2f(570, 800), ButtonLable::DIM_ENTERED),
    Mat(0, 0, sf::Vector2f(0, 0)),
    Back("Back.png", sf::Vector2f(50, 50), ButtonLable::BACK),
    MatEnt("enterrc.png", sf::Vector2f(630, 880), ButtonLable::MAT_ENTER),
    message("daytona.ttf", 20, "To Enter Values: \n\n1) Click on the box \n\n2) Enter the value\n  (Don't Use Numpad) \n\n3) Press Enter", sf::Vector2f(70, 450), sf::Color::Black),
    caution("daytona.ttf", 20, " Some Valid Inputs: -1.2-3.4i , 1.2+3.4i , 1.2 , -3.4i\n\n Space is not required between the characters !", sf::Vector2f(660, 10), sf::Color::Black){
        row = column = 0;
        rctaken = false;
        matmade = false;
        matdefined = false;
        matFull = false;
    }
    
    void setPage() {
  
        rctaken = false;
        matmade = false;
        matdefined = false;
        matFull = false;
        RowIn.setStr("");
        ColIn.setStr("");
        row = 0;
        column = 0;
        bg.setTexture("Background.jpg");
    }

    void respond(sf::Event& event, sf::RenderWindow& window) {
        if(!rctaken) {
            RowIn.respond(event, window, &row, &column);
            ColIn.respond(event, window, &row, &column);
            if(!RowIn.isActive() and !ColIn.isActive()) {                     //some process to improve input taking box's response
                if (TextBox::textboxclicked == sf::Vector2i(0, 0)) {
                    RowIn.activate();
                    ColIn.deactivate();
                    TextBox::textboxclicked = sf::Vector2i(-1, -1);
                }
            else if(TextBox::textboxclicked == sf::Vector2i(0, 1)) {
                    RowIn.deactivate();
                    ColIn.activate();
                    TextBox::textboxclicked = sf::Vector2i(-1, -1);
                }
            }
        }
        if(rctaken and matmade) {
            Mat.respond(event, window, &matFull);             //matfull is true if all values are entered
            if(TextBox::textboxclicked != sf::Vector2i(-1, -1) and Mat.noCellActive()) {
                Mat.activateCell(TextBox::textboxclicked);
            }
            TextBox::textboxclicked = sf::Vector2i(-1, -1);
        }
        if(row != 0 and column != 0 and !rctaken) {
            
            Enter.respond(event, window, &rctaken, &matmade);        //to make the button appear if all inputs are entered
        }
        if(rctaken and !matmade) {
            Mat.createMatrix(row, column, sf::Vector2f((1200 - column * 60 - (column - 1) * 30)/2, (1000 - row * 60 - (row - 1) * 30)/2));
            matmade = true;
            bg.setTexture("bgmat2.jpg");
            message.setStr("");
        }
        if(matFull) {
            MatEnt.respond(event, window, &matdefined);
        }
        TextBox::textboxclicked = sf::Vector2i(-1, -1);
        Back.respond(event, window, &rctaken, &matmade);    //Based on state of boolean variables, the elements will be displayed.
    }
    void draw(sf::RenderWindow& window) {
        bg.draw(window);
        if(!rctaken) {
            RowEnter.draw(window);
            RowIn.draw(window);
            ColEnter.draw(window);
            ColIn.draw(window);
             window.draw(Dividermat);
        }
        if(!matdefined) {
            message.draw(window);
            if(rctaken) {caution.draw(window);}
        }
        if(row != 0 and column != 0 and !rctaken) {
            Enter.draw(window);
        }
        if(rctaken and matmade) {
           Mat.draw(window);
        }
        if(matFull) {
            MatEnt.draw(window);
        }
        Back.draw(window);
    }
};

class MatPage2: public MasterPage {        //it displays the matrix entered, and allows to perform various operations
    private:
    BackGround bg;
    Button Back;
    Det Determinant;
    Rnk Rank;
    Trnspose Transpose;
    Invrse Inverse;
    Adjoint Adj;
    Expo Exponent;
    CoFact CoFactors;
    EigenV Egn;
    std::vector <Button*> Buttons;
    OutputMatrix Matt, temp;
    TextBox power;
    bool set;
    int id, active, p, activeP;
    TextEl result,heading , first_operation,second_operation,third_operation,fourth_operation,
           fifth_operation,sixth_operation,seventh_operation,eighth_operation, message_cofact,caution, pow_ins;
    sf::Texture textureline;                                                           //Some lines to be displayed
    sf::Sprite vertical_line , vertical_line1 , vertical_line2;

    sf::Texture texture_under_line;
    sf::Sprite under_line , under_line1 , line_under_det, line_under_det2,   
               line_under_rank , line_under_rank2,
               line_inv ,line_inv2,
               line_trans, line_trans2,
               line_exp, line_exp2,
               line_adj,line_adj2,
               line_cofact , line_cofact2,
               line_eigen , line_eigen2;

    public:
    MatPage2(): bg("bgmat2.jpg"),
    Back("Back.png", sf::Vector2f(30, 30), ButtonLable::BACK_MAT2),
    Determinant("Det1.png", sf::Vector2f(1630, 95)),
    result("daytonabold.ttf", 40, " Result ", sf::Vector2f(200, 800), sf::Color::Black),
    heading("daytonabold.ttf", 60, " OPERATIONS ", sf::Vector2f(1370, 0), sf::Color::Black),
    first_operation("daytonabold.ttf", 40, " Determinant : ", sf::Vector2f(1320, 118), sf::Color::Black),
    second_operation("daytonabold.ttf", 40, " Rank :  ", sf::Vector2f(1320, 220), sf::Color::Black),
    third_operation("daytonabold.ttf", 40, " Inverse :  ", sf::Vector2f(1320, 330), sf::Color::Black),
    fourth_operation("daytonabold.ttf", 40, " Transpose :  ", sf::Vector2f(1320, 440), sf::Color::Black),  //Label for various buttons
    fifth_operation("daytonabold.ttf", 40, " Adjoint :  ", sf::Vector2f(1320, 550), sf::Color::Black),
    sixth_operation("daytonabold.ttf", 40, " Exponential :  ", sf::Vector2f(1320, 770), sf::Color::Black),
    seventh_operation("daytonabold.ttf", 40, " Cofactor :  ", sf::Vector2f(1320, 660), sf::Color::Black),
    eighth_operation("daytonabold.ttf", 40, " Eigen :  ", sf::Vector2f(1320, 880), sf::Color::Black),
    Transpose("Transpose.png", sf::Vector2f(1590, 425)),
    Rank("Rnk.png", sf::Vector2f(1485, 205)),
    Inverse("Inverse.png", sf::Vector2f(1545, 315)),
    Adj("Adjoint.png", sf::Vector2f(1540, 535)),
    Exponent("expo.png", sf::Vector2f(1610, 755)),
    CoFactors("CoFact.png", sf::Vector2f(1565, 645)), 
    Egn("Eigen.png", sf::Vector2f(1500, 865)), 
    pow_ins("daytona.ttf", 30, "Enter power: ", sf::Vector2f(970, 810), sf::Color::Black),
    power(sf::Vector2f(1170, 800), sf::Vector2f(60, 60), 35, TextBoxLabel::POW),
    caution("daytona.ttf", 20, " Click On The Respective Operation's Button To Get The Result", sf::Vector2f(560, 10), sf::Color::Black),
    message_cofact("COMIC.ttf", 15, "Click on the respective\n elements of matrix to display\n co-factor and minors.", sf::Vector2f(1680, 650), sf::Color::Black)
    {
        textureline.loadFromFile("vertical_line.png");
        vertical_line.setTexture(textureline);
        vertical_line1.setTexture(textureline);
        vertical_line2.setTexture(textureline);

        vertical_line.setPosition(sf::Vector2f(1200, 0));
        vertical_line1.setPosition(sf::Vector2f(1200, 350));
        vertical_line2.setPosition(sf::Vector2f(1200, 700));

        texture_under_line.loadFromFile("underline.png");

        under_line.setTexture(texture_under_line);
        under_line.setPosition(sf::Vector2f(1300, 0));
        under_line1.setTexture(texture_under_line);
        under_line1.setPosition(sf::Vector2f(1500, 0));

        line_under_det.setTexture(texture_under_line);
        line_under_det.setPosition(sf::Vector2f(1300, 110));
        line_under_det2.setTexture(texture_under_line);
        line_under_det2.setPosition(sf::Vector2f(1500, 110));

        line_under_rank.setTexture(texture_under_line);
        line_under_rank.setPosition(sf::Vector2f(1300, 220));
        line_under_rank2.setTexture(texture_under_line);
        line_under_rank2.setPosition(sf::Vector2f(1500, 220));

        line_inv.setTexture(texture_under_line);
        line_inv.setPosition(sf::Vector2f(1300, 330));
        line_inv2.setTexture(texture_under_line);
        line_inv2.setPosition(sf::Vector2f(1500, 330));

        line_trans.setTexture(texture_under_line);
        line_trans.setPosition(sf::Vector2f(1300, 440));
        line_trans2.setTexture(texture_under_line);
        line_trans2.setPosition(sf::Vector2f(1500, 440));

        line_exp.setTexture(texture_under_line);
        line_exp.setPosition(sf::Vector2f(1300, 550));
        line_exp2.setTexture(texture_under_line);
        line_exp2.setPosition(sf::Vector2f(1500, 550));

        line_adj.setTexture(texture_under_line);
        line_adj.setPosition(sf::Vector2f(1300, 660));
        line_adj2.setTexture(texture_under_line);
        line_adj2.setPosition(sf::Vector2f(1500, 660));

        line_cofact.setTexture(texture_under_line);
        line_cofact.setPosition(sf::Vector2f(1300, 770));
        line_cofact2.setTexture(texture_under_line);
        line_cofact2.setPosition(sf::Vector2f(1500, 770));

        line_eigen.setTexture(texture_under_line);
        line_eigen.setPosition(sf::Vector2f(1300, 880));
        line_eigen2.setTexture(texture_under_line);
        line_eigen2.setPosition(sf::Vector2f(1500, 880));


        id = active = -1;
 
        Buttons.push_back(&Determinant);
        Buttons.push_back(&Rank);
        Buttons.push_back(&Inverse);
        Buttons.push_back(&Transpose);
        Buttons.push_back(&Adj);
        Buttons.push_back(&Exponent);
        Buttons.push_back(&CoFactors);
        Buttons.push_back(&Egn);
        set = false;
    }
    void respond(sf::Event& event, sf::RenderWindow& window) {
        Back.respond(event, window);
        Determinant.respond(event, window, id);
        Rank.respond(event, window, id);
        Inverse.respond(event, window, id);
        Transpose.respond(event, window, id);
        Adj.respond(event, window, id);
        CoFactors.respond(event,window, id);
        Exponent.respond(event, window, id);
        Egn.respond(event, window, id);           //if pressed each button sets id to its own id's value
        if(id != -1 and id != active) {          //after each activation, id is reset to -1, hence this will be true if some fresh value of id
            for(int i = 0; i < Buttons.size(); i++) {           //mechanism for activating one button at a time based on id
                if(id != i) {
                    Buttons[i]->deactivate(result, temp);
                }
            }
            Buttons[id]->activate(result, temp);
            active = id;
            id = -1;
        }
        if(active == 5) {power.respond(event, window, &p);}
        if(p != -1 and active == 5) {
            power.setStr("");
            activeP = p;
            p = -1;
            result.setStr("Power  =   " + std::to_string(activeP));
            Exponent.calc(temp, activeP);
        }
        if(active == 6) {Matt.respond(event, window, result);}
        else {Matt.deactivateAll();}
    }
    void setPage() {
        p = active = id = -1;
        power.setStr("");
        Inverse.setResponse();
        Determinant.setDetResponse();
        Adj.setResponse();
        Exponent.setResponse();
        CoFactors.setResponse();
        Egn.setResponse();
        for(auto element: Buttons) {
            element->deactivate(result, temp);
        }
    }
    OutputMatrix* getOutputMat() override{return &Matt;}
    void draw(sf::RenderWindow& window) {
        bg.draw(window);
        Matt.draw(window);
        for(auto element: Buttons) {
            element->Button::draw(window);
        }
        if(active == 5) {
            pow_ins.draw(window);
            power.draw(window);
        }
        result.draw(window);
        Back.draw(window);
        if(active > 1) {temp.draw(window);}
        heading.draw(window);
        if(active == 6) {message_cofact.draw(window);}
        first_operation.draw(window);
        second_operation.draw(window);
        second_operation.draw(window);
        third_operation.draw(window);
        fourth_operation.draw(window);
        fifth_operation.draw(window);
        sixth_operation.draw(window);
        seventh_operation.draw(window);
        eighth_operation.draw(window);
        caution.draw(window);
        window.draw(vertical_line);
        window.draw(vertical_line1);
        window.draw(vertical_line2);
        window.draw(under_line);
        window.draw(under_line1);
        window.draw(line_under_det);
        window.draw(line_under_det2);
        window.draw(line_under_rank);
        window.draw(line_under_rank2);
        window.draw(line_inv);
        window.draw(line_inv2);
        window.draw(line_trans);
        window.draw(line_trans2);
        window.draw(line_exp);
        window.draw(line_exp2);
        window.draw(line_adj);
        window.draw(line_adj2);
        window.draw(line_cofact);
        window.draw(line_cofact2);
         window.draw(line_eigen);
        window.draw(line_eigen2);
    }
    
};

class LinearPage: public MasterPage {         //equivalent to matpg1, takes the input as equations
    private:
    BackGround bg;
    Button back, unknownTaken, MatEnt;
    InputMatrix matIn;
    TextBox UnknownNumberTaker;
    bool unknown_num_taken, mat_full, mat_made, mat_defined, linB;
    int unknowns;
    TextEl data_entry, message,caution ;

    public:
    LinearPage(): bg("Background.jpg"), back("Back.png", sf::Vector2f(50, 50), ButtonLable::BACK),
    matIn(0, 0, sf::Vector2f(0, 0)),
    data_entry("comic_sans.ttf", 40, " Enter the number of unknown variables:  ", sf::Vector2f(160, 420), sf::Color::Black),
    unknownTaken("enterrc.png", sf::Vector2f(495, 535), ButtonLable::DIM_ENTERED),
    UnknownNumberTaker(sf::Vector2f(955, 400), sf::Vector2f(70, 70), 50, TextBoxLabel::UNKNOW_TAKER),
    MatEnt("enterrc.png", sf::Vector2f(480, 900), ButtonLable::LIN_EQ_ENTER),
    message("daytonabold.ttf", 20, "To Enter Values: \n\n1) Click on the box \n\n2) Enter the value\n  (Don't Use Numpad) \n\n3) Press Enter", sf::Vector2f(500, 170), sf::Color::Black),
     caution("daytona.ttf", 20, " Some Valid Inputs: -1.2-3.4i , 1.2+3.4i , 1.2 , -3.4i\n\n Space is not required between the characters !", sf::Vector2f(660, 10), sf::Color::Black){
        unknown_num_taken = false;
        unknowns = 0;
        mat_made = mat_full = mat_defined = false;
        TextBox::textboxclicked = sf::Vector2i(-1, -1);
        linB = true;
    }
    void setPage() {
        unknowns = 0;
        unknown_num_taken = false;
        mat_full = false;
        linB = true;
        mat_defined = false;
        mat_made = false;
        TextBox::textboxclicked = sf::Vector2i(-1, -1);
        UnknownNumberTaker.setStr("");
    
        bg.setTexture("Background.jpg");
    }
    void respond(sf::Event &event, sf::RenderWindow &window) {
        back.respond(event, window);
        if(!unknown_num_taken) {
            UnknownNumberTaker.respond(event, window, &unknowns);
        }
        if(unknowns != 0) {
            unknownTaken.respond(event, window, &unknown_num_taken);
        }
        if(unknown_num_taken and !mat_made) {
            matIn.createMatrix(unknowns, unknowns + 1, sf::Vector2f(200, 200), true);
            mat_made = true;
            bg.setTexture("bgmat2.jpg");
            message.setStr("");
        }
        if(mat_made and !mat_defined) {
            matIn.respond(event, window, &mat_full);
            if(TextBox::textboxclicked != sf::Vector2i(-1, -1) and matIn.noCellActive()) {
                matIn.activateCell(TextBox::textboxclicked);
            }
            TextBox::textboxclicked = sf::Vector2i(-1, -1);
        }
        if(mat_full and !mat_defined) {
            MatEnt.respond(event, window, &mat_defined);
        }
    }
    void draw(sf::RenderWindow& window) {
        bg.draw(window);
        if(!unknown_num_taken) {UnknownNumberTaker.draw(window),data_entry.draw(window);}
        if(!mat_defined) {
            message.draw(window);
            if(unknown_num_taken) {
                caution.draw(window);
            }
        }
        if(unknowns != 0 and !unknown_num_taken) {unknownTaken.draw(window);}
        if(mat_made and !mat_defined) {matIn.draw(window);}
        if(mat_full and !mat_defined) {MatEnt.draw(window);}
        back.draw(window);
    }
};

class LinEqPage2: public MasterPage {   //shows the solution
    private:
    BackGround BG;
    OutputMatrix Equations;
    bool eqn_set;
    TextEl result, soltion;
    std::string intermediates;
    std::vector <Variable> v;
    Button Back;

    public:
    LinEqPage2():BG("bgmat2.jpg"), Equations(), result("comici.ttf", 25, "", sf::Vector2f(175, 660), sf::Color::Black), 
    soltion("daytonabold.ttf", 40, "Solutions : ", sf::Vector2f(120, 610), sf::Color::Black),
    Back("Back.png", sf::Vector2f(50, 50), ButtonLable::BACK_L) {
        eqn_set = false;
        intermediates = "";
    }
    void setPage() {
        Equations.setMat(sf::Vector2f(100, 150), true);
        result.setStr("");
        eqn_set = true;
        float y = 0;
        Matrix reduced;
        switch(matr.SolutionNature()) {
            case 1:                                    //unique solution exists
            v.resize(matr.getRow());
            for(int i = 0; i < matr.getRow(); i++) {
                reduced = matr.ReducedEchelon();
                intermediates = intermediates + reduced.getElement(i, matr.getColumn() - 1) + "\n"; 
                v[i].setPara("comici.ttf", sf::Vector2f(120, 660 + y), 25);
                v[i].setVar(" = ", i + 1);
                y += 35;
            }
            result.setStr(intermediates);
            break;

            case 2:
            result.setStr("Infinte solutions!");
            break;

            case 3:
            result.setStr("No solution!");
        }
    }
    void respond(sf::Event& event, sf::RenderWindow& window) {
        Back.respond(event, window);
    }
    void draw(sf::RenderWindow &window) {
        BG.draw(window);
        if(eqn_set) {
            Equations.draw(window);
            if(matr.SolutionNature() == 1) {
                soltion.draw(window);
                for(auto x:v) {
                    x.draw(window);
                }
            }
            result.draw(window);
        }
        Back.draw(window);
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1000), "Matrix");

    auto homePage = std::make_shared<HomePage>();
    auto matInPage1 = std::make_shared<MatInPg1>();
    auto matPage2 = std::make_shared<MatPage2>();
    auto LinPage = std::make_shared<LinearPage>();
    auto LnPage2 = std::make_shared<LinEqPage2>();

    
    MasterPage::add(homePage);      //0 jus to mean, homepage has index one
    MasterPage::add(matInPage1);    //1
    MasterPage::add(matPage2);      //2
    MasterPage::add(LinPage);       //3
    MasterPage::add(LnPage2);       //4
    MasterPage::currentPage = homePage;

    sf::Image icon; 
    icon.loadFromFile("icon.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
            MasterPage::currentPage->respond(event, window);
        }
        window.clear(sf::Color::White);
        MasterPage::currentPage->draw(window);
        window.display();
    }
    
    return 0;
}