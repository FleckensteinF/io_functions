#ifndef _TOOLS_IO_FUNCTIONS_H_
#define _TOOLS_IO_FUNCTIONS_H_

#include <vector>
#include <map>
#include <string>
#include <boost/filesystem.hpp> 
#include <Eigen/Geometry>

// TODO: reimplement with getLine
// TODO: use specific type string for from string

namespace Tools{
  namespace IOFunctions{

    /*
     * converts any type form and to std::string
     */
    template<class T> std::string toString(const T& t);
    template<class T> T fromString(const std::string& s);

    /*
     * converts vector<float> to eigen matrix
     */
    template <class EigenMatrix> 
      EigenMatrix fromVector(const std::vector<float>& input, const std::string& name);

    /*
     * converts eigen matrix to vector<float>
     */
    template <class EigenMatrix> 
      void toVector(std::vector<float>& output, const EigenMatrix& input);

    /*
     * inserts eigen matrix into vector<float>
     * make sure, there is enough storage allocated to insert eigen matrix!
     */
    template <class EigenMatrix> 
      void toVector(std::vector<float>::iterator insertAt, const EigenMatrix& input);

    /*
     * basic io functions to write data into files
     * and read data from files using different container structures
     */
    template<class T> bool writeToFile(const std::string& filepath, const std::vector<T>& input, const char& separator, const std::string& infoLine="");
    template<class T> bool writeToFile(const std::string& filepath, const std::vector<std::vector<T> >& input, const char& separator, const std::string& infoLine="");
    template<class T> bool writeToFile(const std::string& filepath, const std::vector<std::pair<std::string, std::vector<T> > >& input, const char& separator, const std::string& infoLine="");
    template<class T> bool writeToFile(const std::string& filepath, const std::map<std::string, std::vector<T> >& input, const char& separator, const std::string& infoLine="");

    template<class T> bool readFromFile(const std::string& filepath, std::vector<T>& result, const char& separator, std::string* infoLine=NULL);
    template<class T> bool readFromFile(const std::string& filepath, std::vector<std::vector<T> >& result, const char& separator, std::string* infoLine=NULL);
    template<class T> bool readFromFile(const std::string& filepath, std::vector<std::pair<std::string,std::vector<T> > >& result, const char& separator, std::string* infoLine=NULL);
    template<class T> bool readFromFile(const std::string& filepath, std::map<std::string,std::vector<T> >& result, const char& separator, std::string* infoLine=NULL);

    /*
     * basic functions dealing with file paths
     */

    // true, if input string ends with the character sequence ending
    bool endsWith(const std::string& input, const std::string& ending);

    // returns the string after the last '.'
    std::string fileSuffix(const std::string& path);

    // returns the string after the last '/' and before the last '.'
    std::string fileName(const std::string& filePath);

    // returns everything in front of the last '/'
    std::string containingFolderPathOf(const std::string& filePath);

    // returns the name of the folder 
    // in which the file at filePath is located
    std::string containingFolderOf(const std::string& filePath);

    // returns the filePath with an additional '/' at the end if there is none
    std::string addTrailingSlash(const std::string& filePath);

    // load paths to  all files in directory 
    bool loadFilePathsFromDirectory(const std::string& directory, std::vector<std::string>& filePaths);

    // load paths to  all paths in directory 
    bool loadPathsFromDirectory(const std::string& directory, std::vector<std::string>& paths);

    // loads directory with name directory
    // returns true, if an error occured
    // returns false otherwise
    bool loadDirectory(const std::string& directory, boost::filesystem::path& directoryPath);

    // creates the directory if not already existent
    void loadMakeDirectory(const std::string& directory, boost::filesystem::path& directoryPath);
    void loadMakeDirectory(const std::string& directory);

    // move file from old file path to new file path
    void moveFile(const std::string& oldFilepath, const std::string& newFilepath);

    // splits the string at every occurence of del, removing del
    std::vector<std::string> stringSplit(const std::string& str, const std::string& del);
    
    // compares to strings by only looking at their file names
    bool fileNameCompare(const std::string& string1, const std::string& string2);

    // adding unary predicate class for filename compare
    struct FilenameCompare : public std::unary_function<std::string, bool>{
      std::string referenceValue;
      FilenameCompare(const std::string& referenceValue);
      bool operator() (const std::string &arg);      
    };
  };
};


#include "io_functions.hpp"
#endif // _TOOLS_IO_FUNCTIONS_H_
