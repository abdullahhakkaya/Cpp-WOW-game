#include "include/raylib.h"
#include <string>
#include <cmath>

#define MAX_LETTERS 5  // "PAS" ve "KOYU" kelimelerinin maksimum harf sayısı

// Fonksiyon prototipleri
void DrawGame();
void UpdateGame();
void InitLevel(int level);
void levelControl(int score, int currentLevel);
void emptyBox(int lenght, int x, int y, int xx, int yy);
void emptyBoxPink(int lenght, int x, int y, int xx, int yy);
void emptyBoxDraw(int currentLevel);
void levelUpScreen();

// Global değişkenler
const int screenWidth = 1000;
const int screenHeight = 600;

Vector2 center = { screenWidth / 2, screenHeight / 2 };
float redCircleRadius=140;
float letterRadius=50;
float blueCircleRadius=40;
float distanceToMove=40;
float padding=80;
float whiteCircleRadius = 10;

std::string correctWord1;
std::string correctWord2;
std::string correctWord3;
std::string correctWord4;
std::string correctWord5;
std::string correctWord6;
bool correct1 = false;
bool correct2 = false;
bool correct3 = false;
bool correct4 = false;
bool correct5 = false;
bool correct6 = false;

int wordLength;
float angleStep;
float angle;
char textboxText[MAX_LETTERS + 1];
Rectangle textboxRect;
bool isMouseOver;
bool isTextboxActive;
Rectangle buttonRect;
Rectangle exitButtonRect;
bool isButtonPressed;
bool isCorrect;
bool isWrong;
float messageTimer;
float exitTimer;
int currentLevel;
int score = 0;
int letterPadding = 0;
bool isCorrectTextVisible = false;
Texture2D background;
Texture2D boxImage;
Texture2D boxImagePink;

