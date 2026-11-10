#include <raylib.h>
#include <string.h>

struct Entry
{
    bool select = true;

    int x1, y1;
    int x2, y2;
    int bd = 2;
    char Text[51] = {0};
    char why[2] = {0};
    char val[15] = {0};
    void InitPanel(const char *, int, int, int, int, const char *endval = "");
    void DrawPanel();
    void UpdateInput();
    void Select(Vector2);
    int Read();
};

void Entry::InitPanel(const char *text, int x1, int y1, int x2, int y2, const char *endval)
{
    why[0] = text[0];
    why[1] = '\0';

    strncpy(val, endval, 14);
    val[14] = '\0';

    this->x1 = x1;
    this->x2 = x2;
    this->y1 = y1;
    this->y2 = y2;

    return;
}

void Entry::DrawPanel()
{
    if (select)
    {
        // Активное состояние: рисуем рамку, например, RED или BLUE, и даем ей жирный отступ
        DrawRectangle(x1, y1, x2, y2, BLUE); 
        // Делаем внутренний отступ больше (bd * 2), чтобы синий цвет было хорошо видно
        DrawRectangleGradientH(x1 + bd*2, y1 + bd*2, x2 - (bd * 4), y2 - (bd * 4), WHITE, LIGHTGRAY);
    }
    else
    {
        // Обычное состояние: тонкая черная рамка
        DrawRectangle(x1, y1, x2, y2, BLACK);
        DrawRectangleGradientH(x1 + bd, y1 + bd, x2 - (bd * 2), y2 - (bd * 2), WHITE, GRAY);
    }

    // 2. Идеальный расчет для подсказки 'why'
    // Измеряем длину строки 'why' в пикселях при размере шрифта 10
    int textLengthInPixels = MeasureText(why, 10);

    // Сдвигаем влево ровно на её длину + 10 пикселей отступа от рамки
    int labelX = x1 - textLengthInPixels - 10;
    int labelY = y1 + (y2 / 2) - 5;

    // Рисуем подсказку (теперь она гарантированно не залезет на рамку и не улетит)
    DrawText(why, labelX, labelY, 10, BLACK);

    int labelXval = x1 + x2 + 10;
    int labelYval = y1 + (y2 / 2) - 5;

    DrawText(val, labelXval, labelYval, 10, BLACK);

    // 3. Рисуем вводимый текст внутри рамки
    int inputX = x1 + bd + 10;
    int inputY = y1 + (y2 / 2) - 5;
    DrawText(Text, inputX, inputY, 10, BLACK);

    if (strcmp(val, "m/s") == 0)
    {
        // Измеряем длину строки "m/s"
        int valLength = MeasureText(val, 10);

        // Сдвигаем X в конец и приподнимаем Y
        int degreeX = labelXval + valLength + 1;
        int degreeY = labelYval - 4;

        // Рисуем саму степень
        DrawText("2", degreeX, degreeY, 8, BLACK);
    }

    return;
}

void Entry::Select(Vector2 pos)
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (pos.x > x1 && pos.x < (x1 + x2) && pos.y > y1 && pos.y < (y1 + y2))
            select = true;
        else
            select = false;
    }
}

void Entry::UpdateInput() // Убрали int maxwidth
{
    if (select)
    {
        int len = strlen(Text);
        int key = GetCharPressed();

        // Прямо берём собственную переменную x2!
        int maxTextWidth = x2 - (bd * 2) - 20;

        while (key > 0)
        {
            if ((key >= '0') && (key <= '9') && (len < 35))
            {
                Text[len] = (char)key;
                Text[len + 1] = '\0';
            }
            key = GetCharPressed();
        }

        if (IsKeyDown(KEY_BACKSPACE) && IsKeyDown(KEY_LEFT_CONTROL) && len > 0)
        {
            while (len > 0)
            {
                len--;
                Text[len] = '\0';
            }
        }
        else if (IsKeyPressed(KEY_BACKSPACE) && len > 0)
        {
            len--;
            Text[len] = '\0';
        }
        return;
    }
}

// int Entry::Read()
// {
// }
