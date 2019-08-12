int check15(char chr) // valid: 115
{
    if (((((((((chr * 7) + 1351) << 3) ^ 3064) * 864) + 50) - 906) ^ 2083) == 16053643)
        return 1;
    return 0;
}