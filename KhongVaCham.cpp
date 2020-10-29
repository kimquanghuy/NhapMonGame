#include"KhongVaCham.h"
void kvc::Render()
{
	animation_set->at(0)->Render(x, y);
	//RenderBBox();
}
void kvc::GetBBox(float& l, float& t, float& r, float& b)
{
}