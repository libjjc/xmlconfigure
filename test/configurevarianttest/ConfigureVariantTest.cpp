#include "ConfigureVariantTest.h"

TEST(ConfigureVariantTest, valuetest){
    xc::configure_variant var;

    var = 2;    
    EXPECT_EQ(var.value<int>(), 2);

    int nvalue = var;
    EXPECT_EQ(nvalue, 2);

    std::string str = var.to_string();
    EXPECT_STREQ(str.c_str(), "2");

    xc::configure_variant var1(55.6f);
    float fvalue = var1;
    EXPECT_FLOAT_EQ(fvalue , 55.6f);

    double d_value = 76.435654634532456576;
    var = d_value;
    EXPECT_DOUBLE_EQ(d_value, var.value<double>());

    unsigned int u_value = (unsigned int)-1;
    var = u_value;
    EXPECT_EQ(u_value, var.value<unsigned int>());

    bool b_value = true;
    var = b_value;
    EXPECT_EQ(b_value, var.value<bool>());

    b_value = false;
    var = b_value;
    EXPECT_EQ(b_value, var.value<bool>());

    std::string svalue = "aaaaaaaaabbbbbbbbbbccccccccccddddddddddeeeeeeeeeeffffffffff";
    var = svalue;
    std::string s = var;
    EXPECT_STREQ(s.c_str(), svalue.c_str());
}


TEST(ConfigureNodeTest, ContainerTest){

    xc::configure_node cn("test");

    cn.field<xc::C>("child");
    std::string name = cn.field<xc::G>("child").name();

    EXPECT_STREQ(name.c_str(), "child");
    xc::configure_node& node = cn.field<xc::G>("child");
    xc::configure_variant& var = node.attr<xc::C>("name");
    var = "fuck you!!";
    xc::configure_variant& var1 = node.attr<xc::G>("name");

    EXPECT_STREQ("fuck you!!", var1.to_string().c_str());
    EXPECT_STREQ("fuck you!!", cn.field<xc::G>("child").attr<xc::G>("name").to_string().c_str());
    cn.field<xc::G>("child").attr<xc::C>("name") = "value";
    //std::string attr = cn.field<xc::G>("child")["name"];
    //EXPECT_STREQ(attr.c_str(), "value");
}

TEST(XmlConfiguration, ReadTest){
    xc::configure xmlreader;
    xmlreader.read("D:/1.xml");
	xmlreader.save("D:/2.xml");
    EXPECT_EQ(xmlreader.field<>("first").attr<int>("first_attribute"),1);
    EXPECT_STREQ(xmlreader.field<>("second").attr<std::string>("first_attribute").c_str(), "futao");
    EXPECT_EQ(xmlreader.field<>("third").attr<bool>("first_attribute"), true);
    EXPECT_DOUBLE_EQ(xmlreader.field<>("fifth").attr<double>("first_attribute"), 34.65);
	xc::configure_node cn = xmlreader("sixth");
	double v = cn["first_attribute"].cast<double>();
	std::cout << v << std::endl;
	EXPECT_DOUBLE_EQ(xmlreader("sixth")["first_attribute"].cast<double>(), 34.234);
	//EXPECT_DOUBLE_EQ(xmlreader("fouth.sub")["sub_attr"].cast<double>(), 567435.2346);
}

