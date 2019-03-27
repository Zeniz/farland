#include "stdafx.h"
#include "optionMgr.h"


optionMgr::optionMgr()
{
}


optionMgr::~optionMgr()
{
}

HRESULT optionMgr::init()
{
	IMAGEMANAGER->addImage("optionBg", L"images/option/bg.png", 640, 640);
	IMAGEMANAGER->addFrameImage("optionBarImg", L"images/option/scrollBar.png", 230, 50, 1, 2);
	_bgBox = IMAGEMANAGER->findImage("optionBg");
	

	_titleStr = L"-  OPTION  -";

	_vButtons.clear();
	_isOptionMode = false;
	_selectedButtonIdx = -1;


	//	값 추가시, 이넘도 추가해줄 것.
	this->AddButton(L"Effect Sound", 0.5f);
	this->AddButton(L"BGM Volume", 0.5f);

	this->AddButton(L"Set Default", 0.f, PointMake(590,720), RectMake(570,720,150,20), 0xFFFFFF);
	this->AddButton(L"Back to Title", 0.f, PointMake(840, 720), RectMake(810, 720, 180, 20), 0xFFFFFF);


	return S_OK;
}

void optionMgr::release()
{
}

void optionMgr::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE)) {
		_isOptionMode = !_isOptionMode;
	}
	if (_isOptionMode) {
		int backIdx = _vButtons.size() - 1;
		int defaultIdx = _vButtons.size() - 2;

		_vButtons[defaultIdx].txtColor = 0xFFFFFF;
		_vButtons[backIdx].txtColor = 0xFFFFFF;

		if (PtInRect(&_vButtons[defaultIdx].barRc, PointMake(_ptMouseAbs.x, _ptMouseAbs.y))) {
			_vButtons[defaultIdx].txtColor = 0x797979;
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				this->setDefault();
			}
		}
		if (PtInRect(&_vButtons[backIdx].barRc, PointMake(_ptMouseAbs.x, _ptMouseAbs.y))) {
			_vButtons[backIdx].txtColor = 0x797979;
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				_isOptionMode = false;
				SCENEMANAGER->changeScene("mainmenu");
			}
		}


		//	버튼 클릭관련
		for (int i = 0; i < _vButtons.size() - 2; i++) {
			if (PtInRect(&_vButtons[i].barRc, PointMake(_ptMouseAbs.x, _ptMouseAbs.y))) {
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
					_selectedButtonIdx = i;
				}
			}
		}

		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {
			_selectedButtonIdx = -1;
		}

		if (_selectedButtonIdx != -1) {
			float totalLength = _vButtons[_selectedButtonIdx].barRc.right - _vButtons[_selectedButtonIdx].barRc.left;
			float length = _ptMouseAbs.x - _vButtons[_selectedButtonIdx].barRc.left;

			if (length <= 0) { _vButtons[_selectedButtonIdx].ratio = 0.f; }
			else if (length >= totalLength) { _vButtons[_selectedButtonIdx].ratio = 1.0f; }
			else { _vButtons[_selectedButtonIdx].ratio = length / totalLength; }

			switch (_selectedButtonIdx)
			{
			case (int)OPTION_KINDS::BGM_VOLUME:
				SOUNDMANAGER->setBgmVolume(_vButtons[(int)OPTION_KINDS::BGM_VOLUME].ratio);
				break;

			case (int)OPTION_KINDS::EFFECT_SOUND:
				SOUNDMANAGER->setEffectVolume(_vButtons[(int)OPTION_KINDS::EFFECT_SOUND].ratio);
				break;


			default:
				break;
			}

		}
			






	}
}

void optionMgr::render()
{
	if (_isOptionMode) {
		_bgBox->renderABS(WINSIZEX/2 - _bgBox->GetFrameWidth() / 2, WINSIZEY/2 - _bgBox->GetFrameHeight()/2, 1.0f);
		D2DMANAGER->drawTextD2D(
			D2DMANAGER->createBrush(0xFFFFFF, 1.0f),
			L"consolas", 30,
			_titleStr.c_str(),
			WINSIZEX / 2 - (lstrlenW(_titleStr.c_str()) * 30)/4 + CAMERA2D->getCamPosX(),
			WINSIZEY / 2 - _bgBox->GetFrameHeight() / 2 + 50 + CAMERA2D->getCamPosY()
		);


		for (int i = 0; i < _vButtons.size(); i++) {
			D2DMANAGER->drawTextD2D(
				D2DMANAGER->createBrush(_vButtons[i].txtColor, 1.0f),
				L"consolas", 20,
				_vButtons[i].name.c_str(),
				(float)_vButtons[i].pos.x + CAMERA2D->getCamPosX(),
				(float)_vButtons[i].pos.y + CAMERA2D->getCamPosY()

			);
			if (_vButtons[i].img != nullptr) {
				_vButtons[i].img->frameRenderABS(
					_vButtons[i].barRc.left,
					_vButtons[i].barRc.top,
					_vButtons[i].barRc.right - _vButtons[i].barRc.left,
					_vButtons[i].barRc.bottom - _vButtons[i].barRc.top,
					0, 0, 1.0f
				);

				_vButtons[i].img->frameRenderABS(
					_vButtons[i].barRc.left,
					_vButtons[i].barRc.top,
					(float)(_vButtons[i].barRc.right - _vButtons[i].barRc.left) * _vButtons[i].ratio,
					_vButtons[i].barRc.bottom - _vButtons[i].barRc.top,
					0, 1, 1.0f
				);
			}
			

		}
	}
}

void optionMgr::AddButton(wstring name, float defaultValue)
{
	float yGap = 0;
	tagButton tmpButton;
	tmpButton.img = IMAGEMANAGER->findImage("optionBarImg");
	tmpButton.name = name.c_str();
	tmpButton.pos.x = NAME_START_X;
	tmpButton.ratio = defaultValue;
	tmpButton.txtColor = 0xFFFFFF;

	_vButtons.push_back(tmpButton);
	

	if(_vButtons.size() > 1)
		yGap = (NAME_END_Y - NAME_START_Y) / (_vButtons.size()-1);
	else {
		yGap = (NAME_END_Y - NAME_START_Y);
	}

	for (int i = 0; i < _vButtons.size(); i++) {
		_vButtons[i].pos.y = NAME_START_Y + i * yGap;
		_vButtons[i].barRc = RectMakeCenter(896, _vButtons[i].pos.y + tmpButton.img->GetFrameHeight() / 2, tmpButton.img->GetFrameWidth(), tmpButton.img->GetFrameHeight());
	}

	
	
	
}

void optionMgr::AddButton(wstring name, float defaultValue, POINT pos, RECT rc, COLORREF txtColor)
{
	float yGap = 0;
	tagButton tmpButton;
	tmpButton.img = nullptr;
	tmpButton.name = name.c_str();
	tmpButton.pos = pos;
	//tmpButton.pos.x = NAME_START_X;
	tmpButton.ratio = defaultValue;

	tmpButton.barRc = rc;

	tmpButton.txtColor = 0xFFFFFF;

	_vButtons.push_back(tmpButton);

}

void optionMgr::setButtonTxtColor(int idx, COLORREF txtColor)
{
	_vButtons[idx].txtColor = txtColor;
}

void optionMgr::setDefault()
{
	for (int i = 0; i < _vButtons.size() - 2; i++) {
		_vButtons[i].ratio = 0.5f;
	}
	SOUNDMANAGER->setBgmVolume(0.5f);
	SOUNDMANAGER->setEffectVolume(0.5f);
}
