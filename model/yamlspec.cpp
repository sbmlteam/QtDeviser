#include "yamlspec.h"
#include <fstream>


/***************************************************************
 *         YamlUtils class
***************************************************************/

std::string
YamlUtils::getTypeFromNode(YAML::Node node)
{
  YAML::Node type_node = YamlUtils::getChildNode(node, "type");
  if (type_node.Type() != 2)
  {
    return "";
  }
  std::string type = type_node.as<std::string>();
  return type;
}

const std::string
YamlUtils::getNameValue(idTypePairs pairs, unsigned int n)
{
  return pairs.at(n).first;
}

const std::string
YamlUtils::getTypeValue(idTypePairs pairs, unsigned int n)
{
  return pairs.at(n).second;
}

void
YamlUtils::addIdTypePairs(YAML::const_iterator it, idTypePairs& values)
{
  std::string name = it->first.as<std::string>();
  if (name == "description" || name == "definition")
  {
    return;
  }
  std::string type = YamlUtils::getTypeFromNode(it->second);
  values.push_back(std::make_pair(name, type));
}

YAML::Node
YamlUtils::getChildNode(YAML::Node node, const std::string& name)
{
  for (YAML::const_iterator it = node.begin(); it != node.end(); ++it)
  {
    unsigned int t1 = it->first.Type();
    if (t1 == 2)
    {
      // we are at the node 'name'
      if (it->first.as<std::string>() == name)
      {
        return it->second;
      }
    }
  }
  return YAML::Node(YAML::NodeType::Undefined);
}

void
YamlUtils::printAtts(idTypePairs att)
{
  for (unsigned int i = 0; i < att.size(); ++i)
  {
    cout << i << " : name: " << att.at(i).first << " type: " << att.at(i).second << endl;
  }
}



/***************************************************************
*         YamlClass class
***************************************************************/

YamlClass::YamlClass() :
  mName(""),
  mAttributes(NULL),
  mChildren(NULL)
{
}

YamlClass::YamlClass(const std::string& name) :
  mName(name),
  mAttributes(NULL),
  mChildren(NULL)
{
}

YamlClass::YamlClass(const YamlClass& rhs)
{
  mName = rhs.mName;
  mAttributes = rhs.mAttributes;
  mChildren = rhs.mChildren;

}

YamlClass & 
YamlClass::operator=(const YamlClass& rhs)
{
  if (&rhs == this)
    return *this;

  mName = rhs.mName;
  mAttributes = rhs.mAttributes;
  mChildren = rhs.mChildren;

  return *this;
}


void 
YamlClass::print() 
{
  cout << "class name: " << mName << endl;
  cout << "attributes: " << endl;
  YamlUtils::printAtts(mAttributes);
  cout << "children:" << endl;
  YamlUtils::printAtts(mChildren);
}

void 
YamlClass::addAttributes(YAML::Node node)
{
  YAML::Node name_node = YamlUtils::getChildNode(node, "allowed_parameters");
  for (YAML::const_iterator it = name_node.begin(); it != name_node.end(); ++it)
  {
    YamlUtils::addIdTypePairs(it, mAttributes);
  }
}
  
void 
YamlClass::addChildren(YAML::Node node)
{
  YAML::Node name_node = YamlUtils::getChildNode(node, "allowed_children");
  for (YAML::const_iterator it = name_node.begin(); it != name_node.end(); ++it)
  {
    YamlUtils::addIdTypePairs(it, mChildren);
  }
}

const std::string&
YamlClass::getName()
{
  return mName;
}

const std::string
YamlClass::getAttributeName(unsigned int n)
{
  return YamlUtils::getNameValue(mAttributes, n);
}

const std::string
YamlClass::getAttributeType(unsigned int n)
{
  return YamlUtils::getTypeValue(mAttributes, n);
}

const std::string
YamlClass::getChildClassName(unsigned int n)
{
  return YamlUtils::getNameValue(mChildren, n);
}

const std::string
YamlClass::getChildClassType(unsigned int n)
{
  return YamlUtils::getTypeValue(mChildren, n);
}

idTypePairs 
YamlClass::getChildClasses()
{
  return mChildren;
}


unsigned int 
YamlClass::getNumChildClasses()
{
  return mChildren.size();
}

idPair 
YamlClass::getChildClass(unsigned int n)
{
  return mChildren.at(n);
}

idTypePairs
YamlClass::getAttributes()
{
  return mAttributes;
}


unsigned int
YamlClass::getNumAttributes()
{
  return mAttributes.size();
}

idPair
YamlClass::getAttribute(unsigned int n)
{
  return mAttributes.at(n);
}


/***************************************************************
*         YamlSpec class
***************************************************************/
////YamlSpec::YamlSpec() :
////  mTopLevel(NULL),
////  mChildClasses(NULL)
////{
////  mFilename = "C:\\Development\\SBML\\test.yaml";
////}



YamlSpec::YamlSpec(std::string filename) :
  mTopLevel(NULL),
  mChildClasses(NULL)
{
  mFilename = filename;
}

void 
YamlSpec::parse() 
{
  std::ifstream fin;
  fin.open(mFilename);
  YAML::Node doc = YAML::Load(fin);
  bool first = true;
  for (YAML::const_iterator it = doc.begin(); it != doc.end(); ++it)
  {
    if (first)
    {
      mTopLevel =  new YamlClass(it->first.as<string>());
      mTopLevel->addAttributes(it->second);
      mTopLevel->addChildren(it->second);
      first = false;
    }
    else
    {
      YamlClass *yc = new YamlClass(it->first.as<string>());
      yc->addAttributes(it->second);
      yc->addChildren(it->second);
      mChildClasses.push_back(yc);
    }
  }
}

//void
//YamlSpec::parse(const std::string& filename)
//{
//  std::ifstream fin;
//  fin.open(filename);
//  YAML::Node doc = YAML::Load(fin);
//  bool first = true;
//  for (YAML::const_iterator it = doc.begin(); it != doc.end(); ++it)
//  {
//    if (first)
//    {
//      mTopLevel = new YamlClass(it->first.as<string>());
//      mTopLevel->addAttributes(it->second);
//      mTopLevel->addChildren(it->second);
//      first = false;
//    }
//    else
//    {
//      YamlClass *yc = new YamlClass(it->first.as<string>());
//      yc->addAttributes(it->second);
//      yc->addChildren(it->second);
//      mChildClasses.push_back(yc);
//    }
//  }
//}

void 
YamlSpec::print()
{
  mTopLevel->print();
  cout << "*******\n";
  for (unsigned int n = 0; n < mChildClasses.size(); ++n)
  {
    mChildClasses.at(n)->print();
    cout << "*******\n";
  }
}

YamlClass *
YamlSpec::getTopLevel()
{
 return mTopLevel;
}

std::vector<YamlClass*> 
YamlSpec::getChildClasses()
{
  return mChildClasses;
}

unsigned int
YamlSpec::getNumChildClasses()
{
  return mChildClasses.size();
}

YamlClass*
YamlSpec::getChildClass(unsigned int n)
{
  return mChildClasses.at(n);
}

std::string 
YamlSpec::getFilename()
{
  return mFilename;
}




