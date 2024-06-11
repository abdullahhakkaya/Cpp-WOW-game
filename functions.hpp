#include "level.hpp"

void DrawGame()
{
    BeginDrawing();

    ClearBackground(RAYWHITE);
    DrawTexture(background,0,0,WHITE);

    // Puanı ve seviyeyi ekrana yazdır
    DrawText(("Score: " + std::to_string(score)).c_str(), screenWidth - 170, 20, 30, BLACK);
    DrawText(("Level: " + std::to_string(currentLevel)).c_str(), screenWidth - 170, 50, 30, BLACK);

    // Kırmızı çemberi çiz
    DrawCircleV({ screenWidth - redCircleRadius - padding, screenHeight / 2 }, redCircleRadius, WHITE);
    DrawCircleLinesV({ screenWidth - redCircleRadius - padding, screenHeight / 2 }, redCircleRadius, BLACK);

    // Harfleri dairenin içine yazdırır
    for (int i = 0; i < wordLength; i++)
    {
        // Harfin pozisyonunu hesapla
        Vector2 letterPosition;
        letterPosition.x = screenWidth - redCircleRadius - padding + (redCircleRadius - distanceToMove) * cos(DEG2RAD * angle);
        letterPosition.y = screenHeight / 2 + (redCircleRadius - distanceToMove) * sin(DEG2RAD * angle);

        // Harf çemberini çiz (kırmızı çemberin içinde olsun)
        if (CheckCollisionPointCircle(GetMousePosition(), letterPosition, blueCircleRadius))
        {
            DrawCircleV(letterPosition, blueCircleRadius, Fade(BLUE, 0.5f)); // Fare üzerindeyken dairenin rengi farklı görünsün
        }
        else
        {
            DrawCircleV(letterPosition, blueCircleRadius, BLUE); // Mavi daireler
            DrawCircleLinesV(letterPosition, blueCircleRadius, BLUE); // Mavi daireler
        }

        // Harfi çiz (dairelerin tam merkezine yerleştir)
        DrawText(correctWord1.substr(i, 1).c_str(), static_cast<int>(letterPosition.x + 10) - letterRadius / 2, static_cast<int>(letterPosition.y +5) - letterRadius / 2, 40, WHITE);

        // Bir sonraki harf için açıyı güncelle
        angle += angleStep;
    }

    // Gri dairenin merkezini hesapla
    Vector2 grayCircleCenter = { screenWidth - redCircleRadius - padding, screenHeight / 2 };

    // TextBox
    DrawRectangleRec(textboxRect, WHITE);
    DrawRectangleLinesEx(textboxRect, 1, BLACK);
    DrawText(textboxText, textboxRect.x + 10, textboxRect.y + 15, 40, BLACK);

    // Button
    DrawRectangleRec(buttonRect, isButtonPressed ? DARKBLUE : BLUE);
    DrawRectangleLinesEx(buttonRect, 2, BLACK);
    DrawText("CHECK", buttonRect.x + 10, buttonRect.y + 7, 30, WHITE);

    //Exit button
    DrawRectangleRec(exitButtonRect, isButtonPressed ? RED : MAROON);
    DrawRectangleLinesEx(exitButtonRect, 2, BLACK);
    DrawText("EXIT", exitButtonRect.x + 10, exitButtonRect.y + 7, 30, WHITE);

    //Bos Kutular
    emptyBoxDraw(currentLevel);

    // Doğru/yanlış mesajlarını kontrol et ve gerekirse ekrana yaz
    if (isCorrect || isWrong)
    {
        DrawText(isCorrect ? "DOGRU KELIME" : "YANLIS KELIME", textboxRect.x, textboxRect.y + 70, 20, isCorrect ? GREEN : RED);
    }

    EndDrawing();
}