using namespace xc;
TEST(XmlConfiguration, WriteReaderTest){
    configure writer("root");
    writer.field<C>("colors").attr<const char*>("name", "red").attr<std::string>("rgba", "0xFF000000").attr<float>("fred", 1.f).attr<float>("fgreen", 0.f).attr<float>("fblue", 0.f).attr<bool>("like",false);
    writer("colors",0).field<C>("sub field").attr<const char*>("name", "green").attr<std::string>("rgba", "0x00FF0000").attr<float>("fred", 0.f).attr<float>("fgreen", 0.f).attr<float>("fblue", 0.f).attr<bool>("like",true);
    writer.field<C>("colors").attr<const char*>("name", "blue").attr<std::string>("rgba"    , "0xFF000000").attr<float>("fred", 1.f).attr<float>("fgreen", 0.f).attr<float>("fblue", 0.f).attr<bool>("like",false);
    writer.field<C>("colors").attr<const char*>("name", "color1").attr<std::string>("rgba"  , "0xFF000000").attr<float>("fred", 1.f).attr<float>("fgreen", 0.f).attr<float>("fblue", 0.f).attr<bool>("like",true);
    writer.field<C>("colors").attr<const char*>("name", "color2").attr<std::string>("rgba"  , "0xFF000000").attr<float>("fred", 1.f).attr<float>("fgreen", 0.f).attr<float>("fblue", 0.f).attr<bool>("like",true);
    writer.field<C>("colors").attr<const char*>("name", "color3").attr<std::string>("rgba"  , "0xFF000000").attr<float>("fred", 1.f).attr<float>("fgreen", 0.f).attr<float>("fblue", 0.f).attr<bool>("like",false);
    writer.field<C>("colors").attr<const char*>("name", "color4").attr<std::string>("rgba"  , "0xFF000000").attr<float>("fred", 1.f).attr<float>("fgreen", 0.f).attr<float>("fblue", 0.f).attr<bool>("like",true);
    writer.field<C>("colors").attr<const char*>("name", "color5").attr<std::string>("rgba"  , "0xFF000000").attr<float>("fred", 1.f).attr<float>("fgreen", 0.f).attr<float>("fblue", 0.f).attr<bool>("like",false);
    writer.field<C>("colors").attr<const char*>("name", "color6").attr<std::string>("rgba"  , "0xFF000000").attr<float>("fred", 1.f).attr<float>("fgreen", 0.f).attr<float>("fblue", 0.f).attr<bool>("like",true);
    writer.field<C>("colors").attr<const char*>("name", "color7").attr<std::string>("rgba"  , "0xFF000000").attr<float>("fred", 1.f).attr<float>("fgreen", 0.f).attr<float>("fblue", 0.f).attr<bool>("like",false);
    writer.field<C>("colors").attr<const char*>("name", "color8").attr<std::string>("rgba"  , "0xFF000000").attr<float>("fred", 1.f).attr<float>("fgreen", 0.f).attr<float>("fblue", 0.f).attr<bool>("like",false);
    writer.field<C>("colors").attr<const char*>("name", "color9").attr<std::string>("rgba"  , "0xFF000000").attr<float>("fred", 1.f).attr<float>("fgreen", 0.f).attr<float>("fblue", 0.f).attr<bool>("like",false);
    writer.field<C>("colors").attr<const char*>("name", "color10").attr<std::string>("rgba" , "0xFF000000").attr<float>("fred", 1.f).attr<float>("fgreen", 0.f).attr<float>("fblue", 0.f).attr<bool>("like",true);
    writer.field<C>("colors").attr<const char*>("name", "color11").attr<std::string>("rgba" , "0xFF000000").attr<float>("fred", 1.f).attr<float>("fgreen", 0.f).attr<float>("fblue", 0.f).attr<bool>("like",false);
    writer.field<C>("colors").attr<const char*>("name", "color12").attr<std::string>("rgba" , "0xFF000000").attr<float>("fred", 1.f).attr<float>("fgreen", 0.f).attr<float>("fblue", 0.f).attr<bool>("like",false);
    writer.field<C>("colors").attr<const char*>("name", "color13").attr<std::string>("rgba" , "0xFF000000").attr<float>("fred", 1.f).attr<float>("fgreen", 0.f).attr<float>("fblue", 0.f).attr<bool>("like",true);

    writer.save("D:/left.xml");

    configure reader;
    reader.read("D:/left.xml");
    reader("colors", 9)["name"] = "jvane";
    reader.save("D:/right.xml");
}
