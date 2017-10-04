/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *lineEdit_publickey;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit_plaintext;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;
    QLineEdit *lineEdit_ciphertext;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_4;
    QLineEdit *lineEdit_decrypttext;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_5;
    QLineEdit *lineEdit_decryptedtext;
    QVBoxLayout *verticalLayout_8;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_key;
    QPushButton *pushButton_encrypt;
    QPushButton *pushButton_decrypt;
    QPushButton *pushButton_exit;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(652, 515);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_6 = new QVBoxLayout(centralWidget);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setFamily(QStringLiteral("Candara"));
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);

        verticalLayout->addWidget(label);

        lineEdit_publickey = new QLineEdit(centralWidget);
        lineEdit_publickey->setObjectName(QStringLiteral("lineEdit_publickey"));
        QFont font1;
        font1.setPointSize(10);
        lineEdit_publickey->setFont(font1);

        verticalLayout->addWidget(lineEdit_publickey);


        verticalLayout_5->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);

        verticalLayout_2->addWidget(label_2);

        lineEdit_plaintext = new QLineEdit(centralWidget);
        lineEdit_plaintext->setObjectName(QStringLiteral("lineEdit_plaintext"));
        lineEdit_plaintext->setFont(font1);

        verticalLayout_2->addWidget(lineEdit_plaintext);


        verticalLayout_5->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font);

        verticalLayout_3->addWidget(label_3);

        lineEdit_ciphertext = new QLineEdit(centralWidget);
        lineEdit_ciphertext->setObjectName(QStringLiteral("lineEdit_ciphertext"));
        lineEdit_ciphertext->setFont(font1);

        verticalLayout_3->addWidget(lineEdit_ciphertext);


        verticalLayout_5->addLayout(verticalLayout_3);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font);

        verticalLayout_7->addWidget(label_4);

        lineEdit_decrypttext = new QLineEdit(centralWidget);
        lineEdit_decrypttext->setObjectName(QStringLiteral("lineEdit_decrypttext"));
        lineEdit_decrypttext->setFont(font1);

        verticalLayout_7->addWidget(lineEdit_decrypttext);


        verticalLayout_5->addLayout(verticalLayout_7);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setFont(font);

        verticalLayout_4->addWidget(label_5);

        lineEdit_decryptedtext = new QLineEdit(centralWidget);
        lineEdit_decryptedtext->setObjectName(QStringLiteral("lineEdit_decryptedtext"));
        lineEdit_decryptedtext->setFont(font1);

        verticalLayout_4->addWidget(lineEdit_decryptedtext);


        verticalLayout_5->addLayout(verticalLayout_4);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_8->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(1);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout->setContentsMargins(-1, 0, -1, -1);
        pushButton_key = new QPushButton(centralWidget);
        pushButton_key->setObjectName(QStringLiteral("pushButton_key"));
        pushButton_key->setFont(font1);

        horizontalLayout->addWidget(pushButton_key);

        pushButton_encrypt = new QPushButton(centralWidget);
        pushButton_encrypt->setObjectName(QStringLiteral("pushButton_encrypt"));
        pushButton_encrypt->setFont(font1);

        horizontalLayout->addWidget(pushButton_encrypt);

        pushButton_decrypt = new QPushButton(centralWidget);
        pushButton_decrypt->setObjectName(QStringLiteral("pushButton_decrypt"));
        pushButton_decrypt->setFont(font1);

        horizontalLayout->addWidget(pushButton_decrypt);

        pushButton_exit = new QPushButton(centralWidget);
        pushButton_exit->setObjectName(QStringLiteral("pushButton_exit"));
        pushButton_exit->setFont(font1);

        horizontalLayout->addWidget(pushButton_exit);


        verticalLayout_8->addLayout(horizontalLayout);

        verticalSpacer_2 = new QSpacerItem(20, 35, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_8->addItem(verticalSpacer_2);


        verticalLayout_5->addLayout(verticalLayout_8);


        verticalLayout_6->addLayout(verticalLayout_5);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        label->setText(QApplication::translate("MainWindow", "Generated Public Key:", 0));
        label_2->setText(QApplication::translate("MainWindow", "Message to Encrypt (integers):", 0));
        label_3->setText(QApplication::translate("MainWindow", "Ciphertext (Encrypted Plaintext):", 0));
        label_4->setText(QApplication::translate("MainWindow", "Ciphertext (Encrypted Plaintext):", 0));
        label_5->setText(QApplication::translate("MainWindow", "Plaintext (Decrypted Plaintext):", 0));
        pushButton_key->setText(QApplication::translate("MainWindow", "Generate Key", 0));
        pushButton_encrypt->setText(QApplication::translate("MainWindow", "Encrypt", 0));
        pushButton_decrypt->setText(QApplication::translate("MainWindow", "Decrypt", 0));
        pushButton_exit->setText(QApplication::translate("MainWindow", "Exit", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
