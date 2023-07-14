#include "form0.h"
#include "ui_form0.h"

#include "mainwindow.h"

#include <QtGui>
#include <QtWidgets>

#include <QApplication>
#include <QWidget>
#include <QEvent>
#include <QMouseEvent>
#include <QTimer>
#include <algorithm>
#include <QString>

// qDebug() << "成功";

Form0::Form0(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form0)
{
    ui->setupUi(this);
    this->installEventFilter(this);

}

Form0::~Form0()
{
    delete ui;
}

void Form0::on_pushButton_2_clicked()
{
    MainWindow * main_window = new MainWindow();
    page_num = 0;
    this->close();
    main_window->show();
    qDebug() << "返回主畫面!";
}

//填入取出的檔案內容
QString ReadLineFromFile(const QString& filePath, int lineNumber) {
    QFile file(filePath);
    QString line;
    QString content = "";
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);

        int currentLine = 1;
        int lineNumber2 = lineNumber+1;
        int lineNumber3 = lineNumber2+1;
        int lineNumber4 = lineNumber3+1;

        while (!in.atEnd()) {
            line = in.readLine();
            if (currentLine == lineNumber) {
                content += line;
            }
            if (currentLine == lineNumber2) {
                content += line;
                content += '\n';
            }
            if (currentLine == lineNumber3) {
                content += line;
                content += '\n';
            }
            if (currentLine == lineNumber4) {
                content += line;
                //content += '\n';
            }
            ++currentLine;
        }

        file.close();
    } else {
        qWarning() << "無法打開檔案：" << filePath;
    }

    return content;
}


//把取出的卦象轉換成對應的檔案名稱
std::string Form0::load_data_name(int arr[6]){
    std::string name = "";

    for (int var = 0; var < 6; ++var) {
        if(arr[var]%2==1){
            arr[var]==1;
            name+='1';
        }
        else{
            arr[var]==0;
            name+='0';
        }
    }
    //qDebug() << name ;
    return name;
}

