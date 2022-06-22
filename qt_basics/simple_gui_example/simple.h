//
// Description: simple gui demo header.
//

#pragma once


#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>


namespace ms::demos {
    class Simple :
        public QWidget
    {
        Q_OBJECT

    public:
        explicit
        Simple(QWidget *parent = nullptr);

        ~Simple();

    private slots:
        void
        ShowArea();

    private:
        QLabel      *label1;
        QLabel      *label2;
        QLineEdit   *lineEdit;
        QPushButton *button;
    }; // class "Simple"
} // namespace "ms::demos"
