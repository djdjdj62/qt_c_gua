#ifndef FORM0_H
#define FORM0_H

#include <QWidget>
#include <QMainWindow>
#include <QDebug>

#include <QApplication>
#include <QWidget>
#include <QEvent>
#include <QMouseEvent>
#include <string>

class MainWindow;

extern int gua[6]; //以占卜出的密碼
extern int bian_gua[6];
extern int hu_gua[6];
extern int cuo_gua[6];
extern int zong_gua[6];

extern int gate;
extern int page_num;
extern QString change_set;
extern int change;

namespace Ui {
class Form0;
}

class Form0 : public QWidget
{
    Q_OBJECT


    public:
        explicit Form0(QWidget *parent = nullptr);
        ~Form0();

    private slots:
        void on_pushButton_2_clicked();
        void onFirstShow(int);
        void onSecondShow();
        void onthirdShow(int pic0[6],int pic1[6],int pic2[6],int pic3[6],int pic4[6]);
        void gua_nameShow();
        std::string load_data_name(int arr[6]);

    protected:
        bool eventFilter(QObject *watched, QEvent *event);

    private:
        Ui::Form0 *ui;
        MainWindow * main_window ;
};

#endif // FORM0_H
