#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>
#include <cmath>

//*******************************************************************************
//*																				*
//*																				*
//*		MULTIMEDIA UNIVERSITY -	FACULTY OF INFORMATION SCIENCE AND TECHNOLOGY	*
//*																				*
//*						TAC 3121	APPLIED CRYPTOGRAPHY						*
//*																				*
//*																				*
//*																				*
//*				Coded By	-	Timothy Lam Casem	1142700462					*
//*																				*
//*				Team Member	-	Teoh Jie Sheng		1142702368					*
//*							-	Lim Wei Lun			1142701007					*
//*							-	Tan Wei Hong		1151303044					*
//*							-	Tan Ji Kang			1142701189					*
//*																				*
//*																				*
//*																				*
//*******************************************************************************

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	n = 0, e = 0, d = 0, p = 0, q = 0, phi_n = 0;
	ui->setupUi(this);

	//Set Window Title
	this->setWindowTitle("RSA Encryption Scheme");

	//Set allowed characters to be: a to z, A to Z, 0 to 9, special characters: ,.?:'"!@#$%^&*() and space ' '
	ui->lineEdit_plaintext->setValidator(new QRegExpValidator(QRegExp("^[A-Za-z0-9? .,?:!@#$%^&*()\"']+$"), this));

	//Set Placeholder text
	ui->lineEdit_plaintext->setPlaceholderText("Enter some text...");

	//Disabling Input fields: Users should only be able to enter plaintext to encrypt or ciphertext to decrypt
    ui->lineEdit_publickey->setEnabled(false);
    ui->lineEdit_ciphertext->setEnabled(false);
    ui->pushButton_encrypt->setEnabled(false);
	ui->pushButton_decrypt->setEnabled(false);
	ui->lineEdit_decryptedtext->setEnabled(false);

	//Set Tooltip or Hover text for decrypted text field
	ui->lineEdit_decryptedtext->setToolTip("Auto Capitalization Enabled for Decrypted Text!");

	//Focus the user cusor to the input plaintext field
	ui->pushButton_key->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_exit_clicked()
{
    //Close window if this is triggered
    this->close();
}

