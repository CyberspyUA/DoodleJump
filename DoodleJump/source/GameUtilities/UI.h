#pragma once
void numberToDigits(int score, int dig[50], int &cnt)
{
    int aux = score;
    if (aux != 0)
    {
        while (aux)
        {
            dig[cnt] = aux % 10;
            aux /= 10;
            cnt++;
        }
    }
    else
    {
        dig[cnt] = 0;
        cnt++;
    }
}