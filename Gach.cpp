#include"Gach.h"
void Gach::Render()
{
	animation_set->at(0)->Render(x, y);
	//RenderBBox();
}
void Gach::GetBBox(float& l, float& t, float& r, float& b)
{
	l = x; t = y;
	r = x + GACH_BBOX_W;
	b = y + GACH_BBOX_H;
}