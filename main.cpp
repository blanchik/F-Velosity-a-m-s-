#include <raylib.h>
#include <math.h>
#include "panels.h"

const int width = 800, height = 600;

int x = 400, y = 300;
int endx = 400, endy = 300;
bool start = true, whilepressed = true;
int maxX, maxY, minX, minY;

void DrawMyArrow(int x1, int y1, int x2, int y2, Color color, const char *txt)
{
    // 1. Рисуем основную линию (толщиной 3 пикселя)
    DrawLineEx({(float)x1, (float)y1}, {(float)x2, (float)y2}, 3.0f, color);

    // 2. Считаем угол наклона линии в радианах
    float angle = atan2f(y2 - y1, x2 - x1);

    // Настройки наконечника (можно менять под себя)
    float arrowLength = 15.0f; // Длина стрелочек на конце
    float arrowAngle = 0.4f;   // Угол раскрытия (примерно 23 градуса)

    // 3. Вычисляем координаты для двух «крыльев» стрелки
    // От конечной точки (x2, y2) шагаем назад под углом
    int wing1X = x2 - arrowLength * cosf(angle - arrowAngle);
    int wing1Y = y2 - arrowLength * sinf(angle - arrowAngle);

    int wing2X = x2 - arrowLength * cosf(angle + arrowAngle);
    int wing2Y = y2 - arrowLength * sinf(angle + arrowAngle);

    // 4. Рисуем крылья стрелки
    DrawLineEx({(float)x2, (float)y2}, {(float)wing1X, (float)wing1Y}, 3.0f, color);
    DrawLineEx({(float)x2, (float)y2}, {(float)wing2X, (float)wing2Y}, 3.0f, color);
    // 1. Задаем расстояние от кончика стрелки (x2, y2) до буквы
    float offsetLength = 20.0f;

    // 2. Считаем перпендикулярный угол (поворот на 90 градусов вправо)
    // Если хотите, чтобы буква была с другой стороны, поменяйте знак на минус: (angle - 1.57f)
    float sideAngle = angle + 1.57f;

    // 3. Вычисляем координаты для текста сбоку от точки (x2, y2)
    int textX = x2 + offsetLength * cosf(sideAngle);
    int textY = y2 + offsetLength * sinf(sideAngle);

    // 4. Корректируем сам текст (сдвиг на половину размера шрифта, чтобы буква не съезжала)
    int centerX = textX - 7;
    int centerY = textY - 10;

    // 5. Отрисовываем текст
    DrawText(txt, centerX, centerY, 20, color);
}

void DrawBox()
{
    DrawRectangle(0, 0, 800, 50, RED);
    DrawRectangleGradientV(0, 50, 60, 600, RED, MAGENTA);
    DrawRectangleGradientV(740, 50, 800, 600, RED, MAGENTA);
    DrawRectangle(0, 550, 800, 600, MAGENTA);

    return;
}



int main()
{
    Entry F;
    F.InitPanel("F", 100, 10, 200, 30, "H");
    Entry alfa;
    alfa.InitPanel("a", 400, 10, 200, 30, "m/s");
    InitWindow(width, height, "Стрелка");
    SetTargetFPS(120);
    while (!WindowShouldClose())
    {

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && ((GetMouseX() > 90 && GetMouseY() > 90) && (GetMouseX() < 720 && GetMouseY() < 520)))
        {
            if (start)
            {
                endx = 0;
                endy = 0;
                x = GetMouseX();
                y = GetMouseY();
                start = false;
                whilepressed = true;
            }
            if (!start)
            {
                endx = GetMouseX();
                endy = GetMouseY();
                whilepressed = false;
                maxY = y - 200;
                minY = y + 200;
                if (maxY < 50)
                {
                    maxY = 50;
                }
                if (minY > 545)
                {
                    minY = 545;
                }

                maxX = x + 300;
                minX = x - 300;
                if (minX < 65)
                {
                    minX = 65;
                }
                if (maxX > 740)
                {
                    maxX = 740;
                }
            }
        }
        else
        {
            start = true;
        }

        BeginDrawing();
        ClearBackground(GRAY);
        DrawBox();
        F.UpdateInput();
        F.DrawPanel();
        alfa.UpdateInput();
        alfa.DrawPanel();

        alfa.Select(GetMousePosition());

        F.Select(GetMousePosition());

        if (!whilepressed)
        {
            DrawText(TextFormat("maxY: %d", maxY), 10, 10, 10, GREEN);
            DrawText(TextFormat("Y: %d", y), 10, 20, 10, GREEN);
            DrawText(TextFormat("endy: %d", endy), 10, 30, 10, GREEN);
            DrawText(TextFormat("minX: %d", minX), 10, 40, 10, GREEN);
            DrawText(TextFormat("SelF: %d", F.select), 10, 50, 10, GREEN);
            DrawText(TextFormat("Sela: %d", alfa.select), 10, 60, 10, GREEN);

            DrawMyArrow(minX, y, maxX, y, GREEN, "X");
            DrawMyArrow(x, minY, x, maxY, BLUE, "Y");
        }

        DrawLine(x, y, endx, endy, RED);
        if (x != endx || y != endy)
            DrawMyArrow(x, y, endx, endy, RED, "F");
        DrawCircle(x, y, 3, RED);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}