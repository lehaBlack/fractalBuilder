#include "GLApi_Context.h"

bool GLibContext::convert(double x, double y, double z, Vec3i &answer)
{
	double v[4]{ x, y, z, 1.0 };
	double hmCoord[4];
	double res[3];
	//считаем однородные координаты
	hmCoord[0] = v[0] * pM_[0][0] + v[1] * pM_[0][1] + v[2] * pM_[0][2] + v[3] * pM_[0][3];
	hmCoord[1] = v[0] * pM_[1][0] + v[1] * pM_[1][1] + v[2] * pM_[1][2] + v[3] * pM_[1][3];
	hmCoord[2] = v[0] * pM_[2][0] + v[1] * pM_[2][1] + v[2] * pM_[2][2] + v[3] * pM_[2][3];
	hmCoord[3] = v[0] * pM_[3][0] + v[1] * pM_[3][1] + v[2] * pM_[3][2] + v[3] * pM_[3][3];
	//переводим однородные координаты в декартовы
	res[0] = hmCoord[0] / hmCoord[3];
	res[1] = hmCoord[1] / hmCoord[3];
	res[2] = hmCoord[2] / hmCoord[3];
	//переводим результат в координаты картинки
	answer.x_ = image_.get_width()+static_cast<int>(res[0] * image_.get_width()*0.5);
	answer.y_ = image_.get_height()+static_cast<int>(res[1] * image_.get_height()*0.5);
	answer.z_ = maxZ+static_cast<int>(res[2] * maxZ*0.5);
	//проверяем может ли эта тачка быть отрисованной
	for (int i=0;i<3;i++)
		if(abs(res[i])>1.0)
			return false;
	return true;
}

GLibContext::GLibContext(int width, int height, int bbp):
	image_(width,height,bbp),
	maxZ(1024)
{
	double aspect = static_cast<double>(width) / static_cast<double>(height);
	zBuffer_ = new int[width*height];
	double sr3 = sqrt(3.0);
	pM_[0][0] = sr3/aspect;
	pM_[0][1] = 0.0;
	pM_[0][2] = 0.0;
	pM_[0][3] = 0.0;

	pM_[1][0] = 0.0;
	pM_[1][1] = sr3;
	pM_[1][2] = 0.0;
	pM_[1][3] = 0.0;

	pM_[2][0] = 0.0;
	pM_[2][1] = 0.0;
	pM_[2][2] = -1.0;
	pM_[2][3] = 0.0;

	pM_[3][0] = 0.0;
	pM_[3][1] = 0.0;
	pM_[3][2] = 1.0;
	pM_[3][3] = 0.0;
}

GLibContext::~GLibContext()
{
	delete[] zBuffer_;
}
