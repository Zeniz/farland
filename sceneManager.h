#pragma once
#include "singletonBase.h"
#include <map>

//���� ���� ���ӳ�� ���漱��
class gameNode;

class sceneManager : public singletonBase<sceneManager>
{
public:
	typedef map<string, gameNode*>			 mapSceneList;
	typedef map<string, gameNode*>::iterator mapSceneIter;

private:
	static gameNode*	_currentScene;	//���� ��
	mapSceneList		_mSceneList;

	string _curSceneName;
	string _preSceneName;

public:
	sceneManager();
	~sceneManager();

	HRESULT init();
	void release();
	void update();
	void render();

	//�� �߰� �Ծ�
	gameNode* addScene(string sceneName, gameNode* scene);

	//�� ���� �Ծ�
	HRESULT changeScene(string sceneName);

	void setCurSceneName(string curSceneName) { _curSceneName = curSceneName.c_str(); }
	string getCurSceneName() { return _curSceneName.c_str(); }

	void setPreSceneName(string preSceneName) { _preSceneName = preSceneName.c_str(); }
	string getPreSceneName() { return _preSceneName.c_str(); }


};

