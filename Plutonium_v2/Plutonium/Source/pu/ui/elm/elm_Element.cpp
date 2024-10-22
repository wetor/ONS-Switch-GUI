#include <pu/ui/elm/elm_Element.hpp>
#include <pu/ui/ui_Layout.hpp>

namespace pu::ui::elm
{
    Element::Element()
    {
        this->visible = true;
        this->halign = HorizontalAlign::Left;
        this->valign = VerticalAlign::Up;
        this->parent = NULL;
        //----
        this->disable = false;
    }

    Element::~Element()
    {
    }

    bool Element::IsVisible()
    {
        return this->visible;
    }

    void Element::SetVisible(bool Visible)
    {
        this->visible = Visible;
    }
    bool Element::IsDisable()
    {
        return this->disable;
    }

    void Element::SetDisable(bool Disable)
    {
        this->disable = Disable;
    }
    void Element::SetParent(void *Base)
    {
        this->parent = Base;
    }

    void *Element::GetParent()
    {
        return this->parent;
    }

    void Element::SetHorizontalAlign(HorizontalAlign Align)
    {
        this->halign = Align;
    }

    HorizontalAlign Element::GetHorizontalAlign()
    {
        return this->halign;
    }

    void Element::SetVerticalAlign(VerticalAlign Align)
    {
        this->valign = Align;
    }

    VerticalAlign Element::GetVerticalAlign()
    {
        return this->valign;
    }

    bool Element::HasParent()
    {
        return (this->parent != NULL);
    }

    s32 Element::GetProcessedX()
    {
        s32 rx = this->GetX();
        if(this->parent != NULL)
        {
            Container *cont = (Container*)this->parent;
            rx += cont->GetX();
            switch(this->halign)
            {
                case HorizontalAlign::Center:
                    rx = cont->GetX() + ((cont->GetWidth() - this->GetWidth()) / 2);
                    break;
                case HorizontalAlign::Right:
                    rx = cont->GetX() + (cont->GetWidth() - this->GetWidth());
                    break;
                default:
                    break;
            }
        }
        return rx;
    }

    s32 Element::GetProcessedY()
    {
        s32 ry = this->GetY();
        if(this->parent != NULL)
        {
            Container *cont = (Container*)this->parent;
            ry += cont->GetY();
            switch(this->valign)
            {
                case VerticalAlign::Center:
                    ry = cont->GetY() + ((cont->GetHeight() - this->GetHeight()) / 2);
                    break;
                case VerticalAlign::Down:
                    ry = cont->GetY() + (cont->GetHeight() - this->GetHeight());
                    break;
                default:
                    break;
            }
        }
        return ry;
    }
}