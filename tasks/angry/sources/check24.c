int check24(char chr) // valid: 107
{
    if (((((((((chr * 1) + 1279) << 4) ^ 2849) * 1213) + 406) - 551) ^ 1815) == 29035707)
        return 1;
    return 0;
}