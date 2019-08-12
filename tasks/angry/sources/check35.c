int check35(char chr) // valid: 57
{
    if (((((((((chr * 9) + 1054) << 3) ^ 1207) * 1084) + 1533) - 136) ^ 977) == 14516264)
        return 1;
    return 0;
}