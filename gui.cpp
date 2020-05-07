#include "gui.h"
#include "ui_gui.h"

GUI::GUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GUI)
{
    ui->setupUi(this);
    connect(ui->plusWarte,SIGNAL(pressed()),this,SLOT(AddToWarteschlange()));
    connect(ui->minusWarte,SIGNAL(pressed()),this,SLOT(RemoveFromWarteschlange()));
    connect(ui->actionOffnen,SIGNAL(triggered()),this,SLOT(on_actionOffnen()));    
}

GUI::~GUI()
{
    delete ui;
}

void GUI::AddToWarteschlange(){
    ui->ListSchlange->addItem(QString("Hallo"));
}

void GUI::RemoveFromWarteschlange(){
    ui->ListSchlange->takeItem(0);
}

void GUI::on_actionOffnen()
{
    datei = QFileDialog::getOpenFileName(this,tr("Wählen Sie eine *.cube Datei aus"),"C:\\users\\",tr("CubeDateien (*.cube)"));
}

void GUI::rotate(){
    ui->widget->setRotation(ui->rotation->value());
}