void MainWindow::on_pushButton_key_clicked()
{
	//Change the button text to indicate generating key
	//Disable Generate Key button while it is generating key
	ui->pushButton_key->setText("Generating ...");
	ui->pushButton_key->setEnabled(false);

	//Apply a random seed for qrand() using millisecond since 1970 for a better randomized number
    qsrand(QTime::currentTime().msec());

	//Nested do while loop
	do
	{
		//Give p and q random number with qrand
		//p cannot be smaller than 2 as those will not be prime number
		//We will check if it is prime number with primecheck(int)
		//If primecheck(int) fails, repeat
		//We will need to mod it with 7 and 14 as we have low computational power
		//Low computational power the result of us modding p with 7
		do
		{
			p = qrand() % 7;
		}while (p < 2 || !primecheck(p));

		//Almost similar when generating random number q
		//But we will mod q with 14 not 7 like previously with P to let Q has a few more possible prime number, 7, 11 and 13
		//Because we do not want P and Q to be the same value
		//If P and Q are the same value, euler totient function formula that needs to be used is P^e - P^(e-1)
		//But our euler totient function to find phi(N) is only phi(N) = (P - 1)(Q - 1)
		//Also, if P and Q are the same, we cannot encrypt M with values that are factor of P or Q
		//Example: P = 7 Q = 7, N = P*Q = 49 and phi(N) = 7^2 - 7^1 = 42
		//We let e = 5 then D will be 17 as 5(17) = 1 mod 42
		//We will be restricted for our M as plaintext to be encrypted eith: (M^e mod N) cannot be factors of P which are 7, 14, 21 and so on
		//Those disqualified numbers will clash with our encoders for characters below, thus we will not allow P = Q
		do
		{
			q = qrand() % 14;
		}while (q < 2 || !primecheck(q) || p == q);

		//We will set a previous N variable to allow our key generation to be more dynamic
		//To let our key generation function to display different result from previous generated key
		if (n > 54)
			prevN = n;

		//Obtain n by p * q
		n = p * q;

		//Obtain phi_n by p - 1 and q - 1
		phi_n = (p - 1) * (q - 1);

		//We will repeat if n is smaller than 55 because our encoder that the values of 2 to 54
		//This is because in RSA, M must be smaller than N. M < N
		//We will also repeat if previous N is same as current N
	}while (n < 54 || prevN == n);

	do
	{
		//Get the value of e with qrand
		//As the computer limitation, our highest value of e is set to mod 10
		//We will repeat if e is equal or smaller than 3 as it can cause problems
		//We will also check GCD(e, phi(N)) with euclideancheck(int, int) function and repeat the loop if it fails GCD(e, phi(N)) = 1
		//This will also repeat if e is larger than phi(N) as 1 < e < phi(N)
		do
		{
			e = qrand() % 10;
			e = e % phi_n;
		}while (e <= 3 || !euclideancheck(e, phi_n) || e > phi_n);

		//This will find d from e
		//Formula: d = e^-1 mod phi(n)
		// X and Y variables will be needed in the extended euclidean algorithm to store the coefficient of values
		int x = 0, y = 0;
		multiplicationinversecheck(e, phi_n, &x, &y);

		//After finding the inverse of e with multiplicationinversecheck function, we will get X as the multiplicative inverse
		//The variable Y will be 0 as extended euclidean algorithm will mod phi(N)

		//But, the D might be negative, we will want the minimal positive value for D
		//Therefore, we perform this operation below
		//Add the phi(N) to D and modulus it again
		//Then we will achieve our positive minimal value for D
		d = (x + phi_n) % phi_n;

		//We will repeat this loop if D is smaller than 2 or larger than 14 as it will make exponentiation result extremely huge for C++ native data type (unsigned long long) size of 2^8
		//We will also repeat if taking the largest value of our encoder and perform encryption and decryption using the generated e, d and N will gives us infinity number of NAN value
		//This is not likely to happen anymore as we modded our P, Q, and e to a much smaller number
	}while ((std::isinf((unsigned long long int)pow(((unsigned long long int)pow(54, e) % n), d)) || std::isnan((unsigned long long int)pow(((unsigned long long int)pow(54, e) % n), d))) || d < 2 || d >= 15);

	//Display at the GUI the public key (e,N)
    QString publickey = "Public Key(";
	publickey.append(QString::number(e) + ", " + QString::number(n) + ")");
	ui->lineEdit_publickey->setText(publickey);

	//We can now enable encryption and decryption button if their respective fields are not empty
	if (ui->lineEdit_plaintext->text() != "" || ui->lineEdit_plaintext->text() != NULL)
		ui->pushButton_encrypt->setEnabled(true);
	if (ui->lineEdit_decrypttext->text() != "" || ui->lineEdit_decrypttext->text() != NULL)
		ui->pushButton_decrypt->setEnabled(true);

	//Restore the button's original label
	//Enable the generate key button after the current key generation proccess has completed
	ui->pushButton_key->setText("Generate Key");
	ui->pushButton_key->setEnabled(true);
}

//Check for prime numbers and return true if the paramater given is a prime number else return false
bool MainWindow::primecheck(unsigned long long check)
{
	//To check a number n, we only need to check from 3 to N / 2
	unsigned long long int half = check / 2;

	//If it is divisible by 2, it is not a prime number thus we return false
	if (check % 2 == 0)
        return false;

	//We will loop through by +2 interation skipping even numbers
	for (unsigned int i = 3; i < half; i = i + 2)
    {
		if (check % i == 0)
            return false;
    }
    return true;
}

//Euchlidean check for two given values whether their GCD(X, Y) equals to one and return true else return false
bool MainWindow::euclideancheck(unsigned long long int check, unsigned long long int phi_n)
{
	unsigned long long int result = 0;

	//We we perform the euclidean algorithm
	//We recursively mod it till the last number is 0
    while (check != 0)
    {
		result = phi_n % check;
        phi_n = check;
        check = result;
	}

	//If GCD(check, phi_n) = 1 then we will return true else false
    if (phi_n == 1)
        return true;
    else
        return false;
}