//此處處理需要顯示"變爻爻辭"的部分
void Form0::onFirstShow(int chan_num){
    if(chan_num == 1){
        QString new_change_set="123456";
        for (int i = 0; i < change ; ++i) {
            QChar ch = change_set[i];
            new_change_set.remove(ch);
        }

        std::string name1 = load_data_name(gua);
        QString all_line = "";
        //std::string name1 = "101010";
        QString filePath = QString::fromStdString(":/gua_data/" + name1 + ".txt");
        //主卦
        qDebug() << "長度: " << change;
            qDebug() << "變爻: " << change_set;
        for(int i=0;i<change;i++){
            QChar ch = change_set[i];
            int temp = ch.digitValue();
            temp = temp*4+1;
            qDebug() << "起始行" << temp ;
                QString line = ReadLineFromFile(filePath, temp );
            all_line+=line;
            all_line += '\n';
        }
        //qDebug() << all_line ;
        ui->textBrowser_1->setText(all_line);
        //-----------------------------------
        name1 = load_data_name(bian_gua);
        all_line = "";
        filePath = QString::fromStdString(":/gua_data/" + name1 + ".txt");
        //變卦
        qDebug() << "長度: " << new_change_set.length();
            qDebug() << "變爻: " << new_change_set;
        for(int i=0;i<new_change_set.length();i++){
            QChar ch = new_change_set[i];
            int temp = ch.digitValue();
            temp = temp*4+1;
            QString line = ReadLineFromFile(filePath, temp );
            all_line+=line;
            all_line += '\n';
        }
        ui->textBrowser_3->setText(all_line);
        //-----------------------------------
        name1 = load_data_name(hu_gua);
        all_line = "";
        filePath = QString::fromStdString(":/gua_data/" + name1 + ".txt");
        //互卦
        for(int i=0;i<new_change_set.length();i++){
            QChar ch = new_change_set[i];
            int temp = ch.digitValue();
            temp = temp*4+1;
            QString line = ReadLineFromFile(filePath, temp );
            all_line+=line;
            all_line += '\n';
        }
        ui->textBrowser_4->setText(all_line);
        //-----------------------------------
        name1 = load_data_name(cuo_gua);
        all_line = "";
        filePath = QString::fromStdString(":/gua_data/" + name1 + ".txt");
        //錯卦
        for(int i=0;i<new_change_set.length();i++){
            QChar ch = new_change_set[i];
            int temp = ch.digitValue();
            temp = temp*4+1;
            QString line = ReadLineFromFile(filePath, temp );
            all_line+=line;
            all_line += '\n';
        }
        ui->textBrowser_5->setText(all_line);
        //-----------------------------------
        name1 = load_data_name(zong_gua);
        all_line = "";
        filePath = QString::fromStdString(":/gua_data/" + name1 + ".txt");
        //綜卦
        for(int i=0;i<new_change_set.length();i++){
            QChar ch = new_change_set[i];
            int temp = ch.digitValue();
            temp = temp*4+1;
            QString line = ReadLineFromFile(filePath, temp );
            all_line+=line;
            all_line += '\n';
        }
        ui->textBrowser_6->setText(all_line);

    }else{

        int change_set_len = change_set.length();
        std::string name1 = load_data_name(gua);
        QString all_line = "";
        //std::string name1 = "101010";
        QString filePath = QString::fromStdString(":/gua_data/" + name1 + ".txt");
        //主卦
        qDebug() << "長度: " << change_set_len;
        qDebug() << "變爻: " << change_set;
        for(int i=0;i<change_set_len;i++){
            QChar ch = change_set[i];
            int temp = ch.digitValue();
            temp = temp*4+1;
            qDebug() << "起始行" << temp ;
                QString line = ReadLineFromFile(filePath, temp );
            all_line+=line;
            all_line += '\n';
        }
        //qDebug() << all_line ;
        ui->textBrowser_1->setText(all_line);
        //-----------------------------------
        name1 = load_data_name(bian_gua);
        all_line = "";
        filePath = QString::fromStdString(":/gua_data/" + name1 + ".txt");
        //變卦
        //qDebug() << "長度: " << change_set_len;
            //qDebug() << "變爻: " << change_set;
        for(int i=0;i<change_set_len;i++){
            QChar ch = change_set[i];
            int temp = ch.digitValue();
            temp = temp*4+1;
            //qDebug() << "起始行" << temp ;
                QString line = ReadLineFromFile(filePath, temp );
            all_line+=line;
            all_line += '\n';
        }
        //qDebug() << all_line ;
        ui->textBrowser_3->setText(all_line);
        //-----------------------------------
        name1 = load_data_name(hu_gua);
        all_line = "";
        filePath = QString::fromStdString(":/gua_data/" + name1 + ".txt");
        //互卦
        //qDebug() << "長度: " << change_set_len;
            //qDebug() << "變爻: " << change_set;
        for(int i=0;i<change_set_len;i++){
            QChar ch = change_set[i];
            int temp = ch.digitValue();
            temp = temp*4+1;
            //qDebug() << "起始行" << temp ;
                QString line = ReadLineFromFile(filePath, temp );
            all_line+=line;
            all_line += '\n';
        }
        //qDebug() << all_line ;
        ui->textBrowser_4->setText(all_line);
        //-----------------------------------
        name1 = load_data_name(cuo_gua);
        all_line = "";
        filePath = QString::fromStdString(":/gua_data/" + name1 + ".txt");
        //錯卦
        //qDebug() << "長度: " << change_set_len;
            //qDebug() << "變爻: " << change_set;
        for(int i=0;i<change_set_len;i++){
            QChar ch = change_set[i];
            int temp = ch.digitValue();
            temp = temp*4+1;
            //qDebug() << "起始行" << temp ;
                QString line = ReadLineFromFile(filePath, temp );
            all_line+=line;
            all_line += '\n';
        }
        //qDebug() << all_line ;
        ui->textBrowser_5->setText(all_line);
        //-----------------------------------
        name1 = load_data_name(zong_gua);
        all_line = "";
        filePath = QString::fromStdString(":/gua_data/" + name1 + ".txt");
        //綜卦
        //qDebug() << "長度: " << change_set_len;
            //qDebug() << "變爻: " << change_set;
        for(int i=0;i<change_set_len;i++){
            QChar ch = change_set[i];
            int temp = ch.digitValue();
            temp = temp*4+1;
            //qDebug() << "起始行" << temp ;
            QString line = ReadLineFromFile(filePath, temp );
            all_line+=line;
            all_line += '\n';
        }
        //qDebug() << all_line ;
        ui->textBrowser_6->setText(all_line);
    }
}

