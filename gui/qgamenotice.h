#ifndef QGAMEOVER_H
#define QGAMEOVER_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>
#include <QResizeEvent>
#include <string>
class QButton;

class QGameNotice : public QWidget
{
    Q_OBJECT
public:
    QGameNotice(QWidget *parent=0);
    QButton* getBtn() const;//获取指向resetbutton的指针，用于信号槽
    void notice(int a);

signals:

public slots:

private:
    QButton* reset;//指向resetbutton的指针
    QVBoxLayout *layout;

};

#endif // QGAMEOVER_H