void UpdateGame()
{
    
    // TextBox'in boyutlarını ve konumunu ayarla
    textboxRect.x = 50;
    textboxRect.y = 50;
    textboxRect.width = 240;
    textboxRect.height = 60;

    // Button
    buttonRect.x = 50 + textboxRect.width + 10;
    buttonRect.y = 60;
    buttonRect.width = 120;
    buttonRect.height = 40;

    //ExitButton
    exitButtonRect.x = 850;
    exitButtonRect.y = 90;
    exitButtonRect.width = 100;
    exitButtonRect.height = 40;

    // TextBox
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !isButtonPressed)
    {
        Vector2 mousePosition = GetMousePosition();
        if (CheckCollisionPointRec(mousePosition, buttonRect))
        {
            isButtonPressed = true;
        }
        else
        {
            for (int i = 0; i < wordLength; i++)
            {
                Vector2 letterPosition;
                letterPosition.x = screenWidth - redCircleRadius - padding + (redCircleRadius - distanceToMove) * cos(DEG2RAD * angle);
                letterPosition.y = screenHeight / 2 + (redCircleRadius - distanceToMove) * sin(DEG2RAD * angle);

                if (CheckCollisionPointCircle(mousePosition, letterPosition, blueCircleRadius))
                {
                    snprintf(textboxText, MAX_LETTERS + 1, "%s%c", textboxText, correctWord1[i]);
                    isTextboxActive = true; // TextBox her zaman aktif olsun
                }

                angle += angleStep;
            }
        }
    }

    // Button
    if (isButtonPressed && !isCorrect && !isWrong)
    {
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            std::string inputText(textboxText);
            if (inputText == correctWord1 || inputText == correctWord2 ||
                inputText == correctWord3 || inputText == correctWord4 || 
                inputText == correctWord5 || inputText == correctWord6)
            {
                if(inputText == correctWord1){
                    correct1 = true;}
                if(inputText == correctWord2){
                    correct2 = true;}
                if(inputText == correctWord3){
                    correct3 = true;}
                if(inputText == correctWord4){
                    correct4 = true;}
                if(inputText == correctWord5){
                    correct5 = true;}
                if(inputText == correctWord6){
                    correct6 = true;}
                isCorrect = true;
                messageTimer = GetTime(); // Doğru mesajın gösterilme zamanını kaydet
                score += 1; // Doğru cevapta puanı 5 artır
                isCorrectTextVisible = true; // Mavi renkte yazıyı göster
            }
            else
            {
                isWrong = true;
                messageTimer = GetTime(); // Yanlış mesajın gösterilme zamanını kaydet
            }
        }
    }

    // Doğru/yanlış mesajlarının gösterilme süresini kontrol et
    if ((isCorrect || isWrong) && (GetTime() - messageTimer > 1.0f))
    {
        isCorrect = false;
        isWrong = false;
        textboxText[0] = '\0'; // TextBox'ı temizle
        isButtonPressed = false;
        //isCorrectTextVisible = false; // Mavi renkte yazıyı gizle
    }

    // Exit butonunun işlevleri
    if (CheckCollisionPointRec(GetMousePosition(),exitButtonRect))
    {
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            exitTimer = 0.0f;
            
            while(exitTimer < 10.0f)
            {
                BeginDrawing();
                ClearBackground(RAYWHITE);
                // Puanı ve seviyeyi ekrana yazdır
                DrawText(("Score: " + std::to_string(score)).c_str(), 350, 250, 60, RED);
                DrawText(("Level: " + std::to_string(currentLevel)).c_str(), 350, 310, 60, RED);
                exitTimer += GetFrameTime();
                EndDrawing();
                if (exitTimer >= 5.0f) break;
            }
            CloseWindow();
            
        }
    }
    

    // Mouse'un kücük dairelerin üzerinde olup olmadığını kontrol et
    isMouseOver = false;
    for (int i = 0; i < wordLength; i++)
    {
        Vector2 letterPosition;
        letterPosition.x = screenWidth - redCircleRadius - padding + (redCircleRadius - distanceToMove) * cos(DEG2RAD * angle);
        letterPosition.y = screenHeight / 2 + (redCircleRadius - distanceToMove) * sin(DEG2RAD * angle);

        if (CheckCollisionPointCircle(GetMousePosition(), letterPosition, blueCircleRadius))
        {
            isMouseOver = true;
            break;
        }

        angle += angleStep;
    }

    angle = 0; // Açıyı sıfırla

    // Puanı kontrol et
    levelControl(score,currentLevel);
}
// boş kutuları çizen fonksiyon
void emptyBox(int lenght, int x, int y, int xx, int yy)
{
    int i=0;
    do
    {
        DrawTexture(boxImage,x,y,WHITE);
        x += xx;
        y += yy;
        i++;
    } while (i<lenght);
}
// pembe kutuları çizen fonksiyon
void emptyBoxPink(int lenght, int x, int y, int xx, int yy)
{
    int i=0;
    do
    {
        DrawTexture(boxImagePink,x,y,WHITE);
        x += xx;
        y += yy;
        i++;
    } while (i<lenght);
}