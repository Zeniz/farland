#include "stdafx.h"
#include "utils.h"


namespace CCY_ZENIZ_UTIL
{
	bool PtInDiamond(float centerX, float centerY, POINTF ptMouse) {

		if (abs((centerX - ptMouse.x) / centerX) + abs((centerY - ptMouse.y) / centerY) < 1) {
			return true;
		}
		return false;
	}

	bool PtInDiamond(POINT centerPos, POINTF ptMouse)
	{
		
		POINTF pos = { centerPos.x, centerPos.y };
		if (fabs(pos.x - ptMouse.x) / (64) + fabs(pos.y - ptMouse.y) / 32 < 1) {
			return true;
		}

		//if (fabs(ptMouse.x) / centerPos.x + fabs(ptMouse.x) / centerPos.y < 1) {
		//	return true;
		//}


		return false;
	}



	POINT ConvertIdxToPos(int idxX, int idxY, int tileWid, int tileHei)
	{
		POINT pos;
		pos.x = ((idxX - idxY) * (tileWid / 2));			//tmpPt.x = WINSIZEX / 2 - (i*(TILESIZE_WID / 2)) + (j*(TILESIZE_WID / 2));
		pos.y = tileHei / 2 + ((idxY + idxX) * (tileHei / 2));			//TILESIZE_HEI / 2 + (i * (TILESIZE_HEI / 2)) + (j * (TILESIZE_HEI/2));

		return pos;
	}

	POINT ConvertPosToIdx(int posX, int posY, int tileWid, int tileHei)
	{
		POINT idx;
		
		idx.x = (2 * (posY) + (posX)) / tileWid;
		idx.y = (2 * (posY) + - (posX)) / tileWid;

		return idx;
	}

	const wstring MakeImageName(const WCHAR * imageName, const WCHAR * folderName)
	{
		wstring str = L"";

		if (nullptr != folderName)
		{
			str.append(folderName);
			str.append(L"/");
		}

		str.append(imageName);
		str.append(L".bmp");
		
		return str;
	}
	const wstring AppendInt(const WCHAR * imageName, int value)
	{
		wstring str = L"";

		str.append(imageName);
		str.append(to_wstring(value));

		return str;
	}

