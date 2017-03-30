#include "GLApi_Context.h"

bool GlApi::GLibContext::convert(double x, double y, double z, Vec3i &answer)
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
	answer.z_ = maxZ_+static_cast<int>(res[2] * maxZ_*0.5);
	//проверяем может ли эта тачка быть отрисованной
	for (int i=0;i<3;i++)
		if(abs(res[i])>1.0)
			return false;
	return true;
}

void GlApi::GLibContext::drawPoint(double x, double y, double z, const byte* color)
{
	TGAColor c(color,4);
	Vec3i v;
	convert(x, y, z, v);
	glLib::point(v, image_, c, zBuffer_);
}

void GlApi::GLibContext::drawLine(double x0, double y0, double z0, double x1, double y1, double z1, const byte * color)
{
	Vec3i v0, v1;
	TGAColor c0(color, 4);
	convert(x0, y0, z0, v0);
	convert(x1, y1, z1, v1);
	glLib::line(v0, v1, image_, c0, zBuffer_);
}

void GlApi::GLibContext::drawLine(double x0, double y0, double z0, double x1, double y1, double z1, const byte * color0, const byte * color1)
{
	Vec3i v0, v1;
	TGAColor c0(color0, 4);
	TGAColor c1(color1, 4);
	convert(x0, y0, z0, v0);
	convert(x1, y1, z1, v1);
	glLib::line(v0,v1, image_, c0,c1, zBuffer_);
}

void GlApi::GLibContext::drawTriangle(double x0, double y0, double z0, double x1, double y1, double z1, double x2, double y2, double z2, const byte * color)
{
	Vec3i v0, v1,v2;
	TGAColor c(color, 4);
	convert(x0, y0, z0, v0);
	convert(x1, y1, z1, v1);
	convert(x2, y2, z2, v2);
	glLib::triangle(v0, v1, v2, image_, c, zBuffer_);
}

void GlApi::GLibContext::drawTriangle(double x0, double y0, double z0, double x1, double y1, double z1, double x2, double y2, double z2, const byte * color0, const byte * color1, const byte * color2)
{
	Vec3i v0, v1, v2;
	TGAColor c0(color0, 4);
	TGAColor c1(color1, 4);
	TGAColor c2(color2, 4);
	convert(x0, y0, z0, v0);
	convert(x1, y1, z1, v1);
	convert(x2, y2, z2, v2);
	glLib::triangle(v0, v1, v2, image_, c0, c1, c2, zBuffer_);
}

void GlApi::GLibContext::drawLine(const ColoredVert & v0, const ColoredVert & v1)
{
	if (v0.color1i== v1.color1i)
	{
		drawLine(
			v0.x(), v0.y(), v0.z(),
			v1.x(), v1.y(), v1.z(),
			v0.color4B);
	}
	else
	{
		drawLine(
			v0.x(), v0.y(), v0.z(),
			v1.x(), v1.y(), v1.z(),
			v0.color4B, v1.color4B);
	}
}

void GlApi::GLibContext::drawTriangle(const ColoredVert & v0, const ColoredVert & v1, const ColoredVert & v2)
{
	if (v0.color1i == v1.color1i&&v2.color1i == v1.color1i)
	{
		drawTriangle(
			v0.x(), v0.y(), v0.z(),
			v1.x(), v1.y(), v1.z(),
			v2.x(), v2.y(), v2.z(),
			v0.color4B);
	}
	else
	{
		drawTriangle(
			v0.x(), v0.y(), v0.z(),
			v1.x(), v1.y(), v1.z(),
			v2.x(), v2.y(), v2.z(),
			v0.color4B, v1.color4B, v2.color4B);
	}
}

void GlApi::GLibContext::drawQuade(const ColoredVert & v0, const ColoredVert & v1, 
	const ColoredVert & v2, const ColoredVert & v3)
{
	drawTriangle(v0, v1, v2);
	drawTriangle(v2, v3, v0);
}

void GlApi::GLibContext::TPoints()
{
	while (vertexStor_.size() > 0)
	{
		coordVertT& v = vertexStor_.front();
		drawPoint(v.x(), v.y(), v.z(), v.color4B);
	}
}

void GlApi::GLibContext::TLines()
{
	while (vertexStor_.size() > 1)
	{
		coordVertT& v0 = vertexStor_[0];
		coordVertT& v1 = vertexStor_[1];
		vertexStor_.erase(vertexStor_.begin(), vertexStor_.begin()+2);
		drawLine(v0, v1);
	}
}

