#pragma once

#include <windows.h>
#include <iostream>
#include <string>

#include "shlwapi.h"

//#include "define.h"
#include "USBHidDll.h"

#define CSP_REGISTER_NAME "HED_RSA_Cryptographic_Service_Provider_V1.0"
namespace eIDApplicationManageGUI {

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
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:

		bool g_bPcscDeviceConnected;
		bool g_bHidDeviceConnected;
		HKEY g_hRegProviders;
		String^ lpstrRegImagePath;

		MainForm(void)
		{
			g_bPcscDeviceConnected = false;
			g_bHidDeviceConnected = false;
			g_hRegProviders = NULL;
			lpstrRegImagePath = "";

			InitializeComponent();
			//
			//TODO: 在此处添加构造函数代码
			//
		}

	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	protected: 
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(13, 13);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(59, 12);
			this->label1->TabIndex = 0;
			this->label1->Text = L"选择设备:";
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(2) {L"eID Adaptor USB-HID", L"eID Smart Card Reader PCSC"});
			this->comboBox1->Location = System::Drawing::Point(78, 10);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(242, 20);
			this->comboBox1->TabIndex = 1;
			this->comboBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::comboBox1_SelectedIndexChanged);
			// 
			// button1
			// 
			this->button1->Enabled = false;
			this->button1->Location = System::Drawing::Point(70, 86);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(229, 52);
			this->button1->TabIndex = 2;
			this->button1->Text = L"应用场景一";
			this->button1->UseVisualStyleBackColor = true;
			// 
			// button2
			// 
			this->button2->Enabled = false;
			this->button2->Location = System::Drawing::Point(70, 203);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(229, 55);
			this->button2->TabIndex = 3;
			this->button2->Text = L"应用场景二";
			this->button2->UseVisualStyleBackColor = true;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(383, 329);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->label1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"MainForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"eID应用管理程序";
			this->Load += gcnew System::EventHandler(this, &MainForm::Form1_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void comboBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
				 PHANDLE pWriteHandle;
				 PHANDLE pReadHandle;
				 PSP_DEVICE_INTERFACE_DETAIL_DATA detailData = NULL;
				 
				 if(comboBox1 -> SelectedItem == "eID Adaptor USB-HID"){
					if((detailData = bOpenHidDevice(0x1677, 0x0340)) != NULL){
						 
						 pWriteHandle = (PHANDLE)malloc(sizeof(HANDLE));
						 pReadHandle = (PHANDLE)malloc(sizeof(HANDLE));
						 if(bInitWriteHandle(detailData, pWriteHandle) && bInitReadHandle(detailData, pReadHandle)){	 
							 MessageBox::Show("查找USB设备成功!\r\n");
							 g_bHidDeviceConnected = true;
							 //初始化Write句柄成功!\r\n初始化Read句柄成功!\r\n
//							 this->Hide();
//							this->Owner->Show();
//							this->Owner->Activate();
						 }


					 }else{
						 MessageBox::Show("找不到指定USB设备!\r\n请检查是否插入USB设备！\r\n");
					 }
				 }else if(comboBox1 -> SelectedItem == "eID Smart Card Reader PCSC"){
					 bGetCspRegisterInfo(lpstrRegImagePath);
					 g_bPcscDeviceConnected = true;
				 }
				 if(g_bHidDeviceConnected){
					this->button1->Enabled = true;
					this->button2->Enabled = true;
				 }
			 }

			 bool bGetCspRegisterInfo(String^ lpstrImagePath){
				DWORD dwDisp;
				DWORD dwStatus;
				HRESULT hReturnStatus = NO_ERROR;
				HKEY hRegHandle;

				bool bRet = false;

				WCHAR buf[64] = {'\0'};
				DWORD bufSize = sizeof(buf);

				dwStatus = RegCreateKeyEx(
                    HKEY_LOCAL_MACHINE,
                    TEXT("SOFTWARE\\Microsoft\\Cryptography\\Defaults\\Provider"),
                    0,
                    TEXT(CSP_REGISTER_NAME),
                    REG_OPTION_NON_VOLATILE,
                    KEY_ALL_ACCESS,
                    NULL,
                    &hRegHandle,
                    &dwDisp);
				if (ERROR_SUCCESS == dwStatus)
				{
					dwStatus = RegGetValue(
						hRegHandle,
						TEXT("SOFTWARE\\Microsoft\\Cryptography\\Defaults\\Provider"),
						TEXT(CSP_REGISTER_NAME),
						RRF_RT_REG_SZ,
						NULL,
						(LPBYTE)buf,
						&bufSize);
					if (ERROR_SUCCESS == dwStatus){
						bRet = true;
					}
					
					
				}
				else{
					MessageBox::Show("Plesae Install HED CSP!");
				}
				return bRet;
			 }
	};
}

