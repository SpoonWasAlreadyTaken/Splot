#include <iostream>
#include <raylib.h>
#include <string>
#include <vector>
#include <iterator>

Color colorBG = {4,4,5, 255};
Color colorFG = {181, 143, 255, 255};

size_t height = 256;
size_t width = 256;

Image image;
Texture2D vImage;
RenderTexture2D drawTarget;



void DoFlagParam(const std::string& flag, const char *param);

void LoadFromSTDIN(const char *img);


int main(int argc, char **argv) {
    std::cout << "Args: " << argc << "\n";

    if (argc == 2) {
        LoadFromSTDIN(argv[1]);
        width = image.width;
        height = image.height;
    }
    else {
        for (int i = 1; i < argc; ++i) {
            std::cout << argv[i] << "\n";
            if (argv[i][0] == '-' && argc > i + 1) {
                DoFlagParam(argv[i], argv[i + 1]);
                ++i;
            }
        }
    }

    InitWindow(width + 64, height + 64, "raylib example - basic window");
    vImage = LoadTextureFromImage(image);
    drawTarget = LoadRenderTexture(width, height);

    while (!WindowShouldClose())
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) { 
            BeginTextureMode(drawTarget);
            
            Vector2 mousePos = GetMousePosition();

            DrawCircle(mousePos.x, mousePos.y, 25, RED);

            EndTextureMode();
        }


        BeginDrawing();
        ClearBackground(colorBG);

        if (!image.data) DrawText("OOPS! It seems the image failed to load or is still loading.", (width/2) + 64, (height/2) + 64, 20, colorFG);

        DrawTexture(vImage, 32, 32, WHITE); 
        DrawTextureRec(drawTarget.texture, (Rectangle){0,0, (float)drawTarget.texture.width, (float)-drawTarget.texture.height}, (Vector2){32,32}, WHITE);





        EndDrawing();
    }


    CloseWindow();
    UnloadImage(image);
    UnloadTexture(vImage);

    return 0;
}






void DoFlagParam(const std::string& flag, const char *param) {
    if (flag == "-f") {
        image = LoadImage(param);
        height = image.height;
        width = image.width;
        std::cout << "Loaded image from: " << param << "\n";
    }
    else { std::cout << "Non existant Flag or Paramater\n"; }
}


void LoadFromSTDIN(const char *img) {
    std::vector<unsigned char> data{std::istreambuf_iterator<char>(std::cin), std::istreambuf_iterator<char>()};
    if (data.empty()) { std::cout << "No Image )_:\n"; return; }
    
    image = LoadImageFromMemory(".ppm", data.data(), (int)data.size());
}








