int check16(char chr) // valid: 95
{
    if (((((((((chr * 8) + 1330) << 2) ^ 1622) * 933) + 996) - 385) ^ 1684) == 9312397)
        return 1;
    return 0;
}