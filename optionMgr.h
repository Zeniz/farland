#pragma once
#include "singletonBase.h"

enum class OPTION_KINDS {
	E_OPTION_NONE = -1,
	EFFECT_SOUND,
	BGM_VOLUME,

	E_OPTION_END,
};


class optionMgr : public singletonBase<optionMgr>
{
	bool _isOptionMode;
	int _selectedButtonIdx;

	image* _bgBox;
	wstring _titleStr;

	struct tagButton {
		image* img;
		POINT pos;
		RECT barRc;
		wstring name;
		COLORREF txtColor;
		float ratio;

		int frameY;

	};
	vector<tagButton> _vButtons;


	const int NAME_START_X = 570;
	const int NAME_START_Y = 256;
	const int NAME_END_Y = 400;			//	Max To 640
	const int SCROLL_BAR_START_X = 896;
	

	


public:
	optionMgr();
	~optionMgr();

	HRESULT init();
	void release();
	void update();
	void render();

	void AddButton(wstring name, float defaultValue);
	void AddButton(wstring name, float defaultValue, POINT pos, RECT rc, COLORREF txtColor);
	void setOptionMode(bool value) { _isOptionMode = true; }
	void setButtonTxtColor(int idx, COLORREF txtColor);
	void setDefault();

	float getRatioValue(OPTION_KINDS option) { 
		return _vButtons[(int)option].ratio; 
	}

	bool getIsOptionMode() { return _isOptionMode; }

};

