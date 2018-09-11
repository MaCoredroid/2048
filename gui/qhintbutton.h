#ifndef QHINTBUTTON_H
#define QHINTBUTTON_H

#include <QLabel>
class QHintButton : public QLabel
{
    Q_OBJECT
public:
    QHintButton( QWidget* parent = 0);

signals:
    void clicked();//用于触发信号槽

public slots:

protected:
    void mousePressEvent(QMouseEvent* event);

};

#endif // QHINTBUTTON_H
