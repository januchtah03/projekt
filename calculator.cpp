#include "calculator.h"
#include "ui_calculator.h"
#include <cmath>

double calcVal = 0.0;

// okresla ktory przycisk matematyczny byl ostatnim kliknietym
bool divTrigger = false;
bool multTrigger = false;
bool addTrigger = false;
bool subTrigger = false;
bool powTrigger = false;
bool rtTrigger = false;
bool modTrigger = false;


Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(calcVal));

        // odnosi sie do przyciskow numerycznych
        QPushButton *numButtons[10];

        for(int i = 0; i < 10; ++i){
            QString butName = "Button" + QString::number(i);

            numButtons[i] = Calculator::findChild<QPushButton *>(butName);

            connect(numButtons[i], SIGNAL(released()), this,
                    SLOT(NumPressed()));
        }

        // laczy sygnaly i sloty dla przyciskow matematycznych
        connect(ui->Add, SIGNAL(released()), this,
                SLOT(MathButtonPressed()));
        connect(ui->Subtract, SIGNAL(released()), this,
                SLOT(MathButtonPressed()));
        connect(ui->Multiply, SIGNAL(released()), this,
                SLOT(MathButtonPressed()));
        connect(ui->Divide, SIGNAL(released()), this,
                SLOT(MathButtonPressed()));
        connect(ui->Power, SIGNAL(released()), this,
                SLOT(MathButtonPressed()));
        connect(ui->Root, SIGNAL(released()), this,
                SLOT(MathButtonPressed()));
        connect(ui->Modulo, SIGNAL(released()), this,
                SLOT(MathButtonPressed()));

        // laczy przycisk =
        connect(ui->Equal, SIGNAL(released()), this,
                SLOT(EqualButtonPressed()));

        // laczy przycisk zmiany znaku
        connect(ui->ChangeSign, SIGNAL(released()), this,
                SLOT(ChangeNumberSign()));

        connect(ui->Clear, SIGNAL(released()), this,
                SLOT(Clear()));

}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumPressed(){

    QPushButton *button = (QPushButton *)sender();

    QString butVal = button->text();

    // daje wartosc na pole tekstowe
    QString displayVal = ui->Display->text();

    if((displayVal.toDouble() == 0) || (displayVal.toDouble() == 0.0)){

        // calcVal = butVal.toDouble();
        ui->Display->setText(butVal);

    } else {
        // daje nowa liczbe po prawo tego co sie tam znajduje
        QString newVal = displayVal + butVal;

        double dblNewVal = newVal.toDouble();

        // calcVal = newVal.toDouble();

        ui->Display->setText(QString::number(dblNewVal, 'g', 16));

    }
}

void Calculator::MathButtonPressed(){

    // anuluje wcisniete wczesniej przyciski matematyczne
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;
    powTrigger = false;
    rtTrigger = false;
    modTrigger = false;

    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();

    QPushButton *button = (QPushButton *)sender();

    QString butVal = button->text();

    if(QString::compare(butVal, "/", Qt::CaseInsensitive) == 0){
        divTrigger = true;
    } else if(QString::compare(butVal, "*", Qt::CaseInsensitive) == 0){
        multTrigger = true;
    } else if(QString::compare(butVal, "+", Qt::CaseInsensitive) == 0){
        addTrigger = true;
    } else if(QString::compare(butVal, "-", Qt::CaseInsensitive) == 0) {
        subTrigger = true;
    } else if(QString::compare(butVal, "pow", Qt::CaseInsensitive) == 0) {
        powTrigger = true;
    } else if(QString::compare(butVal, "root", Qt::CaseInsensitive) == 0) {
        rtTrigger = true;
    } else if(QString::compare(butVal, "%", Qt::CaseInsensitive) == 0) {
        modTrigger = true;
    }

    // czyszcze display
    ui->Display->setText("");

}
void Calculator::EqualButtonPressed(){

    double solution = 0.0;

    // daje wartosc w displayu
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();

    // upewniam sie ze przycisk matematyczny zostal wcisniety
    if(addTrigger || subTrigger || multTrigger || divTrigger || modTrigger || powTrigger || rtTrigger){
        if(addTrigger){
            solution = calcVal + dblDisplayVal;
        } else if(subTrigger){
            solution = calcVal - dblDisplayVal;
        } else if(multTrigger){
            solution = calcVal * dblDisplayVal;
        } else if(divTrigger) {
            solution = calcVal / dblDisplayVal;
        } else if(modTrigger) {
            solution = (int)calcVal % (int)dblDisplayVal;
        } else if(powTrigger) {
            solution = pow(calcVal,dblDisplayVal);
        } else if(rtTrigger) {
            solution = pow(calcVal,1.0/dblDisplayVal);
        }
    }

    // umieszcza rozwiazanie w displayu
    ui->Display->setText(QString::number(solution));

}

void Calculator::ChangeNumberSign(){

    // umieszcza wartosc w displayu
    QString displayVal = ui->Display->text();

    // RegExp sprawdza czy to liczba
    QRegExp reg("[-+]?[0-9.]*");

    // jesli to liczba, zmienia znak
    if(reg.exactMatch(displayVal)){
        double dblDisplayVal = displayVal.toDouble();
        double dblDisplayValSign = -1 * dblDisplayVal;

        ui->Display->setText(QString::number(dblDisplayValSign));
    }

}

void Calculator::Clear(){
    ui->Display->setText("0");
}
