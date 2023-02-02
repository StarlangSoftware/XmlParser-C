For Developers
============
You can also see [C++](https://github.com/starlangsoftware/XmlParser-CPP), 
[Java](https://github.com/starlangsoftware/XmlParser), or [Js](https://github.com/starlangsoftware/XmlParser-Js) repository.

## Requirements

* [C Compiler](#cpp)
* [Git](#git)


### CPP
To check if you have compatible C Compiler installed,
* Open CLion IDE 
* Preferences >Build,Execution,Deployment > Toolchain  

### Git

Install the [latest version of Git](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git).

## Download Code

In order to work on code, create a fork from GitHub page. 
Use Git for cloning the code to your local or below line for Ubuntu:

	git clone <your-fork-git-link>

A directory called XmlParser-C will be created. Or you can use below link for exploring the code:

	git clone https://github.com/starlangsoftware/XmlParser-C.git

## Open project with CLion IDE

To import projects from Git with version control:

* Open CLion IDE , select Get From Version Control.

* In the Import window, click URL tab and paste github URL.

* Click open as Project.

Result: The imported project is listed in the Project Explorer view and files are loaded.


## Compile

**From IDE**

After being done with the downloading and opening project, select **Build Project** option from **Build** menu.

Detailed Description
============

In order to load an xml document, we use the constructor

    Xml_document_ptr doc = create_xml_document(fileName);
    
and parse with the parse method

    parse(doc);
    
Root node of the document can be obtained via the getFirstChild method:

    rootNode = doc->root;
  
For example, to iterate over the first level tags in the xml file one can use

    Xml_element_ptr rootNode = doc->root;
    Xml_element_ptr childNode = rootNode->first_child;
    while (childNode != NULL){
      ...
      childNode = childNode->next_sibling;
    }

Tag name can be obtained via getName, pcData via getPcData methods.
