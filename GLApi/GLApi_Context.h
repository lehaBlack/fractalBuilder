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
	//���� ���������=60��
	//������ ������� ���������=0
	//������� ������� ���������=100
	double pM_[4][4];
	//��������� ���������� �� ����������������
	//� ���������� �� ��������+�������
	bool convert(double x, double y, double z, Vec3i &answer);
public:
	GLibContext(int width, int height, int bbp);
	~GLibContext();
};

