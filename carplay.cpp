#include "carplay.h"
#include "ui_carplay.h"

Carplay::Carplay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Carplay)
{
    ui->setupUi(this);
}

Carplay::~Carplay()
{
    delete ui;
}