void GlApi::GLibContext::TLinesLoop()
{
	bool lastIteration = false;
	if (vertexStor_.size() < 2)
		return;
	coordVertT& v0 = vertexStor_.front();
	vertexStor_.pop_front();
	coordVertT v1 = v0;
	coordVertT v2;
	do
	{
		if (vertexStor_.size() > 0)
		{
			v2 = vertexStor_.front();
			vertexStor_.pop_front();
		}

		drawLine(v1, v2);

		v1 = v2;
		if (lastIteration)
			break;
		if (vertexStor_.size() == 0)
		{
			v2 = v0;
			lastIteration = true;
		}
	} while (true);
}

void GlApi::GLibContext::TLinesStrip()
{
	if (vertexStor_.size() < 2)
		return;
	coordVertT v0 = vertexStor_.front();
	vertexStor_.pop_front();

	while (vertexStor_.size() > 0);
	{
		coordVertT &v1 = vertexStor_.front();
		vertexStor_.pop_front();

		drawLine(v0, v1);

		v0 = v1;
	}
}

void GlApi::GLibContext::Ttriangles()
{
	while (vertexStor_.size() > 2)
	{
		coordVertT& v0 = vertexStor_[0];
		coordVertT& v1 = vertexStor_[1];
		coordVertT& v2 = vertexStor_[2];
		vertexStor_.erase(vertexStor_.begin(), vertexStor_.begin() + 3);
		drawTriangle(v0, v1, v2);
	}
}

void GlApi::GLibContext::TtrianglesStrip()
{
	bool lastIteration = false;
	if (vertexStor_.size() < 2)
		return;
	coordVertT v0 = vertexStor_[0];
	coordVertT v1 = vertexStor_[1];

	vertexStor_.erase(vertexStor_.begin(), vertexStor_.begin() + 2);

	while (vertexStor_.size() > 0);
	{
		coordVertT &v2 = vertexStor_.front();
		vertexStor_.pop_front();

		drawTriangle(v0,v1, v2);

		v0 = v1;
		v1 = v2;
	}
}

void GlApi::GLibContext::TtrianglesFan()
{
	bool lastIteration = false;
	if (vertexStor_.size() < 3)
		return;
	coordVertT& v0 = vertexStor_[0];
	coordVertT  v1 = vertexStor_[1];
	vertexStor_.erase(vertexStor_.begin(), vertexStor_.begin() + 2);
	while (vertexStor_.size() > 0)
	{
		coordVertT& v2 = vertexStor_.front();
		vertexStor_.pop_front();

		drawTriangle(v0,v1, v2);
		v1 = v2;
	}
}

void GlApi::GLibContext::Tquads()
{
	while (vertexStor_.size() > 3)
	{
		coordVertT& v0 = vertexStor_[0];
		coordVertT& v1 = vertexStor_[1];
		coordVertT& v2 = vertexStor_[2];
		coordVertT& v3 = vertexStor_[3];
		vertexStor_.erase(vertexStor_.begin(), vertexStor_.begin() + 4);
		drawQuade(v0, v1, v2, v3);
	}
}

void GlApi::GLibContext::TquadsStrip()
{
	if (vertexStor_.size() < 4)
		return;
	coordVertT v0 = vertexStor_[0];
	coordVertT v1 = vertexStor_[1];
	vertexStor_.erase(vertexStor_.begin(), vertexStor_.begin() + 2);

	while (vertexStor_.size() > 0);
	{
		coordVertT &v2 = vertexStor_[0];
		coordVertT &v3 = vertexStor_[1];
		vertexStor_.erase(vertexStor_.begin(), vertexStor_.begin() + 2);

		drawQuade(v0, v1, v2, v3);

		v0 = v2;
		v1 = v3;
	}
}

void GlApi::GLibContext::Tprocessing()
{
	/*
	GlApi_POLYGON		 = GL_POLYGON,
	*/
	switch (mode_)
	{
	case GlApi_POINTS:
	{
		TPoints();
		break;
	}
	case GlApi_LINES:
	{
		TLines();
		break;
	}
	case GlApi_LINE_LOOP:
	{
		TLinesLoop();
		break;
	}
	case GlApi_LINE_STRIP:
	{
		TLinesStrip();
		break;
	}
	case GlApi_TRIANGLES:
	{
		Ttriangles();
		break;
	}
	case GlApi_TRIANGLE_STRIP:
	{
		TtrianglesStrip();
		break;
	}
	case GlApi_TRIANGLE_FAN:
	{
		TtrianglesFan();
		break;
	}
	case GlApi_QUADS:
	{
		Tquads();
		break;
	}
	case GlApi_QUAD_STRIP:
	{
		TquadsStrip();
		break;
	}
	case GlApi_POLYGON:
	{
		throw std::exception("error GlApi_POLYGON not yet implemented");
		break;
	}
	}
}

