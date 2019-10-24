#include "MyForm.h"


using namespace System;
using namespace System::Windows::Forms;


[STAThread]
void Main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	_2048::MyForm form;
	Application::Run(%form);
}

System::Void _2048::MyForm::render(unsigned int** model)
{
	// ���������� ����� � ��������������� ������, �� ���� ��� ����� ����, ���������� ������ ������
	this->label1->Text = model[0][0] == 0 ? "" : model[0][0].ToString();
	this->label2->Text = model[1][0] == 0 ? "" : model[1][0].ToString();
	this->label3->Text = model[2][0] == 0 ? "" : model[2][0].ToString();
	this->label4->Text = model[3][0] == 0 ? "" : model[3][0].ToString();

	this->label5->Text = model[0][1] == 0 ? "" : model[0][1].ToString();
	this->label6->Text = model[1][1] == 0 ? "" : model[1][1].ToString();
	this->label7->Text = model[2][1] == 0 ? "" : model[2][1].ToString();
	this->label8->Text = model[3][1] == 0 ? "" : model[3][1].ToString();

	this->label9->Text = model[0][2] == 0 ? "" : model[0][2].ToString();
	this->label10->Text = model[1][2] == 0 ? "" : model[1][2].ToString();
	this->label11->Text = model[2][2] == 0 ? "" : model[2][2].ToString();
	this->label12->Text = model[3][2] == 0 ? "" : model[3][2].ToString();

	this->label13->Text = model[0][3] == 0 ? "" : model[0][3].ToString();
	this->label14->Text = model[1][3] == 0 ? "" : model[1][3].ToString();
	this->label15->Text = model[2][3] == 0 ? "" : model[2][3].ToString();
	this->label16->Text = model[3][3] == 0 ? "" : model[3][3].ToString();

	return System::Void();
}

inline System::Void _2048::MyForm::MyForm_KeyPress(System::Object ^ sender, System::Windows::Forms::KeyPressEventArgs ^ e) {
	// ��������:
	// 0. ������� ������ ������, ��������� �� ������� (MyForm.h, �����������)
	// 1. ���������� ������� ������ ����������� ����
	// 2. � ����������� �� ������� �������, �������� ����� � �� ��� ���� �������
	// 3. �������� ����� � ���� �� ������

	
	// ��������� ������� ������
	// w � �����
	// s � ����
	// a � �����
	// d � ������

	switch ((char) e->KeyChar) {

	case 'w':
	case 70:
		
		for (unsigned int col = 0; col < 4; col++) {

			// 1. ���������� ���������� �����, �������� ������� ������

			for (unsigned int i = 0; i < 3; i++) {
				if (this->model[col][i] == this->model[col][i + 1]) {
					this->model[col][i] += this->model[col][i + 1];
					this->model[col][i + 1] = 0;
				}
			}

			// 2. ����������� ���� � ����� ���
			for (unsigned int i = 0; i < 3; i++) {
				for (unsigned int j = 3; j > i; j--) {
					if (this->model[col][j - 1] == 0) {
						std::swap(this->model[col][j - 1], this->model[col][j]);
					}
				}
			}
		}

		break;

	case 's':
	case 75:
		for (unsigned int col = 0; col < 4; col++) {

			// ��� �� �� �����, �� � �������� �����������:

			for (unsigned int i = 0; i < 3; i++) {
				if (this->model[col][i] == this->model[col][i + 1]) {
					this->model[col][i + 1] += this->model[col][i];	// �������� ����������� ��������
					this->model[col][i] = 0;	// ���� ������������ � ������ ������
				}
			}

			for (unsigned int i = 0; i < 3; i++) {
				for (unsigned int j = 3; j > i; j--) {
					if (this->model[col][j] == 0) {	// ��������� �� ���� �� ��, ��� ������, � ��, ��� ������
						std::swap(this->model[col][j - 1], this->model[col][j]);
					}
				}
			}
		}
		break;

	case 'a':
	case 68:
		for (unsigned int row = 0; row < 4; row++) {

			// �� �� �����, �� ������ �������� �� � ������ �������, � � ������ ������

			for (unsigned int i = 0; i < 3; i++) {
				if (this->model[i][row] == this->model[i + 1][row]) {
					this->model[i][row] += this->model[i + 1][row];
					this->model[i + 1][row] = 0;
				}
			}

			for (unsigned int i = 0; i < 3; i++) {
				for (unsigned int j = 3; j > i; j--) {
					if (this->model[j - 1][row] == 0) {
						std::swap(this->model[j - 1][row], this->model[j][row]);
					}
				}
			}
		}
		break;

	case 'd':
	case 50:
		for (unsigned int row = 0; row < 4; row++) {

			// ��������� ���������� ������������� �������� � ������ �������:

			for (unsigned int i = 0; i < 3; i++) {
				if (this->model[i][row] == this->model[i + 1][row]) {
					this->model[i + 1][row] += this->model[i][row]; // ��� ���
					this->model[i][row] = 0; // � ���
				}
			}

			for (unsigned int i = 0; i < 3; i++) {
				for (unsigned int j = 3; j > i; j--) {
					if (this->model[j][row] == 0) { // � ��� ���
						std::swap(this->model[j - 1][row], this->model[j][row]);
					}
				}
			}
		}
		break;

	}


	// ��������� ����� �����.
	// �� �������� ����, � ������������ 66% ����������� ����� "2",
	//                 � � ������������ 33% �           ����� "4".


	// �������� ������ ������
	unsigned char breaker = 0;	// ����� ��� ����� 1, ��� ����� ����������
	for (unsigned int i = 0; i < 4 && !breaker; i++) {
		for (unsigned int j = 0; j < 4 && !breaker; j++) {
			if (this->model[i][j] == 0) {
				if ((unsigned int) rand() % 3 == 0) {
					// ���� ����� 33% � �� 0, 1 � 2 ����� 0, �� ���� ������ "4"
					this->model[i][j] = 4;
				}
				else {
					// ����� (���� ����� 66%) � ������ "2"
					this->model[i][j] = 2;
				}
				breaker = 1;
			}
	
		}

	}


	// ���������� ������ ������ �� �����
	this->render(this->model);
}
