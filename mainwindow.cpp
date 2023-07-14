#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "random"
#include <algorithm>

int gua[6];
int bian_gua[6];
int hu_gua[6];
int cuo_gua[6];
int zong_gua[6];

//控制桿
int gate; //卦象介紹顯示
int page_num; //頁碼label顯示
QString change_set; //變爻位置
int change; //變爻數



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void random_str(int *arr){
    int temp[3];
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 49);
    int randomNum ;
    for(int i=0;i<6;i++){
        int odd =0,even =0;
        for (int l = 0; l < 3 ; ++l) {
            randomNum = dist(gen);
            randomNum /=4;
            randomNum%=2;
            temp[l]=randomNum;
        }
        for(int l=0;l<3;l++){   //計算三個隨機數字的奇偶
            switch(temp[l]){
                case 0:
                    even+=1;
                    break;
                case 1:
                    odd+=1;
                    break;
                default:
                    break;
            }
        }
        //奇數為陽，偶數為陰
        //統計後計算一個爻 ( 偶數為陰，奇數為陽。 兩陰一陽(2+2+1=5(奇數))固此數為少陽)
        if(even==3){    //三個偶數--老陰
            arr[i]=6;
        }
        if(odd==3){     //三個奇數--老陽
            arr[i]=9;
        }
        if(even==1&&odd==2){    //一個偶數兩個奇數--少陰
            arr[i]=8;
        }
        if(even==2&&odd==1){    //一個奇數兩個偶數--少陽
            arr[i]=7;
        }

    }
    //*arr = dist(gen);
}

void put_gua_data(int *bian_gua ,int *hu_gua ,int *cuo_gua, int *zong_gua){
    //變卦
    for(int i =0;i<6;i++){
        bian_gua[i]=gua[i];
        if(gua[i]==6){
            bian_gua[i]=9;}
        if(gua[i]==9){
            bian_gua[i]=6;}
        //錯卦
        if(gua[i]==6){
            cuo_gua[i]=9;}
        if(gua[i]==9){
            cuo_gua[i]=6;}
        if(gua[i]==7){
            cuo_gua[i]=8;}
        if(gua[i]==8){
            cuo_gua[i]=7;}
        //綜卦
        zong_gua[i]=gua[5-i];
    }
    //互卦
    hu_gua[0]=gua[1];
    hu_gua[1]=gua[2];
    hu_gua[2]=gua[3];
    hu_gua[3]=gua[2];
    hu_gua[4]=gua[3];
    hu_gua[5]=gua[4];
}

void MainWindow::on_pushButton_clicked()
{
    //畫面初始化
    gate = 0;
    page_num = 1;
    change_set="";
    change=0;
    setHidden(true);
    Form0 * form_0 = new Form0();

    random_str(gua);

//    gua[0]=9;
//    gua[1]=8;
//    gua[2]=9;
//    gua[3]=6;
//    gua[4]=7;
//    gua[5]=9;

    for(int i=0;i<6;i++){
        if(gua[i]==6){
            change+=1;
            change_set+= QString::number(i+1);
        }
        if(gua[i]==9){
            change+=1;
            change_set+= QString::number(i+1);
        }
    }

    std::reverse(gua, gua + 6);

    for (int i = 0; i < 6; ++i) {
        qDebug() << gua[i];
    }


    put_gua_data(bian_gua,hu_gua,cuo_gua,zong_gua);

    qDebug() << "-------";

    for (int i = 0; i < 6; ++i) {
        qDebug() << bian_gua[i];
    }


    qDebug() << change;

    form_0 -> show();
}


void MainWindow::on_pushButton_2_clicked()
{
    this->close();
    play * pl = new play();
    pl->show();
}

