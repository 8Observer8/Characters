#include <QDebug>
#include <QMessageBox>
#include "Dialog.h"
#include "ui_Dialog.h"

enum Character {
    AllCharacters, Cat, Dog
};

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    // Open a database
    database = QSqlDatabase::addDatabase( "QSQLITE" );
    path = QDir::currentPath() + QString("/Characters.sqlite");
    database.setDatabaseName( path );
    database.open();

    model = new QSqlRelationalTableModel( this );
    showAllCharacters();

    ui->charactersComboBox->addItem( "Все персонажи", AllCharacters );
    ui->charactersComboBox->addItem( "Кошка", Cat );
    ui->charactersComboBox->addItem( "Собака", Dog );
}

Dialog::~Dialog()
{
    database.close();
    delete ui;
}

void Dialog::on_charactersComboBox_currentIndexChanged( int index )
{
    Character character = static_cast<Character>( ui->charactersComboBox->currentData().toInt() );

    switch ( character ) {
        case AllCharacters:
            showAllCharacters();
            break;
        case Cat:
            showCat();
            break;
        case Dog:
            showDog();
            break;
        default:
            QMessageBox::information( this, tr( "Сообщение" ), tr( "Неизвестный пункт" ) );
            break;
    }
}

void Dialog::showAllCharacters()
{
    if ( !database.isOpen() ) {
        QMessageBox::information( this, tr( "Сообщение" ),
                                  tr( "База данных не открылась. Проверьте наличия файла \"%1\"" ).arg( path ) );
    }

    delete model;
    model = new QSqlTableModel( this );
    model->setTable("CharactersTable");
    model->select();
    model->setEditStrategy( QSqlTableModel::OnRowChange );
    ui->tableView->setModel( model );

    model->setHeaderData( 0, Qt::Horizontal, tr( "Номер" ) );
    model->setHeaderData( 1, Qt::Horizontal, tr( "Персонаж" ) );
    model->setHeaderData( 2, Qt::Horizontal, tr( "Количество" ) );
}

void Dialog::showCat()
{
    if ( !database.isOpen() ) {
        QMessageBox::information( this, tr( "Сообщение" ),
                                  tr( "База данных не открылась. Проверьте наличия файла \"%1\"" ).arg( path ) );
    }

    delete model;
    model = new QSqlTableModel( this );
    model->setTable("CatTable");
    model->select();
    model->setEditStrategy(QSqlTableModel::OnRowChange);
    ui->tableView->setModel(model);

    model->setHeaderData( 0, Qt::Horizontal, tr( "Номер" ) );
    model->setHeaderData( 1, Qt::Horizontal, tr( "Царство" ) );
    model->setHeaderData( 2, Qt::Horizontal, tr( "Тип" ) );
    model->setHeaderData( 3, Qt::Horizontal, tr( "Класс" ) );
    model->setHeaderData( 4, Qt::Horizontal, tr( "Отряд" ) );
    model->setHeaderData( 5, Qt::Horizontal, tr( "Семейство" ) );
    model->setHeaderData( 6, Qt::Horizontal, tr( "Род" ) );
    model->setHeaderData( 7, Qt::Horizontal, tr( "Вид" ) );
}

void Dialog::showDog()
{
    if ( !database.isOpen() ) {
        QMessageBox::information( this, tr( "Сообщение" ),
                                  tr( "База данных не открылась. Проверьте наличия файла \"%1\"" ).arg( path ) );
    }

    delete model;
    model = new QSqlTableModel( this );
    model->setTable("DogTable");
    model->select();
    model->setEditStrategy(QSqlTableModel::OnRowChange);
    ui->tableView->setModel(model);

    model->setHeaderData( 0, Qt::Horizontal, tr( "Номер" ) );
    model->setHeaderData( 1, Qt::Horizontal, tr( "Царство" ) );
    model->setHeaderData( 2, Qt::Horizontal, tr( "Тип" ) );
    model->setHeaderData( 3, Qt::Horizontal, tr( "Класс" ) );
    model->setHeaderData( 4, Qt::Horizontal, tr( "Отряд" ) );
    model->setHeaderData( 5, Qt::Horizontal, tr( "Семейство" ) );
    model->setHeaderData( 6, Qt::Horizontal, tr( "Род" ) );
    model->setHeaderData( 7, Qt::Horizontal, tr( "Вид" ) );
}
