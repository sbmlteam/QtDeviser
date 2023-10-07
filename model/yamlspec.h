#ifndef YAMLSPEC_H
#define YAMLSPEC_H
#include <vector>
#include <iostream>
#include <yaml-cpp\yaml.h>

using namespace std;

typedef pair<string, string> idPair;
typedef vector<idPair> idTypePairs;

// utility class
class YamlUtils
{
public:

  // get the child node with the given name
  static YAML::Node getChildNode(YAML::Node node, const std::string& name);

  // takes a pointer to a pair of nodes, where first is a name and second is a map
  static void addIdTypePairs(YAML::const_iterator it, idTypePairs& values);

  // gets the value of the type node from a map
  static std::string getTypeFromNode(YAML::Node node);

  // gets the name value from the nth idTypePairs
  static const std::string getNameValue(idTypePairs pairs, unsigned int n);

  // gets the type value from the nth idTypePairs
  static const std::string getTypeValue(idTypePairs pairs, unsigned int n);

  // prints the values of an idTypePairs: for debugging
  static void printAtts(idTypePairs att);

};

class YamlClass
{
public:
  // class to represent the values of fields necessary to describe a class in deviser
  YamlClass();
  
  // construct a class using the name
  YamlClass(const std::string& name);

  YamlClass(const YamlClass& rhs);

  YamlClass& operator=(const YamlClass& rhs);

  // print values from the class: mainly for debugging
  void print();

  // add the names and values as idTypePairs from the node 
  // that come under the heading 'allowed_parameters'
  void addAttributes(YAML::Node node);

  // add the names and values as idTypePairs from the node 
  // that come under the heading 'allowed_children'
  void addChildren(YAML::Node node);

  // return the name of the deviser class
  const std::string& getName();

  // get the name of the nth attribute
  const std::string getAttributeName(unsigned int n);

  // get the type of the nth attribute
  const std::string getAttributeType(unsigned int n);

  // get the name of the nth child class
  const std::string getChildClassName(unsigned int n);

  // get the type of the nth child class
  const std::string getChildClassType(unsigned int n);

  // return the set off type pairs
  idTypePairs getChildClasses();

  // return the number of child classes
  unsigned int getNumChildClasses();

  // return the nth child class
  idPair getChildClass(unsigned int n);

  // return the set off type pairs
  idTypePairs getAttributes();

  // return the number of child classes
  unsigned int getNumAttributes();

  // return the nth child class
  idPair getAttribute(unsigned int n);

private:
  std::string mName;
  idTypePairs mAttributes;
  idTypePairs mChildren;
};

class YamlSpec
{
public:
 //  YamlSpec();
  // class to parse a filename
  // and contain details of the whole specification
  YamlSpec(std::string filename);

  // parse the specification into a YamlClass instance representing the top level
  // and a vector of YamlClass instances representing the other deviser classes
  void parse();

//  void parse(const std::string& filename);

  // print the values of the specification: mainly for debugging
  void print();

  // return a pointer to the top level class
  YamlClass* getTopLevel();

  // return the vector of child classes
  std::vector<YamlClass*> getChildClasses();

  // return the number of child classes
  unsigned int getNumChildClasses();

  // return the nth child class
  YamlClass* getChildClass(unsigned int n);

  std::string getFilename();

private:
  std::string mFilename;
  std::vector<YamlClass*> mChildClasses;
  YamlClass *mTopLevel;
};

#endif // YAMLSPEC_H