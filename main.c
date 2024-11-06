#include "raylib.h"
#include <math.h>


typedef struct Sun {
    int centerX;        // X-coordinate of the sun's center
    int centerY;        // Y-coordinate of the sun's center
    float innerRadius;  // Inner radius of the sun
    float outerRadius;  // Outer radius of the sun
    int numRays;        // Number of rays extending from the sun
    Color color;        // Color of the sun
} Sun;

void DrawSunWithRays(Sun *sun, float waveTime) {
    for (int i = 0; i < sun->numRays; i++) {
        float angle = 2.0f * PI * i / sun->numRays;
        float nextAngle = 2.0f * PI * (i + 1) / sun->numRays;

        float waveOffset1 = sinf(angle + waveTime) * 10.0f;
        float waveOffset2 = sinf(nextAngle + waveTime) * 10.0f;

        Vector2 p1 = { sun->centerX + sun->innerRadius * cosf(angle),
                        sun->centerY + sun->innerRadius * sinf(angle) + waveOffset1 };
        Vector2 p2 = { sun->centerX + sun->outerRadius * cosf(angle),
                        sun->centerY + sun->outerRadius * sinf(angle) + waveOffset1 };
        Vector2 p3 = { sun->centerX + sun->outerRadius * cosf(nextAngle),
                        sun->centerY + sun->outerRadius * sinf(nextAngle) + waveOffset2 };

        DrawTriangle((Vector2){ sun->centerX, sun->centerY + sinf(waveTime) * 10.0f }, p1, p2, sun->color);
        DrawTriangle((Vector2){ sun->centerX, sun->centerY + sinf(waveTime) * 10.0f }, p2, p3, sun->color);
    }

    DrawCircle(sun->centerX, sun->centerY + sinf(waveTime) * 10.0f, sun->innerRadius, sun->color);
}

typedef struct FlagStripe {
    Color color;        // Color of the stripe
    int heightOffset;   // Height offset for drawing
} FlagStripe;

void DrawFlagStripes(FlagStripe *stripes, int stripeCount, int screenWidth, int screenHeight, float waveTime) {
    for (int i = 0; i < stripeCount; i++) {
        float yOffset = sinf(waveTime + i * PI / 3) * 10.0f; // Sine wave for each stripe
        DrawRectangle(0, i * screenHeight / 3 + yOffset, screenWidth, screenHeight / 3, stripes[i].color);
    }
}

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Kurdistan Flag");
    SetTargetFPS(60);
    float waveTime = 0.0f;

    Sun kurdistanSun = { screenWidth / 2, screenHeight / 2, 50, 80, 21, YELLOW };

    FlagStripe stripes[3] = {
        { RED, 0 },    // Red stripe (top)
        { WHITE, 1 },  // White stripe (middle)
        { GREEN, 2 }   // Green stripe (bottom)
    };

    while (!WindowShouldClose()) {
        // Update waveTime for continuous motion
        waveTime += 0.05f;

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawFlagStripes(stripes, 3, screenWidth, screenHeight, waveTime);

        DrawSunWithRays(&kurdistanSun, waveTime);

        EndDrawing();
    }

    CloseWindow();
    return 0;                          
}
