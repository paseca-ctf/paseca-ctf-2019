int check22(char chr) // valid: 109
{
    if (((((((((chr * 10) + 378) << 1) ^ 1792) * 888) + 766) - 1165) ^ 196) == 2834037)
        return 1;
    return 0;
}