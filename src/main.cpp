#include <raylib.h>
#include "quad.hpp"
#include "button.hpp"
#include <array>
#include "css.hpp"

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 600;

    // TODO: make examples of all quadliterals
    std::array<Quad, 16> quadExamples = {{
        Quad({Vector2{300, 100}, Vector2{100, 100}, Vector2{100, 300}, Vector2{300, 300}}), // square 'parallel' to the x axis
        Quad({Vector2{100, 200}, Vector2{200, 100}, Vector2{300, 200}, Vector2{200, 300}}), // square tilted
        Quad({Vector2{100, 200}, Vector2{100, 100}, Vector2{500, 100}, Vector2{500, 200}}), // rectangle
        Quad({Vector2{100, 200}, Vector2{200, 100}, Vector2{400, 300}, Vector2{300, 400}}), // rectangle tilted
        Quad({Vector2{100, 200}, Vector2{200, 50}, Vector2{400, 100}, Vector2{300, 250}}), // rhombus
        Quad({Vector2{100, 200}, Vector2{200, 50}, Vector2{400, 50}, Vector2{300, 200}}), // rhombus tilted
        Quad({Vector2{100, 200}, Vector2{100, 100}, Vector2{500, 100}, Vector2{500, 200}}), // TODO: kite
        Quad({Vector2{100, 200}, Vector2{100, 100}, Vector2{500, 100}, Vector2{500, 200}}), // TODO: kite tilted
        Quad({Vector2{100, 200}, Vector2{100, 100}, Vector2{500, 100}, Vector2{500, 200}}), // TODO: parallelogram
        Quad({Vector2{100, 200}, Vector2{100, 100}, Vector2{500, 100}, Vector2{500, 200}}), // TODO: parallelogram tilted
        Quad({Vector2{100, 200}, Vector2{100, 100}, Vector2{500, 100}, Vector2{500, 200}}), // TODO: isosceles trapezium
        Quad({Vector2{100, 200}, Vector2{100, 100}, Vector2{500, 100}, Vector2{500, 200}}), // TODO: isosceles trapezium tilted
        Quad({Vector2{100, 200}, Vector2{100, 100}, Vector2{500, 100}, Vector2{500, 200}}), // TODO: trapezium
        Quad({Vector2{100, 200}, Vector2{100, 100}, Vector2{500, 100}, Vector2{500, 200}}), // TODO: trapezium tilted
        Quad({Vector2{100, 200}, Vector2{200, 70}, Vector2{400, 50}, Vector2{300, 220}}), // irregular quad
        Quad({Vector2{100, 200}, Vector2{100, 100}, Vector2{500, 100}, Vector2{500, 200}}), // TODO: arrow
    }};

    Quad currQuad = quadExamples[0];

    InitWindow(screenWidth, screenHeight, "RAYLIB!");
    SetTargetFPS(60);
    Vector2 mouseLeft = { -10.0f, -10.0f };
    bool isInside = false;
    Button nextButton = Button(10, 10, "NEXT");
    Color vec2Color = BLACK;
    Vector2 point;
    size_t index = 0;

    while (!WindowShouldClose())
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            mouseLeft = GetMousePosition();
            point = {mouseLeft.x, mouseLeft.y};
        }

        BeginDrawing();
        ClearBackground(DARKGREEN);

        if (mouseLeft.x < nextButton.x1 && mouseLeft.x > nextButton.x && mouseLeft.y < nextButton.y1 && mouseLeft.y > nextButton.y) {
            index++;
            if (index == quadExamples.size()) {
                index = 0;
            }
            currQuad = quadExamples[index];
        }
        else if (mouseLeft.x > 0 && mouseLeft.y > 0) {
            isInside = currQuad.IsVector2In(mouseLeft);
            if (isInside) {
                vec2Color = BLACK;
            } else {
                vec2Color = YELLOW;
            }
        }

        currQuad.Draw();
        nextButton.Draw();
        if (!(point.x < nextButton.x1 && point.x > nextButton.x && point.y < nextButton.y1 && point.y > nextButton.y)) {
            DrawCircle(point.x, point.y, 4, vec2Color);
        }
        EndDrawing();
        mouseLeft = { -10.0f, -10.0f };
    }

    CloseWindow();
    return 0;
}
