#include "xmlproc.h"

void saveXMLFile(TiXmlNode* pRoot , std::string filename) {
    TiXmlDocument doc;
    TiXmlDeclaration* decl = new TiXmlDeclaration("1.0" , "" , "");
    doc.LinkEndChild(decl);
    doc.LinkEndChild(pRoot);
    bool result = doc.SaveFile(filename.c_str());
    if(!result)
        throw XMLException("can't save root into file " + filename);
}

void loadXMLFile(TiXmlNode*& pRoot , std::string filename) {
    TiXmlDocument doc(filename.c_str());
    if(!doc.LoadFile())
        throw XMLException("can't load file " + filename);

    TiXmlHandle hDoc(&doc);
    TiXmlElement* pElem = hDoc.FirstChildElement().Element();
    if(!pElem)
        throw XMLException("can't load file " + filename);

    pRoot = pElem->Clone();
}

std::string getXMLElementValue(TiXmlNode*& pRoot , std::string path) {
    TiXmlNode* pNode = getXMLElement(pRoot , path);
    if(pNode == NULL) {
        return "";
    }
    if(path.find('@') == path.npos) {
        // getting text node
        const char* text = pNode->ToElement()->GetText();
        return text != NULL ? std::string(text) : "";
    } else {
        // getting attribute
        std::string attrName = path.substr(path.find('@') + 1 , path.length() - path.find('@') - 1).c_str();
        const char* attrValue = pNode->ToElement()->Attribute(attrName.c_str());
        if(attrValue == NULL) {
            return "";
        }
        return std::string(attrValue);
    }
    return "";
}

void setXMLElementValue(TiXmlNode*& pRoot , std::string path , const std::string& value) {
    TiXmlNode* pNode = getXMLElement(pRoot , path);
    if(pNode == NULL)
        throw XMLException("can't set value to node " + path);

    if(path.find('@') == path.npos) {
        // setting text node
        TiXmlText* pText = pNode->FirstChild()->ToText();
        if(pText == NULL)
            throw XMLException("can't set value to attribute " + path);

        pText->SetValue(value.c_str());
    } else {
        // setting attribute
        pNode->ToElement()->SetAttribute(path.substr(path.find('@') + 1 , path.length() - path.find('@') - 1).c_str() , value.c_str());
    }
}

TiXmlNode* getXMLElement(TiXmlNode* pRoot , std::string path) {
    TiXmlHandle handle(pRoot);
    path = path.substr(0 , path.rfind("@"));
    if(!path.empty() && path.find_last_of('/') == path.length() - 1) {
        path.erase(--path.end());
    }
    if(!path.empty()) {
        std::istringstream xpath(path);
        std::string nodeValue;
        while(!xpath.eof()) {
            getline(xpath , nodeValue , '/');
            handle = handle.FirstChild(nodeValue.c_str());
        }
    }
    return handle.Node();
}


TiXmlNode * getXMLChildNodeWithAttValue(TiXmlNode * pParent,
                                       std::string attName, std::string value) {
    if(!pParent || !pParent->FirstChild())
        return NULL;

    const char * attValue;
    TiXmlElement * childEl = NULL;

    for(TiXmlNode * childNode = pParent->FirstChild() ;
            childNode ; childNode = childNode->NextSibling()) {
        childEl = childNode->ToElement();
        attValue = childEl->Attribute(attName.c_str());
        if(!attValue || strlen(attValue) < 1)
            throw XMLException("child element doesn't have attribute: " + attName);

        if(value == attValue)
            return childNode;
    }
    return NULL;
}
