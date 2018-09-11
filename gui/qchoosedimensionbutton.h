#ifndef QCHOOSEDIMENSIONBUTTON_H
#define QCHOOSEDIMENSIONBUTTON_H
#include <QLabel>
class QChooseDimensionButton : public QLabel
{
    Q_OBJECT
public:
    QChooseDimensionButton( QWidget* parent = 0,int dimension=4 );

signals:
    void clicked();

public slots:

protected:
    void mousePressEvent(QMouseEvent* event);

};
#endif // QCHOOSEDIMENSIONBUTTON_H
