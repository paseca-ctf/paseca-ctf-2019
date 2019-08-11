int check35(char chr) // valid: 57
{
    if (((((((((chr * 8) + 1589) << 2) ^ 1412) * 1305) + 653) - 282) ^ 1271) == 8831636)
        return 1;
    return 0;
}