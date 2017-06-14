#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>

// Key press textures constants
enum KeyPressTextures
{
    KEY_PRESS_TEXTURE_DEFAULT,
    KEY_PRESS_TEXTURE_UP,
    KEY_PRESS_TEXTURE_DOWN,
    KEY_PRESS_TEXTURE_LEFT,
    KEY_PRESS_TEXTURE_RIGHT,
    KEY_PRESS_TEXTURE_TOTAL
};

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// The window we'll be rendering to
SDL_Window* gWindow = NULL;

// The window renderer
SDL_Renderer* gRenderer = NULL;

// The images that correspond to a keypress
SDL_Texture* gKeyPressTextures[KEY_PRESS_TEXTURE_TOTAL];

// Current displayed image
SDL_Texture* gCurrentTexture = NULL;

// Starts up SDL and creates window
bool init();

// Loads media
bool loadMedia();

// Frees media and shuts down SDL
void close();

// Loads individual image
SDL_Texture* loadTexture(std::string path);

int main(int argc, char* args[]) {
    // Start up SDL and create window
    if (!init()) {
        printf("Failed to initialize!\n");
    } else {
        // Load media
        if (!loadMedia()) {
            printf("Failed to load media!\n");
        } else {
            // Main loop flag
            bool quit = false;

            // Event handler
            SDL_Event e;

            // Set default current texture
            gCurrentTexture = gKeyPressTextures[KEY_PRESS_TEXTURE_DEFAULT];

            // While application is running
            while (!quit) {
                // Handle events on queue
                while (SDL_PollEvent(&e) != 0) {
                    // User requests quit
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    } else if(e.type == SDL_KEYDOWN) { // User presses a key
                        // Select textures based on key press
                        switch (e.key.keysym.sym) {
                            case SDLK_UP:
                                gCurrentTexture = gKeyPressTextures[KEY_PRESS_TEXTURE_UP];
                                break;

                            case SDLK_DOWN:
                                gCurrentTexture = gKeyPressTextures[KEY_PRESS_TEXTURE_DOWN];
                                break;

                            case SDLK_LEFT:
                                gCurrentTexture = gKeyPressTextures[KEY_PRESS_TEXTURE_LEFT];
                                break;

                            case SDLK_RIGHT:
                                gCurrentTexture = gKeyPressTextures[KEY_PRESS_TEXTURE_RIGHT];
                                break;

                            default:
                                gCurrentTexture = gKeyPressTextures[KEY_PRESS_TEXTURE_DEFAULT];
                                break;
                        }
                    }
                }

                // Clear screen
                SDL_RenderClear(gRenderer);

                // Render texture to screen
                SDL_RenderCopy(gRenderer, gCurrentTexture, NULL, NULL);

                // Update screen
                SDL_RenderPresent(gRenderer);
            }
        }
    }

    // Free resources and close SDL
    close();

    return 0;
}

bool init() {
    // Initialization flag
    bool success = true;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    } else {
        // Create window
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        } else {
            // Set texture filtering to linear
            if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
                printf("Warning: Linear texture filtering not enabled!");
            }

            // Create window
            gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
            if (gWindow == NULL) {
                printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            } else {
                // Create renderer for window
                gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
                if (gRenderer == NULL) {
                    printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                    success = false;
                } else {
                    // Initialize renderer color
                    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                    // Initialize PNG loading
                    int imgFlags = IMG_INIT_PNG;
                    if (!(IMG_Init(imgFlags) & imgFlags)) {
                        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                        success = false;
                    }
                }
            }
        }
    }

    return success;
}

bool loadMedia() {
    // Loading success flag
    bool success = true;

    // Load default texture
    gKeyPressTextures[KEY_PRESS_TEXTURE_DEFAULT] = loadTexture("press.png");
    if (gKeyPressTextures[KEY_PRESS_TEXTURE_DEFAULT] == NULL) {
        puts("Failed to load default image!");
        puts("Please run this binary on your directory.");
        success = false;
    }

    // Load up texture
    gKeyPressTextures[KEY_PRESS_TEXTURE_UP] = loadTexture("up.png");
    if (gKeyPressTextures[KEY_PRESS_TEXTURE_UP] == NULL) {
        puts("Failed to load up image!");
        puts("Please run this binary on your directory.");
        success = false;
    }

    // Load down texture
    gKeyPressTextures[KEY_PRESS_TEXTURE_DOWN] = loadTexture("down.png");
    if (gKeyPressTextures[KEY_PRESS_TEXTURE_DOWN] == NULL) {
        puts("Failed to load down image!");
        puts("Please run this binary on your directory.");
        success = false;
    }

    // Load left texture
    gKeyPressTextures[KEY_PRESS_TEXTURE_LEFT] = loadTexture("left.png");
    if (gKeyPressTextures[KEY_PRESS_TEXTURE_LEFT] == NULL) {
        puts("Failed to load left image!");
        puts("Please run this binary on your directory.");
        success = false;
    }

    // Load right texture
    gKeyPressTextures[KEY_PRESS_TEXTURE_RIGHT] = loadTexture("right.png");
    if (gKeyPressTextures[KEY_PRESS_TEXTURE_RIGHT] == NULL) {
        puts("Failed to load right image!");
        puts("Please run this binary on your directory.");
        success = false;
    }

    return success;
}

void close() {
    // Free loaded image
    SDL_DestroyTexture(gCurrentTexture);
    gCurrentTexture = NULL;

    // Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

SDL_Texture* loadTexture(std::string path)
{
    // The final texture
    SDL_Texture* newTexture = NULL;

    // Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    } else {
        // Create texture from texture pixels
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == NULL) {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }

        // Get rid of old loaded texture
        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}
