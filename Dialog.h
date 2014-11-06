#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtSql>

namespace Ui {
    class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:

    void on_charactersComboBox_currentIndexChanged(int index);

private:
    void showAllCharacters();
    void showCat();
    void showDog();

private:
    Ui::Dialog *ui;
    QSqlDatabase database;
    QSqlTableModel *model;
    QString path;
};

#endif // DIALOG_H
