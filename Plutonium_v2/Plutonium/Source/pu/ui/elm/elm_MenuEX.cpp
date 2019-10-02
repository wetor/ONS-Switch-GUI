#include <pu/ui/elm/elm_MenuEX.hpp>

namespace pu::ui::elm
{
void TransRect::SetSource(SDL_Rect rect)
{
    state = TRAN::BEGIN;
    curr = src = rect;
}
void TransRect::SetTarget(SDL_Rect rect, s32 time)
{
    state = TRAN::BEGIN;
    dst = rect;
    this->curr_time = this->time = time;
    if (time != 0)
    {
        speed_x = (dst.x - src.x) / time;
        speed_y = (dst.y - src.y) / time;
        speed_w = (dst.w - src.w) / time;
        speed_h = (dst.h - src.h) / time;
    }
    else
    {
        speed_x = speed_y = speed_w = speed_h = 0;
    }
}
void TransRect::SetRect(SDL_Rect src, SDL_Rect dst, s32 time)
{
    SetSource(src);
    SetTarget(dst, time);
    state = TRAN::BEGIN;
}
void TransRect::ReSet()
{
    curr_time = this->time;
    state = TRAN::BEGIN;
    curr = src;
}
void TransRect::Trans()
{
    if (state != TRAN::BEGIN)
        return;
    mode = 1;
    curr = src;
    state = TRAN::TRANS;
}
void TransRect::Restore()
{
    if (state != TRAN::END)
        return;
    mode = 2;
    curr = dst;
    state = TRAN::RESTROE;
}
void TransRect::End()
{
    ReSet();
    state = TRAN::END;
}
void TransRect::Update()
{
    if (curr_time <= 0)
    {
        if (state == TRAN::TRANS) //src to dst
        {
            End();
        }
        else if (state == TRAN::RESTROE) //dst to src
        {
            ReSet();
        }
    }
    if (state == TRAN::END || state == TRAN::BEGIN)
        return;
    curr_time--;

    if (state == TRAN::TRANS) //src to dst
    {
        curr.x += speed_x;
        curr.y += speed_y;
        curr.w += speed_w;
        curr.h += speed_h;
    }
    else if (state == TRAN::RESTROE) //dst to src
    {
        curr.x -= speed_x;
        curr.y -= speed_y;
        curr.w -= speed_w;
        curr.h -= speed_h;
    }
}
int TransRect::GetX()
{
    if (state == TRAN::BEGIN)
        return src.x;
    else if (state == TRAN::END)
        return dst.x;
    else
        return curr.x;
};
int TransRect::GetY()
{
    if (state == TRAN::BEGIN)
        return src.y;
    else if (state == TRAN::END)
        return dst.y;
    else
        return curr.y;
};
int TransRect::GetW()
{
    if (state == TRAN::BEGIN)
        return src.w;
    else if (state == TRAN::END)
        return dst.w;
    else
        return curr.w;
};
int TransRect::GetH()
{
    if (state == TRAN::BEGIN)
        return src.h;
    else if (state == TRAN::END)
        return dst.h;
    else
        return curr.h;
};

MenuEX::MenuEX(s32 X, s32 Y, s32 Width, s32 Height, Color OptionColor, s32 ItemSize, s32 SelectSize, s32 ItemsToShow) : Element::Element()
{
	this->h = Height;
	this->pretouch = false;
	this->uptime = false;
	this->uphold = false;
	this->downtime = false;
	this->downhold = false;
	this->move_step = 0;
	this->move_speed = 10;
	this->selsize = SelectSize;

	ItemsToShow += 2;
	this->alpha_count = 240;
	this->alpha_flag = 0;
	this->touch_area = new SDL_Rect[ItemsToShow];
	this->show_index = new u32[ItemsToShow];

	for (u32 i = 0; i < ItemsToShow; i++)
	{
		show_index[i] = 0;
	}



    this->x = X;
    this->y = Y;
    this->w = Width;
    this->clr = OptionColor;
    this->scb = {110, 110, 110, 255};
    this->isize = ItemSize;
    this->ishow = ItemsToShow;
    this->previsel = 0;
    this->isel = 0;
    this->fisel = 0;
    this->selfact = 255;
    this->pselfact = 0;
    this->onselch = [&]() {};
    this->icdown = false;
    this->dtouch = false;
    this->fcs = {40, 40, 40, 255};
    this->basestatus = 0;
    this->font = render::LoadDefaultFont(25);
	SetType(TYPE::TOP);
}

s32 MenuEX::GetX()
{
    return this->x;
}

void MenuEX::SetX(s32 X)
{
    this->x = X;
}

s32 MenuEX::GetY()
{
    return this->y;
}

void MenuEX::SetY(s32 Y)
{
    this->y = Y;
}

s32 MenuEX::GetWidth()
{
    return this->w;
}

void MenuEX::SetWidth(s32 Width)
{
    this->w = Width;
}

s32 MenuEX::GetHeight()
{
    return (this->isize * this->ishow);
}

s32 MenuEX::GetItemSize()
{
    return this->isize;
}

void MenuEX::SetItemSize(s32 ItemSize)
{
    this->isize = ItemSize;
}

s32 MenuEX::GetNumberOfItemsToShow()
{
    return this->ishow;
}

void MenuEX::SetNumberOfItemsToShow(s32 ItemsToShow)
{
    this->ishow = ItemsToShow;
}

Color MenuEX::GetColor()
{
    return this->clr;
}

void MenuEX::SetColor(Color Color)
{
    this->clr = Color;
}

Color MenuEX::GetOnFocusColor()
{
    return this->fcs;
}

void MenuEX::SetOnFocusColor(Color Color)
{
    this->fcs = Color;
}

Color MenuEX::GetScrollbarColor()
{
    return this->scb;
}

void MenuEX::SetScrollbarColor(Color Color)
{
    this->scb = Color;
}

void MenuEX::SetOnSelectionChanged(std::function<void()> Callback)
{
    this->onselch = Callback;
}

void MenuEX::AddItem(MenuItem::Ref &Item)
{
    this->itms.push_back(Item);
}

void MenuEX::ClearItems()
{
    this->itms.clear();
    this->loadednames.clear();
    this->loadedicons.clear();
}

void MenuEX::SetCooldownEnabled(bool Cooldown)
{
    this->icdown = Cooldown;
}

MenuItem::Ref &MenuEX::GetSelectedItem()
{
    return this->itms[this->isel];
}

std::vector<MenuItem::Ref> &MenuEX::GetItems()
{
    return this->itms;
}

s32 MenuEX::GetSelectedIndex()
{
    return this->isel;
}

void MenuEX::SetSelectedIndex(s32 Index)
{
    if (this->itms.size() > Index)
    {
        this->isel = Index;
        this->fisel = 0;
        if (this->isel >= (this->itms.size() - this->ishow))
            this->fisel = this->itms.size() - this->ishow;
        else if (this->isel < this->ishow)
            this->fisel = 0;
        else
            this->fisel = this->isel;

        ReloadItemRenders();
        this->selfact = 255;
        this->pselfact = 0;
    }
}
s32 MenuEX::GetSelectSize()
{
	return this->selsize;
}
void MenuEX::SetSelectSize(s32 SelectSize)
{
	this->selsize = SelectSize;
}
TYPE MenuEX::GetType(){
	return this->draw_type;
}
void MenuEX::SetType(TYPE type)
{
	this->draw_type = type;
	switch (type)
	{
	case TYPE::TOP:
		this->selrect.SetRect({0, y, isize, isize}, {0, y, selsize, selsize}, 10);
		this->prerect.SetRect({0, y, selsize, selsize}, {0, y, isize, isize}, 10);
		this->disrect.SetRect({0, 0, 0, 0}, {(selsize - isize) / 2, 0, isize - selsize, isize - selsize}, 10);
		break;
	case TYPE::DOWN:
		this->selrect.SetRect({0, y + h - isize, isize, isize}, {0, y + h - selsize, selsize, selsize}, 10);
		this->prerect.SetRect({0, y + h - selsize, selsize, selsize}, {0, y + h - isize, isize, isize}, 10);
		this->disrect.SetRect({0, 0, 0, 0}, {(selsize - isize) / 2, selsize - isize, isize - selsize, isize - selsize}, 10);
		break;
	default:
		break;
	}
	this->SetDisable(Element::IsDisable());
}
void MenuEX::SetDisable(bool Disable)
{
	printf("set disable %d \n", Disable);
	if (Disable)
		this->disrect.Trans();
	else
		this->disrect.Restore();
	Element::SetDisable(Disable);
}
void MenuEX::OnRender(render::Renderer::Ref &Drawer, s32 X, s32 Y)
{
    if (!this->itms.empty())
	{
		if (this->selrect.GetState() == TRAN::BEGIN)
			this->selrect.End();
		if (this->prerect.GetState() == TRAN::BEGIN)
			this->prerect.End();

		this->selrect.Update();
		this->prerect.Update();
		this->disrect.Update();

		if (this->move_step <= -this->move_speed)
			this->move_step += this->move_speed;
		else if (this->move_step >= this->move_speed)
			this->move_step -= this->move_speed;
		else
			this->move_step = 0;

		s32 cx, sx, cy;
		s32 cw, ch;
		sx = this->x - this->isize * 3 / 2 + this->move_step;
		//u32 its = this->ishow;
		//if (its > this->itms.size()) its = this->itms.size();
		//for(u32 i = this->fisel; i < (its + this->fisel); i++)

		for (u32 ii = 0; ii < this->ishow; ii++)
		{
			cx = sx;
			cx += this->disrect.GetX();
			if (this->draw_type == TYPE::TOP)
			{
				cy = this->y;
			}
			else if (this->draw_type == TYPE::DOWN)
			{
				cy = this->y + this->h - this->isize;
			}
			u32 i = show_index[ii];
			cw = this->isize;
			ch = this->isize;
			s32 clrr = this->clr.R;
			s32 clrg = this->clr.G;
			s32 clrb = this->clr.B;
			s32 nr = clrr - 70;
			if (nr < 0)
				nr = 0;
			s32 ng = clrg - 70;
			if (ng < 0)
				ng = 0;
			s32 nb = clrb - 70;
			if (nb < 0)
				nb = 0;
			Color nclr(nr, ng, nb, this->clr.A);
            auto loadedidx = i - this->fisel;
            auto curname = this->loadednames[loadedidx];
            auto curicon = this->loadedicons[loadedidx];
			//if (this->isel == i) //select into
			if(ii == this->ishow/2)
			{
				cy = this->selrect.GetY();
				cw = this->selrect.GetW();
				ch = this->selrect.GetH();

				//printf("w %d h %d state %d\n", cw, ch, selrect.GetState());
				cy += this->disrect.GetY();
				cw += this->disrect.GetW();
				ch += this->disrect.GetH();
				//printf("disrect y %d state %d\n", this->disrect.GetY(), this->disrect.GetState());
				//printf("sel x:%d y:%d w:%d h:%d\n",cx,cy,cw,ch);
				Drawer->RenderRectangleFill(this->clr, cx, cy, cw, ch);
				if (this->selfact < 240)
				{
					Drawer->RenderRectangleFill(Color(this->fcs.R, this->fcs.G, this->fcs.B, this->selfact), cx, cy, cw, ch);
					this->selfact += 6;
				}
				else
					Drawer->RenderRectangleFill(this->fcs, cx, cy, cw, ch);
			}
			else if (this->prev_index == ii) //select left
			{

				cy = this->prerect.GetY();
				cw = this->prerect.GetW();
				ch = this->prerect.GetH();
				//printf("pre x:%d y:%d w:%d h:%d\n",cx,cy,cw,ch);
				Drawer->RenderRectangleFill(this->clr, cx, cy, cw, ch);
				if (this->pselfact > 0)
				{
					Drawer->RenderRectangleFill(Color(this->fcs.R, this->fcs.G, this->fcs.B, this->pselfact), cx, cy, cw, ch);
					this->pselfact -= 10;
				}
				else
					Drawer->RenderRectangleFill(this->clr, cx, cy, cw, ch);
			}
			else
			{
				Drawer->RenderRectangleFill(this->clr, cx, cy, cw, ch);
			}

			auto itm = this->itms[i];
			u32 xh = render::GetTextHeight(this->font, itm->GetName());
			u32 xw = render::GetTextWidth(this->font, itm->GetName());

			u32 tx = cx + (cw - xw) / 2;
			u32 ty;
			if (this->draw_type == TYPE::TOP)
				ty = cy + ch + 10;
			else if (this->draw_type == TYPE::DOWN)
				ty = cy - xh - 10;
			if (itm->HasIcon())
			{
				u32 icd = (cw - 10);
				u32 icx = (cx + 5);
				u32 icy = (cy + 5);
				//ty = (icy + icd + 5);

				Drawer->RenderTextureScaled(curicon, icx, icy, icd, icd);
			}

			Drawer->RenderTexture(curname, tx, ty);

			if (this->isel == i)
			{
				Drawer->RenderRectangleEx(Color(5, 185, 140, this->alpha_count), cx, cy, cw, ch, 4);
				if (this->alpha_flag == 0 || this->alpha_count >= 240)
				{
					this->alpha_count -= 3;
					if (this->alpha_count <= 60)
						this->alpha_flag = 1;
				}
				else if (this->alpha_flag == 1 || this->alpha_count <= 60)
				{
					this->alpha_count += 3;
					if (this->alpha_count >= 240)
						this->alpha_flag = 0;
				}
			}
			touch_area[ii] = {cx, cy, cw, ch};
			sx += cw;
		}
	}
}



void MenuEX::OnInputTouch(u64 Down, u64 Up, u64 Held, bool Touch)
{
	touchPosition tch;
	hidTouchRead(&tch, 0);
	if ((tch.px >= x && tch.px <= x + w && tch.py >= y && tch.py <= y + h) || this->pretouch)
	{
		if (Down & KEY_TOUCH) //按下
		{

			this->touch_down.x = tch.px;
			this->touch_down.y = tch.py;
			touch_time = SDL_GetTicks();
			//printf("down  %d\n",touch_time);
		}
		else if (Held & KEY_TOUCH) //按住
		{
			if (touch_time > 0)
			{
				this->pretouch = true;
				this->touch_curr.x = tch.px;
				this->touch_curr.y = tch.py;
				int val = tch.px - this->touch_down.x; //计算按住移动量

				//根据移动量执行对应的方向键
				if (val > 0 && val > this->isize)
				{
					this->touch_down.x += this->isize;
					OnInputKey(TYPE::LEFT);
				}
				else if (val < 0 && -val > this->isize)
				{
					this->touch_down.x -= this->isize;
					OnInputKey(TYPE::RIGHT);
				}
			}
		}
		else
		{
			if (touch_time > 0)
			{
				this->pretouch = false;
				u32 held_time = SDL_GetTicks() - touch_time;
				int val1 = this->touch_curr.x - this->touch_down.x;
				int val2 = this->touch_curr.y - this->touch_down.y;

				if (held_time < 250 && ((val1 > 0 ? val1 : -val1) < 20) && ((val2 > 0 ? val2 : -val2) < 20))
				{
					//段时间轻触
					for (u32 i = 0; i < this->ishow; i++)
					{
						if ((touch_area[i].x + touch_area[i].w > this->touch_curr.x) &&
							(this->touch_curr.x > touch_area[i].x) &&
							((touch_area[i].y + touch_area[i].h) > this->touch_curr.y) &&
							(this->touch_curr.y > touch_area[i].y))
						{
							//在第i个item范围内
							if (this->isel == show_index[i])
								this->dtouch = true;
							else
							{
								this->selrect.ReSet();
								this->selrect.Trans();
							}

							int move_step = i - this->ishow / 2;

							//根据轻触位置计算移动方向
							if (this->touch_curr.x > this->w / 2) //right
							{
								if (move_step < 0)
									move_step += this->itms.size();
								this->move_step = this->isize * move_step;
								this->move_speed = (((abs(this->move_step) - 1) / this->isize) + 1) * 10;
								printf("right speed %d\n", move_speed);
							}
							else //left
							{
								if (move_step > 0)
									move_step -= this->itms.size();
								this->move_step = this->isize * move_step;
								this->move_speed = (((abs(this->move_step) - 1) / this->isize) + 1) * 10;
								printf("left speed %d\n", move_speed);
							}

							this->previsel = this->isel;
							this->isel = show_index[i];
							(this->onselch)();
							if (show_index[i] == this->isel)
								this->selfact = 240;
							else if (show_index[i] == this->previsel)
								this->pselfact = 0;
							break;
						}
					}
				}
				else
				{
					//按下弹起
				}
				touch_time = 0;
			}
		}
	}
}
//共用部分，透明处理
void MenuEX::OnInputShare()
{
	(this->onselch)();
	if (!this->itms.empty())
		for (u32 i = 0; i < this->itms.size(); i++)
		{
			if (i == this->isel)
				this->selfact = 0;
			else if (i == this->previsel)
				this->pselfact = 240;
		}
}
//处理、模拟按键 dt:方向  hold:是否为触摸
void MenuEX::OnInputKey(TYPE dt, bool hold)
{
	if (dt == TYPE::RIGHT)
	{
		this->selrect.ReSet();
		this->prerect.ReSet();
		this->selrect.Trans();
		this->prerect.Trans(); //开始矩形变化计算

		this->move_step += this->isize;
		this->move_speed = (((abs(this->move_step) - 1) / this->isize) + 1) * 10 * (hold ? 2 : 1); //移动速度
		if (!hold && !downtime)
			this->downtp = std::chrono::steady_clock::now();
		if (this->isel < (this->itms.size() - 1))
		{
			this->previsel = this->isel;
			if ((this->isel - this->fisel) == (this->ishow - 1))
			{
				this->fisel++;
				this->isel++;
				(this->onselch)();
			}
			else
			{
				this->isel++;
				OnInputShare();
			}
		}
		else
		{
			this->previsel = this->itms.size() - 1;
			this->isel = 0;
			this->fisel = 0;
			//if(hold)
			//	(this->onselch)();
			OnInputShare();
		}
		if (!hold)
			downtime = !downtime;
	}
	else if (dt == TYPE::LEFT)
	{
		this->selrect.ReSet();
		this->prerect.ReSet();
		this->selrect.Trans();
		this->prerect.Trans();
		this->move_step -= this->isize;
		this->move_speed = (((abs(this->move_step) - 1) / this->isize) + 1) * 10 * (hold ? 2 : 1);
		if (!hold && !uptime)
			this->uptp = std::chrono::steady_clock::now();
		if (this->isel > 0)
		{
			this->previsel = this->isel;
			if (this->isel == this->fisel)
			{
				this->fisel--;
				this->isel--;
				(this->onselch)();
			}
			else
			{
				this->isel--;
				OnInputShare();
			}
		}
		else
		{
			this->previsel = 0;
			this->isel = this->itms.size() - 1;
			if (this->itms.size() > this->ishow)
				this->fisel = this->itms.size() - this->ishow;
			else
				this->fisel = 0;
			//if(hold)
			//	(this->onselch)();
			OnInputShare();
		}
		if (!hold)
			uptime = !uptime;
	}
}
//当前选中、之前选择项计算
void MenuEX::OnInputUpdate()
{
	int fis_index = (this->isel - (this->ishow / 2));
	for (u32 i = 0; i < this->ishow; i++)
	{
		int index = i + fis_index;
		while (index < 0)
			index += this->itms.size();
		while (index >= this->itms.size())
			index -= this->itms.size();
		show_index[i] = index;
	}
	this->prev_index = this->ishow / 2;
	if (this->previsel == this->itms.size() - 1 && this->isel == 0)
		this->prev_index--;
	else if (this->previsel == 0 && this->isel == this->itms.size() - 1)
		this->prev_index++;
	else if (this->previsel < this->isel)
		this->prev_index--;
	else if (this->previsel > this->isel)
		this->prev_index++;
}
void MenuEX::OnInput(u64 Down, u64 Up, u64 Held, bool Touch)
{
	if (this->itms.empty())
		return;
	//printf("touch %d %d %d  \n", Down & KEY_TOUCH, Up & KEY_TOUCH, Held & KEY_TOUCH);
	if (this->dtouch)
	{
		if ((this->selfact >= 240) && (this->pselfact <= 0))
		{
			if (this->icdown)
				this->icdown = false;
			else
				(this->itms[this->isel]->GetCallback(0))();
			this->dtouch = false;
		}
	}
	else
	{

		if (Down & KEY_TOUCH || Held & KEY_TOUCH || Up & KEY_TOUCH || this->pretouch)
		{
			OnInputTouch(Down, Up, Held, Touch);
		}
		else if (Down & KEY_RIGHT)
		{
			OnInputKey(TYPE::RIGHT);
		}
		else if (Down & KEY_LEFT)
		{
			OnInputKey(TYPE::LEFT);
		}
		else
		{
			u32 ipc = this->itms[this->isel]->GetCallbackCount();
			if (ipc > 0)
				for (u32 i = 0; i < ipc; i++)
				{
					if (Down & this->itms[this->isel]->GetCallbackKey(i))
					{
						if (this->icdown)
							this->icdown = false;
						else
							(this->itms[this->isel]->GetCallback(i))();
					}
				}
		}
		auto curtp = std::chrono::steady_clock::now();
		if (downtime && !downhold)
		{
			u64 downdiff = std::chrono::duration_cast<std::chrono::milliseconds>(curtp - this->downtp).count();
			if (downdiff >= 500)
			{
				downhold = true;
			}
		}
		else if (downhold)
		{

			if (Held & KEY_RIGHT)
			{
				if (this->move_step != 0)
				{
					OnInputUpdate();
					return;
				}
				OnInputKey(TYPE::RIGHT, true);
				//SDL_Delay(120);
			}
			else
			{
				downhold = false;
				downtime = false;
			}
		}
		if (uptime && !uphold)
		{
			u64 updiff = std::chrono::duration_cast<std::chrono::milliseconds>(curtp - this->uptp).count();
			if (updiff >= 500)
			{
				uphold = true;
			}
		}
		else if (uphold)
		{
			if (Held & KEY_LEFT)
			{
				if (this->move_step != 0)
				{
					OnInputUpdate();
					return;
				}
				OnInputKey(TYPE::LEFT, true);
				//SDL_Delay(120);
			}
			else
			{
				uphold = false;
				uptime = false;
			}
		}
		OnInputUpdate();
		//printf("previsel=%d isel=%d  prev_index=%d\n", this->previsel, this->isel, this->prev_index);
	}
}

/*
void MenuEX::OnInput(u64 Down, u64 Up, u64 Held, bool Touch)
{
    if (itms.empty())
        return;
    if (basestatus == 1)
    {
        auto curtime = std::chrono::steady_clock::now();
        auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(curtime - basetime).count();
        if (diff >= 150)
        {
            basestatus = 2;
        }
    }
    if (Touch)
    {
        touchPosition tch;
        hidTouchRead(&tch, 0);
        s32 cx = this->GetProcessedX();
        s32 cy = this->GetProcessedY();
        s32 cw = this->w;
        s32 ch = this->isize;
        s32 its = this->ishow;
        if (its > this->itms.size())
            its = this->itms.size();
        if ((its + this->fisel) > this->itms.size())
            its = this->itms.size() - this->fisel;
        for (s32 i = this->fisel; i < (this->fisel + its); i++)
        {
            if (((cx + cw) > tch.px) && (tch.px > cx) && ((cy + ch) > tch.py) && (tch.py > cy))
            {
                this->dtouch = true;
                this->previsel = this->isel;
                this->isel = i;
                (this->onselch)();
                if (i == this->isel)
                    this->selfact = 255;
                else if (i == this->previsel)
                    this->pselfact = 0;
                break;
            }
            cy += this->isize;
        }
    }
    else if (this->dtouch)
    {
        if ((this->selfact >= 255) && (this->pselfact <= 0))
        {
            if (this->icdown)
                this->icdown = false;
            else
                (this->itms[this->isel]->GetCallback(0))();
            this->dtouch = false;
        }
    }
    else
    {
        if ((Down & KEY_DDOWN) || (Down & KEY_LSTICK_DOWN) || (Held & KEY_RSTICK_DOWN))
        {
            bool move = true;
            if (Held & KEY_RSTICK_DOWN)
            {
                move = false;
                if (basestatus == 0)
                {
                    basetime = std::chrono::steady_clock::now();
                    basestatus = 1;
                }
                else if (basestatus == 2)
                {
                    basestatus = 0;
                    move = true;
                }
            }
            if (move)
            {
                if (this->isel < (this->itms.size() - 1))
                {
                    if ((this->isel - this->fisel) == (this->ishow - 1))
                    {
                        this->fisel++;
                        this->isel++;
                        (this->onselch)();
                        ReloadItemRenders();
                    }
                    else
                    {
                        this->previsel = this->isel;
                        this->isel++;
                        (this->onselch)();
                        if (!this->itms.empty())
                            for (s32 i = 0; i < this->itms.size(); i++)
                            {
                                if (i == this->isel)
                                    this->selfact = 0;
                                else if (i == this->previsel)
                                    this->pselfact = 255;
                            }
                    }
                }
                else
                {
                    this->isel = 0;
                    this->fisel = 0;
                    if (this->itms.size() >= this->ishow)
                    {
                        ReloadItemRenders();
                    }
                }
            }
        }
        else if ((Down & KEY_DUP) || (Down & KEY_LSTICK_UP) || (Held & KEY_RSTICK_UP))
        {
            bool move = true;
            if (Held & KEY_RSTICK_UP)
            {
                move = false;
                if (basestatus == 0)
                {
                    basetime = std::chrono::steady_clock::now();
                    basestatus = 1;
                }
                else if (basestatus == 2)
                {
                    basestatus = 0;
                    move = true;
                }
            }
            if (move)
            {
                if (this->isel > 0)
                {
                    if (this->isel == this->fisel)
                    {
                        this->fisel--;
                        this->isel--;
                        (this->onselch)();
                        ReloadItemRenders();
                    }
                    else
                    {
                        this->previsel = this->isel;
                        this->isel--;
                        (this->onselch)();
                        if (!this->itms.empty())
                            for (s32 i = 0; i < this->itms.size(); i++)
                            {
                                if (i == this->isel)
                                    this->selfact = 0;
                                else if (i == this->previsel)
                                    this->pselfact = 255;
                            }
                    }
                }
                else
                {
                    this->isel = this->itms.size() - 1;
                    this->fisel = 0;
                    if (this->itms.size() >= this->ishow)
                    {
                        this->fisel = this->itms.size() - this->ishow;
                        ReloadItemRenders();
                    }
                }
            }
        }
        else
        {
            s32 ipc = this->itms[this->isel]->GetCallbackCount();
            if (ipc > 0)
                for (s32 i = 0; i < ipc; i++)
                {
                    if (Down & this->itms[this->isel]->GetCallbackKey(i))
                    {
                        if (this->icdown)
                            this->icdown = false;
                        else
                            (this->itms[this->isel]->GetCallback(i))();
                    }
                }
        }
    }
}*/

void MenuEX::ReloadItemRenders()
{
    for (u32 i = 0; i < this->loadednames.size(); i++)
        render::DeleteTexture(this->loadednames[i]);
    for (u32 i = 0; i < this->loadedicons.size(); i++)
        render::DeleteTexture(this->loadedicons[i]);
    this->loadednames.clear();
    this->loadedicons.clear();
    s32 its = this->ishow;
    if (its > this->itms.size())
        its = this->itms.size();
    if ((its + this->fisel) > this->itms.size())
        its = this->itms.size() - this->fisel;
    for (s32 i = this->fisel; i < (its + this->fisel); i++)
    {
        auto strname = this->itms[i]->GetName();
        auto tex = render::RenderText(this->font, strname, this->itms[i]->GetColor());
        this->loadednames.push_back(tex);
        if (this->itms[i]->HasIcon())
        {
            auto stricon = this->itms[i]->GetIcon();
            auto icontex = render::LoadImage(stricon);
            this->loadedicons.push_back(icontex);
        }
        else
            this->loadedicons.push_back(NULL);
    }
}
} // namespace pu::ui::elm