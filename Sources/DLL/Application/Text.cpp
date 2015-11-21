
#include "GL/glew.h"
#include "Text.h"


Text::Text() : font("UbuntuMono-B.ttf")
{
	font.FaceSize(16);
	font.CharMap(FT_Encoding::FT_ENCODING_UNICODE);
}

void Text::render(std::string line1, std::string line2)
{
	font.Render(line1.c_str(), -1, FTPoint(10.0, 26.0, 0.0), FTPoint(), FTGL::RENDER_ALL);
	font.Render(line2.c_str(), -1, FTPoint(10.0, 10.0, 0.0), FTPoint(), FTGL::RENDER_ALL);
}