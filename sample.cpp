#include <string>
#include <iostream>
#include "argsParser.h"
using namespace std;


using namespace argsParser;
const char* INPUT_MODEL ="test.model";
const float INPUT_THRESH = 0.5f;
const char* OUTPUT_PATH = "./path";
const int BATCH_SIZE = 1;
const int INPUT_CHANNEL = 3;
const int INPUT_H = 224;
const int INPUT_W = 224;

int main( int argc, char** argv )
{
    parser::ADD_ARG_STRING("input_file",Desc("input file"),DefaultValue(INPUT_MODEL),ValueDesc("file"));
    parser::ADD_ARG_FLOAT("input_thresh",Desc("input thresh value"),DefaultValue(to_string(INPUT_THRESH)));
    parser::ADD_ARG_STRING("output_path",Desc("output file path"),DefaultValue(OUTPUT_PATH),ValueDesc("path"));
    parser::ADD_ARG_INT("N",Desc("batch_size"),DefaultValue(to_string(BATCH_SIZE)));
    parser::ADD_ARG_INT("C",Desc("channel"),DefaultValue(to_string(INPUT_CHANNEL)));
    parser::ADD_ARG_INT("H",Desc("height"),DefaultValue(to_string(INPUT_H)));
    parser::ADD_ARG_INT("W",Desc("width"),DefaultValue(to_string(INPUT_W)));

    if(argc < 2){
        parser::printDesc();
        exit(-1);
    }

    parser::parseArgs(argc,argv);
    std::cout << "input_file:" << parser::getStringValue("input_file") << std::endl;
    std::cout << "input_thresh:" << parser::getFloatValue("input_thresh") << std::endl;
    std::cout << "output_path:" << parser::getStringValue("output_path") << std::endl;

    int n = parser::getIntValue("N");
    int c = parser::getIntValue("C");
    int h = parser::getIntValue("H");
    int w = parser::getIntValue("W");
    std::cout << "<N,C,H,W>:" << n << " " << c << " " << h << " " << w << std::endl;
    return 1;
}