GlApi::GLibContext::GLibContext(int width, int height):
	image_(width,height,4),
	maxZ_(1024),
	mode_(GlApi_NOT_INIT),
	pointW_(1)
{
	selectedColor_[0] = 255;
	selectedColor_[1] = 255;
	selectedColor_[2] = 255;
	selectedColor_[3] = 255;

	clearColor_[0] = 0;
	clearColor_[1] = 0;
	clearColor_[2] = 0;
	clearColor_[3] = 255;

	translatedV_[0] = 0.0;
	translatedV_[1] = 0.0;
	translatedV_[2] = 0.0;

	double aspect = static_cast<double>(width) / static_cast<double>(height);
	zBuffer_ = new int[width*height];
	GLibPerspective(45.0, aspect, 0.1, 100.0);
}

void GlApi::GLibContext::GLibPerspective(double fovy, GLdouble aspect, GLdouble n, GLdouble f)
{
	double sr = 1.0/tan((fovy*M_PI/180.0)*0.5);
	pM_[0][0] = sr/aspect;
	pM_[0][1] = 0.0;
	pM_[0][2] = 0.0;
	pM_[0][3] = 0.0;

	pM_[1][0] = 0.0;
	pM_[1][1] = sr;
	pM_[1][2] = 0.0;
	pM_[1][3] = 0.0;

	pM_[2][0] = 0.0;
	pM_[2][1] = 0.0;
	pM_[2][2] = (f+n)/(f-n);
	pM_[2][3] =(-2.0*f*n)/(f-n);

	pM_[3][0] = 0.0;
	pM_[3][1] = 0.0;
	pM_[3][2] = 1.0;
	pM_[3][3] = 0.0;
}

void GlApi::GLibContext::GLibBegin(BeginMode mode)
{
	GLibEnd();
	mode_ = mode;
}

void GlApi::GLibContext::GLibEnd()
{
	Tprocessing();
	mode_ = GlApi_NOT_INIT;
	vertexStor_.clear();
}

void GlApi::GLibContext::GLibClear()
{
	ZeroMemory(zBuffer_, image_.get_width()*image_.get_height() * sizeof(zBuffer_[0]));
	const int &c = *(int*)clearColor_;
	int* buffer = (int*)image_.buffer();
	for (int i = 0; i < image_.get_width()*image_.get_height(); i++)
	{
		buffer[i] = c;
	}
}

void GlApi::GLibContext::GLibColor4d(double r, double g, double b, double a)
{
	GLibColor4ub(
		static_cast<byte>(abs(r) * 255),
		static_cast<byte>(abs(g) * 255),
		static_cast<byte>(abs(b) * 255),
		static_cast<byte>(abs(a) * 255));
}

void GlApi::GLibContext::GLibColor3d(double r, double g, double b)
{
	GLibColor4d(r, g, b, 1.0);
}

void GlApi::GLibContext::GLibColor4f(float r, float g, float b, float a)
{
	GLibColor4ub(
		static_cast<byte>(abs(r) * 255),
		static_cast<byte>(abs(g) * 255),
		static_cast<byte>(abs(b) * 255),
		static_cast<byte>(abs(a) * 255));
}

void GlApi::GLibContext::GLibColor3f(float r, float g, float b)
{
	GLibColor4f(r, g, b, 1.0f);
}

void GlApi::GLibContext::GLibColor4ub(byte r, byte g, byte b, byte a)
{
	selectedColor_[0] = r;
	selectedColor_[1] = g;
	selectedColor_[2] = b;
	selectedColor_[3] = a;
}

void GlApi::GLibContext::GLibColor4b(char r, char g, char b, char a)
{
	GLibColor4ub(abs(r), abs(g), abs(b), abs(a));
}

void GlApi::GLibContext::GLibColor3ub(byte r, byte g, byte b)
{
	GLibColor4ub(r, g, b, 255);
}

void GlApi::GLibContext::GLibColor3b(char r, char g, char b)
{
	GLibColor4ub(abs(r), abs(g), abs(b), 255);
}

