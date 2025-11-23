/**
 * LogReader Interface for the Assignment
 * Do not modify the class definition, but you may add other helper functions outside the class
 */

#ifndef LOGREADER_H
#define LOGREADER_H

/**
 * LogReader class. Provides mechanisms to read a log file and return
 * lower-case versions of tag tokens from that file.
 *
 * A tag is defined as the token immediately following the literal "#tag:"
 * up to the next whitespace or end of line.
 */

#include <string>
#include <fstream>

using namespace std;

class LogReader
{
  public:

    /**
     * Constructor. Opens the file with the given filename and associates it
     * with the logFile stream.
     * Initializes the other members.
     * Prints an error message then terminates the program if the file cannot be opened.
     * Must not perform any other processing.
     * @param filename - a C string naming the file to read.
     */
     LogReader(const char *filename);

    /**
     * Closes the file.
     */
     void close();

    /**
     * Returns a string, being the next tag in the file (converted to lower case).
     * Returns an empty string if the next tag contains no letters or if no tag is present.
     * Uses a one-word lookahead on lines.
     * @return - string - next tag token.
     */
     string getNextTag();

    /**
     * Returns true if there is a further tag-bearing line in the file, false if we have reached the
     * end of file (based on the lookahead).
     * @return - bool - !eof
     */
     bool isNextTag();

  private:
     ifstream logFile;
     string nextLine;
     bool eofFound;

     /**
      * Helper function to extract the tag token from a line.
      * A tag is the token immediately following "#tag:" up to whitespace or EOL.
      * If the line has no "#tag:", should return an empty string.
      * @param line - the line from which to extract the tag.
      * @return - string - the extracted tag token (case not normalised here).
      */
     static string extractTag(string line);
};

#endif
