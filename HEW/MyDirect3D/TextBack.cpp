//#include "main.h"
//#include "TextBack.h"
//
//
//TextBack::TextBack()
//{
//	Initialize();
//}
//
//
//TextBack::~TextBack()
//{
//
//}
//
//void TextBack::Initialize()
//{
//	m_textback = new XManager;
//	m_textback->Initialize();
//	m_textback->LoadXFile("Models/textback.x", false);
//
//	m_pos = D3DXVECTOR3(-10.0f, 1.5f, -1.0f);
//
//	m_textback->SetTranslation(m_pos);
//	m_textback->SetScaling(2.0f);
//}
//
//void TextBack::Update()
//{
//	m_textback->Update();
//}
//
//void TextBack::Draw()
//{
//	m_textback->Draw();
//}
//
//void TextBack::Finalize()
//{
//	m_textback->Finalize();
//	delete m_textback;
//}
//
//D3DXVECTOR3 TextBack::GetTextBackPos() {
//	return m_pos;
//}