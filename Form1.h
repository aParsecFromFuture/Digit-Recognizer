#pragma once
#include "cnn.h"

/*
	Architecture for digit recognitizion

	Conv2D(16, 5, 5)->Relu()->MaxPool()->BatchNorm()->Conv2D(32, 5, 5)->Relu()->MaxPool()->BatchNorm()->Dense(128)->Relu()->BatchNorm()->Dense(10)->Softmax()
	Image shape (width=28, height=28, channel=1)
	Batch size = 64
	Momentum = 0.9
	Learning rate = 0.1

	Architecture for letter recognitizion

	Conv2D(32, 5, 5)->Relu()->MaxPool()->BatchNorm()->Conv2D(64, 5, 5)->Relu()->MaxPool()->BatchNorm()->Dense(256)->Relu()->BatchNorm()->Dense(26)->Softmax()
	Image shape (width=28, height=28, channel=1)
	Batch size = 128
	Momentum = 0.9
	Learning rate = 0.1

	The CNN library is running on x64 bit/release mode

	Digit and letter datasets retrieved from:
	Cohen, G., Afshar, S., Tapson, J., & van Schaik, A. (2017). EMNIST: an extension of MNIST to handwritten letters. http://arxiv.org/abs/1702.05373

	Author: Farukcan Saðlam
*/

static const char* to_letter[26] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };

namespace CppCLRWinformsProjekt {
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;
	
