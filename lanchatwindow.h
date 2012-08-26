#ifndef LANCHATWINDOW_H
#define LANCHATWINDOW_H

#include <QMainWindow>

namespace Ui {
class LANChatWindow;
}

class LANChatWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit LANChatWindow(QWidget *parent = 0);
    ~LANChatWindow();
    
private:
    Ui::LANChatWindow *ui;
};

#endif // LANCHATWINDOW_H
