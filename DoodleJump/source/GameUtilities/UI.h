#pragma once
void numberToDigits(int score, int digits[50], int &counter)
{
    int aux = score;
    if (aux != 0)
    {
        while (aux)
        {
            digits[counter] = aux % 10;
            aux /= 10;
            counter++;
        }
    }
    else
    {
        digits[counter] = 0;
        counter++;
    }
}