//This function will find the multiplicative inverse of e mod n
//The number n will be larger than the number e
//At the end, the variable X that is passed by reference will contain our multiplicative inverse
void MainWindow::multiplicationinversecheck(unsigned long long int e, unsigned long long int n, int *x, int *y)
{
	//If e and n is relatively prime, GCD(e, n) = 1
	//And euclidean algorithm has reached the end then return the function so we can proceed to extended euclidean algorithm
	if (e == 0)
	{
		*x = 0, *y = 1;
		return;
	}

	//We will need these variable for our extended euclidean algorithm
	//This x1 and y1 will store the co-efficient of previous equation
	//X and Y that is calculated at line 214 and 215 will be the co-efficient value of current equation
	int x1 = 0, y1 = 0;
	//We perform recursive operation as extended euclidean algorithm contains recursive operation
	multiplicationinversecheck(n % e, e, &x1, &y1);

	//Here is where we calculate X which is the co-efficient of the smallest value in extended euclidean algorithm
	//For y, it will be the co-efficient of largest value
	*x = y1 - (n / e) * x1;
	*y = x1;
}

//The function to encrypt the plaintext
//Plaintext must not be zero or larger than n, as we have use Regular Expression to validate our plaintext input fields
void MainWindow::on_pushButton_encrypt_clicked()
{
	//Formula: C = M^e mod N
	//Clear the line field to input the ciphertext
	ui->lineEdit_ciphertext->clear();

	//Obtain the plaintext
	plainText = ui->lineEdit_plaintext->text();

	//We will encode the plaintext here using encoder() and the encoded values will be stored in plainTextEncoded
	encoder();

	//We take each plaintext and power it to e and mod n
	cipherTextEncoded.clear();
	for (int i = 0; i < plainTextEncoded.size(); i++)
	{
		cipherTextEncoded += (unsigned long long int)pow(plainTextEncoded.at(i), e) % n;
	}

	//Display the ciphertext (encrypted plaintext) at our GUI
	QString currentciphertextText;
	for (int i = 0; i < cipherTextEncoded.size(); i++)
	{
		currentciphertextText = ui->lineEdit_ciphertext->text();
		ui->lineEdit_ciphertext->setText(currentciphertextText + QString::number(cipherTextEncoded.at(i)) + " ");
		ui->lineEdit_decrypttext->setText(currentciphertextText + QString::number(cipherTextEncoded.at(i)) + " ");
	}
	//Remove the extra space at last character
	QString ciphertextreset = ui->lineEdit_ciphertext->text();
	ciphertextreset.chop(1);
	ui->lineEdit_ciphertext->setText(ciphertextreset);
	ui->lineEdit_decrypttext->setText(ciphertextreset);

	//Enabling the decrypt button after encryption completes
	ui->pushButton_decrypt->setEnabled(true);
}

//This is where we will perform our decryption
void MainWindow::on_pushButton_decrypt_clicked()
{
	//Formula: M = C^d mod n
	//Clear the linefield to input our decrypted text
	ui->lineEdit_decryptedtext->clear();

	//Get the ciphertext
	cipherText = ui->lineEdit_decrypttext->text();

	//After getting the ciphertext, we split them with ' ' space
	cipherTextDecode.clear();
	QStringList cipherTextToDecode = cipherText.split(' ');

	//We will decrypt those ciphertext with P = C^d mod N
	for (int i = 0; i < cipherTextToDecode.size(); i++)
	{
		cipherTextDecode += fmod(pow(cipherTextToDecode.at(i).toInt(), d), n);
	}

	//We will run our decoder after decrypting the values
	decoder();


	//Lastly, we display the decrypted ciphertext at our GUI
	for (int i = 0; i < plainTextDecoded.size(); i++)
	{
		if ((plainTextDecoded.at(i).at(0).isLetter() && i > 0 && plainTextDecoded.at(i - 1).at(0).isSpace()) || (i == 0 && plainTextDecoded.at(i).at(0).isLetter()))
			ui->lineEdit_decryptedtext->setText(ui->lineEdit_decryptedtext->text() + plainTextDecoded.at(i).toUpper());
		else
			ui->lineEdit_decryptedtext->setText(ui->lineEdit_decryptedtext->text() + plainTextDecoded.at(i));
	}
}

