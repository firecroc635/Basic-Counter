#include "include/raylib.h" // for the window and stuff
#include "stdlib.h" // for itoa
#include "math.h"


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    int screenWidth = 500;
    int screenHeight = 500;
    Vector2 CacheScreenSize = {screenWidth, screenHeight};

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Basic counter");


    // Initialization
    //--------------------------------------------------------------------------------------

    //Loaded images
    Image IconImg = LoadImage("./Resources/WinIcon.png");
    SetWindowIcon(IconImg);         // Setting window Icon

    //Button properties
    Vector2 incButtonPos = {screenWidth*0.75, screenHeight*0.5};    //Increment button  init position
    Vector2 decButtonPos = {screenWidth*0.25, screenHeight*0.5};    //Decremenet button init position

    //Colors
    Color textCol = {0x00, 0x00, 0x00, 0xff};

    //Font usage
    float countSize = 70;   //Counted number font size

    //Font
    Font TextFont = LoadFontEx("./Resources/fonts/Nexa-Heavy.ttf", 70, 0, 250); //Main font used everywhere
    
    //Counter
    int count = 0;              //The counter variable which will hold the number we counted to
    char countC[10] = "0";      //The char that will be the "text" version of our count variable

    itoa(count, countC, 10);    //Iota to achieve what is said above
    Vector2 WcountC = MeasureTextEx(TextFont, countC, countSize, (float) 1);
    int WcountCR = 5 * round(WcountC.x / 5);
    

    Vector2 countPos = { screenWidth/2 - WcountC.x/2, screenHeight/2 - WcountC.y/2 };

    bool redraw = true;
    bool IncMouseHover = false;
    bool DecMouseHover = false;
    //--------------------------------------------------------------------------------------

    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //-----------------------------------------------------------------------------------------------------------

        //Optimisation bullshit
        if (GetScreenWidth() != CacheScreenSize.x ||  GetScreenHeight() != CacheScreenSize.y)  //Checks if screen is resized, then updates a "cached" screensize variable
        {
            CacheScreenSize = (Vector2){GetScreenWidth(), GetScreenHeight()};

            incButtonPos = (Vector2){CacheScreenSize.x*0.75, CacheScreenSize.y*0.5};
            decButtonPos = (Vector2){CacheScreenSize.x*0.25, CacheScreenSize.y*0.5};
            countPos = (Vector2) { CacheScreenSize.x/2 - WcountC.x/2, CacheScreenSize.y/2 - WcountC.y/2 };


            redraw = true;
        }

        //The poorly written if-statements
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if(CheckCollisionPointCircle(GetMousePosition(), incButtonPos, 40))
            {
                ++count;

                itoa(count, countC, 10);
                WcountC = MeasureTextEx(TextFont, countC, countSize, (float) 1);
                WcountCR = 5 * round(WcountC.x / 5);

                countPos = (Vector2) { CacheScreenSize.x/2 - WcountCR/2, CacheScreenSize.y/2 - WcountC.y/2 };

                redraw = true;
            }
            
            if (CheckCollisionPointCircle(GetMousePosition(), decButtonPos, 40))
            {
                --count;

                itoa(count, countC, 10);
                WcountC = MeasureTextEx(TextFont, countC, countSize, (float) 1);
                WcountCR = 5 * round(WcountC.x / 5);

                countPos = (Vector2) { CacheScreenSize.x/2 - WcountCR/2, CacheScreenSize.y/2 - WcountC.y/2 };

                redraw = true;
            }
                

        }
        
        if (CheckCollisionPointCircle(GetMousePosition(), incButtonPos, 40))
        {
            IncMouseHover = redraw = true;
        } 
        else if (CheckCollisionPointCircle(GetMousePosition(), decButtonPos, 40))
        {
            DecMouseHover = redraw = true;
        }

        if (IncMouseHover == true && !CheckCollisionPointCircle(GetMousePosition(), incButtonPos, 40))
        {
            IncMouseHover = false;
            redraw = true;
        } 
        else if (DecMouseHover == true && !CheckCollisionPointCircle(GetMousePosition(), decButtonPos, 40)) {
            DecMouseHover = false;
            redraw = true;
        }

        //-----------------------------------------------------------------------------------------------------------


        // Draw
        //----------------------------------------------------------------------------------
        if(redraw = true)
        {
            BeginDrawing();

                ClearBackground((Color) {0xcc, 0xcc, 0xcc, 0xff});
                
                if (DecMouseHover == 1)
                {
                    DrawCircleV(decButtonPos, 44, (Color) {0x44, 0x44, 0x44, 0xff});
                    DrawCircleV(decButtonPos, 34, (Color) {0x77, 0x77, 0x77, 0xff});
                    
                    DrawCircleV(incButtonPos, 40, (Color) {0x00, 0x00, 0x00, 0xff});
                    DrawCircleV(incButtonPos, 30, (Color) {0x55, 0x55, 0x55, 0xff});

                    DrawTriangle((Vector2){decButtonPos.x - 22, decButtonPos.y},
                    (Vector2){decButtonPos.x, decButtonPos.y+22},
                    (Vector2){decButtonPos.x + 22, decButtonPos.y},
                    (Color) {0xbb,0xbb,0xbb,0xff});

                    DrawTriangle((Vector2){incButtonPos.x + 20, incButtonPos.y},
                    (Vector2){incButtonPos.x, incButtonPos.y-20},
                    (Vector2){incButtonPos.x - 20, incButtonPos.y},
                    (Color) {0x88,0x88,0x88,0xff});

                } else if (IncMouseHover == 1)
                {
                    DrawCircleV(incButtonPos, 44, (Color) {0x44, 0x44, 0x44, 0xff});
                    DrawCircleV(incButtonPos, 33, (Color) {0x77, 0x77, 0x77, 0xff});
                    DrawCircleV(decButtonPos, 40, (Color) {0x00, 0x00, 0x00, 0xff});
                    DrawCircleV(decButtonPos, 30, (Color) {0x55, 0x55, 0x55, 0xff});

                    DrawTriangle((Vector2){incButtonPos.x + 22, incButtonPos.y},
                    (Vector2){incButtonPos.x, incButtonPos.y-22},
                    (Vector2){incButtonPos.x - 22, incButtonPos.y},
                    (Color) {0xbb,0xbb,0xbb,0xff});

                    DrawTriangle((Vector2){decButtonPos.x - 20, decButtonPos.y},
                    (Vector2){decButtonPos.x, decButtonPos.y+20},
                    (Vector2){decButtonPos.x + 20, decButtonPos.y},
                    (Color) {0x88,0x88,0x88,0xff});

                } else {
                    DrawCircleV(incButtonPos, 40, (Color) {0x00, 0x00, 0x00, 0xff});
                    DrawCircleV(incButtonPos, 30, (Color) {0x55, 0x55, 0x55, 0xff});    
                    DrawCircleV(decButtonPos, 40, (Color) {0x00, 0x00, 0x00, 0xff});
                    DrawCircleV(decButtonPos, 30, (Color) {0x55, 0x55, 0x55, 0xff});
                    DrawTriangle((Vector2){decButtonPos.x - 20, decButtonPos.y},
                    (Vector2){decButtonPos.x, decButtonPos.y+20},
                    (Vector2){decButtonPos.x + 20, decButtonPos.y},
                    (Color) {0x88,0x88,0x88,0xff});
                    DrawTriangle((Vector2){incButtonPos.x + 20, incButtonPos.y},
                    (Vector2){incButtonPos.x, incButtonPos.y-20},
                    (Vector2){incButtonPos.x - 20, incButtonPos.y},
                    (Color) {0x88,0x88,0x88,0xff});
                }

                DrawTextEx(TextFont, countC, countPos, countSize, (float)1, textCol);
                redraw = false;

            EndDrawing();
        }
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadFont(TextFont);

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}