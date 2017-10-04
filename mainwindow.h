#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_exit_clicked();

    void on_pushButton_key_clicked();

    void on_pushButton_encrypt_clicked();

    void on_pushButton_decrypt_clicked();

	void on_lineEdit_decrypttext_textChanged(const QString &arg1);

	void on_lineEdit_plaintext_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;

	bool primecheck(unsigned long long int check);

	bool euclideancheck(unsigned long long int check, unsigned long long int phi_n);

	unsigned long long int n, e, phi_n, p, q, prevN;

	long long int d;

	QString plainText, cipherText;

	QList<int> plainTextEncoded, cipherTextDecode, cipherTextEncoded;

	QList<QString> plainTextDecoded;

	void multiplicationinversecheck(unsigned long long e, unsigned long long int n, int *x, int *y);

	void encoder();

	void decoder();
};

#endif // MAINWINDOW_H
