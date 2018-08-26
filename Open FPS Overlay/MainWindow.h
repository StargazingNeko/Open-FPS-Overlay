#include "rapidjson\document.h"
#include "rapidjson/filereadstream.h"
#include <iostream>
#include <sstream>
#include <Windows.h>
#include <fstream>
#include <cstdio>

#pragma once

namespace OpenFPSOverlay {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MainWindow
	/// </summary>
	public ref class MainWindow : public System::Windows::Forms::Form
	{
	public:
		MainWindow(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			std::stringstream ss;
			std::ifstream cfgFile("config.json");
			if (cfgFile)
			{
				ss << cfgFile.rdbuf();
				cfgFile.close();
			}
			else
			{
				throw std::runtime_error("Unable to open configuration!");
			}
			
			rapidjson::Document doc;
			if(doc.Parse(ss.str().c_str()).HasParseError)
				throw std::invalid_argument("Parse Error");
			
			std::string boundHotKey = doc[0]["Hotkey"].GetString();


			std::stringstream str;
			str << boundHotKey;
			int boundHotKeyHex;
			str >> std::hex >> boundHotKeyHex;

			textBox1->Text = boundHotKeyHex.ToString(); //Place holder, will instead have the hex converted to the actual key before setting the text to mentioned key. (e.g, 0x7B will be read as F12)
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  bindKeyButton;
	protected:
	private: System::Windows::Forms::TextBox^  textBox1;

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->bindKeyButton = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// bindKeyButton
			// 
			this->bindKeyButton->Font = (gcnew System::Drawing::Font(L"Arial", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->bindKeyButton->Location = System::Drawing::Point(40, 45);
			this->bindKeyButton->Name = L"bindKeyButton";
			this->bindKeyButton->Size = System::Drawing::Size(75, 23);
			this->bindKeyButton->TabIndex = 0;
			this->bindKeyButton->Text = L"Bind Key";
			this->bindKeyButton->UseVisualStyleBackColor = true;
			this->bindKeyButton->Click += gcnew System::EventHandler(this, &MainWindow::bindKeyButton_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(27, 12);
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			this->textBox1->Size = System::Drawing::Size(100, 20);
			this->textBox1->TabIndex = 1;
			this->textBox1->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBox1->WordWrap = false;
			// 
			// MainWindow
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->ClientSize = System::Drawing::Size(152, 81);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->bindKeyButton);
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(168, 120);
			this->MinimizeBox = false;
			this->MinimumSize = System::Drawing::Size(168, 120);
			this->Name = L"MainWindow";
			this->ShowIcon = false;
			this->Text = L"OFO";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void bindKeyButton_Click(System::Object^  sender, System::EventArgs^  e)
	{

	}
	};
}
