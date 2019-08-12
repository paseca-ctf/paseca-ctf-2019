int check5(char chr) // valid: 99
{
    if (((((((((chr * 1) + 58) << 4) ^ 1889) * 309) + 1487) - 713) ^ 3552) == 1160011)
        return 1;
    return 0;
}