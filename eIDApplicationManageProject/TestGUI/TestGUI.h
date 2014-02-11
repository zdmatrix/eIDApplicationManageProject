#pragma once

#include "HDIFD20B.h"

namespace TestGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Form1 摘要
	///
	/// 警告: 如果更改此类的名称，则需要更改
	///          与此类所依赖的所有 .resx 文件关联的托管资源编译器工具的
	///          “资源文件名”属性。否则，
	///          设计器将不能与此窗体的关联
	///          本地化资源正确交互。
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: 在此处添加构造函数代码
			//
		}

	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  btnCallHDIFD20B;
	protected: 

	private:
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 设计器支持所需的方法 - 不要
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->btnCallHDIFD20B = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// btnCallHDIFD20B
			// 
			this->btnCallHDIFD20B->Location = System::Drawing::Point(13, 13);
			this->btnCallHDIFD20B->Name = L"btnCallHDIFD20B";
			this->btnCallHDIFD20B->Size = System::Drawing::Size(133, 23);
			this->btnCallHDIFD20B->TabIndex = 0;
			this->btnCallHDIFD20B->Text = L"调用HDIFD20B.dll";
			this->btnCallHDIFD20B->UseVisualStyleBackColor = true;
			this->btnCallHDIFD20B->Click += gcnew System::EventHandler(this, &Form1::btnCallHDIFD20B_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(292, 266);
			this->Controls->Add(this->btnCallHDIFD20B);
			this->Name = L"Form1";
			this->Text = L"测试程序";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void btnCallHDIFD20B_Click(System::Object^  sender, System::EventArgs^  e) {
				 HANDLE hReader;
				 DWORD ret = 0;
				 ret = HD_OpenPort(21, 9600, 8, &hReader);
				 if(ret == 0x9000){
					 MessageBox::Show("OpenPort done!");
				 }else{
					 MessageBox::Show("OpenPort failed!");
				 }
			 }
	};
}

