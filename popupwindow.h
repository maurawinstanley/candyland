#ifndef POPUPWINDOW_H
#define POPUPWINDOW_H

#include <QDialog>

namespace Ui {
class Popupwindow;
}

class Popupwindow : public QDialog
{
    Q_OBJECT

public:
    explicit Popupwindow(QWidget *parent = nullptr);
    ~Popupwindow();

    int get_num_players() { return num_players_; };

private slots:

    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_clicked();

private:
    Ui::Popupwindow *ui;

    int num_players_;
signals:
    // for distance
    void finish_clicked();
};

#endif // POPUPWINDOW_H
