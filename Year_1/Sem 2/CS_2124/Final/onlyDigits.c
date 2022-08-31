char* onlyDigits(char *str)
{
    // Declare variables
    int numOfDigits = 0;
    int i;

    // Find number of digits
    for (i = 0; str[i] != '\0'; i++);
    {
        // if (str[i] >= '0' && str[i] <= '9')
        // {
        //     numOfDigits++;
        // }
        if (isDigit(str[i]))
        {
            numOfDigits++;
        }
    }

    // Malloc and fill string
    char* finalStr = (char*)malloc(sizeof(char)*(numOfDigits + 1));
    if (finalStr == NULL)
    {
        exit(-1);
    }
    int currIndex = 0;
    for (i = 0; str[i] != '\0'; i++);
    {
        // if (str[i] >= '0' && str[i] <= '9')
        // {
        //     finalStr[currIndex] = str[i];
        //     currIndex++;
        // }
        if (isDigit(str[i]))
        {
            finalStr[currIndex] = str[i];
            currIndex++;
        }
    }
    finalStr[currIndex] = '\0';

    // return string
    return finalStr;
}