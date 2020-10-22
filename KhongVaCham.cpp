#include"KhongVaCham.h"
void kvc::Render()
{
	animation_set->at(0)->Render(x, y);
	//RenderBBox();
}
void kvc::GetBBox(float& l, float& t, float& r, float& b)
{
	/*l = x; t = y;
	r = x + KVC_BBOX_W;
	b = y + KVC_BBOX_H;*/
}