#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QApplication>
#include <QFileDialog>
#include <QImageReader>
#include <QSettings>
#include <QDesktopServices>
#include <QBuffer>

MainWindow::MainWindow( QWidget * parent )
    : QMainWindow( parent ),
      ui( new Ui::MainWindow )
{
    ui->setupUi( this );

    QPalette palette = ui->scrollArea->palette();
    palette.setColor( QPalette::Background, Qt::lightGray );
    ui->scrollArea->setPalette( palette );

    updateStates();
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_tButtonSelectIcon_clicked()
{
    QString filters = tr( "Image" );
    filters += " (";
    foreach ( const QByteArray & format, QImageReader::supportedImageFormats() )
        filters += QString( " *.%1" ).arg( QString( format.toLower() ) );
    filters += " )";

    const QString & dir = QDesktopServices::storageLocation( QDesktopServices::PicturesLocation );
    const QString & fileName = QFileDialog::getOpenFileName( this, tr( "Selecting an image" ), dir, filters );
    if ( fileName.isEmpty() )
        return;

    QPixmap pixmap( fileName );
    pixmap = pixmap.scaled( QSize( 64, 64 ), Qt::KeepAspectRatio );
    ui->iconLabel->setPixmap( pixmap );
}
void MainWindow::on_tButtonOpen_clicked()
{
    const QString & fileName = QFileDialog::getOpenFileName( this, QString(), QString(), "QmInfo ( *.qminfo )\nЛюбой ( *.* )" );
    if ( fileName.isEmpty() )
        return;

    QSettings ini( fileName, QSettings::IniFormat );
    ini.setIniCodec( "utf8" );

    QByteArray byteArray = ini.value( "Icon" ).toByteArray();
    QPixmap pixmap;
    pixmap.loadFromData( byteArray );

    ui->listWidgetFiles->clear();

    ui->iconLabel->setPixmap( pixmap );
    ui->lEditNameLanguage->setText( ini.value( "Name" ).toString() );
    ui->lEditAuthor->setText( ini.value( "Author" ).toString() );
    ui->lEditContact->setText( ini.value( "Contact" ).toString() );
    ui->listWidgetFiles->addItems( ini.value( "Files" ).toStringList() );

    updateStates();
}
void MainWindow::on_tButtonSaveAs_clicked()
{
    const QString & fileName = QFileDialog::getSaveFileName( this, QString(), QString(), "QmInfo ( *.qminfo )" );
    if ( fileName.isEmpty() )
        return;

    QByteArray icon;
    QBuffer buffer( &icon );
    buffer.open( QIODevice::WriteOnly );
    ui->iconLabel->pixmap()->save( &buffer, "png" );

    QStringList files;
    for ( int i = 0; i < ui->listWidgetFiles->count(); i++ )
        files << ui->listWidgetFiles->item( i )->text();

    QSettings ini( fileName, QSettings::IniFormat );
    ini.setIniCodec( "utf8" );
    ini.setValue( "Icon", icon );
    ini.setValue( "Name", ui->lEditNameLanguage->text() );
    ini.setValue( "Author", ui->lEditAuthor->text() );
    ini.setValue( "Contact", ui->lEditContact->text() );
    ini.setValue( "Files", files );
}
void MainWindow::on_tButtonQuit_clicked()
{
    qApp->quit();
}

void MainWindow::on_listWidgetFiles_itemSelectionChanged()
{
    updateStates();
}
void MainWindow::on_tButtonAdd_clicked()
{
    const QStringList & files = QFileDialog::getOpenFileNames( this );
    if ( files.isEmpty() )
        return;

    foreach ( const QString & fileName, files )
    {
        bool original = true;
        for ( int i = 0; i < ui->listWidgetFiles->count(); i++ )
           if ( ui->listWidgetFiles->item( i )->text() == fileName )
           {
               original = false;
               break;
           }

        if ( original )
            ui->listWidgetFiles->addItem( fileName );
    }

    updateStates();
}
void MainWindow::on_tButtonRemove_clicked()
{
    foreach ( QListWidgetItem * item, ui->listWidgetFiles->selectedItems() )
    {
        ui->listWidgetFiles->removeItemWidget( item );
        delete item;
    }

    updateStates();
}
void MainWindow::on_tButtonRemoveAll_clicked()
{
    ui->listWidgetFiles->clear();

    updateStates();
}

void MainWindow::updateStates()
{
    bool isEmpty = ui->listWidgetFiles->count() == 0;
    bool hasSelection = ui->listWidgetFiles->selectionModel()->hasSelection();

    ui->tButtonRemove->setEnabled( hasSelection );
    ui->tButtonRemoveAll->setEnabled( !isEmpty );
}
