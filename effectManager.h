#pragma once
#include "singletonBase.h"
#include <vector>
#include <map>

class effect;

class effectManager : public singletonBase<effectManager>
{
private:
	//생산
	typedef vector<effect*>								arrEffects;			//	버퍼만큼 같은이펙트를 추가한다.
	typedef vector<effect*>::iterator					iterEffects;
	//가공
	typedef map<string, arrEffects>						arrEffect;			//	그 버퍼벡터에 이름을 붙여 map으로 저장한다.
	typedef map<string, arrEffects>::iterator			iterEffect;
	//포장
	typedef vector<map<string, arrEffects>>				arrTotalEffect;
	typedef vector<map<string, arrEffects>>::iterator	iterTotalEffect;

private:

	arrEffect _mEffects;				//	수정중인 최종저장소 map<string, vector>

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

