#ifndef QRESETBUTTON_H
#define QRESETBUTTON_H

#include <QLabel>

class QButton : public QLabel
{
    Q_OBJECT
public:
    QButton( QWidget* parent = 0);
    void settext(int a);

signals:
    void clicked();//用于触发信号槽

public slots:

protected:
    void mousePressEvent(QMouseEvent* event);

};

#endif // QRESETBUTTON_H