//6,5,4,3,0個變爻只顯示"卦義",除了6個變爻的 乾卦以「用九」爻辭，坤卦以「用六」爻辭
void Form0::onSecondShow(){
    std::string name1 = load_data_name(gua);
    QString filePath = QString::fromStdString(":/gua_data/" + name1 + ".txt");
    QString line = ReadLineFromFile(filePath, 29 );
    ui->textBrowser_1->setText(line);

    name1 = load_data_name(bian_gua);
    filePath = QString::fromStdString(":/gua_data/" + name1 + ".txt");
    line = ReadLineFromFile(filePath, 29 );
    ui->textBrowser_3->setText(line);

    name1 = load_data_name(hu_gua);
    filePath = QString::fromStdString(":/gua_data/" + name1 + ".txt");
    line = ReadLineFromFile(filePath, 29 );
    ui->textBrowser_4->setText(line);

    name1 = load_data_name(cuo_gua);
    filePath = QString::fromStdString(":/gua_data/" + name1 + ".txt");
    line = ReadLineFromFile(filePath, 29 );
    ui->textBrowser_5->setText(line);

    name1 = load_data_name(zong_gua);
    filePath = QString::fromStdString(":/gua_data/" + name1 + ".txt");
    line = ReadLineFromFile(filePath, 29 );
    ui->textBrowser_6->setText(line);

}

void Form0::gua_nameShow(){
    QString all_line = "";
    std::string name1 = load_data_name(gua);
    QString filePath = QString::fromStdString(":/gua_data/" + name1 + ".txt");
    QString line = ReadLineFromFile(filePath, 1 );
    all_line = "主卦 "+line;
    ui->label_17->setText(all_line);

    name1 = load_data_name(bian_gua);
    filePath = QString::fromStdString(":/gua_data/" + name1 + ".txt");
    line = ReadLineFromFile(filePath, 1 );
    all_line = "變卦 "+line;
    ui->label_37->setText(all_line);

    name1 = load_data_name(hu_gua);
    filePath = QString::fromStdString(":/gua_data/" + name1 + ".txt");
    line = ReadLineFromFile(filePath, 1 );
    all_line = "互卦 "+line;
    ui->label_47->setText(all_line);

    name1 = load_data_name(cuo_gua);
    filePath = QString::fromStdString(":/gua_data/" + name1 + ".txt");
    line = ReadLineFromFile(filePath, 1 );
    all_line = "錯卦 "+line;
    ui->label_57->setText(all_line);

    name1 = load_data_name(zong_gua);
    filePath = QString::fromStdString(":/gua_data/" + name1 + ".txt");
    line = ReadLineFromFile(filePath, 1 );
    all_line = "綜卦 "+line;
    ui->label_67->setText(all_line);
}

