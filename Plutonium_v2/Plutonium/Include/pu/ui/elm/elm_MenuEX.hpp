
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
#include <pu/ui/elm/elm_Menu.hpp>
#include <vector>
#include <chrono>
#include <functional>

namespace pu::ui::elm
{
enum TYPE
{
    TOP,
    DOWN,
    LEFT,
    RIGHT,
    HOLD
};
enum TRAN
{
    BEGIN,
    TRANS,
    RESTROE,
    END
};
class TransRect
{
public:
    TransRect(){};
    void SetSource(SDL_Rect rect);
    void SetTarget(SDL_Rect rect, s32 time);
    void SetRect(SDL_Rect src, SDL_Rect dst, s32 time);
    void ReSet();
    void Trans();
    void Restore();
    void Update();
    void End();

    TRAN GetState() { return state; };
    int GetX();
    int GetY();
    int GetW();
    int GetH();
    SDL_Rect GetSource() { return src; };
    SDL_Rect GetTarget() { return dst; };

private:
    int mode, time, curr_time;
    TRAN state;
    int speed_x, speed_y, speed_w, speed_h;
    SDL_Rect src, dst, curr;
};

class MenuEX : public Element
{
public:
    MenuEX(s32 X, s32 Y, s32 Width, s32 Height, Color OptionColor, s32 ItemSize, s32 SelectSize, s32 ItemsToShow);
    PU_SMART_CTOR(MenuEX)

    s32 GetX();
    void SetX(s32 X);
    s32 GetY();
    void SetY(s32 Y);
    s32 GetWidth();
    void SetWidth(s32 Width);
    s32 GetHeight();
    s32 GetItemSize();
    void SetItemSize(s32 ItemSize);
    s32 GetNumberOfItemsToShow();
    void SetNumberOfItemsToShow(s32 ItemsToShow);
    Color GetColor();
    void SetColor(Color Color);
    Color GetOnFocusColor();
    void SetOnFocusColor(Color Color);
    Color GetScrollbarColor();
    void SetScrollbarColor(Color Color);
    void SetOnSelectionChanged(std::function<void()> Callback);
    void AddItem(MenuItem::Ref &Item);
    void ClearItems();
    void SetCooldownEnabled(bool Cooldown);
    MenuItem::Ref &GetSelectedItem();
    std::vector<MenuItem::Ref> &GetItems();
    s32 GetSelectedIndex();
    void SetSelectedIndex(s32 Index);
    void OnRender(render::Renderer::Ref &Drawer, s32 X, s32 Y);
    void OnInput(u64 Down, u64 Up, u64 Held, bool Touch);

    //--------------
    s32 GetSelectSize();
    void SetSelectSize(s32 SelectSize);
    void SetType(TYPE type);
    TYPE GetType();
    void SetDisable(bool Disable);
    void OnInputTouch(u64 Down, u64 Up, u64 Held, bool Touch);
    void OnInputKey(TYPE dt, bool hold =false);
    void OnInputShare();
    void OnInputUpdate();

private:
    void ReloadItemRenders();
    bool dtouch;
    s32 x;
    s32 y;
    s32 w;
    s32 isize;
    s32 ishow;
    s32 previsel;
    s32 fisel;
    s32 isel;
    s32 pselfact;
    s32 selfact;
    Color scb;
    Color clr;
    Color fcs;
    bool icdown;
    int basestatus;

    //----------
    s32 h;
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
    //-------------

    std::chrono::time_point<std::chrono::steady_clock> basetime;
    std::function<void()> onselch;
    std::vector<MenuItem::Ref> itms;
    render::NativeFont font;
    std::vector<render::NativeTexture> loadednames;
    std::vector<render::NativeTexture> loadedicons;
};
} // namespace pu::ui::elm