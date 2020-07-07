#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

#include <ti/grlib/grlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"

#define CIRCLE_X 63
#define CIRCLE_Y 63
#define CIRCLE_RADIUS 20

// Initialization function for graphics
void initializeGraphics(Graphics_Context* g_sContext_p) {
    // Initialize the LCD
    Crystalfontz128x128_Init();
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);

    // Initialize context
    Graphics_initContext(g_sContext_p, &g_sCrystalfontz128x128, &g_sCrystalfontz128x128_funcs);

    // Set colors and fonts
    Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);
    Graphics_setBackgroundColor(g_sContext_p, GRAPHICS_COLOR_BLACK);
    Graphics_setFont(g_sContext_p, &g_sFontCmss12);

    // Clear the screen
    Graphics_clearDisplay(g_sContext_p);
}

// Function to restart timer
void restartTimer() {
    Timer32_setCount(TIMER32_0_BASE, 3000000); // 1 second
    Timer32_startTimer(TIMER32_0_BASE, true);
}

// Function to check if timer is expired
bool isTimerExpired() {
    return (Timer32_getValue(TIMER32_0_BASE) == 0);
}

int main(void)
{
    // Stop watchdog timer
    MAP_WDT_A_holdTimer();

    // Initializations
    Graphics_Context g_sContext; // Create context
    initializeGraphics(&g_sContext);

    // Draw initial graphics
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_YELLOW);
    Graphics_fillCircle(&g_sContext, CIRCLE_X, CIRCLE_Y, CIRCLE_RADIUS);

    // Initialize and start a one-shot timer
    Timer32_initModule(TIMER32_0_BASE, TIMER32_PRESCALER_1, TIMER32_32BIT, TIMER32_PERIODIC_MODE);
    restartTimer();

    // Start demo
    while(!isTimerExpired()); // Wait one second

    // Draw blue quarter circle
    Graphics_Rectangle clipRegion = {63, 0, 127, 63}; // Top-right quadrant
    Graphics_setClipRegion(&g_sContext, &clipRegion);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLUE);
    Graphics_fillCircle(&g_sContext, CIRCLE_X, CIRCLE_Y, CIRCLE_RADIUS);

    restartTimer();
    while(!isTimerExpired()); // Wait one second

    // Draw red quarter circle
    clipRegion = (Graphics_Rectangle) {0, 0, 63, 63}; // Top-left quadrant
    Graphics_setClipRegion(&g_sContext, &clipRegion);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_RED);
    Graphics_fillCircle(&g_sContext, CIRCLE_X, CIRCLE_Y, CIRCLE_RADIUS);

    restartTimer();
    while(!isTimerExpired()); // Wait one second

    // Draw green quarter circle
    clipRegion = (Graphics_Rectangle) {63, 63, 127, 127}; // Bottom-right quadrant
    Graphics_setClipRegion(&g_sContext, &clipRegion);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_GREEN);
    Graphics_fillCircle(&g_sContext, CIRCLE_X, CIRCLE_Y, CIRCLE_RADIUS);

    restartTimer();
    while(!isTimerExpired()); // Wait one second

    // Draw black semicircle
    clipRegion = (Graphics_Rectangle) {0, 0, 127, 63}; // Upper half
    Graphics_setClipRegion(&g_sContext, &clipRegion);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    Graphics_fillCircle(&g_sContext, CIRCLE_X, CIRCLE_Y, CIRCLE_RADIUS/2);

    restartTimer();
    while(!isTimerExpired()); // Wait one second

    // Draw white semicircle
    clipRegion = (Graphics_Rectangle) {0, 63, 127, 127}; // Lower half
    Graphics_setClipRegion(&g_sContext, &clipRegion);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    Graphics_fillCircle(&g_sContext, CIRCLE_X, CIRCLE_Y, CIRCLE_RADIUS/2);

    restartTimer();
    while(1);
}
