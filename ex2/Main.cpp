#include <iostream>
#include <fstream>
#include <string>
#include "LogReader.h"

using namespace std;

const int MAX_TAGS = 5;

string gTags[MAX_TAGS];
int gCounts[MAX_TAGS];
int gNumTags = 0;
int gTotalLines = 0;
string gLogFileName = "";

void printBarChart(ofstream &outFile);

ostream &operator<<(ostream &out, const LogReader &reader);

int main()
{
    string logFileName;
    string tagFileName;
    string outputFileName;

    cout << "Enter log file name: ";
    cin >> logFileName;

    cout << "Enter tag list file name: ";
    cin >> tagFileName;

    cout << "Enter output file name: ";
    cin >> outputFileName;

    gLogFileName = logFileName;

    ifstream tagFile(tagFileName.c_str());
    if (!tagFile)
    {
        cout << "Could not open " << tagFileName << endl;
        return 1;
    }

    gNumTags = 0;
    while (gNumTags < MAX_TAGS && getline(tagFile, gTags[gNumTags]))
    {
        if (gTags[gNumTags] != "")
        {
            gCounts[gNumTags] = 0;
            gNumTags = gNumTags + 1;
        }
    }

    tagFile.close();

    if (gNumTags == 0)
    {
        cout << "No tags read" << endl;
        return 1;
    }

    LogReader reader(logFileName.c_str());

    gTotalLines = 0;

    while (reader.isNextTag())
    {
        string tag = reader.getNextTag();
        gTotalLines = gTotalLines + 1;

        if (tag == "")
        {
            continue;
        }

        int index = -1;

        for (int i = 0; i < gNumTags; i++)
        {
            if (gTags[i] == tag)
            {
                index = i;
                break;
            }
        }

        if (index != -1)
        {
            gCounts[index] = gCounts[index] + 1;
        }
    }

    reader.close();

    ofstream outFile(outputFileName.c_str());
    if (!outFile)
    {
        cout << "Could not open " << outputFileName << endl;
        return 1;
    }

    printBarChart(outFile);

    outFile.close();

    cout << endl;
    cout << reader << endl;

    return 0;
}

void printBarChart(ofstream &outFile)
{
    int maxCount = 0;
    for (int i = 0; i < gNumTags; i++)
    {
        if (gCounts[i] > maxCount)
        {
            maxCount = gCounts[i];
        }
    }

    cout << "Tag Frequency Chart" << endl;
    outFile << "Tag Frequency Chart" << endl;

    for (int i = 0; i < gNumTags; i++)
    {
        if (gTags[i] == "")
        {
            continue;
        }

        int percent = 0;
        if (gTotalLines > 0)
        {
            percent = gCounts[i] * 100 / gTotalLines;
        }

        int barLength = 0;
        if (maxCount > 0 && gCounts[i] > 0)
        {
            barLength = (gCounts[i] * 10 + maxCount / 2) / maxCount;
            if (barLength < 1)
            {
                barLength = 1;
            }
        }

        string bar = "";
        for (int j = 0; j < barLength; j++)
        {
            bar = bar + "=";
        }

        cout << gTags[i] << " " << bar << " " << gCounts[i] << " (" << percent << "%)" << endl;
        outFile << gTags[i] << " " << bar << " " << gCounts[i] << " (" << percent << "%)" << endl;
    }
}

ostream &operator<<(ostream &out, const LogReader &)
{
    out << "Log summary for file: " << gLogFileName << endl;
    out << "Total lines: " << gTotalLines << endl;

    string tagsCopy[MAX_TAGS];
    int countsCopy[MAX_TAGS];

    for (int i = 0; i < gNumTags; i++)
    {
        tagsCopy[i] = gTags[i];
        countsCopy[i] = gCounts[i];
    }

    int maxCount = 0;
    for (int i = 0; i < gNumTags; i++)
    {
        if (countsCopy[i] > maxCount)
        {
            maxCount = countsCopy[i];
        }
    }

    for (int i = 0; i < gNumTags - 1; i++)
    {
        for (int j = i + 1; j < gNumTags; j++)
        {
            if (countsCopy[j] > countsCopy[i])
            {
                int tempCount = countsCopy[i];
                countsCopy[i] = countsCopy[j];
                countsCopy[j] = tempCount;

                string tempTag = tagsCopy[i];
                tagsCopy[i] = tagsCopy[j];
                tagsCopy[j] = tempTag;
            }
            else if (countsCopy[j] == countsCopy[i] && tagsCopy[j] < tagsCopy[i])
            {
                string tempTag = tagsCopy[i];
                tagsCopy[i] = tagsCopy[j];
                tagsCopy[j] = tempTag;
            }
        }
    }

    out << "Sorted tag chart" << endl;

    for (int i = 0; i < gNumTags; i++)
    {
        if (tagsCopy[i] == "")
        {
            continue;
        }

        int percent = 0;
        if (gTotalLines > 0)
        {
            percent = countsCopy[i] * 100 / gTotalLines;
        }

        int barLength = 0;
        if (maxCount > 0 && countsCopy[i] > 0)
        {
            barLength = (countsCopy[i] * 10 + maxCount / 2) / maxCount;
            if (barLength < 1)
            {
                barLength = 1;
            }
        }

        string bar = "";
        for (int k = 0; k < barLength; k++)
        {
            bar = bar + "=";
        }

        out << tagsCopy[i] << " " << bar << " " << countsCopy[i] << " (" << percent << "%)" << endl;
    }

    return out;
}