void InitLevel(int level)
{
    // Seviyeye göre değişen parametrelerin ayarlanması
    switch (level)
    {
        case 1:
            correctWord1 = "PAS";
            correctWord2 = "SAP";
            correctWord3 = "-";
            correctWord4 = "-";
            correctWord5 = "-";
            correctWord6 = "-";
            break;
        case 2:
            correctWord1 = "KOYU";
            correctWord2 = "OYUK";
            correctWord3 = "YOK";
            correctWord4 = "KOY";
            correctWord5 = "-";
            correctWord6 = "-";
            break;
        case 3:
            correctWord1 = "ADAM";
            correctWord2 = "DAM";
            correctWord3 = "ADA";
            correctWord4 = "DAMA";
            correctWord5 = "AMA";
            correctWord6 = "-";
            break;
        case 4:
            correctWord1 = "ARKA";
            correctWord2 = "ARA";
            correctWord3 = "KARA";
            correctWord4 = "KAR";
            correctWord5 = "-";
            correctWord6 = "-";
            break;
        case 5:
            correctWord1 = "PINAR";
            correctWord2 = "ARI";
            correctWord3 = "NAR";
            correctWord4 = "ANI";
            correctWord5 = "-";
            correctWord6 = "-";
            break;
        case 6:
            correctWord1 = "KAZIK";
            correctWord2 = "KAZI";
            correctWord3 = "KAZ";
            correctWord4 = "KIZAK";
            correctWord5 = "KIZ";
            correctWord6 = "AKI";
            break;
        case 7:
            correctWord1 = "CEKET";
            correctWord2 = "TEK";
            correctWord3 = "ETEK";
            correctWord4 = "TEKE";
            correctWord5 = "ECE";
            correctWord6 = "-";
            break;
        case 8:
            correctWord1 = "SAHNE";
            correctWord2 = "SEN";
            correctWord3 = "HAN";
            correctWord4 = "HANE";
            correctWord5 = "SAN";
            correctWord6 = "HAS";
            break;
        case 9:
            correctWord1 = "KONUT";
            correctWord2 = "KONU";
            correctWord3 = "KOT";
            correctWord4 = "NOT";
            correctWord5 = "TOK";
            correctWord6 = "TON";
            break;
        case 10:
            correctWord1 = "LOKUM";
            correctWord2 = "OKUL";
            correctWord3 = "KUL";
            correctWord4 = "KUM";
            correctWord5 = "KOL";
            correctWord6 = "OLUK";
            break;
        default:
            break;
    }

    wordLength = correctWord1.length();

    // Harfleri kırmızı çemberin içine dağıtmak için açı hesaplaması
    angleStep = 360.0f / wordLength;
    angle = 0;

    // Diğer değişkenlerin başlangıç değerleri
    textboxText[0] = '\0';
    isButtonPressed = false;
    isCorrect = false;
    isWrong = false;
    messageTimer = 0.0f;
    currentLevel = level;
    correct1 = false;
    correct2 = false;
    correct3 = false;
    correct4 = false;
    correct5 = false;
    correct6 = false;
}
void levelControl(int score, int currentLevel)
{
     if (score >= 2 && currentLevel == 1 && (GetTime() - messageTimer > 2.0f))
    {
        InitLevel(2); // Seviye 2'ye geç
    }
     if (score >= 6 && currentLevel == 2 && (GetTime() - messageTimer > 2.0f))
    {
        InitLevel(3); // Seviye 3'ye geç
    }
     if (score >= 11 && currentLevel == 3 && (GetTime() - messageTimer > 2.0f))
    {
        InitLevel(4); // Seviye 4'ye geç
    }
     if (score >= 15 && currentLevel == 4 && (GetTime() - messageTimer > 2.0f))
    {
        InitLevel(5); // Seviye 5'ye geç
    }
     if (score >= 19 && currentLevel == 5 && (GetTime() - messageTimer > 2.0f))
    {
        InitLevel(6); // Seviye 6'ye geç
    }
     if (score >=25 && currentLevel == 6 && (GetTime() - messageTimer > 2.0f))
    {
        InitLevel(7); // Seviye 7'ye geç
    }
     if (score >= 30 && currentLevel == 7 && (GetTime() - messageTimer > 2.0f))
    {
        InitLevel(8); // Seviye 8'ye geç
    }
     if (score >= 36 && currentLevel == 8 && (GetTime() - messageTimer > 2.0f))
    {
        InitLevel(9); // Seviye 9'ye geç
    }
     if (score >= 42 && currentLevel == 9 && (GetTime() - messageTimer > 2.0f))
    {
        InitLevel(10); // Seviye 10'ye geç
    }
}

