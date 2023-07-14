#ifndef CARPLAY_H
#define CARPLAY_H


#include <QMainWindow>
#include <QWidget>


class MainWindow;

namespace Ui {
class Carplay;
}

class Carplay : public QWidget
{
    Q_OBJECT

public:
    explicit Carplay(QWidget *parent = nullptr);
    ~Carplay();

private:
    Ui::Carplay *ui;
    MainWindow * main_window ;
};

#endif // CARPLAY_H
