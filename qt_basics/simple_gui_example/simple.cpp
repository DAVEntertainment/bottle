//
// Description: simple gui demo source.
//


#include "simple.h"

#include <QGridLayout>


namespace ms::demos {
    const static double PI = 3.1415926;

    Simple::Simple(QWidget *parent) :
        QWidget(parent)
    {
        label1 = new QLabel(this);
        label1->setText(tr("请输入圆的半径："));

        lineEdit = new QLineEdit(this);
        label2 = new QLabel(this);
        button = new QPushButton(this);
        button->setText(tr("显示对应圆的面积"));

        QGridLayout *mainLayout = new QGridLayout(this);
        mainLayout->addWidget(label1, 0, 0);
        mainLayout->addWidget(lineEdit, 0, 1);
        mainLayout->addWidget(label2, 1, 0);
        mainLayout->addWidget(button, 1, 1);
        setLayout(mainLayout);

        connect(button, SIGNAL(clicked()), this, SLOT(ShowArea()));
        connect(lineEdit, SIGNAL(textChanged(QString)), this, SLOT(ShowArea()));
    }

    Simple::~Simple()
    {}

    void Simple::ShowArea()
    {
        bool ok;
        QString tempStr;
        QString valueStr = lineEdit->text();
        int valueInt = valueStr.toInt(&ok);
        double area = valueInt * valueInt * PI;
        label2->setText(tempStr.setNum(area));
    }
} // namespace "ms::demos"
