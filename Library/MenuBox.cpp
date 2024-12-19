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

// ===== Đọc file sơ đồ ghế =====
bool readSeatMapFromFile(const std::string& filename, char seatMap[100][8], int& rows, int& cols)
{
    std::ifstream inFile(filename);
    if (!inFile.is_open())
    {
        std::cerr << "Error: Không thể mở file " << filename << " để đọc.\n";
        return false;
    }

    rows = 0;
    std::string line;
    while (std::getline(inFile, line) && rows < 100)
    {
        for (int i = 0, j = 0; j < line.size() && i < 8; j += 2, i++)
        {
            seatMap[rows][i] = line[j];
        }
        rows++;
    }
    cols = 8; // Luôn có 8 ghế trên mỗi hàng
    inFile.close();
    return true;
}

// ===== Cập nhật trạng thái ghế trong file =====
bool updateSeatStatusInFile(const std::string& filename, int row, int col, int status)
{
    std::ifstream inFile(filename);
    if (!inFile.is_open())
    {
        std::cerr << "Error: Không thể mở file " << filename << " để đọc.\n";
        return false;
    }

    std::string lines[100];
    int i = 0;
    while (std::getline(inFile, lines[i]))
    {
        i++;
    }
    inFile.close();

    lines[row][col * 2] = status ? '1' : '0'; // Mỗi ghế cách nhau 1 dấu cách trong file

    std::ofstream outFile(filename);
    if (!outFile.is_open())
    {
        std::cerr << "Error: Không thể mở file " << filename << " để ghi.\n";
        return false;
    }
    for (int j = 0; j < i; j++)
    {
        outFile << lines[j] << "\n";
    }
    outFile.close();
    return true;
}

// ===== In sơ đồ ghế có ID ghế =====
void printSeatMapWithIDs(const char seatMap[100][8], int rows, int cols, int cursorRow, int cursorCol)
{
    system("cls");
    for (int i = 0; i < rows; i++)
    {
        gotoXY(10, 5 + i); // Vị trí hàng ghế in ra
        for (int j = 0; j < cols; j++)
        {
            // Hiển thị ID ghế
            std::string seatID = std::to_string(i + 1) + char('A' + j);

            if (seatMap[i][j] == '1') // Ghế đã được đặt
            {
                textcolor(12); // Màu đỏ
            }
            else if (i == cursorRow && j == cursorCol) // Ghế đang chọn
            {
                textcolor(14); // Màu vàng
            }
            else
            {
                textcolor(10); // Ghế trống
            }

            std::cout << "[" << seatID << "] ";
        }
        std::cout << std::endl;
    }
    textcolor(7); // Màu mặc định
}

// ===== Tạo sơ đồ ghế tương tác =====
std::string createSeatMapWithIDs(const std::string& ID_chuyenBay)
{
    std::string filename = "./Database/SeatDB/" + ID_chuyenBay + ".txt";
    char seatMap[100][8];
    int rows, cols;

    // Đọc sơ đồ ghế từ file
    if (!readSeatMapFromFile(filename, seatMap, rows, cols))
    {
        return "";
    }

    gotoXY(10, 5 + rows + 1);
    textcolor(12); // Màu xanh lam
    std::cout << "← ↑ → ↓: Di chuyển | ENTER: Chọn ghế | ESC: Hủy" << std::endl;
    textcolor(7);

    int cursorRow = 0, cursorCol = 0; // Vị trí con trỏ chọn ghế
    while (true)
    {
        printSeatMapWithIDs(seatMap, rows, cols, cursorRow, cursorCol);

        int key = _getch();
        if (key == 224) // Phím mũi tên
        {
            key = _getch();
            switch (key)
            {
            case 72: // Lên
                cursorRow = (cursorRow > 0) ? cursorRow - 1 : rows - 1;
                break;
            case 80: // Xuống
                cursorRow = (cursorRow < rows - 1) ? cursorRow + 1 : 0;
                break;
            case 75: // Trái
                cursorCol = (cursorCol > 0) ? cursorCol - 1 : cols - 1;
                break;
            case 77: // Phải
                cursorCol = (cursorCol < cols - 1) ? cursorCol + 1 : 0;
                break;
            }
        }
        else if (key == 13) // Phím Enter
        {
            if (seatMap[cursorRow][cursorCol] == '0') // Ghế chưa được đặt
            {
                seatMap[cursorRow][cursorCol] = '1'; // Đánh dấu ghế
                updateSeatStatusInFile(filename, cursorRow, cursorCol, 1);
                return std::to_string(cursorRow + 1) + char('A' + cursorCol);
            }
            else
            {
                // Thông báo nếu ghế đã được đặt
                gotoXY(10, 5 + rows + 2);
                textcolor(12);
                std::cout << "Ghế này đã được đặt! Vui lòng chọn ghế khác.";
                textcolor(7);
            }
        }
    }
}