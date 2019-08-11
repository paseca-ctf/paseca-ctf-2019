int check8(char chr) // valid: 100
{
    if (((((((((chr * 3) + 1237) << 2) ^ 983) * 1230) + 977) - 1049) ^ 3079) == 8758149)
        return 1;
    return 0;
}