	public ref class Form1 : public System::Windows::Forms::Form
	{
		bool is_drawing = false;
		int training_mode = 0; // 0 = digit, 1 = letter
		ImageArray* test_image;
		CNN* model;
		Graphics^ image_graphics;
		Bitmap^ digit_image;
		int lineWidth = 14;
		float* prediction;
		

	private: System::Windows::Forms::PictureBox^ pictureBox2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::ToolStripMenuItem^ modeToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ digitsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ lettersToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ clearToolStripMenuItem;
	public:
		Form1(void)
		{
			InitializeComponent();

			prediction = new float[26];

			for (int i = 0; i < 10; i++)
				prediction[i] = 0.0f;
			
			model = new CNN;
			model->load_from("weight_digits.txt");
			
			test_image = new ImageArray(28, 28, 1);
			test_image->alloc(1);
			
			digit_image = gcnew Bitmap(280, 280);

			for (int i = 0; i < digit_image->Width; i++)
				for (int j = 0; j < digit_image->Height; j++)
					digit_image->SetPixel(i, j, Color::White);

			image_graphics = Graphics::FromImage(digit_image);
			pictureBox1->Image = digit_image;
		}

	protected:
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ loadToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ runToolStripMenuItem;
	private: System::ComponentModel::IContainer^ components;

	protected:

	private:


#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->loadToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->runToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->clearToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->modeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->digitsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->lettersToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::SystemColors::Control;
			this->pictureBox1->Location = System::Drawing::Point(12, 43);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(340, 340);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::pictureBox1_MouseDown);
			this->pictureBox1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::pictureBox1_MouseMove);
			this->pictureBox1->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::pictureBox1_MouseUp);
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->loadToolStripMenuItem,
					this->modeToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(862, 28);
			this->menuStrip1->TabIndex = 1;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// loadToolStripMenuItem
			// 
			this->loadToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->runToolStripMenuItem,
					this->clearToolStripMenuItem
			});
			this->loadToolStripMenuItem->Name = L"loadToolStripMenuItem";
			this->loadToolStripMenuItem->Size = System::Drawing::Size(66, 24);
			this->loadToolStripMenuItem->Text = L"Model";
			// 
			// runToolStripMenuItem
			// 
			this->runToolStripMenuItem->Name = L"runToolStripMenuItem";
			this->runToolStripMenuItem->Size = System::Drawing::Size(126, 26);
			this->runToolStripMenuItem->Text = L"Run";
			this->runToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::runToolStripMenuItem_Click);
			// 
			// clearToolStripMenuItem
			// 
			this->clearToolStripMenuItem->Name = L"clearToolStripMenuItem";
			this->clearToolStripMenuItem->Size = System::Drawing::Size(126, 26);
			this->clearToolStripMenuItem->Text = L"Clear";
			this->clearToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::clearToolStripMenuItem_Click);
			// 
			// modeToolStripMenuItem
			// 
			this->modeToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->digitsToolStripMenuItem,
					this->lettersToolStripMenuItem
			});
			this->modeToolStripMenuItem->Name = L"modeToolStripMenuItem";
			this->modeToolStripMenuItem->Size = System::Drawing::Size(62, 24);
			this->modeToolStripMenuItem->Text = L"Mode";
			// 
			// digitsToolStripMenuItem
			// 
			this->digitsToolStripMenuItem->Name = L"digitsToolStripMenuItem";
			this->digitsToolStripMenuItem->Size = System::Drawing::Size(136, 26);
			this->digitsToolStripMenuItem->Text = L"Digits";
			this->digitsToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::digitsToolStripMenuItem_Click);
			// 
			// lettersToolStripMenuItem
			// 
			this->lettersToolStripMenuItem->Name = L"lettersToolStripMenuItem";
			this->lettersToolStripMenuItem->Size = System::Drawing::Size(136, 26);
			this->lettersToolStripMenuItem->Text = L"Letters";
			this->lettersToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::lettersToolStripMenuItem_Click);
			// 
			// pictureBox2
			// 
			this->pictureBox2->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->pictureBox2->Location = System::Drawing::Point(381, 43);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(450, 340);
			this->pictureBox2->TabIndex = 2;
			this->pictureBox2->TabStop = false;
			this->pictureBox2->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::pictureBox2_Paint);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->label1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(162)));
			this->label1->Location = System::Drawing::Point(466, 64);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(283, 32);
			this->label1->TabIndex = 3;
			this->label1->Text = L"PREDICTION STATS";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ControlDark;
			this->ClientSize = System::Drawing::Size(862, 396);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->menuStrip1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MainMenuStrip = this->menuStrip1;
			this->MaximizeBox = false;
			this->Name = L"Form1";
			this->Text = L"Digit/Letter recognizer";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void pictureBox1_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		is_drawing = true;
	}

	private: System::Void pictureBox1_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		is_drawing = false;
	}

	private: System::Void pictureBox1_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (is_drawing) {
			image_graphics->FillEllipse(Brushes::Black, Drawing::Rectangle(e->X - (lineWidth / 2), e->Y - (lineWidth / 2), lineWidth, lineWidth));
			pictureBox1->Image = digit_image;
		}
	}

	private: System::Void runToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		float* pixel_array = test_image->raw();
		float gray_color;

		for (int i = 0; i < 28; i++) {
			for (int j = 0; j < 28; j++) {
				gray_color = 0.0f;
				for (int k = 0; k < 10; k++)
					for (int l = 0; l < 10; l++)
						gray_color += digit_image->GetPixel(j * 10 + l, i * 10 + k).R;

				pixel_array[i * 28 + j] = (255.0f - gray_color / 100.0f);
			}
		}
		
		ImageArray::min_max_scaling(*test_image);
		
		const float* results = model->test(*test_image).raw();

		if (training_mode == 0)
			for (int i = 0; i < 10; i++)
				prediction[i] = results[i];
		
		if (training_mode == 1)
			for (int i = 0; i < 26; i++)
				prediction[i] = results[i];
		
		pictureBox2->Refresh();
	}

	private: System::Void clearToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		for (int i = 0; i < digit_image->Width; i++)
			for (int j = 0; j < digit_image->Height; j++)
				digit_image->SetPixel(i, j, Color::White);

		pictureBox1->Image = digit_image;
	}

	private: System::Void pictureBox2_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		Drawing::Pen^ axis_pen = gcnew Pen(Color::Black);
		Drawing::Pen^ grid_pen = gcnew Pen(Color::Gray);
		Drawing::Pen^ tick_pen = gcnew Pen(Color::Black);
		Drawing::Font^ tickFont = gcnew Drawing::Font("Times New Roman", 12.0f);

		e->Graphics->DrawLine(axis_pen, 50, 240, 300, 240);
		e->Graphics->DrawLine(axis_pen, 60, 60, 60, 250);
		e->Graphics->DrawLine(grid_pen, 50, 200, 300, 200);
		e->Graphics->DrawLine(grid_pen, 50, 160, 300, 160);
		e->Graphics->DrawLine(grid_pen, 50, 120, 300, 120);
		e->Graphics->DrawLine(grid_pen, 50, 80, 300, 80);

		e->Graphics->DrawString("0.25", tickFont, Brushes::Black, RectangleF(24, 182, 40, 20));
		e->Graphics->DrawString("0.50", tickFont, Brushes::Black, RectangleF(24, 142, 40, 20));
		e->Graphics->DrawString("0.75", tickFont, Brushes::Black, RectangleF(24, 102, 40, 20));
		e->Graphics->DrawString("1.00", tickFont, Brushes::Black, RectangleF(24, 62, 40, 20));

		if (training_mode == 0) {
			e->Graphics->DrawString("0    1    2    3    4    5    6    7    8    9", tickFont, Brushes::Black, RectangleF(66, 240, 240, 20));

			for (int i = 0; i < 10; i++)
				e->Graphics->FillRectangle(Brushes::Blue, Rectangle(66 + i * 24, 240 - 160 * prediction[i], 10, 160 * prediction[i] + 1));
		}
		if (training_mode == 1) {
			float max;
			int top_letters[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
			int max_index;
			bool pass;
			for (int i = 0; i < 10; i++) {
				max_index = 0;
				max = 0.0f;
				for (int j = 0; j < 26; j++) {
					pass = false;
					for (int k = 0; k < 10; k++)
						if (j == top_letters[k])
							pass = true;
					if (pass)
						continue;

					if (max < prediction[j]) {
						max = prediction[j];
						max_index = j;
					}
				}	
				top_letters[i] = max_index;
				e->Graphics->FillRectangle(Brushes::Blue, Rectangle(68 + i * 24, 240 - 160 * prediction[top_letters[i]], 10, 160 * prediction[top_letters[i]] + 1));
				e->Graphics->DrawString(gcnew String(to_letter[top_letters[i]]), tickFont, Brushes::Black, RectangleF(66 + i * 24, 240, 240, 20));
			}
		}
	}

	private: System::Void digitsToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		model->load_from("weight_digits.txt");
		for (int i = 0; i < 10; i++)
			prediction[i] = 0.0f;

		training_mode = 0;
		pictureBox2->Refresh();
	}

	private: System::Void lettersToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		model->load_from("weight_letters.txt");
		for (int i = 0; i < 26; i++)
			prediction[i] = (25 - i) * 0.0001f;

		training_mode = 1;
		pictureBox2->Refresh();
	}
};
}