// seviyeye göre boş kutuları çizen fonksiyon
void emptyBoxDraw(int currentLevel)
{
    if(currentLevel==1)
    {
        emptyBox(3,100,200,0,60);
        emptyBox(2,160,320,60,0);
        if(correct1)
        {
            emptyBoxPink(3,100,200,0,60);
            for(int i=0 ,letterPadding = 0; i<correctWord1.length();i++,letterPadding += 60)
            {
            DrawText(correctWord1.substr(i,1).c_str(),110,(210+letterPadding),50,WHITE);
            }
        }
        if(correct2)
        {
            emptyBoxPink(3,100,320,60,0);
            for(int i=0 ,letterPadding = 0; i<correctWord2.length();i++,letterPadding += 60)
            {
            DrawText(correctWord2.substr(i,1).c_str(),110+letterPadding,330,50,WHITE);
            }
        }
        
    }
    if(currentLevel==2)
    {
        emptyBox(3,100,200,0,60);
        emptyBox(3,160,320,60,0);
        emptyBox(4,280,200,0,60);
        emptyBox(3,220,200,60,0);
        if(correct1)
        {
            emptyBoxPink(4,100,320,60,0);
            for(int i=0 ,letterPadding = 0; i<correctWord1.length();i++,letterPadding += 60)
            {
            DrawText(correctWord1.substr(i,1).c_str(),110+letterPadding,(330),50,WHITE);
            }
        }
        if(correct2)
        {
            emptyBoxPink(4,280,200,0,60);
            for(int i=0 ,letterPadding = 0; i<correctWord2.length();i++,letterPadding += 60)
            {
            DrawText(correctWord2.substr(i,1).c_str(),290,210+letterPadding,50,WHITE);
            }
        }
        if(correct3)
        {
            emptyBoxPink(3,100,200,0,60);
            for(int i=0 ,letterPadding = 0; i<correctWord3.length();i++,letterPadding += 60)
            {
            DrawText(correctWord3.substr(i,1).c_str(),110,(210+letterPadding),50,WHITE);
            }
        }
        if(correct4)
        {
            emptyBoxPink(3,220,200,60,0);
            for(int i=0 ,letterPadding = 0; i<correctWord4.length();i++,letterPadding += 60)
            {
            DrawText(correctWord4.substr(i,1).c_str(),230+letterPadding,210,50,WHITE);
            }
        }
    }
    if(currentLevel==3)
    {
        emptyBox(3,100,260,0,60);
        emptyBox(4,160,200,60,0);
        emptyBox(3,220,260,0,60);
        emptyBox(1,160,320,60,0);
        emptyBox(2,280,380,60,0);
        
        if(correct1)
        {
            emptyBoxPink(4,160,200,60,0);
            for(int i=0 ,letterPadding = 0; i<correctWord1.length();i++,letterPadding += 60)
            {
            DrawText(correctWord1.substr(i,1).c_str(),170+letterPadding,(210),50,WHITE);
            }
        }
        if(correct2)
        {
            emptyBoxPink(3,100,320,60,0);
            for(int i=0 ,letterPadding = 0; i<correctWord2.length();i++,letterPadding += 60)
            {
            DrawText(correctWord2.substr(i,1).c_str(),110+letterPadding,330,50,WHITE);
            }
        }
        if(correct3)
        {
            emptyBoxPink(3,100,260,0,60);
            for(int i=0 ,letterPadding = 0; i<correctWord3.length();i++,letterPadding += 60)
            {
            DrawText(correctWord3.substr(i,1).c_str(),110,(270+letterPadding),50,WHITE);
            }
        }
        if(correct4)
        {
            emptyBoxPink(4,220,200,0,60);
            for(int i=0 ,letterPadding = 0; i<correctWord4.length();i++,letterPadding += 60)
            {
            DrawText(correctWord4.substr(i,1).c_str(),230,210+letterPadding,50,WHITE);
            }
        }
        if(correct5)
        {
            emptyBoxPink(3,220,380,60,0);
            for(int i=0 ,letterPadding = 0; i<correctWord5.length();i++,letterPadding += 60)
            {
            DrawText(correctWord5.substr(i,1).c_str(),230+letterPadding,385,50,WHITE);
            }
        }
    }
    if(currentLevel==4)
    {
        emptyBox(3,160,200,0,60);
        emptyBox(3,220,260,60,0);
        emptyBox(3,100,380,60,0);
        emptyBox(2,340,320,0,60);
        if(correct1)
        {
            emptyBoxPink(4,160,260,60,0);
            for(int i=0 ,letterPadding = 0; i<correctWord1.length();i++,letterPadding += 60)
            {
            DrawText(correctWord1.substr(i,1).c_str(),170+letterPadding,(270),50,WHITE);
            }
        }
        if(correct2)
        {
            emptyBoxPink(3,340,260,0,60);
            for(int i=0 ,letterPadding = 0; i<correctWord2.length();i++,letterPadding += 60)
            {
            DrawText(correctWord2.substr(i,1).c_str(),350,270+letterPadding,50,WHITE);
            }
        }
        if(correct3)
        {
            emptyBoxPink(4,160,200,0,60);
            for(int i=0 ,letterPadding = 0; i<correctWord3.length();i++,letterPadding += 60)
            {
            DrawText(correctWord3.substr(i,1).c_str(),170,(210+letterPadding),50,WHITE);
            }
        }
        if(correct4)
        {
            emptyBoxPink(3,100,380,60,0);
            for(int i=0 ,letterPadding = 0; i<correctWord4.length();i++,letterPadding += 60)
            {
            DrawText(correctWord4.substr(i,1).c_str(),110+letterPadding,390,50,WHITE);
            }
        }
    }
    if(currentLevel==5)
    {
        emptyBox(3,100,200,60,0);
        emptyBox(1,160,260,60,0);
        emptyBox(4,100,320,60,0);
        emptyBox(3,340,260,0,60);
        if(correct1)
        {
            emptyBoxPink(5,100,320,60,0);
            for(int i=0 ,letterPadding = 0; i<correctWord1.length();i++,letterPadding += 60)
            {
            DrawText(correctWord1.substr(i,1).c_str(),110+letterPadding,(330),50,WHITE);
            }
        }
        if(correct2)
        {
            emptyBoxPink(3,340,260,0,60);
            for(int i=0 ,letterPadding = 0; i<correctWord2.length();i++,letterPadding += 60)
            {
            DrawText(correctWord2.substr(i,1).c_str(),350,270+letterPadding,50,WHITE);
            }
        }
        if(correct3)
        {
            emptyBoxPink(3,100,200,60,0);
            for(int i=0 ,letterPadding = 0; i<correctWord3.length();i++,letterPadding += 60)
            {
            DrawText(correctWord3.substr(i,1).c_str(),110+letterPadding,(210),50,WHITE);
            }
        }
        if(correct4)
        {
            emptyBoxPink(3,160,200,0,60);
            for(int i=0 ,letterPadding = 0; i<correctWord4.length();i++,letterPadding += 60)
            {
            DrawText(correctWord4.substr(i,1).c_str(),170,210+letterPadding,50,WHITE);
            }
        }
    }
    if(currentLevel==6)
    {
        emptyBox(3,160,200,0,60);
        emptyBox(5,100,260,60,0);
        emptyBox(3,40,380,60,0);
        emptyBox(4,280,200,0,60);
        emptyBox(3,280,440,60,0);
        emptyBox(2,400,320,0,60);
        
        if(correct1)
        {
            emptyBoxPink(5,100,260,60,0);
            for(int i=0 ,letterPadding = 0; i<correctWord1.length();i++,letterPadding += 60)
            {
            DrawText(correctWord1.substr(i,1).c_str(),110+letterPadding,(270),50,WHITE);
            }
        }
        if(correct2)
        {
            emptyBoxPink(4,160,200,0,60);
            for(int i=0 ,letterPadding = 0; i<correctWord2.length();i++,letterPadding += 60)
            {
            DrawText(correctWord2.substr(i,1).c_str(),170,210+letterPadding,50,WHITE);
            }
        }
        if(correct3)
        {
            emptyBoxPink(3,280,440,60,0);
            for(int i=0 ,letterPadding = 0; i<correctWord3.length();i++,letterPadding += 60)
            {
            DrawText(correctWord3.substr(i,1).c_str(),290+letterPadding,(450),50,WHITE);
            }
        }
        if(correct4)
        {
            emptyBoxPink(5,280,200,0,60);
            for(int i=0 ,letterPadding = 0; i<correctWord4.length();i++,letterPadding += 60)
            {
            DrawText(correctWord4.substr(i,1).c_str(),290,210+letterPadding,50,WHITE);
            }
        }
        if(correct5)
        {
            emptyBoxPink(3,400,320,0,60);
            for(int i=0 ,letterPadding = 0; i<correctWord5.length();i++,letterPadding += 60)
            {
            DrawText(correctWord5.substr(i,1).c_str(),410,330+letterPadding,50,WHITE);
            }
        }
        if(correct6)
        {
            emptyBoxPink(3,40,380,60,0);
            for(int i=0 ,letterPadding = 0; i<correctWord6.length();i++,letterPadding += 60)
            {
            DrawText(correctWord6.substr(i,1).c_str(),50+letterPadding,390,50,WHITE);
            }
        }
    }
    if(currentLevel==7)
    {
        emptyBox(2,100,260,60,0);
        emptyBox(3,220,260,0,60);
        emptyBox(3,280,320,60,0);
        emptyBox(2,340,200,0,60);
        emptyBox(5,100,440,60,0);
        
        if(correct1)
        {
            emptyBoxPink(5,100,440,60,0);
            for(int i=0 ,letterPadding = 0; i<correctWord1.length();i++,letterPadding += 60)
            {
            DrawText(correctWord1.substr(i,1).c_str(),110+letterPadding,(450),50,WHITE);
            }
        }
        if(correct2)
        {
            emptyBoxPink(3,340,200,0,60);
            for(int i=0 ,letterPadding = 0; i<correctWord2.length();i++,letterPadding += 60)
            {
            DrawText(correctWord2.substr(i,1).c_str(),350,210+letterPadding,50,WHITE);
            }
        }
        if(correct3)
        {
            emptyBoxPink(4,220,260,0,60);
            for(int i=0 ,letterPadding = 0; i<correctWord3.length();i++,letterPadding += 60)
            {
            DrawText(correctWord3.substr(i,1).c_str(),230,(270+letterPadding),50,WHITE);
            }
        }
        if(correct4)
        {
            emptyBoxPink(4,220,320,60,0);
            for(int i=0 ,letterPadding = 0; i<correctWord4.length();i++,letterPadding += 60)
            {
            DrawText(correctWord4.substr(i,1).c_str(),230+letterPadding,330,50,WHITE);
            }
        }
        if(correct5)
        {
            emptyBoxPink(3,100,260,60,0);
            for(int i=0 ,letterPadding = 0; i<correctWord5.length();i++,letterPadding += 60)
            {
            DrawText(correctWord5.substr(i,1).c_str(),110+letterPadding,270,50,WHITE);
            }
        }
    }
    if(currentLevel==8)
    {
        emptyBox(5,40,380,60,0);
        emptyBox(1,160,440,0,60);
        emptyBox(3,40,500,60,0);
        emptyBox(2,280,260,0,60);
        emptyBox(3,280,200,60,0);
        emptyBox(2,400,260,0,60);
        
        if(correct1)
        {
            emptyBoxPink(5,40,380,60,0);
            for(int i=0 ,letterPadding = 0; i<correctWord1.length();i++,letterPadding += 60)
            {
            DrawText(correctWord1.substr(i,1).c_str(),50+letterPadding,(390),50,WHITE);
            }
        }
        if(correct2)
        {
            emptyBoxPink(3,40,500,60,0);
            for(int i=0 ,letterPadding = 0; i<correctWord2.length();i++,letterPadding += 60)
            {
            DrawText(correctWord2.substr(i,1).c_str(),50+letterPadding,510,50,WHITE);
            }
        }
        if(correct3)
        {
            emptyBoxPink(3,160,380,0,60);
            for(int i=0 ,letterPadding = 0; i<correctWord3.length();i++,letterPadding += 60)
            {
            DrawText(correctWord3.substr(i,1).c_str(),170,(390+letterPadding),50,WHITE);
            }
        }
        if(correct4)
        {
            emptyBoxPink(4,280,200,0,60);
            for(int i=0 ,letterPadding = 0; i<correctWord4.length();i++,letterPadding += 60)
            {
            DrawText(correctWord4.substr(i,1).c_str(),290,210+letterPadding,50,WHITE);
            }
        }
        if(correct5)
        {
            emptyBoxPink(3,400,200,0,60);
            for(int i=0 ,letterPadding = 0; i<correctWord5.length();i++,letterPadding += 60)
            {
            DrawText(correctWord5.substr(i,1).c_str(),410,210+letterPadding,50,WHITE);
            }
        }
        if(correct6)
        {
            emptyBoxPink(3,280,200,60,0);
            for(int i=0 ,letterPadding = 0; i<correctWord6.length();i++,letterPadding += 60)
            {
            DrawText(correctWord6.substr(i,1).c_str(),290+letterPadding,210,50,WHITE);
            }
        }
    }
    if(currentLevel==9)
    {
        emptyBox(3,100,260,0,60);
        emptyBox(3,160,380,60,0);
        emptyBox(3,280,200,60,0);
        emptyBox(4,280,260,0,60);
        emptyBox(2,340,320,60,0);
        emptyBox(2,340,440,60,0);
        
        if(correct1)
        {
            emptyBoxPink(5,280,200,0,60);
            for(int i=0 ,letterPadding = 0; i<correctWord1.length();i++,letterPadding += 60)
            {
            DrawText(correctWord1.substr(i,1).c_str(),290,(210+letterPadding),50,WHITE);
            }
        }
        if(correct2)
        {
            emptyBoxPink(4,100,380,60,0);
            for(int i=0 ,letterPadding = 0; i<correctWord2.length();i++,letterPadding += 60)
            {
            DrawText(correctWord2.substr(i,1).c_str(),110+letterPadding,390,50,WHITE);
            }
        }
        if(correct3)
        {
            emptyBoxPink(3,280,200,60,0);
            for(int i=0 ,letterPadding = 0; i<correctWord3.length();i++,letterPadding += 60)
            {
            DrawText(correctWord3.substr(i,1).c_str(),290+letterPadding,(210),50,WHITE);
            }
        }
        if(correct4)
        {
            emptyBoxPink(3,280,320,60,0);
            for(int i=0 ,letterPadding = 0; i<correctWord4.length();i++,letterPadding += 60)
            {
            DrawText(correctWord4.substr(i,1).c_str(),290+letterPadding,330,50,WHITE);
            }
        }
        if(correct5)
        {
            emptyBoxPink(3,100,260,0,60);
            for(int i=0 ,letterPadding = 0; i<correctWord5.length();i++,letterPadding += 60)
            {
            DrawText(correctWord5.substr(i,1).c_str(),110,270+letterPadding,50,WHITE);
            }
        }
        if(correct6)
        {
            emptyBoxPink(3,280,440,60,0);
            for(int i=0 ,letterPadding = 0; i<correctWord6.length();i++,letterPadding += 60)
            {
            DrawText(correctWord6.substr(i,1).c_str(),290+letterPadding,450,50,WHITE);
            }
        }
    }
    if(currentLevel==10)
    {
        emptyBox(3,100,200,60,0);
        emptyBox(2,100,260,0,60);
        emptyBox(3,220,260,0,60);
        emptyBox(3,100,440,60,0);
        emptyBox(2,280,260,60,0);
        emptyBox(4,400,200,0,60);
        
        if(correct1)
        {
            emptyBoxPink(5,220,200,0,60);
            for(int i=0 ,letterPadding = 0; i<correctWord1.length();i++,letterPadding += 60)
            {
            DrawText(correctWord1.substr(i,1).c_str(),230,(210+letterPadding),50,WHITE);
            }
        }
        if(correct2)
        {
            emptyBoxPink(4,400,200,0,60);
            for(int i=0 ,letterPadding = 0; i<correctWord2.length();i++,letterPadding += 60)
            {
            DrawText(correctWord2.substr(i,1).c_str(),410,210+letterPadding,50,WHITE);
            }
        }
        if(correct3)
        {
            emptyBoxPink(3,100,200,60,0);
            for(int i=0 ,letterPadding = 0; i<correctWord3.length();i++,letterPadding += 60)
            {
            DrawText(correctWord3.substr(i,1).c_str(),110+letterPadding,(210),50,WHITE);
            }
        }
        if(correct4)
        {
            emptyBoxPink(3,100,440,60,0);
            for(int i=0 ,letterPadding = 0; i<correctWord4.length();i++,letterPadding += 60)
            {
            DrawText(correctWord4.substr(i,1).c_str(),110+letterPadding,450,50,WHITE);
            }
        }
        if(correct5)
        {
            emptyBoxPink(3,100,200,0,60);
            for(int i=0 ,letterPadding = 0; i<correctWord5.length();i++,letterPadding += 60)
            {
            DrawText(correctWord5.substr(i,1).c_str(),110,210+letterPadding,50,WHITE);
            }
        }
        if(correct6)
        {
            emptyBoxPink(4,220,260,60,0);
            for(int i=0 ,letterPadding = 0; i<correctWord6.length();i++,letterPadding += 60)
            {
            DrawText(correctWord6.substr(i,1).c_str(),230+letterPadding,270,50,WHITE);
            }
        }
    }
}


