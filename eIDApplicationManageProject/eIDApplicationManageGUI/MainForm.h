#pragma once

#include <windows.h>
#include <iostream>
#include <string>
#include <tchar.h>
//#include <atlstr.h>

#include "shlwapi.h"

//#include "define.h"
#include "USBHidDll.h"
#include "cspdk.h"

#define PCSC_REGISTER_NAME "SOFTWARE\\Microsoft\\Cryptography\\Defaults\\Provider\\HED_PCSC_Cryptographic_Service_Provider_V1.0"
#define HID_REGISTER_NAME "SOFTWARE\\Microsoft\\Cryptography\\Defaults\\Provider\\HED_HID_Cryptographic_Service_Provider_V1.0"
#define PCSC_DEVICE_ID  0x01
#define HID_DEVICE_ID   0x02

typedef BOOL(WINAPI *pCPAcquireContext)(
	OUT HCRYPTPROV *phProv,
    IN  LPCSTR szContainer,
    IN  DWORD dwFlags,
    IN  PVTableProvStruc pVTable);


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
		String^ lpsImagePath;
		HINSTANCE hDLL;
		DWORD dwDeviceType;

		MainForm(void)
		{
			g_bPcscDeviceConnected = false;
			g_bHidDeviceConnected = false;
			g_hRegProviders = NULL;
			lpstrRegImagePath = "";
			lpsImagePath = "";

			InitializeComponent();
			//
			//TODO: 在此处添加构造函数代码
			//
		}
	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::TextBox^  textCardTestSW;
	private: System::Windows::Forms::TextBox^  textOpStatusCardTest;
	private: System::Windows::Forms::TextBox^  textRandomData;
	private: System::Windows::Forms::TextBox^  textWriteCard;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Button^  btnWriteCard;
	private: System::Windows::Forms::Button^  btnReadCard;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Button^  btnPowerUp;
	private: System::Windows::Forms::Button^  btnPowerDown;
	private: System::Windows::Forms::Button^  btnProbeCard;
	private: System::Windows::Forms::TabPage^  tabPage2;
	private: System::Windows::Forms::Label^  label17;
	private: System::Windows::Forms::TextBox^  textConsume;
	private: System::Windows::Forms::Button^  btnCounsume;
	private: System::Windows::Forms::Label^  label16;
	private: System::Windows::Forms::Button^  btnCharge;
	private: System::Windows::Forms::TextBox^  textCharge;
	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::TextBox^  textBanlanceElecMoney;
	private: System::Windows::Forms::Button^  btnBanlance;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::TabPage^  tabPage3;
	private: System::Windows::Forms::Label^  label33;
	private: System::Windows::Forms::Label^  label32;
	private: System::Windows::Forms::Label^  label29;
	private: System::Windows::Forms::PictureBox^  pictureBoxSrcAccount;
	private: System::Windows::Forms::PictureBox^  pictureBoxDstAccount;
	private: System::Windows::Forms::PictureBox^  pictureBoxTransCash;
	private: System::Windows::Forms::Label^  label25;
	private: System::Windows::Forms::Label^  label18;
	private: System::Windows::Forms::PictureBox^  pictureBoxAuthCode;
	private: System::Windows::Forms::TextBox^  textBanlanceNewUKey;
	private: System::Windows::Forms::Button^  btnUKeyBanlance;
	private: System::Windows::Forms::Button^  btnSendData;
	private: System::Windows::Forms::Label^  label24;
	private: System::Windows::Forms::TextBox^  textTransCash;
	private: System::Windows::Forms::TextBox^  textBoxDstAccount;
	private: System::Windows::Forms::Label^  label23;
	private: System::Windows::Forms::TextBox^  textBoxSrcAccount;
	private: System::Windows::Forms::Label^  label22;
	private: System::Windows::Forms::Label^  label21;
	private: System::Windows::Forms::Button^  btnRSAKey;
	private: System::Windows::Forms::TextBox^  textBoxRSAKey;
	private: System::Windows::Forms::Label^  label20;
	private: System::Windows::Forms::Label^  label19;
	private: System::Windows::Forms::TabPage^  tabPage4;
	private: System::Windows::Forms::Label^  label31;
	private: System::Windows::Forms::PictureBox^  pictureBoxLogIn;
	private: System::Windows::Forms::TextBox^  textResponseCode;
	private: System::Windows::Forms::Button^  btnLogIn;
	private: System::Windows::Forms::Label^  label30;
	private: System::Windows::Forms::Button^  btnGenerateResponseCode;
	private: System::Windows::Forms::Label^  label28;
	private: System::Windows::Forms::TextBox^  textChallangeCode;
	private: System::Windows::Forms::Button^  btnGenerateChallangeCode;
	private: System::Windows::Forms::Label^  label27;
	private: System::Windows::Forms::Label^  label26;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::ComboBox^  comboBox1;

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->textCardTestSW = (gcnew System::Windows::Forms::TextBox());
			this->textOpStatusCardTest = (gcnew System::Windows::Forms::TextBox());
			this->textRandomData = (gcnew System::Windows::Forms::TextBox());
			this->textWriteCard = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->btnWriteCard = (gcnew System::Windows::Forms::Button());
			this->btnReadCard = (gcnew System::Windows::Forms::Button());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->btnPowerUp = (gcnew System::Windows::Forms::Button());
			this->btnPowerDown = (gcnew System::Windows::Forms::Button());
			this->btnProbeCard = (gcnew System::Windows::Forms::Button());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->textConsume = (gcnew System::Windows::Forms::TextBox());
			this->btnCounsume = (gcnew System::Windows::Forms::Button());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->btnCharge = (gcnew System::Windows::Forms::Button());
			this->textCharge = (gcnew System::Windows::Forms::TextBox());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->textBanlanceElecMoney = (gcnew System::Windows::Forms::TextBox());
			this->btnBanlance = (gcnew System::Windows::Forms::Button());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->label33 = (gcnew System::Windows::Forms::Label());
			this->label32 = (gcnew System::Windows::Forms::Label());
			this->label29 = (gcnew System::Windows::Forms::Label());
			this->pictureBoxSrcAccount = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBoxDstAccount = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBoxTransCash = (gcnew System::Windows::Forms::PictureBox());
			this->label25 = (gcnew System::Windows::Forms::Label());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->pictureBoxAuthCode = (gcnew System::Windows::Forms::PictureBox());
			this->textBanlanceNewUKey = (gcnew System::Windows::Forms::TextBox());
			this->btnUKeyBanlance = (gcnew System::Windows::Forms::Button());
			this->btnSendData = (gcnew System::Windows::Forms::Button());
			this->label24 = (gcnew System::Windows::Forms::Label());
			this->textTransCash = (gcnew System::Windows::Forms::TextBox());
			this->textBoxDstAccount = (gcnew System::Windows::Forms::TextBox());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->textBoxSrcAccount = (gcnew System::Windows::Forms::TextBox());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->btnRSAKey = (gcnew System::Windows::Forms::Button());
			this->textBoxRSAKey = (gcnew System::Windows::Forms::TextBox());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->tabPage4 = (gcnew System::Windows::Forms::TabPage());
			this->label31 = (gcnew System::Windows::Forms::Label());
			this->pictureBoxLogIn = (gcnew System::Windows::Forms::PictureBox());
			this->textResponseCode = (gcnew System::Windows::Forms::TextBox());
			this->btnLogIn = (gcnew System::Windows::Forms::Button());
			this->label30 = (gcnew System::Windows::Forms::Label());
			this->btnGenerateResponseCode = (gcnew System::Windows::Forms::Button());
			this->label28 = (gcnew System::Windows::Forms::Label());
			this->textChallangeCode = (gcnew System::Windows::Forms::TextBox());
			this->btnGenerateChallangeCode = (gcnew System::Windows::Forms::Button());
			this->label27 = (gcnew System::Windows::Forms::Label());
			this->label26 = (gcnew System::Windows::Forms::Label());
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->tabPage2->SuspendLayout();
			this->tabPage3->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBoxSrcAccount))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBoxDstAccount))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBoxTransCash))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBoxAuthCode))->BeginInit();
			this->tabPage4->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBoxLogIn))->BeginInit();
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
			// tabControl1
			// 
			this->tabControl1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Controls->Add(this->tabPage3);
			this->tabControl1->Controls->Add(this->tabPage4);
			this->tabControl1->Font = (gcnew System::Drawing::Font(L"宋体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->tabControl1->Location = System::Drawing::Point(15, 42);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(575, 391);
			this->tabControl1->TabIndex = 2;
			// 
			// tabPage1
			// 
			this->tabPage1->BackColor = System::Drawing::Color::Transparent;
			this->tabPage1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->tabPage1->Controls->Add(this->label7);
			this->tabPage1->Controls->Add(this->textCardTestSW);
			this->tabPage1->Controls->Add(this->textOpStatusCardTest);
			this->tabPage1->Controls->Add(this->textRandomData);
			this->tabPage1->Controls->Add(this->textWriteCard);
			this->tabPage1->Controls->Add(this->label6);
			this->tabPage1->Controls->Add(this->label5);
			this->tabPage1->Controls->Add(this->btnWriteCard);
			this->tabPage1->Controls->Add(this->btnReadCard);
			this->tabPage1->Controls->Add(this->label4);
			this->tabPage1->Controls->Add(this->label3);
			this->tabPage1->Controls->Add(this->label2);
			this->tabPage1->Controls->Add(this->btnPowerUp);
			this->tabPage1->Controls->Add(this->btnPowerDown);
			this->tabPage1->Controls->Add(this->btnProbeCard);
			this->tabPage1->Font = (gcnew System::Drawing::Font(L"宋体", 10.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->tabPage1->Location = System::Drawing::Point(4, 25);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(567, 362);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"卡测试";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(15, 305);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(49, 14);
			this->label7->TabIndex = 16;
			this->label7->Text = L"返回SW";
			// 
			// textCardTestSW
			// 
			this->textCardTestSW->Location = System::Drawing::Point(84, 302);
			this->textCardTestSW->Name = L"textCardTestSW";
			this->textCardTestSW->ReadOnly = true;
			this->textCardTestSW->Size = System::Drawing::Size(240, 23);
			this->textCardTestSW->TabIndex = 15;
			this->textCardTestSW->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textOpStatusCardTest
			// 
			this->textOpStatusCardTest->Location = System::Drawing::Point(84, 266);
			this->textOpStatusCardTest->Name = L"textOpStatusCardTest";
			this->textOpStatusCardTest->ReadOnly = true;
			this->textOpStatusCardTest->Size = System::Drawing::Size(240, 23);
			this->textOpStatusCardTest->TabIndex = 14;
			this->textOpStatusCardTest->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textRandomData
			// 
			this->textRandomData->Location = System::Drawing::Point(9, 140);
			this->textRandomData->Name = L"textRandomData";
			this->textRandomData->ReadOnly = true;
			this->textRandomData->Size = System::Drawing::Size(214, 23);
			this->textRandomData->TabIndex = 13;
			this->textRandomData->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textWriteCard
			// 
			this->textWriteCard->Location = System::Drawing::Point(9, 175);
			this->textWriteCard->Name = L"textWriteCard";
			this->textWriteCard->Size = System::Drawing::Size(214, 23);
			this->textWriteCard->TabIndex = 12;
			this->textWriteCard->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(15, 269);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(63, 14);
			this->label6->TabIndex = 9;
			this->label6->Text = L"操作状态";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"宋体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label5->Location = System::Drawing::Point(6, 229);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(176, 16);
			this->label5->TabIndex = 8;
			this->label5->Text = L"三 操作状态及返回数据";
			// 
			// btnWriteCard
			// 
			this->btnWriteCard->Font = (gcnew System::Drawing::Font(L"宋体", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->btnWriteCard->Location = System::Drawing::Point(229, 175);
			this->btnWriteCard->Name = L"btnWriteCard";
			this->btnWriteCard->Size = System::Drawing::Size(95, 23);
			this->btnWriteCard->TabIndex = 7;
			this->btnWriteCard->Text = L"写卡";
			this->btnWriteCard->UseVisualStyleBackColor = true;
			// 
			// btnReadCard
			// 
			this->btnReadCard->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->btnReadCard->Font = (gcnew System::Drawing::Font(L"宋体", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->btnReadCard->Location = System::Drawing::Point(229, 140);
			this->btnReadCard->Name = L"btnReadCard";
			this->btnReadCard->Size = System::Drawing::Size(95, 23);
			this->btnReadCard->TabIndex = 6;
			this->btnReadCard->Text = L"读8字节随机数";
			this->btnReadCard->UseVisualStyleBackColor = true;
			// 
			// label4
			// 
			this->label4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"宋体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label4->Location = System::Drawing::Point(6, 103);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(112, 16);
			this->label4->TabIndex = 5;
			this->label4->Text = L"二 读写卡操作";
			// 
			// label3
			// 
			this->label3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->label3->BackColor = System::Drawing::Color::LightGray;
			this->label3->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label3->Font = (gcnew System::Drawing::Font(L"宋体", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label3->Location = System::Drawing::Point(339, 3);
			this->label3->Margin = System::Windows::Forms::Padding(5);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(221, 352);
			this->label3->TabIndex = 4;
			this->label3->Text = resources->GetString(L"label3.Text");
			// 
			// label2
			// 
			this->label2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"宋体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label2->Location = System::Drawing::Point(6, 20);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(112, 16);
			this->label2->TabIndex = 3;
			this->label2->Text = L"一 卡状态检测";
			// 
			// btnPowerUp
			// 
			this->btnPowerUp->Font = (gcnew System::Drawing::Font(L"宋体", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->btnPowerUp->Location = System::Drawing::Point(249, 56);
			this->btnPowerUp->Name = L"btnPowerUp";
			this->btnPowerUp->Size = System::Drawing::Size(75, 23);
			this->btnPowerUp->TabIndex = 2;
			this->btnPowerUp->Text = L"卡上电复位";
			this->btnPowerUp->UseVisualStyleBackColor = true;
			// 
			// btnPowerDown
			// 
			this->btnPowerDown->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->btnPowerDown->Font = (gcnew System::Drawing::Font(L"宋体", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->btnPowerDown->Location = System::Drawing::Point(133, 56);
			this->btnPowerDown->Name = L"btnPowerDown";
			this->btnPowerDown->Size = System::Drawing::Size(75, 23);
			this->btnPowerDown->TabIndex = 1;
			this->btnPowerDown->Text = L"卡掉电";
			this->btnPowerDown->UseVisualStyleBackColor = true;
			// 
			// btnProbeCard
			// 
			this->btnProbeCard->Font = (gcnew System::Drawing::Font(L"宋体", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->btnProbeCard->Location = System::Drawing::Point(9, 56);
			this->btnProbeCard->Name = L"btnProbeCard";
			this->btnProbeCard->Size = System::Drawing::Size(75, 23);
			this->btnProbeCard->TabIndex = 0;
			this->btnProbeCard->Text = L"探卡";
			this->btnProbeCard->UseVisualStyleBackColor = true;
			// 
			// tabPage2
			// 
			this->tabPage2->AccessibleRole = System::Windows::Forms::AccessibleRole::TitleBar;
			this->tabPage2->Controls->Add(this->label17);
			this->tabPage2->Controls->Add(this->textConsume);
			this->tabPage2->Controls->Add(this->btnCounsume);
			this->tabPage2->Controls->Add(this->label16);
			this->tabPage2->Controls->Add(this->btnCharge);
			this->tabPage2->Controls->Add(this->textCharge);
			this->tabPage2->Controls->Add(this->label15);
			this->tabPage2->Controls->Add(this->textBanlanceElecMoney);
			this->tabPage2->Controls->Add(this->btnBanlance);
			this->tabPage2->Controls->Add(this->label14);
			this->tabPage2->Location = System::Drawing::Point(4, 25);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(567, 362);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"电子现金";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Location = System::Drawing::Point(6, 234);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(96, 16);
			this->label17->TabIndex = 17;
			this->label17->Text = L"三 查询余额";
			// 
			// textConsume
			// 
			this->textConsume->Location = System::Drawing::Point(71, 170);
			this->textConsume->Name = L"textConsume";
			this->textConsume->Size = System::Drawing::Size(158, 26);
			this->textConsume->TabIndex = 13;
			this->textConsume->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// btnCounsume
			// 
			this->btnCounsume->Location = System::Drawing::Point(237, 170);
			this->btnCounsume->Name = L"btnCounsume";
			this->btnCounsume->Size = System::Drawing::Size(91, 23);
			this->btnCounsume->TabIndex = 12;
			this->btnCounsume->Text = L"消费";
			this->btnCounsume->UseVisualStyleBackColor = true;
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Location = System::Drawing::Point(6, 131);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(64, 16);
			this->label16->TabIndex = 11;
			this->label16->Text = L"二 消费";
			// 
			// btnCharge
			// 
			this->btnCharge->Location = System::Drawing::Point(238, 78);
			this->btnCharge->Name = L"btnCharge";
			this->btnCharge->Size = System::Drawing::Size(90, 23);
			this->btnCharge->TabIndex = 10;
			this->btnCharge->Text = L"充值";
			this->btnCharge->UseVisualStyleBackColor = true;
//			this->btnCharge->Click += gcnew System::EventHandler(this, &MainForm::btnCharge_Click);
			// 
			// textCharge
			// 
			this->textCharge->Location = System::Drawing::Point(71, 78);
			this->textCharge->Name = L"textCharge";
			this->textCharge->Size = System::Drawing::Size(158, 26);
			this->textCharge->TabIndex = 9;
			this->textCharge->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(6, 37);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(64, 16);
			this->label15->TabIndex = 8;
			this->label15->Text = L"一 充值";
			// 
			// textBanlanceElecMoney
			// 
			this->textBanlanceElecMoney->Location = System::Drawing::Point(71, 266);
			this->textBanlanceElecMoney->Name = L"textBanlanceElecMoney";
			this->textBanlanceElecMoney->ReadOnly = true;
			this->textBanlanceElecMoney->Size = System::Drawing::Size(158, 26);
			this->textBanlanceElecMoney->TabIndex = 7;
			this->textBanlanceElecMoney->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// btnBanlance
			// 
			this->btnBanlance->Font = (gcnew System::Drawing::Font(L"宋体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->btnBanlance->Location = System::Drawing::Point(237, 266);
			this->btnBanlance->Name = L"btnBanlance";
			this->btnBanlance->Size = System::Drawing::Size(91, 23);
			this->btnBanlance->TabIndex = 6;
			this->btnBanlance->Text = L"查询余额";
			this->btnBanlance->UseVisualStyleBackColor = true;
			// 
			// label14
			// 
			this->label14->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->label14->BackColor = System::Drawing::Color::LightGray;
			this->label14->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label14->Font = (gcnew System::Drawing::Font(L"宋体", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label14->Location = System::Drawing::Point(342, 8);
			this->label14->Margin = System::Windows::Forms::Padding(5);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(220, 349);
			this->label14->TabIndex = 5;
			this->label14->Text = L"\r\n操作说明：\r\n\r\n一 充值\r\n\r\n   输入充值金额，单击“充值”按钮，\r\n   可视卡屏幕上显示充值金额，确认无\r\n   误后根据操作提示完成充值。\r\n\r\n" 
				L"二 消费\r\n\r\n   输入消费金额，单击“消费”按钮，\r\n   可视卡屏幕上显示充值金额，确认无\r\n   误后根据操作提示完成充值。\r\n\r\n三 查询余额\r\n\r\n" 
				L"   单击“查询余额”按钮读取卡中余额";
			// 
			// tabPage3
			// 
			this->tabPage3->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->tabPage3->Controls->Add(this->label33);
			this->tabPage3->Controls->Add(this->label32);
			this->tabPage3->Controls->Add(this->label29);
			this->tabPage3->Controls->Add(this->pictureBoxSrcAccount);
			this->tabPage3->Controls->Add(this->pictureBoxDstAccount);
			this->tabPage3->Controls->Add(this->pictureBoxTransCash);
			this->tabPage3->Controls->Add(this->label25);
			this->tabPage3->Controls->Add(this->label18);
			this->tabPage3->Controls->Add(this->pictureBoxAuthCode);
			this->tabPage3->Controls->Add(this->textBanlanceNewUKey);
			this->tabPage3->Controls->Add(this->btnUKeyBanlance);
			this->tabPage3->Controls->Add(this->btnSendData);
			this->tabPage3->Controls->Add(this->label24);
			this->tabPage3->Controls->Add(this->textTransCash);
			this->tabPage3->Controls->Add(this->textBoxDstAccount);
			this->tabPage3->Controls->Add(this->label23);
			this->tabPage3->Controls->Add(this->textBoxSrcAccount);
			this->tabPage3->Controls->Add(this->label22);
			this->tabPage3->Controls->Add(this->label21);
			this->tabPage3->Controls->Add(this->btnRSAKey);
			this->tabPage3->Controls->Add(this->textBoxRSAKey);
			this->tabPage3->Controls->Add(this->label20);
			this->tabPage3->Controls->Add(this->label19);
			this->tabPage3->Location = System::Drawing::Point(4, 25);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->Padding = System::Windows::Forms::Padding(3);
			this->tabPage3->Size = System::Drawing::Size(567, 362);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = L"二代UKey";
			this->tabPage3->UseVisualStyleBackColor = true;
			// 
			// label33
			// 
			this->label33->AutoSize = true;
			this->label33->Font = (gcnew System::Drawing::Font(L"宋体", 10.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label33->Location = System::Drawing::Point(19, 318);
			this->label33->Name = L"label33";
			this->label33->Size = System::Drawing::Size(49, 14);
			this->label33->TabIndex = 34;
			this->label33->Text = L"认证码";
			// 
			// label32
			// 
			this->label32->AutoSize = true;
			this->label32->Font = (gcnew System::Drawing::Font(L"宋体", 10.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label32->Location = System::Drawing::Point(19, 284);
			this->label32->Name = L"label32";
			this->label32->Size = System::Drawing::Size(63, 14);
			this->label32->TabIndex = 33;
			this->label32->Text = L"转账金额";
			// 
			// label29
			// 
			this->label29->AutoSize = true;
			this->label29->Font = (gcnew System::Drawing::Font(L"宋体", 10.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label29->Location = System::Drawing::Point(19, 250);
			this->label29->Name = L"label29";
			this->label29->Size = System::Drawing::Size(63, 14);
			this->label29->TabIndex = 32;
			this->label29->Text = L"目的账户";
			// 
			// pictureBoxSrcAccount
			// 
			this->pictureBoxSrcAccount->Location = System::Drawing::Point(87, 202);
			this->pictureBoxSrcAccount->Name = L"pictureBoxSrcAccount";
			this->pictureBoxSrcAccount->Size = System::Drawing::Size(237, 35);
			this->pictureBoxSrcAccount->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBoxSrcAccount->TabIndex = 31;
			this->pictureBoxSrcAccount->TabStop = false;
			// 
			// pictureBoxDstAccount
			// 
			this->pictureBoxDstAccount->Location = System::Drawing::Point(87, 236);
			this->pictureBoxDstAccount->Name = L"pictureBoxDstAccount";
			this->pictureBoxDstAccount->Size = System::Drawing::Size(237, 35);
			this->pictureBoxDstAccount->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBoxDstAccount->TabIndex = 30;
			this->pictureBoxDstAccount->TabStop = false;
			// 
			// pictureBoxTransCash
			// 
			this->pictureBoxTransCash->Location = System::Drawing::Point(87, 270);
			this->pictureBoxTransCash->Name = L"pictureBoxTransCash";
			this->pictureBoxTransCash->Size = System::Drawing::Size(237, 35);
			this->pictureBoxTransCash->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBoxTransCash->TabIndex = 29;
			this->pictureBoxTransCash->TabStop = false;
			// 
			// label25
			// 
			this->label25->AutoSize = true;
			this->label25->Font = (gcnew System::Drawing::Font(L"宋体", 10.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label25->Location = System::Drawing::Point(19, 216);
			this->label25->Name = L"label25";
			this->label25->Size = System::Drawing::Size(49, 14);
			this->label25->TabIndex = 28;
			this->label25->Text = L"源账户";
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Location = System::Drawing::Point(152, 183);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(104, 16);
			this->label18->TabIndex = 27;
			this->label18->Text = L"卡处理后数据";
			// 
			// pictureBoxAuthCode
			// 
			this->pictureBoxAuthCode->Location = System::Drawing::Point(87, 304);
			this->pictureBoxAuthCode->Name = L"pictureBoxAuthCode";
			this->pictureBoxAuthCode->Size = System::Drawing::Size(237, 35);
			this->pictureBoxAuthCode->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBoxAuthCode->TabIndex = 25;
			this->pictureBoxAuthCode->TabStop = false;
			// 
			// textBanlanceNewUKey
			// 
			this->textBanlanceNewUKey->Location = System::Drawing::Point(441, 21);
			this->textBanlanceNewUKey->Name = L"textBanlanceNewUKey";
			this->textBanlanceNewUKey->ReadOnly = true;
			this->textBanlanceNewUKey->Size = System::Drawing::Size(111, 26);
			this->textBanlanceNewUKey->TabIndex = 24;
			this->textBanlanceNewUKey->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// btnUKeyBanlance
			// 
			this->btnUKeyBanlance->Font = (gcnew System::Drawing::Font(L"宋体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->btnUKeyBanlance->Location = System::Drawing::Point(344, 21);
			this->btnUKeyBanlance->Name = L"btnUKeyBanlance";
			this->btnUKeyBanlance->Size = System::Drawing::Size(91, 23);
			this->btnUKeyBanlance->TabIndex = 23;
			this->btnUKeyBanlance->Text = L"查询余额";
			this->btnUKeyBanlance->UseVisualStyleBackColor = true;
			// 
			// btnSendData
			// 
			this->btnSendData->Font = (gcnew System::Drawing::Font(L"宋体", 10.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->btnSendData->Location = System::Drawing::Point(249, 102);
			this->btnSendData->Name = L"btnSendData";
			this->btnSendData->Size = System::Drawing::Size(75, 47);
			this->btnSendData->TabIndex = 19;
			this->btnSendData->Text = L"提交数据给可视卡";
			this->btnSendData->UseVisualStyleBackColor = true;
			// 
			// label24
			// 
			this->label24->AutoSize = true;
			this->label24->Font = (gcnew System::Drawing::Font(L"宋体", 10.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label24->Location = System::Drawing::Point(19, 150);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(63, 14);
			this->label24->TabIndex = 18;
			this->label24->Text = L"转账金额";
			// 
			// textTransCash
			// 
			this->textTransCash->Location = System::Drawing::Point(87, 145);
			this->textTransCash->Name = L"textTransCash";
			this->textTransCash->Size = System::Drawing::Size(142, 26);
			this->textTransCash->TabIndex = 17;
			this->textTransCash->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textBoxDstAccount
			// 
			this->textBoxDstAccount->Location = System::Drawing::Point(87, 113);
			this->textBoxDstAccount->Name = L"textBoxDstAccount";
			this->textBoxDstAccount->ReadOnly = true;
			this->textBoxDstAccount->Size = System::Drawing::Size(142, 26);
			this->textBoxDstAccount->TabIndex = 16;
			this->textBoxDstAccount->Text = L"1023456789";
			this->textBoxDstAccount->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label23
			// 
			this->label23->AutoSize = true;
			this->label23->Font = (gcnew System::Drawing::Font(L"宋体", 10.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label23->Location = System::Drawing::Point(18, 118);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(63, 14);
			this->label23->TabIndex = 15;
			this->label23->Text = L"目的账户";
			// 
			// textBoxSrcAccount
			// 
			this->textBoxSrcAccount->Location = System::Drawing::Point(87, 81);
			this->textBoxSrcAccount->Name = L"textBoxSrcAccount";
			this->textBoxSrcAccount->ReadOnly = true;
			this->textBoxSrcAccount->Size = System::Drawing::Size(142, 26);
			this->textBoxSrcAccount->TabIndex = 14;
			this->textBoxSrcAccount->Text = L"1234567890";
			this->textBoxSrcAccount->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label22
			// 
			this->label22->AutoSize = true;
			this->label22->Font = (gcnew System::Drawing::Font(L"宋体", 10.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label22->Location = System::Drawing::Point(19, 86);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(49, 14);
			this->label22->TabIndex = 13;
			this->label22->Text = L"源账户";
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->Font = (gcnew System::Drawing::Font(L"宋体", 10.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label21->Location = System::Drawing::Point(6, 62);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(56, 14);
			this->label21->TabIndex = 12;
			this->label21->Text = L"二 转账";
			// 
			// btnRSAKey
			// 
			this->btnRSAKey->Font = (gcnew System::Drawing::Font(L"宋体", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->btnRSAKey->Location = System::Drawing::Point(21, 27);
			this->btnRSAKey->Name = L"btnRSAKey";
			this->btnRSAKey->Size = System::Drawing::Size(60, 23);
			this->btnRSAKey->TabIndex = 11;
			this->btnRSAKey->Text = L"取公钥";
			this->btnRSAKey->UseVisualStyleBackColor = true;
			// 
			// textBoxRSAKey
			// 
			this->textBoxRSAKey->Location = System::Drawing::Point(87, 24);
			this->textBoxRSAKey->Name = L"textBoxRSAKey";
			this->textBoxRSAKey->ReadOnly = true;
			this->textBoxRSAKey->Size = System::Drawing::Size(237, 26);
			this->textBoxRSAKey->TabIndex = 10;
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Font = (gcnew System::Drawing::Font(L"宋体", 10.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label20->Location = System::Drawing::Point(6, 5);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(105, 14);
			this->label20->TabIndex = 9;
			this->label20->Text = L"一 生成RSA公钥";
			// 
			// label19
			// 
			this->label19->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->label19->BackColor = System::Drawing::Color::LightGray;
			this->label19->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label19->Font = (gcnew System::Drawing::Font(L"宋体", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label19->Location = System::Drawing::Point(339, 62);
			this->label19->Margin = System::Windows::Forms::Padding(5);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(220, 292);
			this->label19->TabIndex = 6;
			this->label19->Text = L"\r\n操作说明：\r\n\r\n一 生成RSA公钥\r\n\r\n   利用可视卡上SE模块生成RSA公私\r\n   钥对，并显示公钥\r\n\r\n二 转账\r\n\r\n   将源账户，目的账户" 
				L"及转账金额信息\r\n   送可视卡，可视卡生成一认证码并显\r\n   示在可视卡上，同时回传经过卡上SE\r\n   模块处理后的交易信息，两边确认后\r\n   完成交易" 
				L"\r\n\r\n三 查询余额\r\n\r\n   单击“查询余额”按钮读取卡中余额\r\n";
			// 
			// tabPage4
			// 
			this->tabPage4->Controls->Add(this->label31);
			this->tabPage4->Controls->Add(this->pictureBoxLogIn);
			this->tabPage4->Controls->Add(this->textResponseCode);
			this->tabPage4->Controls->Add(this->btnLogIn);
			this->tabPage4->Controls->Add(this->label30);
			this->tabPage4->Controls->Add(this->btnGenerateResponseCode);
			this->tabPage4->Controls->Add(this->label28);
			this->tabPage4->Controls->Add(this->textChallangeCode);
			this->tabPage4->Controls->Add(this->btnGenerateChallangeCode);
			this->tabPage4->Controls->Add(this->label27);
			this->tabPage4->Controls->Add(this->label26);
			this->tabPage4->Location = System::Drawing::Point(4, 25);
			this->tabPage4->Name = L"tabPage4";
			this->tabPage4->Padding = System::Windows::Forms::Padding(3);
			this->tabPage4->Size = System::Drawing::Size(567, 362);
			this->tabPage4->TabIndex = 3;
			this->tabPage4->Text = L"OTP";
			this->tabPage4->UseVisualStyleBackColor = true;
			// 
			// label31
			// 
			this->label31->AutoSize = true;
			this->label31->Font = (gcnew System::Drawing::Font(L"宋体", 10.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label31->Location = System::Drawing::Point(7, 300);
			this->label31->Name = L"label31";
			this->label31->Size = System::Drawing::Size(0, 14);
			this->label31->TabIndex = 21;
			// 
			// pictureBoxLogIn
			// 
			this->pictureBoxLogIn->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBoxLogIn.Image")));
			this->pictureBoxLogIn->Location = System::Drawing::Point(10, 192);
			this->pictureBoxLogIn->Name = L"pictureBoxLogIn";
			this->pictureBoxLogIn->Size = System::Drawing::Size(302, 163);
			this->pictureBoxLogIn->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBoxLogIn->TabIndex = 20;
			this->pictureBoxLogIn->TabStop = false;
			this->pictureBoxLogIn->Visible = false;
			// 
			// textResponseCode
			// 
			this->textResponseCode->Location = System::Drawing::Point(10, 160);
			this->textResponseCode->Name = L"textResponseCode";
			this->textResponseCode->ReadOnly = true;
			this->textResponseCode->Size = System::Drawing::Size(201, 26);
			this->textResponseCode->TabIndex = 19;
			this->textResponseCode->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// btnLogIn
			// 
			this->btnLogIn->Font = (gcnew System::Drawing::Font(L"宋体", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->btnLogIn->Location = System::Drawing::Point(217, 162);
			this->btnLogIn->Name = L"btnLogIn";
			this->btnLogIn->Size = System::Drawing::Size(95, 23);
			this->btnLogIn->TabIndex = 18;
			this->btnLogIn->Text = L"登录";
			this->btnLogIn->UseVisualStyleBackColor = true;
			// 
			// label30
			// 
			this->label30->AutoSize = true;
			this->label30->Font = (gcnew System::Drawing::Font(L"宋体", 10.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label30->Location = System::Drawing::Point(7, 143);
			this->label30->Name = L"label30";
			this->label30->Size = System::Drawing::Size(56, 14);
			this->label30->TabIndex = 17;
			this->label30->Text = L"三 登录";
			// 
			// btnGenerateResponseCode
			// 
			this->btnGenerateResponseCode->Font = (gcnew System::Drawing::Font(L"宋体", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->btnGenerateResponseCode->Location = System::Drawing::Point(71, 109);
			this->btnGenerateResponseCode->Name = L"btnGenerateResponseCode";
			this->btnGenerateResponseCode->Size = System::Drawing::Size(180, 23);
			this->btnGenerateResponseCode->TabIndex = 15;
			this->btnGenerateResponseCode->Text = L"生成应答码";
			this->btnGenerateResponseCode->UseVisualStyleBackColor = true;
			// 
			// label28
			// 
			this->label28->AutoSize = true;
			this->label28->Font = (gcnew System::Drawing::Font(L"宋体", 10.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label28->Location = System::Drawing::Point(7, 92);
			this->label28->Name = L"label28";
			this->label28->Size = System::Drawing::Size(98, 14);
			this->label28->TabIndex = 14;
			this->label28->Text = L"二 生成应答码";
			// 
			// textChallangeCode
			// 
			this->textChallangeCode->Location = System::Drawing::Point(111, 47);
			this->textChallangeCode->Name = L"textChallangeCode";
			this->textChallangeCode->ReadOnly = true;
			this->textChallangeCode->Size = System::Drawing::Size(201, 26);
			this->textChallangeCode->TabIndex = 13;
			this->textChallangeCode->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// btnGenerateChallangeCode
			// 
			this->btnGenerateChallangeCode->Font = (gcnew System::Drawing::Font(L"宋体", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->btnGenerateChallangeCode->Location = System::Drawing::Point(9, 47);
			this->btnGenerateChallangeCode->Name = L"btnGenerateChallangeCode";
			this->btnGenerateChallangeCode->Size = System::Drawing::Size(95, 23);
			this->btnGenerateChallangeCode->TabIndex = 12;
			this->btnGenerateChallangeCode->Text = L"获得挑战码";
			this->btnGenerateChallangeCode->UseVisualStyleBackColor = true;
			// 
			// label27
			// 
			this->label27->AutoSize = true;
			this->label27->Font = (gcnew System::Drawing::Font(L"宋体", 10.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label27->Location = System::Drawing::Point(7, 17);
			this->label27->Name = L"label27";
			this->label27->Size = System::Drawing::Size(98, 14);
			this->label27->TabIndex = 10;
			this->label27->Text = L"一 获得挑战码";
			// 
			// label26
			// 
			this->label26->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->label26->BackColor = System::Drawing::Color::LightGray;
			this->label26->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label26->Font = (gcnew System::Drawing::Font(L"宋体", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label26->Location = System::Drawing::Point(342, 8);
			this->label26->Margin = System::Windows::Forms::Padding(5);
			this->label26->Name = L"label26";
			this->label26->Size = System::Drawing::Size(220, 346);
			this->label26->TabIndex = 7;
			this->label26->Text = resources->GetString(L"label26.Text");
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->ClientSize = System::Drawing::Size(599, 445);
			this->Controls->Add(this->tabControl1);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->label1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"MainForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"eID应用管理程序";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage1->PerformLayout();
			this->tabPage2->ResumeLayout(false);
			this->tabPage2->PerformLayout();
			this->tabPage3->ResumeLayout(false);
			this->tabPage3->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBoxSrcAccount))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBoxDstAccount))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBoxTransCash))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBoxAuthCode))->EndInit();
			this->tabPage4->ResumeLayout(false);
			this->tabPage4->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBoxLogIn))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MainForm_Load(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void comboBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
				 PHANDLE pWriteHandle;
				 PHANDLE pReadHandle;
				 PSP_DEVICE_INTERFACE_DETAIL_DATA detailData = NULL;
				 
				 if(comboBox1 -> SelectedItem == "eID Adaptor USB-HID"){
					dwDeviceType = HID_DEVICE_ID;
//					 if((detailData = bOpenHidDevice(0x1677, 0x0340)) != NULL){
					 if((detailData = bOpenHidDevice(0x0400, 0x345a)) != NULL){	 
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
					 dwDeviceType = PCSC_DEVICE_ID;
					 hDLL = bGetCspRegisterInfo(dwDeviceType);
					 
					 if(hDLL != NULL){	
						g_bPcscDeviceConnected = true;
					 }else{
						g_bPcscDeviceConnected = false;
					 }
				 }
				 if(g_bPcscDeviceConnected){
//					this->button1->Enabled = true;
//					this->button2->Enabled = true;
				 }
			 }

	HINSTANCE  bGetCspRegisterInfo(DWORD type){
				
				DWORD dwStatus;
				
				HKEY hRegHandle;

				DWORD dwType = REG_SZ;

				CHAR buf[256] = {'\0'};
				DWORD bufSize = sizeof(buf);
				LPCSTR lpsRegName;
				
				switch (type){
					case PCSC_DEVICE_ID:
						lpsRegName = PCSC_REGISTER_NAME;
						break;
					case HID_DEVICE_ID:
						lpsRegName = HID_REGISTER_NAME;
						break;
					default:
						lpsRegName = "";
						break;
				};

				dwStatus = RegOpenKeyEx(
					HKEY_LOCAL_MACHINE,
//					TEXT(PCSC_REGISTER_NAME),
					TEXT(lpsRegName),
					0,
					KEY_READ,
					&hRegHandle);
				if (ERROR_SUCCESS == dwStatus)
				{

					dwStatus = RegQueryValueEx(
						hRegHandle,
						TEXT("Image Path"),
						NULL,
						&dwType,
						(LPBYTE)buf,
						&bufSize);

					if (ERROR_SUCCESS == dwStatus){
						hDLL = LoadLibrary(buf);
						

//						if(NULL != hDLL){
//							bRet = true;
/*
							pCPAcquireContext cPAcquireContext;
							cPAcquireContext = (pCPAcquireContext)GetProcAddress(hDLL, "CPAcquireContext");
							if(NULL == cPAcquireContext){
								bRet = false;
								MessageBox::Show("Find function \"CPAcquireContext\" failed!");
							}else{
								cPAcquireContext(NULL, NULL, NULL, NULL);
								bRet = true;
							}
*/
//						}else{
//							bRet = false;
//						}
						
					}else{
						hDLL = NULL;
					}	
				}
				else{
					hDLL = NULL;
					MessageBox::Show("Plesae Install HED CSP!");
					
				}
				RegCloseKey(hRegHandle);
				return hDLL;;
			 }

			 
	
};

	
}

