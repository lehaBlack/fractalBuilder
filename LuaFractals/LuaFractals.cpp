// LuaFractals.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <fractals\fractals.h>
#include <fractals\TockensStream.h>
#include <glib\tgaimage.h>
#include <glib\glLib.h>
#include <GLApi\GLApi_Context.h>
int fractalScriptMain()
{
     fractals::scriptFileExec("testLuaFractal.lua");
     return 0;
}
int imageDebug()
{
     TGAImage image(200, 200, 3);
     Vec2i t0[3] = { Vec2i(180, 70),   Vec2i(50, 160),  Vec2i(70, 80) };
     Vec2i t1[3] = { Vec2i(10, 10),  Vec2i(10, 190),   Vec2i(390, 50) };
     Vec2i t2[3] = { Vec2i(180, 150), Vec2i(120, 160), Vec2i(130, 180) };
     
     TGAColor red(255, 0, 0);
     TGAColor green(0, 255, 0);
     TGAColor blue(0, 0, 255);

     //glLib::triangle(t0[0], t0[1], t0[2], image, red);
     glLib::triangle(t1[0], t1[1], t1[2], image, blue, red, green);
     //glLib::triangle(t2[0], t2[1], t2[2], image, green);

     image.write_tga_file("res.tga");
    return 0;
}
int glapiContextDebug()
{
     GlApi::GLibContext ctx(680,460);
     ctx.GLibBegin(GlApi::GlApi_QUADS);
     ctx.GLibTranslate(0.0, 0.0, -6.0);
     ctx.GLibColor3d(0.0, 0.0, 1.0);
     ctx.GLibVertex2d(0.0, 1.0);
     ctx.GLibColor3d(0.0, 1.0, 0.0);
     ctx.GLibVertex2d(0.0, 0.0);
     ctx.GLibColor3d(1.0, 0.0, 0.0);
     ctx.GLibVertex2d(1.0, 0.0);
     ctx.GLibVertex2d(1.0, 1.0);
     ctx.GLibEnd();
     ctx.GLibSave("context_test.tga");
     return 0;
}
int main()
{
     glapiContextDebug();
     return 0;
}