void GlApi::GLibContext::GLibColor4ui(unsigned int r, unsigned int g, unsigned int b, unsigned int a)
{
	GLibColor4ub(r, g, b, a);
}

void GlApi::GLibContext::GLibColor4i(int r, int g, int b, int a)
{
	GLibColor4ub(abs(r), abs(g), abs(b), abs(a));
}

void GlApi::GLibContext::GLibColor3ui(unsigned int r, unsigned int g, unsigned int b)
{
	GLibColor4ub(r, g, b, 255);
}

void GlApi::GLibContext::GLibColor3i(int r, int g, int b)
{
	GLibColor4ub(abs(r), abs(g), abs(b), 255);
}

void GlApi::GLibContext::GLibColor4us(unsigned short r, unsigned short g, unsigned short b, unsigned short a)
{
	GLibColor4ub(r, g, b, a);
}

void GlApi::GLibContext::GLibColor4s(short r, short g, short b, short a)
{
	GLibColor4ub(abs(r), abs(g), abs(b), abs(a));
}

void GlApi::GLibContext::GLibColor3us(unsigned short r, unsigned short g, unsigned short b)
{
	GLibColor4ub(r, g, b, 255);
}

void GlApi::GLibContext::GLibColor3s(short r, short g, short b)
{
	GLibColor4ub(abs(r), abs(g), abs(b), 255);
}

void GlApi::GLibContext::GLibVertex3d(double x, double y, double z)
{
	ColoredVert tmp;
	tmp.setColor(selectedColor_);

	tmp.x() = x + translatedV_[0];
	tmp.y() = y + translatedV_[1];
	tmp.z() = z + translatedV_[2];
	vertexStor_.push_back(tmp);
}

void GlApi::GLibContext::GLibVertex2d(double x, double y)
{
	GLibVertex3d(x, y, 0.0);
}

void GlApi::GLibContext::GLibVertex3f(float x, float y, float z)
{
	GLibVertex3d(
		static_cast<double>(x),
		static_cast<double>(y),
		static_cast<double>(z)
	);
}

void GlApi::GLibContext::GLibVertex2f(float x, float y)
{
	GLibVertex3f(x, y, 0.0f);
}

void GlApi::GLibContext::GLibVertex3s(short x, short y, short z)
{
	GLibVertex3d(
		static_cast<double>(x),
		static_cast<double>(y),
		static_cast<double>(z)
	);
}

void GlApi::GLibContext::GLibVertex2s(short x, short y)
{
	GLibVertex3s(x, y, 0);
}

void GlApi::GLibContext::GLibVertex3i(int x, int y, int z)
{
	GLibVertex3d(
		static_cast<double>(x),
		static_cast<double>(y),
		static_cast<double>(z)
	);
}

void GlApi::GLibContext::GLibVertex2i(int x, int y)
{
	GLibVertex3i(x, y, 0);
}

void GlApi::GLibContext::GLibTranslate(double x, double y, double z)
{
	translatedV_[0] = x;
	translatedV_[1] = y;
	translatedV_[2] = z;
}

void GlApi::GLibContext::GLibSave(const char * fileName)
{
	image_.write_tga_file(fileName);
}

GlApi::GLibContext::~GLibContext()
{
	delete[] zBuffer_;
}

GlApi::GLibContext::ColoredVert::ColoredVert()
{
	ZeroMemory(this, sizeof(*this));
}

GlApi::GLibContext::ColoredVert::ColoredVert(const ColoredVert &tmp)
{
	memcpy(this, &tmp, sizeof(tmp));
}

GlApi::GLibContext::ColoredVert & GlApi::GLibContext::ColoredVert::operator=(const ColoredVert &tmp)
{
	memcpy(this, &tmp, sizeof(tmp));
	return *this;
}

void GlApi::GLibContext::ColoredVert::setColor(byte * c)
{
	color1i = *(int*)c;
}

double & GlApi::GLibContext::ColoredVert::x()
{
	return coordinates[0];
}

double & GlApi::GLibContext::ColoredVert::y()
{
	return coordinates[1];
}

double & GlApi::GLibContext::ColoredVert::z()
{
	return coordinates[2];
}

const double & GlApi::GLibContext::ColoredVert::x() const
{
	return coordinates[0];
}

const double & GlApi::GLibContext::ColoredVert::y() const
{
	return coordinates[1];
}

const double & GlApi::GLibContext::ColoredVert::z() const
{
	return coordinates[2];
}
