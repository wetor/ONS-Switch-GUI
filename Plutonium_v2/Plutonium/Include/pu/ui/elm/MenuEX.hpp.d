
/*

    Plutonium library

    @file Menu.hpp
    @brief A Menu is a very useful Element for option browsing or selecting.
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <pu/pu_String.hpp>
#include <pu/ui/elm/elm_Element.hpp>
#include <vector>
#include <functional>
#include <chrono>

namespace pu::element
{
    enum TYPE{
        TOP,
        DOWN,
        LEFT,
        RIGHT,
        HOLD
    };
    enum TRAN{
        BEGIN,
        TRANS,
        RESTROE,
        END
    };
class TransRect{
public:
    TransRect(){};
    void SetSource(SDL_Rect rect);
    void SetTarget(SDL_Rect rect,s32 time);
    void SetRect(SDL_Rect src,SDL_Rect dst,s32 time);
    void ReSet();
    void Trans();
    void Restore();
    void Update();
    void End();

    TRAN GetState(){return state;};
    int GetX();
    int GetY();
    int GetW();
    int GetH();
    SDL_Rect GetSource(){return src;};
    SDL_Rect GetTarget(){return dst;};
private:
    int mode,time,curr_time;
    TRAN state;
    int speed_x,speed_y,speed_w,speed_h;
    SDL_Rect src,dst,curr;
};

class MenuEX : public Element
{
public:
    MenuEX(s32 X, s32 Y, s32 Width, s32 Height, draw::Color OptionColor, s32 ItemSize, s32 SelectSize, s32 ItemsToShow);
    ~MenuEX();
    s32 GetX();
    void SetX(s32 X);
    s32 GetY();
    void SetY(s32 Y);
    s32 GetWidth();
    void SetWidth(s32 Width);
    s32 GetHeight();
    void SetHeight(s32 Height);
    s32 GetItemSize();
    void SetItemSize(s32 ItemSize);
    s32 GetNumberOfItemsToShow();
    void SetNumberOfItemsToShow(s32 ItemsToShow);
    draw::Color GetColor();
    void SetColor(draw::Color Color);
    draw::Color GetOnFocusColor();
    void SetOnFocusColor(draw::Color Color);
    draw::Color GetScrollbarColor();
    void SetScrollbarColor(draw::Color Color);
    void SetOnSelectionChanged(std::function<void()> Callback);
    void AddItem(MenuItem *Item);
    void ClearItems();
    void SetCooldownEnabled(bool Cooldown);
    MenuItem *GetSelectedItem();
    s32 GetSelectedIndex();
    void SetSelectedIndex(s32 Index);
    void OnRender(render::Renderer *Drawer);
    void OnInput(u64 Down, u64 Up, u64 Held, bool Touch, bool Focus);

    s32 GetSelectSize();
    void SetSelectSize(s32 SelectSize);
    void SetType(TYPE type);
    TYPE GetType();
    void OnInputTouch(u64 Down, u64 Up, u64 Held, bool Touch, bool Focus);
    void OnInputKey(TYPE dt, bool hold =false);
    void OnInputShare();
    void OnInputUpdate();

    void SetDisable(bool Disable);
private:
    
    
    bool dtouch;
    s32 x;
    s32 y;
    s32 w;
    s32 h;
    s32 isize;
    s32 ishow;
    s32 previsel;
    s32 fisel;
    s32 isel;
    s32 pselfact;
    s32 selfact;
    draw::Color scb;
    draw::Color clr;
    draw::Color fcs;
    bool icdown;
    std::function<void()> onselch;
    std::vector<MenuItem *> itms;

    TransRect selrect;
    TransRect prerect;
    TransRect disrect;

    SDL_Rect *touch_area;
    u32 *show_index;
    SDL_Point touch_down;
    SDL_Point touch_curr;
    u32 touch_time;
    u32 prev_index;
    s32 move_step;
    s32 move_speed;
    u32 alpha_count;
    u32 alpha_flag;
    s32 selsize;

    bool uptime;
	bool uphold;
    bool pretouch;
	std::chrono::time_point<std::chrono::steady_clock> uptp;
	bool downtime;
	bool downhold;
	std::chrono::time_point<std::chrono::steady_clock> downtp;
    TYPE draw_type;
    
    


};
} // namespace pu::element