//放置爻象的圖檔的對應label
void Form0::onthirdShow(int pic0[6],int pic1[6],int pic2[6],int pic3[6],int pic4[6]){

    QString data_name ="";
    //QString data_name =":/image_data/6.jpg";
    //主卦爻像圖案________________________________________________________________
    data_name =":/image_data/"+QString::number(pic0[0])+".jpg";
    QPixmap pixmap11(data_name);
    pixmap11 = pixmap11.scaled(ui->label_11->size(), Qt::KeepAspectRatio);
    ui->label_11->setPixmap(pixmap11);

    data_name =":/image_data/"+QString::number(pic0[1])+".jpg";
    QPixmap pixmap12(data_name);
    pixmap12 = pixmap12.scaled(ui->label_12->size(), Qt::KeepAspectRatio);
    ui->label_12->setPixmap(pixmap12);

    data_name =":/image_data/"+QString::number(pic0[2])+".jpg";
    QPixmap pixmap13(data_name);
    pixmap13 = pixmap13.scaled(ui->label_13->size(), Qt::KeepAspectRatio);
    ui->label_13->setPixmap(pixmap13);

    data_name =":/image_data/"+QString::number(pic0[3])+".jpg";
    QPixmap pixmap14(data_name);
    pixmap14 = pixmap14.scaled(ui->label_14->size(), Qt::KeepAspectRatio);
    ui->label_14->setPixmap(pixmap14);

    data_name =":/image_data/"+QString::number(pic0[4])+".jpg";
    QPixmap pixmap15(data_name);
    pixmap15 = pixmap15.scaled(ui->label_15->size(), Qt::KeepAspectRatio);
    ui->label_15->setPixmap(pixmap15);

    data_name =":/image_data/"+QString::number(pic0[5])+".jpg";
    QPixmap pixmap16(data_name);
    pixmap16 = pixmap16.scaled(ui->label_16->size(), Qt::KeepAspectRatio);
    ui->label_16->setPixmap(pixmap16);
    //變卦爻像圖案________________________________________________________________
    data_name =":/image_data/"+QString::number(pic1[0])+".jpg";
    QPixmap pixmap31(data_name);
    pixmap31 = pixmap31.scaled(ui->label_31->size(), Qt::KeepAspectRatio);
    ui->label_31->setPixmap(pixmap31);

    data_name =":/image_data/"+QString::number(pic1[1])+".jpg";
    QPixmap pixmap32(data_name);
    pixmap32 = pixmap32.scaled(ui->label_32->size(), Qt::KeepAspectRatio);
    ui->label_32->setPixmap(pixmap32);

    data_name =":/image_data/"+QString::number(pic1[2])+".jpg";
    QPixmap pixmap33(data_name);
    pixmap33 = pixmap33.scaled(ui->label_33->size(), Qt::KeepAspectRatio);
    ui->label_33->setPixmap(pixmap33);

    data_name =":/image_data/"+QString::number(pic1[3])+".jpg";
    QPixmap pixmap34(data_name);
    pixmap34 = pixmap34.scaled(ui->label_34->size(), Qt::KeepAspectRatio);
    ui->label_34->setPixmap(pixmap34);

    data_name =":/image_data/"+QString::number(pic1[4])+".jpg";
    QPixmap pixmap35(data_name);
    pixmap35 = pixmap35.scaled(ui->label_35->size(), Qt::KeepAspectRatio);
    ui->label_35->setPixmap(pixmap35);

    data_name =":/image_data/"+QString::number(pic1[5])+".jpg";
    QPixmap pixmap36(data_name);
    pixmap36 = pixmap36.scaled(ui->label_36->size(), Qt::KeepAspectRatio);
    ui->label_36->setPixmap(pixmap36);
    //互卦爻像圖案________________________________________________________________
    data_name =":/image_data/"+QString::number(pic2[0])+".jpg";
    QPixmap pixmap41(data_name);
    pixmap41 = pixmap41.scaled(ui->label_41->size(), Qt::KeepAspectRatio);
    ui->label_41->setPixmap(pixmap41);

    data_name =":/image_data/"+QString::number(pic2[1])+".jpg";
    QPixmap pixmap42(data_name);
    pixmap42 = pixmap32.scaled(ui->label_42->size(), Qt::KeepAspectRatio);
    ui->label_42->setPixmap(pixmap42);

    data_name =":/image_data/"+QString::number(pic2[2])+".jpg";
    QPixmap pixmap43(data_name);
    pixmap43 = pixmap43.scaled(ui->label_43->size(), Qt::KeepAspectRatio);
    ui->label_43->setPixmap(pixmap43);

    data_name =":/image_data/"+QString::number(pic2[3])+".jpg";
    QPixmap pixmap44(data_name);
    pixmap44 = pixmap44.scaled(ui->label_44->size(), Qt::KeepAspectRatio);
    ui->label_44->setPixmap(pixmap44);

    data_name =":/image_data/"+QString::number(pic2[4])+".jpg";
    QPixmap pixmap45(data_name);
    pixmap45 = pixmap45.scaled(ui->label_45->size(), Qt::KeepAspectRatio);
    ui->label_45->setPixmap(pixmap45);

    data_name =":/image_data/"+QString::number(pic2[5])+".jpg";
    QPixmap pixmap46(data_name);
    pixmap46 = pixmap46.scaled(ui->label_46->size(), Qt::KeepAspectRatio);
    ui->label_46->setPixmap(pixmap46);
    //錯卦爻像圖案________________________________________________________________
    data_name =":/image_data/"+QString::number(pic3[0])+".jpg";
    QPixmap pixmap51(data_name);
    pixmap51 = pixmap51.scaled(ui->label_51->size(), Qt::KeepAspectRatio);
    ui->label_51->setPixmap(pixmap51);

    data_name =":/image_data/"+QString::number(pic3[1])+".jpg";
    QPixmap pixmap52(data_name);
    pixmap52 = pixmap52.scaled(ui->label_52->size(), Qt::KeepAspectRatio);
    ui->label_52->setPixmap(pixmap52);

    data_name =":/image_data/"+QString::number(pic3[2])+".jpg";
    QPixmap pixmap53(data_name);
    pixmap53 = pixmap53.scaled(ui->label_53->size(), Qt::KeepAspectRatio);
    ui->label_53->setPixmap(pixmap53);

    data_name =":/image_data/"+QString::number(pic3[3])+".jpg";
    QPixmap pixmap54(data_name);
    pixmap54 = pixmap54.scaled(ui->label_54->size(), Qt::KeepAspectRatio);
    ui->label_54->setPixmap(pixmap54);

    data_name =":/image_data/"+QString::number(pic3[4])+".jpg";
    QPixmap pixmap55(data_name);
    pixmap55 = pixmap55.scaled(ui->label_55->size(), Qt::KeepAspectRatio);
    ui->label_55->setPixmap(pixmap55);

    data_name =":/image_data/"+QString::number(pic3[5])+".jpg";
    QPixmap pixmap56(data_name);
    pixmap56 = pixmap56.scaled(ui->label_56->size(), Qt::KeepAspectRatio);
    ui->label_56->setPixmap(pixmap56);
    //綜卦爻像圖案________________________________________________________________
    data_name =":/image_data/"+QString::number(pic4[0])+".jpg";
    QPixmap pixmap61(data_name);
    pixmap61 = pixmap61.scaled(ui->label_61->size(), Qt::KeepAspectRatio);
    ui->label_61->setPixmap(pixmap61);

    data_name =":/image_data/"+QString::number(pic4[1])+".jpg";
    QPixmap pixmap62(data_name);
    pixmap62 = pixmap62.scaled(ui->label_62->size(), Qt::KeepAspectRatio);
    ui->label_62->setPixmap(pixmap62);

    data_name =":/image_data/"+QString::number(pic4[2])+".jpg";
    QPixmap pixmap63(data_name);
    pixmap63 = pixmap63.scaled(ui->label_63->size(), Qt::KeepAspectRatio);
    ui->label_63->setPixmap(pixmap63);

    data_name =":/image_data/"+QString::number(pic4[3])+".jpg";
    QPixmap pixmap64(data_name);
    pixmap64 = pixmap64.scaled(ui->label_64->size(), Qt::KeepAspectRatio);
    ui->label_64->setPixmap(pixmap64);

    data_name =":/image_data/"+QString::number(pic4[4])+".jpg";
    QPixmap pixmap65(data_name);
    pixmap65 = pixmap65.scaled(ui->label_65->size(), Qt::KeepAspectRatio);
    ui->label_65->setPixmap(pixmap65);

    data_name =":/image_data/"+QString::number(pic4[5])+".jpg";
    QPixmap pixmap66(data_name);
    pixmap66 = pixmap66.scaled(ui->label_66->size(), Qt::KeepAspectRatio);
    ui->label_66->setPixmap(pixmap66);
}

