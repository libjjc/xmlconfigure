#include <xmlconfigure.h>


int main(int argc, char** argv){
    
    xc::configure xmlwriter("root");
    xmlwriter.field<xc::C>("first").attr<xc::C>("first_attribute") = 1;
    xmlwriter.field<xc::C>("second").attr<xc::C>("first_attribute") = "xml_configure";
    xmlwriter.field<xc::C>("third").attr<xc::C>("first_attribute") = "true";
    xmlwriter.field<xc::C>("fouth").attr<xc::C>("first_attribute") = false;
    xmlwriter.field<xc::C>("fifth").attr<xc::C>("first_attribute") = 34.65;
    xmlwriter.field<xc::C>("sixth").attr<xc::C>("first_attribute") = 34.234f;
    xmlwriter.field<xc::C>("seventh").attr<xc::C>("first_attribute") = 75u;
    xmlwriter.save("D:/1.xml");

    xc::configure xmlreader;
    xmlreader.read("D:/1.xml");

    return 0;
}

//<root>
//    <first first_attribute="1" />
//</root>