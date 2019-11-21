#ifndef BOARDWINDOW_H
#define BOARDWINDOW_H

#include <QMainWindow>

namespace Ui {
class BoardWindow;
}

class BoardWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BoardWindow(QWidget *parent = nullptr);
    ~BoardWindow();

private:
    Ui::BoardWindow *ui;
};

#endif // BOARDWINDOW_H
