#include "stdafx.h"
#include "playGround.h"

playGround::playGround()
{
}


playGround::~playGround()
{
}

HRESULT playGround::init()
{
	gameNode::init(true);

	_mapEditor = new mapEditor;
	_testMap = new testMap;
	



	SCENEMANAGER->addScene("mapEditor", _mapEditor);
	SCENEMANAGER->addScene("testMap", _testMap);
	

	SCENEMANAGER->changeScene("testMap");


	return S_OK;
}

void playGround::release()
{
	gameNode::release();
	
}

void playGround::update()
{
	gameNode::update();

	SCENEMANAGER->update();

}

void playGround::render()
{
	// Draw 시작 - 이 코드가 빠지면 D2D 출력 X
	D2DMANAGER->beginDraw();
	//===========================================================================
	//				##		여기에 코드 작성(Start)			##

	SCENEMANAGER->render();

	




	//				##			여기에 코드 작성(End)			##
	//===========================================================================
	//				##카메라 정보 마우스 정보 시간정보 출력	##===================
	WCHAR str[128];
	swprintf_s(str, L"cameraX : %d", CAMERA2D->getCamPosX());
	D2DMANAGER->drawText(str, CAMERA2D->getCamPosX(), CAMERA2D->getCamPosY() + 80);
	swprintf_s(str, L"cameraY : %d", CAMERA2D->getCamPosY());
	D2DMANAGER->drawText(str, CAMERA2D->getCamPosX(), CAMERA2D->getCamPosY() + 100);
	swprintf_s(str, L"mouse : [%.1f %.1f]", _ptMouse.x, _ptMouse.y);
	D2DMANAGER->drawText(str, CAMERA2D->getCamPosX(), CAMERA2D->getCamPosY() + 140);
	swprintf_s(str, L"mouseABS : [%.1f %.1f]", _ptMouseAbs.x, _ptMouseAbs.y);
	D2DMANAGER->drawText(str, CAMERA2D->getCamPosX(), CAMERA2D->getCamPosY() + 160);

	//int aaaa = 10;
	//wstring aaa = L"아나" + to_wstring(aaaa);
	//D2DMANAGER->drawText(aaa.c_str(), CAMERA2D->getCamPosX(), CAMERA2D->getCamPosY() + 200);

	//TIMEMANAGER->render();
	// Draw 끝 - 이 코드가 빠지면 D2D 출력 X
	D2DMANAGER->endDraw();
}