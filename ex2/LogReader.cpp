#include "LogReader.h"
#include <cctype>
#include <cstdlib>
#include <iostream>

using namespace std;

string LogReader::extractTag(string line)
{
    const string marker = "#tag:";
    size_t pos = line.find(marker);
    if (pos == string::npos)
    {
        return "";
    }

    pos = pos + marker.length();

    string token = "";
    while (pos < line.length() && !isspace(static_cast<unsigned char>(line[pos])))
    {
        token = token + line[pos];
        pos = pos + 1;
    }

    return token;
}

LogReader::LogReader(const char *fname)
{
    logFile.open(fname);
    if (!logFile)
    {
        cout << "Failed to open " << fname << endl;
        exit(1);
    }

    if (!getline(logFile, nextLine))
    {
        eofFound = true;
        nextLine = "";
    }
    else
    {
        if (!nextLine.empty() && nextLine.back() == '\r')
        {
            nextLine.pop_back();
        }
        eofFound = false;
    }
}

string LogReader::getNextTag()
{
    string line = nextLine;

    if (!getline(logFile, nextLine))
    {
        eofFound = true;
        nextLine = "";
    }
    else
    {
        if (!nextLine.empty() && nextLine.back() == '\r')
        {
            nextLine.pop_back();
        }
    }

    string tag = extractTag(line);

    bool hasLetter = false;
    for (int i = 0; i < (int)tag.length(); i++)
    {
        char c = tag[i];
        if (isalpha(static_cast<unsigned char>(c)))
        {
            hasLetter = true;
            break;
        }
    }

    if (!hasLetter)
    {
        return "";
    }

    for (int i = 0; i < (int)tag.length(); i++)
    {
        tag[i] = static_cast<char>(tolower(static_cast<unsigned char>(tag[i])));
    }

    return tag;
}

bool LogReader::isNextTag()
{
    return !eofFound;
}

void LogReader::close()
{
    if (logFile.is_open())
    {
        logFile.close();
    }
}
