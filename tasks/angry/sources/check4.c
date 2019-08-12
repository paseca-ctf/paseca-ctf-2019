int check4(char chr) // valid: 101
{
    if (((((((((chr * 4) + 463) << 4) ^ 3978) * 1153) + 1339) - 1293) ^ 384) == 17039208)
        return 1;
    return 0;
}