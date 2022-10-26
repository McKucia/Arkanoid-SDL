#pragma once

class Configuration
{
private:
   Configuration() {}

public:
   static float screenWidth;
   static float screenHeight;

   static constexpr float paddleWidth = 100;
   static constexpr float paddleHeight = 25;
   static constexpr float paddleSpeed = 45;
   static constexpr float paddleMarginBottom = 10;
   static constexpr char paddleSpritePath[] = "./data/01-Breakout-Tiles.png";

   static constexpr float ballSpeed = 50;
   static constexpr float ballSpeedIncrement = 0.5f;
   static constexpr float ballDiameter = 15;
   static constexpr char ballSpritePath[] = "./data/62-Breakout-Tiles.png";

   static constexpr float brickWidth = 40;
   static constexpr float brickHeight = 20;
   static constexpr char redBrickSpritePath[] = "./data/07-Breakout-Tiles.png";
   static constexpr char pinkBrickSpritePath[] = "./data/05-Breakout-Tiles.png";

   static constexpr float cursorWidth = 30;
   static constexpr float cursorHeight = 30;
   static constexpr char cursorSpritePath[] = "./data/crosshair.png";

   static constexpr float abilitySpeed = 30;
   static constexpr float abilityWidth = 20;
   static constexpr float abilityHeight = 20;
   static constexpr char abilitySpritePath[] = "./data/59-Breakout-Tiles.png";

   static constexpr int boardColumns = 18;
   static constexpr int boardRows = 4;

   static constexpr float boardUpperLeftPosY = 20;
};