int check20(char chr) // valid: 107
{
    if (((((((((chr * 9) + 540) << 4) ^ 3219) * 1793) + 288) - 1025) ^ 540) == 37355934)
        return 1;
    return 0;
}