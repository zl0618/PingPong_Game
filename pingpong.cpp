#include "raylib.h"

struct Ball {
    float x, y;
    float speedX, speedY;
    float radius;
    Color color;
    
    Ball(float startX, float startY, float sX, float sY, float r, Color c) {
        x = startX;
        y = startY;
        speedX = sX;
        speedY = sY;
        radius = r;
        color = c;
    }
    
    void Update() {
        x += speedX * GetFrameTime();
        y += speedY * GetFrameTime();
        
        // Only bounce off top and bottom walls (not left/right for scoring)
        if (y > GetScreenHeight() || y < 0) {
            speedY = -speedY;
        }
    }
    
    void Draw() {
        DrawCircle(x, y, radius, color);
    }
};

struct Paddle {
    float x, y;
    float width, height;
    float speed;
    Color color;
    bool isLeftPaddle;
    
    Paddle(float startX, float startY, float w, float h, float s, Color c, bool left) {
        x = startX;
        y = startY;
        width = w;
        height = h;
        speed = s;
        color = c;
        isLeftPaddle = left;
    }
    
    void Update(){
        if (isLeftPaddle) {
            // Left paddle: W and S keys
            if (IsKeyDown(KEY_W) && y > 0) {
                y -= speed * GetFrameTime(); // Move up
            }
            if (IsKeyDown(KEY_S) && y < GetScreenHeight() - height) {
                y += speed * GetFrameTime(); // Move down
            }
        } else {
            // Right paddle: UP and DOWN arrow keys
            if (IsKeyDown(KEY_UP) && y > 0) {
                y -= speed * GetFrameTime(); // Move up
            }
            if (IsKeyDown(KEY_DOWN) && y < GetScreenHeight() - height) {
                y += speed * GetFrameTime(); // Move down
            }
        }
    }
    
    void Draw() {
        DrawRectangle(x, y, width, height, color);
    }
};

struct Score {
    int leftScore;
    int rightScore;
    
    Score() {
        leftScore = 0;
        rightScore = 0;
    }
    
    void CheckGoal(Ball& ball) {
        // If ball goes off left side, right player scores
        if (ball.x < 0) {
            rightScore++;
            ResetBall(ball);
        }
        // If ball goes off right side, left player scores
        else if (ball.x > GetScreenWidth()) {
            leftScore++;
            ResetBall(ball);
        }
    }
    
    void ResetBall(Ball& ball) {
        ball.x = GetScreenWidth() / 2;
        ball.y = GetScreenHeight() / 2;
        // Reverse direction so ball goes toward the player who didn't score
        ball.speedX = -ball.speedX;
    }

    void Draw() {
        DrawText(TextFormat("Left: %d", leftScore), 10, 30, 20, LIGHTGRAY);
        DrawText(TextFormat("Right: %d", rightScore), GetScreenWidth() - 150, 30, 20, LIGHTGRAY);
    }
};

bool CheckCollision(Ball& ball, Paddle& paddle) {
    if (ball.x + ball.radius > paddle.x && 
        ball.x - ball.radius < paddle.x + paddle.width &&
        ball.y + ball.radius > paddle.y && 
        ball.y - ball.radius < paddle.y + paddle.height) {
        
        // Ball is colliding with the paddle
        ball.speedX = -ball.speedX; // Reverse the X speed
        return true;
    }
    return false;
}

bool CheckPoints(Ball& ball, Paddle& leftPaddle, Paddle& rightPaddle) {
    if (CheckCollision(ball, leftPaddle) || CheckCollision(ball, rightPaddle))
        return true;
    return false;
}

int main(){
    // Create a window
    InitWindow(800, 600, "Pong Game"); 
    SetWindowState(FLAG_VSYNC_HINT); // Enable VSync to limit the frame rate
    
    Ball ball(400, 300, 200, 200, 5, BLACK);
    Paddle leftPaddle(10, 250, 10, 100, 300, LIGHTGRAY, true);   // true = left paddle
    Paddle rightPaddle(780, 250, 10, 100, 300, LIGHTGRAY, false); // false = right paddle
    Score gameScore;
    
    bool gameStarted = false; // Game state: false = start screen, true = playing

    while (!WindowShouldClose()) {
        
        // Check if any key is pressed to start the game
        if (!gameStarted && GetKeyPressed() != 0) {
            gameStarted = true;
        }
        
        // Only update game objects if game has started
        if (gameStarted) {
            ball.Update();
            leftPaddle.Update();
            rightPaddle.Update();
            
            // Check collisions
            CheckCollision(ball, leftPaddle);
            CheckCollision(ball, rightPaddle);
            
            // Check for goals and update score
            gameScore.CheckGoal(ball);
        }

        BeginDrawing(); // Start the rendering process
            ClearBackground(RAYWHITE); // Clear the background with a white color
            
            if (!gameStarted) {
                // Show start screen
                DrawText("PONG GAME", GetScreenWidth()/2 - 150, GetScreenHeight()/2 - 100, 60, BLACK);
                DrawText("Press any key to start", GetScreenWidth()/2 - 120, GetScreenHeight()/2 - 20, 30, GRAY);
                DrawText("Left Player: W/S keys", GetScreenWidth()/2 - 110, GetScreenHeight()/2 + 20, 20, LIGHTGRAY);
                DrawText("Right Player: UP/DOWN arrows", GetScreenWidth()/2 - 140, GetScreenHeight()/2 + 50, 20, LIGHTGRAY);
            } else {
                // Show game
                ball.Draw();
                leftPaddle.Draw();
                rightPaddle.Draw();
                gameScore.Draw();
            }

            DrawFPS(0,0); // FPS is frame per second, displayed at position (10, 10)
        EndDrawing(); 
    }

    CloseWindow(); 
    return 0;
}