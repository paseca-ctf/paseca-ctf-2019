int check11(char chr) // valid: 95
{
    if (((((((((chr * 4) + 285) << 1) ^ 453) * 28) + 267) - 340) ^ 849) == 35306)
        return 1;
    return 0;
}