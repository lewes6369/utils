/*************************************************************************
The MIT License(MIT)
Copyright(c) 2017 lewes/Liu Hao lewes6369@gmail.com
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*************************************************************************/

#ifndef __ARGS_PARSER_H_
#define __ARGS_PARSER_H_

//used for main cpp only included once

//#include <unordered_map>
#include <map>
#include <string>
#include <regex>
#include <iomanip>
#include <iostream>

namespace argsParser
{
    using std::string;

    enum class P_DATA_TYPE
    {
        PARSER_BOOL,
        PARSER_INT,
        PARSER_FLOAT,
        PARSER_DOUBLE,
        PARSER_STRING,
        PARSER_ENUM
    };

    struct parserInfo
    {
        string desc;
        string defaultValue;
        string valueDesc;

        P_DATA_TYPE dataType;
        string value;
    };

    typedef string Desc;
    typedef string ValueDesc;
    typedef string DefaultValue;

    class parser
    {

        #define ADD_ARG_FUNCS(DATA_TYPE) \
        static void ADD_ARG_##DATA_TYPE(string name,Desc desc,DefaultValue defaultValue,ValueDesc valueDesc =""){   \
            InnerInitArgs(name,desc,defaultValue,valueDesc,P_DATA_TYPE::PARSER_##DATA_TYPE); \
        }

        public:
        static void InnerInitArgs(string name,Desc desc,DefaultValue defaultValue,ValueDesc valueDesc,P_DATA_TYPE dataType)
        {
            mArgs.emplace(std::make_pair(name, parserInfo{desc,defaultValue,valueDesc, dataType ,defaultValue}));
        }

        ADD_ARG_FUNCS(INT);
        ADD_ARG_FUNCS(FLOAT);
        ADD_ARG_FUNCS(STRING);
        ADD_ARG_FUNCS(BOOL);

        static void printDesc()
        {   
            for (const auto& data :mArgs )
            {
                string name = data.first;
                auto& info = data.second;
                
                if(info.valueDesc.length() > 0)
                    name += "=<" + info.valueDesc + ">"; 

                std::cout << std::left << std::setw(20) << name;
                std::cout << std::setw(2) << "=" << std::setw(2);
                std::cout << std::left << std::setw(100) << info.desc + "(default:" + info.defaultValue + ")";
                std::cout << std::endl;
            }
        }

        static void parseArgs(int argc,char** argv)
        {
            string* str_argvs = new string[argc];
            for(int i = 0;i<argc;++i)
                str_argvs[i] = argv[i];

            std::regex args_regex(R"(--(.+)=(.+))");
            std::smatch matches;
            for (int i = 1;i<argc;++i) {
                if(std::regex_match(str_argvs[i], matches, args_regex) && matches.size() ==3 )
                {   
                    string key = matches[1].str();
                    string value = matches[2].str();
                    if (mArgs.find(key)!=mArgs.end())
                        mArgs[key].value = value;
                    else
                        std::cout << "do not have the param named:" << key << " ";
                }
                else
                    std::cout << "set param wrong ,need \'--{param}={value}\'" << std::endl;
            } 

            if(str_argvs)
                delete [] str_argvs;

#ifdef LOG_ALL_ARGS 
            std::cout << "####### input args####### " << std::endl;
            for (const auto& data :mArgs )
                std::cout << data.first << "=" << data.second.value << "; " ;
            std::cout << std::endl; 
#endif
        }

        static int getIntValue(string name)
        {
            return mArgs.find(name)!=mArgs.end() ? std::stoi( mArgs[name].value) : 0;
        }

        static float getFloatValue(string name)
        {
            return mArgs.find(name)!=mArgs.end() ? std::stof( mArgs[name].value) : 0.0;
        }

        static string getStringValue(string name)
        {
            return mArgs.find(name)!=mArgs.end() ? mArgs[name].value : "";
        }

        static bool getBoolValue(string name)
        {
            return mArgs.find(name)!=mArgs.end() ? std::stoi( mArgs[name].value) != 0 : 0;
        }


    private:
        static std::map<string,parserInfo> mArgs;
    };

    std::map<string,parserInfo> parser::mArgs ;
};


#endif