bool Form0::eventFilter(QObject *watched, QEvent *evn)
{
    static int press_x;
    static int press_y;
    static int relea_x;
    static int relea_y;

    if(gate == 0 ){
        switch(change){
            case 0:
                onSecondShow();
                qDebug() << "沒有變爻";
                ui->label_18->setText("以本卦卦辭來解卦");
                break;
            case 1:
                onFirstShow(0);
                qDebug() << "有1變爻";
                ui->label_18->setText("以本卦變爻來解卦");
                break;
            case 2:
                onFirstShow(0);
                qDebug() << "有2變爻";
                ui->label_18->setText("以本卦兩個變爻來解卦");
                break;
            case 3:
                onSecondShow();
                qDebug() << "有3變爻";
                ui->label_18->setText("以本卦卦辭和變卦卦辭來解卦\n本卦為現在，變卦為趨向");
                break;
            case 4:
                onFirstShow(1);
                qDebug() << "有4變爻";
                ui->label_18->setText("以變卦無變爻者為解\n上爻為現在，下爻為趨勢");
                break;
            case 5:
                onFirstShow(1);
                qDebug() << "有5變爻";
                ui->label_18->setText("以變卦無變爻為解");
                break;
            case 6:
                onSecondShow();
                qDebug() << "有6變爻";
                ui->label_18->setText("乾/坤以本卦卦辭\n其他以變卦卦辭解");
                break;
        }
        if(change>=1){
            QString all_change = "變爻位置: ";
            for(int i =0;i<change;i++){
                    switch( change_set[i].digitValue() ) {
                        case 1:
                            all_change+="初";
                            break;
                        case 2:
                            all_change+="二";
                            break;
                        case 3:
                            all_change+="三";
                            break;
                        case 4:
                            all_change+="四";
                            break;
                        case 5:
                            all_change+="五";
                            break;
                        case 6:
                            all_change+="上";
                            break;
                    }
                    all_change+=' ';
            }
            ui->label_19->setText(all_change);
        }
        gua_nameShow();

        onthirdShow(gua,bian_gua,hu_gua,cuo_gua,zong_gua);

        //ui->label_11->setText(QString("%1").arg(gua[5]));
//        ui->label_12->setText(QString("%1").arg(gua[4]));
//        ui->label_13->setText(QString("%1").arg(gua[3]));
//        ui->label_14->setText(QString("%1").arg(gua[2]));
//        ui->label_15->setText(QString("%1").arg(gua[1]));
//        ui->label_16->setText(QString("%1").arg(gua[0]));

        //ui->label_17->setText(line);

//        ui->label_31->setText(QString("%1").arg(bian_gua[5]));
//        ui->label_32->setText(QString("%1").arg(bian_gua[4]));
//        ui->label_33->setText(QString("%1").arg(bian_gua[3]));
//        ui->label_34->setText(QString("%1").arg(bian_gua[2]));
//        ui->label_35->setText(QString("%1").arg(bian_gua[1]));
//        ui->label_36->setText(QString("%1").arg(bian_gua[0]));
        ui->label_38->setText("事情日後發展的結果");

//        ui->label_41->setText(QString("%1").arg(hu_gua[5]));
//        ui->label_42->setText(QString("%1").arg(hu_gua[4]));
//        ui->label_43->setText(QString("%1").arg(hu_gua[3]));
//        ui->label_44->setText(QString("%1").arg(hu_gua[2]));
//        ui->label_45->setText(QString("%1").arg(hu_gua[1]));
//        ui->label_46->setText(QString("%1").arg(hu_gua[0]));
        ui->label_48->setText("為事情發展的過程");

//        ui->label_51->setText(QString("%1").arg(cuo_gua[5]));
//        ui->label_52->setText(QString("%1").arg(cuo_gua[4]));
//        ui->label_53->setText(QString("%1").arg(cuo_gua[3]));
//        ui->label_54->setText(QString("%1").arg(cuo_gua[2]));
//        ui->label_55->setText(QString("%1").arg(cuo_gua[1]));
//        ui->label_56->setText(QString("%1").arg(cuo_gua[0]));
        ui->label_58->setText("反面(相對應)的角度\n看待事情發展");

//        ui->label_61->setText(QString("%1").arg(zong_gua[5]));
//        ui->label_62->setText(QString("%1").arg(zong_gua[4]));
//        ui->label_63->setText(QString("%1").arg(zong_gua[3]));
//        ui->label_64->setText(QString("%1").arg(zong_gua[2]));
//        ui->label_65->setText(QString("%1").arg(zong_gua[1]));
//        ui->label_66->setText(QString("%1").arg(zong_gua[0]));
        ui->label_68->setText("從另外一個角度來\n思考所占測的事情");

        gate =1;
    }


    QMouseEvent *event = static_cast<QMouseEvent *>(evn);

    if (event->type() == QEvent::MouseButtonPress) {
        press_x = event->globalX();
        press_y = event->globalY();
        //qDebug() << "!!";
    }

    if (event->type() == QEvent::MouseButtonRelease) {
        relea_x = event->globalX();
        relea_y = event->globalY();
        //qDebug() << "!";
    }


    if ((relea_x - press_x) > 20 && event->type() == QEvent::MouseButtonRelease && qAbs(relea_y - press_y)<50) {
        int current_page = ui->stackedWidget->currentIndex();
        if (current_page > 0 ) {
            qDebug() << "右滑!";
            page_num--;

            ui->label_page_name->setText(QString("頁碼:  %1/5").arg(page_num));

            ui->stackedWidget->setCurrentIndex(current_page - 1);
        }
    }

    if ((press_x- relea_x ) > 20 && event->type() == QEvent::MouseButtonRelease && qAbs(relea_y - press_y)<50) {
        int current_page = ui->stackedWidget->currentIndex();
        if (current_page <= 3  ) {
            page_num++;
            qDebug() << "左滑!";
            //for (int i = 0; i < 6; ++i) { qDebug() << gua[i]; }

            ui->label_page_name->setText(QString("頁碼:  %1/5").arg(page_num));

            ui->stackedWidget->setCurrentIndex(current_page + 1);
        }
    }

    return QWidget::eventFilter(watched, event);
}
