#include "MenuBox.h"

MenuBox::MenuBox(int num, char data[200][200])
{
    this->num = num;

    Option = new char *[num];
    for (int i = 0; i < this->num; i++)
    {
        Option[i] = new char[100];
    }

    for (int i = 0; i < this->num; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            Option[i][j] = data[i][j];
        }
    }
}

void MenuBox::print(int idx, char **content)
{
    std::cout << content[idx];
}
int MenuBox::getChoose(int choose)
{
    return choose;
}
int MenuBox::menu()
{
    gotoXY(0, 0);
    ShowCur(0);

    int w = 40;
    int h = 2;
    int t_color = 11;
    int b_color = 1;
    int b_color_sang = 75;
    for (int i = 0; i < this->num; i++)
    {
        boxes(xx, yy, w, h, t_color, b_color, this->Option, this->num);
    }

    int xp = xx;
    int yp = yy; // toạ độ thanh sáng
    bool kt = true;
    int xcu = xp, ycu = yp;
    while (true)
    {

        // in
        if (kt == true)
        {
            gotoXY(xcu, ycu);
            lightBox(xcu, ycu, w, h, b_color, this->Option, (ycu - yy) / 2);
            xcu = xp;
            ycu = yp;
            lightBox(xp, yp, w, h, b_color_sang, this->Option, (yp - yy) / 2);
            kt = false;
        }
        // ddieeu khien di chuyen
        if (_kbhit())
        {
            char c = _getch();
            if (c == 72)
            {
                kt = true;
                if (yp != yy)
                    yp -= 2;
                else
                    yp = yy + h * (this->num - 1);
            }
            else if (c == 80)
            {
                kt = true;
                if (yp != yy + h * (this->num - 1))
                    yp += 2;
                else
                    yp = yy;
            }
            else if (c == 13)
            {
                textcolor(3);
                choose = (yp - yy) / 2 + 1;
                // cout << choose << endl;
                system("cls");
                return choose;
            }
        }
    }
}
void MenuBox::lightBox(int xx, int yy, int w, int h, int b_color, char **content, int idx)
{
    textcolor(b_color);
    for (int i = yy + 1; i <= yy + h - 1; i++)
    {
        for (int j = xx + 1; j <= xx + w - 1; j++)
        {
            gotoXY(j, i);
            std::cout << " ";
        }
    }
    SetColor(7);
    gotoXY(xx + 1, yy + 1);
    print(idx, content);
}
void MenuBox::box(int xx, int yy, int w, int h, int t_color, int b_color, char **content, int idx)
{
    textcolor(b_color);
    for (int i = yy + 1; i <= yy + h - 1; i++)
    {
        for (int j = xx + 1; j <= xx + w - 1; j++)
        {
            gotoXY(j, i);
            std::cout << " ";
        }
    }
    SetColor(7);
    gotoXY(xx + 1, yy + 1);
    print(idx, content);
    textcolor(3);
    SetColor(t_color);

    if (h == 1 || w <= 1)
        return;
    for (int i = xx; i <= xx + w; i++)
    {
        gotoXY(i, yy);
        std::cout << "─";
        gotoXY(i, yy + h);
        std::cout << "─";
    }
    for (int i = yy; i <= yy + h; i++)
    {
        gotoXY(xx, i);
        std::cout << "│";
        gotoXY(xx + w, i);
        std::cout << "│";
    }
    gotoXY(xx, yy);
    std::cout << "┌";
    gotoXY(xx + w, yy);
    std::cout << "┐";
    gotoXY(xx, yy + h);
    std::cout << "└";
    gotoXY(xx + w, yy + h);
    std::cout << "┘";
    gotoXY(xx, yy + h);
    std::cout << std::endl;
}
void MenuBox::boxes(int xx, int yy, int w, int h, int t_color, int b_color, char **content, int count)
{
    for (int i = 0; i < count; i++)
    {
        box(xx, yy + i * 2, w, h, 11, 1, content, i);
        if (i != 0)
        {
            gotoXY(xx, yy + i * 2);
            std::cout << "├";
            gotoXY(xx + w, yy + i * 2);
            std::cout << "┤";
        }
    }
}