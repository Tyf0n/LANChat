#include "lanchatwindow.h"
#include "ui_lanchatwindow.h"

#include "net/peerfinder.h"

LANChatWindow::LANChatWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LANChatWindow)
{
    ui->setupUi(this);

    PeerFinder *finder = new PeerFinder(this);

    finder->start();
}

LANChatWindow::~LANChatWindow()
{
    delete ui;
}