void MainWindow::encoder()
{
	plainTextEncoded.clear();
	for (int i = 0; i < plainText.size(); i++)
	{
		//Declare a Char variable that store the current alphabet in small letter
		char plainTextChar;

		//If the character at position "i" is a letter then we will convert it to small capital letter before processing
		//If it is non-letter, we will not convert it to char
		if (plainText.at(i).isLetter())
			plainTextChar = plainText.at(i).toLower().toLatin1();
		else
			plainTextChar = plainText.at(i).toLatin1();

		//Encoding starts
		switch (plainTextChar)
		{
			case 'a':
				plainTextEncoded += 2;
				break;
			case 'b':
				plainTextEncoded += 3;
				break;
			case 'c':
				plainTextEncoded += 4;
				break;
			case 'd':
				plainTextEncoded += 5;
				break;
			case 'e':
				plainTextEncoded += 6;
				break;
			case 'f':
				plainTextEncoded += 7;
				break;
			case 'g':
				plainTextEncoded += 8;
				break;
			case 'h':
				plainTextEncoded += 9;
				break;
			case 'i':
				plainTextEncoded += 10;
				break;
			case 'j':
				plainTextEncoded += 11;
				break;
			case 'k':
				plainTextEncoded += 12;
				break;
			case 'l':
				plainTextEncoded += 13;
				break;
			case 'm':
				plainTextEncoded += 14;
				break;
			case 'n':
				plainTextEncoded += 15;
				break;
			case 'o':
				plainTextEncoded += 16;
				break;
			case 'p':
				plainTextEncoded += 17;
				break;
			case 'q':
				plainTextEncoded += 18;
				break;
			case 'r':
				plainTextEncoded += 19;
				break;
			case 's':
				plainTextEncoded += 20;
				break;
			case 't':
				plainTextEncoded += 21;
				break;
			case 'u':
				plainTextEncoded += 22;
				break;
			case 'v':
				plainTextEncoded += 23;
				break;
			case 'w':
				plainTextEncoded += 24;
				break;
			case 'x':
				plainTextEncoded += 25;
				break;
			case 'y':
				plainTextEncoded += 26;
				break;
			case 'z':
				plainTextEncoded += 27;
				break;
			case '0':
				plainTextEncoded += 28;
				break;
			case '1':
				plainTextEncoded += 29;
				break;
			case '2':
				plainTextEncoded += 30;
				break;
			case '3':
				plainTextEncoded += 31;
				break;
			case '4':
				plainTextEncoded += 32;
				break;
			case '5':
				plainTextEncoded += 33;
				break;
			case '6':
				plainTextEncoded += 34;
				break;
			case '7':
				plainTextEncoded += 35;
				break;
			case '8':
				plainTextEncoded += 36;
				break;
			case '9':
				plainTextEncoded += 37;
				break;
			case ' ':
				plainTextEncoded += 38;
				break;
			case '.':
				plainTextEncoded += 39;
				break;
			case ',':
				plainTextEncoded += 40;
				break;
			case '?':
				plainTextEncoded += 41;
				break;
			case ':':
				plainTextEncoded += 42;
				break;
			case '!':
				plainTextEncoded += 43;
				break;
			case '@':
				plainTextEncoded += 44;
				break;
			case '#':
				plainTextEncoded += 45;
				break;
			case '$':
				plainTextEncoded += 46;
				break;
			case '%':
				plainTextEncoded += 47;
				break;
			case '^':
				plainTextEncoded += 48;
				break;
			case '&':
				plainTextEncoded += 49;
				break;
			case '*':
				plainTextEncoded += 50;
				break;
			case '(':
				plainTextEncoded += 51;
				break;
			case ')':
				plainTextEncoded += 52;
				break;
			case '"':
				plainTextEncoded += 53;
				break;
			case '\'':
				plainTextEncoded += 54;
				break;
			default:
				break;
		}
	}
}

