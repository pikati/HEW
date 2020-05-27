//#include "Joycon.h"
//#include "TextBack.h"
//#include "Text.h"
//#include "Input.h"
//
//Text::Text()
//{
//
//}
//
//Text::~Text()
//{
//
//}
//
//void Text::Initialize(int i)
//{
//	m_text = new XManager;
//	m_text->Initialize();
//
//	m_textPos = D3DXVECTOR3(-10.0f, 1.0f, 1.0f);
//	m_text->SetTranslation(m_textPos);
//	//m_text->SetRotationX();
//
//	m_num = i;
//
//	switch (m_num)
//	{
//	default:
//		break;
//	case 0:
//		m_text->LoadXFile("Models/text1.x", false);
//		m_text->SetScaling(1.0f);
//		//StartInterval();
//		break;
//	case 1:
//		m_text->LoadXFile("Models/text2.x", false);
//		m_text->SetScaling(1.0f);
//		break;
//	case 2:
//		m_text->LoadXFile("Models/text3.x", false);
//		m_text->SetScaling(1.0f);
//		break;
//	case 3:
//		m_text->LoadXFile("Models/text4.x", false);
//		m_text->SetScaling(1.0f);
//		break;
//	case 4:
//		m_text->LoadXFile("Models/text5.x", false);
//		m_text->SetScaling(1.0f);
//		break;
//	case 5:
//		m_text->LoadXFile("Models/text1.x", false);
//		m_text->SetScaling(1.0f);
//		break;
//	case 6:
//		m_text->LoadXFile("Models/text2.x", false);
//		m_text->SetScaling(1.0f);
//		break;
//	case 7:
//		m_text->LoadXFile("Models/text3.x", false);
//		m_text->SetScaling(1.0f);
//		break;
//	case 8:
//		m_text->LoadXFile("Models/text4.x", false);
//		m_text->SetScaling(1.0f);
//		break;
//	case 9:
//		m_text->LoadXFile("Models/text5.x", false);
//		m_text->SetScaling(1.0f);
//		break;
//	case 10:
//		m_text->LoadXFile("Models/text1.x", false);
//		m_text->SetScaling(1.0f);
//		break;
//	case 11:
//		m_text->LoadXFile("Models/text2.x", false);
//		m_text->SetScaling(1.0f);
//		break;
//	case 12:
//		m_text->LoadXFile("Models/text3.x", false);
//		m_text->SetScaling(1.0f);
//		break;
//	case 13:
//		m_text->LoadXFile("Models/text4.x", false);
//		m_text->SetScaling(1.0f);
//		break;
//	case 14:
//		m_text->LoadXFile("Models/text5.x", false);
//		m_text->SetScaling(1.0f);
//		break;
//	case 15:
//		m_text->LoadXFile("Models/text1.x", false);
//		m_text->SetScaling(1.0f);
//		break;
//	case 16:
//		m_text->LoadXFile("Models/text2.x", false);
//		m_text->SetScaling(1.0f);
//		break;
//	}
//}
//
//void Text::NextInitialize()
//{
//	m_next = new XManager;
//	m_next->Initialize();
//
//	m_nextPos = D3DXVECTOR3(-10.8f, 0.2f, 1.0f);
//	m_next->SetTranslation(m_nextPos);
//	m_next->SetScaling(0.08f,0.6f, 1.0f);
//	m_next->LoadXFile("Models/text5.x", false);
//
//	bInterval = true;
//	interVal = INTERVAL;
//	m_bEnable = false;
//}
//
//void Text::Update()
//{
//	m_text->Update();
//}
//
//void Text::NextUpdate()
//{
//	m_next->Update();
//}
//
//void Text::Draw()
//{
//	m_text->Draw();
//}
//
//void Text::NextDraw()
//{
//	m_next->Draw();
//}
//
//void Text::Finalize()
//{
//	m_text->Finalize();
//	delete m_text;
//}
//
//void Text::NextFinalize()
//{
//	m_next->Finalize();
//	delete m_next;
//}
//
//D3DXVECTOR3 Text::GetTextPos() {
//	return m_textPos;
//}
//
//bool Text::IsEnable() {
//	return m_bEnable;
//}
//
//
//void Text::TrueChange() {
//	m_bEnable = true;
//}
//
//void Text::FalseChange() {
//	m_bEnable = false;
//}
//
//void Text::CheckInterval() {
//	if (bInterval)
//	{
//		interVal--;
//		if (interVal <= 0)
//		{
//			bInterval = false;
//			interVal = INTERVAL;
//		}
//	}
//}
//
//void Text::StartInterval() {
//	bInterval = true;
//}
//
////int Text::GetInterval() {
////	return interVal;
////}
//
//bool Text::GetbInterval() {
//	return bInterval;
//}