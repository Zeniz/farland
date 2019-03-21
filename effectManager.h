#pragma once
#include "singletonBase.h"
#include <vector>
#include <map>

class effect;

class effectManager : public singletonBase<effectManager>
{
private:
	//����
	typedef vector<effect*>								arrEffects;			//	���۸�ŭ ��������Ʈ�� �߰��Ѵ�.
	typedef vector<effect*>::iterator					iterEffects;
	//����
	typedef map<string, arrEffects>						arrEffect;			//	�� ���ۺ��Ϳ� �̸��� �ٿ� map���� �����Ѵ�.
	typedef map<string, arrEffects>::iterator			iterEffect;
	//����
	typedef vector<map<string, arrEffects>>				arrTotalEffect;
	typedef vector<map<string, arrEffects>>::iterator	iterTotalEffect;

private:

	arrEffect _mEffects;				//	�������� ��������� map<string, vector>

	arrTotalEffect _vTotalEffect;

public:
	effectManager();
	~effectManager();

	HRESULT init();
	void release();
	void update();
	void render();
	void renderReverseX();

	void addEffect(string effectName, string imageName, int imageWidth, int imageHeight,
		int effectWidth, int effectHeight, int fps, float elapsedTime, int buffer);

	void play(string effectName, int x, int y);
};

