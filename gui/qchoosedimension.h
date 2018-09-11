#ifndef QCHOOSEDIMENSION_H
#define QCHOOSEDIMENSION_H
#include <QWidget>
#include"gui/qchoosedimensionbutton.h"
class ChooseDimensionButton;

class QChooseDimension : public QWidget
{
    Q_OBJECT
public:
    explicit QChooseDimension(QWidget *parent = 0);
    int getDimension();
    QChooseDimensionButton* getQChooseDimensionButton() const;
    QChooseDimensionButton* getbutton1() const;
    QChooseDimensionButton* getbutton2() const;
    QChooseDimensionButton* getbutton3() const;
signals:

public slots:
    void setchosen();
private:
    QChooseDimensionButton* ChooseDimension1;
    QChooseDimensionButton* ChooseDimension2;
    QChooseDimensionButton* ChooseDimension3;
    void setDimension4();
    void setDimension5();
    void setDimension6();
};
#endif // QCHOOSEDIMENSION_H