	POINT PointMake(int x, int y)
	{
		POINT pt = { x, y };

		return pt;
	}
	POINTF PointFMake(float x, float y)
	{
		POINTF pt = { x, y };

		return pt;
	}
	void LineMake(HDC hdc, int startX, int startY, int endX, int endY, bool isAbsolut)
	{
		float posX;
		float posY;
		float posX2;
		float posY2;

		if (isAbsolut) {
			posX = startX;
			posY = startY;
			posX2 = endX;
			posY2 = endY;
		}
		else {
			posX = startX - (int)CAMERA2D->getCamPosX();
			posY = startY - (int)CAMERA2D->getCamPosY();
			posX2 = endX - (int)CAMERA2D->getCamPosX();
			posY2 = endY - (int)CAMERA2D->getCamPosY();
		}

		MoveToEx(hdc, posX, posY, NULL);
		LineTo(hdc, posX2, posY2);
	}
	void LineMake(HDC hdc, POINTF start, POINTF end, bool isAbsolut)
	{
		float posX;
		float posY;
		float posX2;
		float posY2;

		if (isAbsolut) {
			posX = start.x;
			posY = start.y;
			posX2 = end.x;
			posY2 = end.y;
		}
		else {
			posX = start.x - (int)CAMERA2D->getCamPosX();
			posY = start.y - (int)CAMERA2D->getCamPosY();
			posX2 = end.x - (int)CAMERA2D->getCamPosX();
			posY2 = end.y - (int)CAMERA2D->getCamPosY();
		}

		MoveToEx(hdc, posX, posY, NULL);
		LineTo(hdc, posX2, posY2);
	}
	RECT RectMake(int x, int y, int width, int height)
	{
		RECT rc = { x, y, x + width, y + height };
		return rc;
	}
	RECT RectMakeCenter(int x, int y, int width, int height)
	{
		RECT rc = { x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2) };
		return rc;
	}



	ELLIPSE EllipseMake(float x, float y, float r)
	{
		ELLIPSE rt;
		rt.p.x = x;
		rt.p.y = y;
		rt.r = r;
		return rt;
	}

	float RadToDeg(float angle)
	{
		if (angle < 0)		angle += PI2;
		if (angle >= PI2)	angle -= PI2;


		return angle * (180.0f / PI);
	}
	float DegToRad(float angle)
	{
		if (angle < 0)		angle += 360;
		if (angle >= 360)	angle -= 360;

		return angle * (PI / 180.0f);
	}
	//거리 구하는 함수
	float getDistance(float x1, float y1, float x2, float y2)
	{
		float x = x2 - x1;
		float y = y2 - y1;

		return (x * x + y * y);
	}

	float getDistance(POINTF & p1, POINTF & p2)
	{
		return (p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y);
	}

	bool EllipseCollision(ELLIPSE & e1, ELLIPSE & e2)
	{
		float d = e1.r + e2.r;
		return ((d*d) >= getDistance(e1.p, e2.p));
	}

	float getCenter(float a, float b)
	{
		return a + (b - a) / 2;
	}

	POINT getRectCenter(RECT & rc)
	{
		POINT p;
		p.x = getCenter(rc.left, rc.right);
		p.y = getCenter(rc.top, rc.bottom);
		return p;
	}

	float getRectXCenter(RECT & rc)
	{
		return getCenter(rc.left, rc.right);
	}

	float getRectYCenter(RECT & rc)
	{
		return getCenter(rc.top, rc.bottom);
	}

	float getRectWidth(RECT & rc)
	{
		return rc.right - rc.left;
	}

	float getRectHeight(RECT & rc)
	{
		return rc.bottom - rc.top;
	}

	bool PtInEllipse(ELLIPSE & e, POINTF p)
	{
		return ((e.r * e.r) >= getDistance(e.p, p));
	}

	bool PtInEllipse(ELLIPSE & e, float x, float y)
	{
		return ((e.r * e.r) >= getDistance(e.p.x, e.p.y, x, y));
	}

	float dCosf(float angle)
	{
		return cosf(DegToRad(angle));
	}

	float dSinf(float angle)
	{
		return sinf(DegToRad(angle));
	}

	float getAngle(POINTF p, POINTF target)
	{
		float angle = -atan2f(target.y - p.y, target.x - p.x);

		if (angle < 0)		angle += PI2;
		if (angle > PI2)	angle -= PI2;
		return angle;
	}

	float getAngle(float x, float y, float x2, float y2)
	{
		float angle = -atan2f(y2 - y, x2 - x);

		if (angle < 0)		angle += PI2;
		if (angle > PI2)	angle -= PI2;
		return angle;
		
	}

	float getAngle2(POINTF p, POINTF target)
	{
		float angle;
		float deltaX = target.x - p.x;
		float deltaY = target.y - p.y;
		float distance = sqrtf(deltaX* deltaX + deltaY * deltaY);
		angle = acosf(deltaX / distance);
		if (deltaY < 0)
		{
			angle = 2 * PI - angle;
			if (angle > 2 * PI) angle -= 2 * PI;
		}
		return angle;
	}

	float getAngle2(float x, float y, float x2, float y2)
	{
		float angle;
		float deltaX = x2 - x;
		float deltaY = y2 - y;
		float distance = sqrtf(deltaX* deltaX + deltaY * deltaY);
		angle = acosf(deltaX / distance);
		if (deltaY < 0)
		{
			angle = 2 * PI - angle;
			if (angle > 2 * PI) angle -= 2 * PI;
		}
		return angle;
	}

	float dGetAngle(POINTF target, POINTF p)
	{
		return RadToDeg(-atan2f(target.y - p.y, target.x - p.x));
	}

	float dGetAngle(float x2, float y2, float x, float y)
	{
		return RadToDeg(-atan2f(y2 - y, x2 - x));
	}

	float dGetAngle2(POINTF target, POINTF p)
	{
		float angle;
		float deltaX = target.x - p.x;
		float deltaY = target.y - p.y;
		float distance = sqrtf(deltaX* deltaX + deltaY * deltaY);
		angle = acosf(deltaX / distance);
		if (deltaY < 0)
		{
			angle = 2 * PI - angle;
		}
		return RadToDeg(angle);
	}

	float dGetAngle2(float x2, float y2, float x, float y)
	{
		float angle;
		float deltaX = x2 - x;
		float deltaY = y2 - y;
		float distance = sqrtf(deltaX* deltaX + deltaY * deltaY);
		angle = acosf(deltaX / distance);
		if (deltaY < 0)
		{
			angle = 2 * PI - angle;
		}
		return RadToDeg(angle);
	}

	bool RectEllipseCollition(RECT & rc, ELLIPSE & e)
	{
		if ((rc.left <= e.p.x && e.p.x <= rc.right) || (rc.top <= e.p.y && e.p.y <= rc.bottom))
		{
			POINT p;
			p.x = e.p.x;
			p.y = e.p.y;
			RECT rc2 = { rc.left - e.r, rc.top - e.r, rc.right + e.r, rc.bottom + e.r };
			if (PtInRect(&rc2, p))return true;
		}
		else
		{
			POINTF p;
			p.x = rc.left;
			p.y = rc.top;
			if (PtInEllipse(e, p)) return true;
			p.x = rc.left;
			p.y = rc.bottom;
			if (PtInEllipse(e, p)) return true;
			p.x = rc.right;
			p.y = rc.top;
			if (PtInEllipse(e, p)) return true;
			p.x = rc.right;
			p.y = rc.bottom;
			if (PtInEllipse(e, p)) return true;
		}
		return false;
	}

	wstring string2wstring(string str)
	{

		int nLen = MultiByteToWideChar(CP_ACP, 0, &str[0], str.size(), NULL, NULL);
		wstring strUni(nLen, 0);
		MultiByteToWideChar(CP_ACP, 0, &str[0], str.size(), &strUni[0], nLen);

		return strUni;
	}

}