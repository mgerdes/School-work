
int main() {
    char c;

    char chari[50]; // assumes no word is longer than 49 characters
    int iPtr;
    bool IsDelimiter = false, WasDelimiter = false;
    for (int i = 0; i < 50; i++) 
    {
        chari[i] = '\0';
    }
    ifstream InFile;
    InFile.open("W:\\Shakespeare.txt", ios::binary);
    if (InFile.fail())
    {
        cout << "Unable to open input file\n\n"
            << "Program Exiting\n\nPress ENTER to exit\n";
        cin.get(c);
        exit(1);
    }
    iPtr = 0;
    InFile.get(c);
    while (!InFile.eof())
    {
        IsDelimiter = c == 32 || c == 10 || c == 13 || c == 9 ||
                c == '.' || c == ',' || c == '!' || c == ';' ||
                c == ':' || c == '(' || c == ')';

        if (IsDelimiter && !WasDelimiter)
        {
            WasDelimiter = true;

            //insert the shiz

            for (int i = 0; i < 50; i++)
            {
                chari[i] = '\0';
            }
            iptr = 0;
        }
        else if (!IsDelimiter)
        {
            chari[iPtr] = c;
            iPtr++;
        }
        else if (IsDelimiter && WasDelimiter)
        {
            // do nothing
        }
        WasDelimiter = IsDelimiter;
        InFile.get(c);

    }
    InFile.close();

    return 0;
}