//Our decoder
void MainWindow::decoder()
{
	plainTextDecoded.clear();
	for (int i = 0; i < cipherTextDecode.size(); i++)
	{
		//Declare a int variable that store the current ciphertext value
		int plainTextChar = cipherTextDecode.at(i);

		switch (plainTextChar)
		{
			case 2:
				plainTextDecoded += "a";
				break;
			case 3:
				plainTextDecoded += "b";
				break;
			case 4:
				plainTextDecoded += "c";
				break;
			case 5:
				plainTextDecoded += "d";
				break;
			case 6:
				plainTextDecoded += "e";
				break;
			case 7:
				plainTextDecoded += "f";
				break;
			case 8:
				plainTextDecoded += "g";
				break;
			case 9:
				plainTextDecoded += "h";
				break;
			case 10:
				plainTextDecoded += "i";
				break;
			case 11:
				plainTextDecoded += "j";
				break;
			case 12:
				plainTextDecoded += "k";
				break;
			case 13:
				plainTextDecoded += "l";
				break;
			case 14:
				plainTextDecoded += "m";
				break;
			case 15:
				plainTextDecoded += "n";
				break;
			case 16:
				plainTextDecoded += "o";
				break;
			case 17:
				plainTextDecoded += "p";
				break;
			case 18:
				plainTextDecoded += "q";
				break;
			case 19:
				plainTextDecoded += "r";
				break;
			case 20:
				plainTextDecoded += "s";
				break;
			case 21:
				plainTextDecoded += "t";
				break;
			case 22:
				plainTextDecoded += "u";
				break;
			case 23:
				plainTextDecoded += "v";
				break;
			case 24:
				plainTextDecoded += "w";
				break;
			case 25:
				plainTextDecoded += "x";
				break;
			case 26:
				plainTextDecoded += "y";
				break;
			case 27:
				plainTextDecoded += "z";
				break;
			case 28:
				plainTextDecoded += "0";
				break;
			case 29:
				plainTextDecoded += "1";
				break;
			case 30:
				plainTextDecoded += "2";
				break;
			case 31:
				plainTextDecoded += "3";
				break;
			case 32:
				plainTextDecoded += "4";
				break;
			case 33:
				plainTextDecoded += "5";
				break;
			case 34:
				plainTextDecoded += "6";
				break;
			case 35:
				plainTextDecoded += "7";
				break;
			case 36:
				plainTextDecoded += "8";
				break;
			case 37:
				plainTextDecoded += "9";
				break;
			case 38:
				plainTextDecoded += " ";
				break;
			case 39:
				plainTextDecoded += ".";
				break;
			case 40:
				plainTextDecoded += ",";
				break;
			case 41:
				plainTextDecoded += "?";
				break;
			case 42:
				plainTextDecoded += ":";
				break;
			case 43:
				plainTextDecoded += "!";
				break;
			case 44:
				plainTextDecoded += "@";
				break;
			case 45:
				plainTextDecoded += "#";
				break;
			case 46:
				plainTextDecoded += "$";
				break;
			case 47:
				plainTextDecoded += "%";
				break;
			case 48:
				plainTextDecoded += "^";
				break;
			case 49:
				plainTextDecoded += "&";
				break;
			case 50:
				plainTextDecoded += "*";
				break;
			case 51:
				plainTextDecoded += "(";
				break;
			case 52:
				plainTextDecoded += ")";
				break;
			case 53:
				plainTextDecoded += "\"";
				break;
			case 54:
				plainTextDecoded += "'";
				break;
			default:
				break;
		}
	}
}

//Event when ciphertext field's text has changed
void MainWindow::on_lineEdit_decrypttext_textChanged(const QString &arg1)
{
	//Enabling the decrypt button when the field is not empty
	//Also check if generate key button is pressed (if d is 0), if not then do not enable the button
	if ((arg1 != "" || arg1 != NULL) && d != 0)
		ui->pushButton_decrypt->setEnabled(true);
	else
		ui->pushButton_decrypt->setEnabled(false);
}

//Event when plaintext field's text has changed
void MainWindow::on_lineEdit_plaintext_textChanged(const QString &arg1)
{
	//Enabling the encrypt button when the field is not empty
	//Also check if generate key button is pressed (if e is 0), if not then do not enable the button
	if ((arg1 != "" || arg1 != NULL) && e != 0)
		ui->pushButton_encrypt->setEnabled(true);
	else
		ui->pushButton_encrypt->setEnabled(false);
}
