#pragma once
#include "GlApi.h"
#include <glib\glLib.h>
#include <stack>
class GLibContext
{
private:
	TGAImage image_;
	int *zBuffer_;
	int maxZ;
	//угол объектива=60гр
	//нижняя граница отсечения=0
	//верхняя граница отсечения=100
	double pM_[4][4];
	//переводим координаты из пользовательских
	//в координаты на картинке+глубина
	bool convert(double x, double y, double z, Vec3i &answer);
public:
	GLibContext(int width, int height, int bbp);
	~GLibContext();
};

