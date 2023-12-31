#include "General.h"
#include <math.h>
float General::calculateRotation(int mouseX, int mouseY, int centerX, int centerY)
{
    float X = mouseX - centerX;
    float Y = mouseY - centerY;

    float cosa = X/sqrt(pow(X,2) + pow(Y, 2));
    
    if(mouseY > centerY)
        return acos(cosa) *  180 / 3.14;
    return -acos(cosa) * 180 / 3.14;
}

bool General::collisionCheck(SDL_Rect* A, SDL_Rect* B)
{
    if (A == nullptr or B == nullptr) return false;

	bool bHorizontal = (A->x < B->x + B->w && B->x < A->x + A->w);
	bool bVertical = (A->y < B->y + B->h && B->y < A->y + A->h);
	return bHorizontal && bVertical;
}

float General::deg2rad(float deg)
{
    return deg * 3.14 / 180;
}

float General::calculateDistance(int x1, int y1, int x2, int y2)
{
    return sqrt(pow(x1 - x2 , 2) + pow(y1 - y2, 2));
}

float General::pointDistance(SDL_Point* A, SDL_Point* B)
{
    return sqrt(pow(A->x - B->x, 2) + pow(A->y - B->y, 2));
}
