#include <raylib.h>
#include "quad.hpp"
#include "button.hpp"
#include <array>
#include "css.hpp"

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 600;
    Quad quad = Quad();

    // TODO: make examples of all quadliterals
    std::array<std::array<Vector2, 4>, 16> quadExamples = {{
        {Vector2{300, 100}, Vector2{100, 100}, Vector2{100, 300}, Vector2{300, 300}}, // square 'parallel' to the x axis
        {Vector2{100, 200}, Vector2{200, 100}, Vector2{300, 200}, Vector2{200, 300}}, // square tilted
        {Vector2{100, 200}, Vector2{100, 100}, Vector2{500, 100}, Vector2{500, 200}}, // rectangle
        {Vector2{100, 200}, Vector2{200, 100}, Vector2{400, 300}, Vector2{300, 400}}, // rectangle tilted
        {Vector2{100, 200}, Vector2{100, 100}, Vector2{500, 100}, Vector2{500, 200}}, // TODO: rhombus
        {Vector2{100, 200}, Vector2{100, 100}, Vector2{500, 100}, Vector2{500, 200}}, // TODO: rhombus tilted
        {Vector2{100, 200}, Vector2{100, 100}, Vector2{500, 100}, Vector2{500, 200}}, // TODO: kite
        {Vector2{100, 200}, Vector2{100, 100}, Vector2{500, 100}, Vector2{500, 200}}, // TODO: kite tilted
        {Vector2{100, 200}, Vector2{100, 100}, Vector2{500, 100}, Vector2{500, 200}}, // TODO: parallelogram
        {Vector2{100, 200}, Vector2{100, 100}, Vector2{500, 100}, Vector2{500, 200}}, // TODO: parallelogram tilted
        {Vector2{100, 200}, Vector2{100, 100}, Vector2{500, 100}, Vector2{500, 200}}, // TODO: isosceles trapezium
        {Vector2{100, 200}, Vector2{100, 100}, Vector2{500, 100}, Vector2{500, 200}}, // TODO: isosceles trapezium tilted
        {Vector2{100, 200}, Vector2{100, 100}, Vector2{500, 100}, Vector2{500, 200}}, // TODO: trapezium
        {Vector2{100, 200}, Vector2{100, 100}, Vector2{500, 100}, Vector2{500, 200}}, // TODO: trapezium tilted
        {Vector2{100, 200}, Vector2{100, 100}, Vector2{500, 100}, Vector2{500, 200}}, // TODO: irregular quad
        {Vector2{100, 200}, Vector2{100, 100}, Vector2{500, 100}, Vector2{500, 200}}, // TODO: arrow
    }};
    quad.SetDimensions(quadExamples[0][0], quadExamples[0][1], quadExamples[0][2], quadExamples[0][3]);

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
            quad.SetDimensions(quadExamples[index][0], quadExamples[index][1], quadExamples[index][2], quadExamples[index][3]);
        }
        else if (mouseLeft.x > 0 && mouseLeft.y > 0) {
            isInside = quad.IsVector2In(mouseLeft);
            if (isInside) {
                vec2Color = BLACK;
            } else {
                vec2Color = YELLOW;
            }
        }

        quad.Draw();
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
