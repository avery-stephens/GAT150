#include "json.h"
#include "rapidjson/istreamwrapper.h"
#include "Core/Logger.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Math/Rect.h"
#include <fstream>

namespace gooblegorb::json
{
    bool gooblegorb::json::Load(const std::string& filename, rapidjson::Document& document)
    {
        // !! create a std::ifstream object called stream 
        // !! check if it is open, if not use LOG to print !! ERROR !! and return false 
        // !! https://riptutorial.com/cplusplus/example/1625/opening-a-file 

        std::ifstream stream(filename);
        if (stream.is_open() == false) 
        {
            LOG("!! ERROR !! opening file %s", filename.c_str());
            return false;
        }

        rapidjson::IStreamWrapper istream(stream);
        document.ParseStream(istream);
        if (document.IsObject() == false)
        {
            LOG("json file cannot be read %s.", filename.c_str());
            return false;
        }

        return true;
    }

    bool Get(const rapidjson::Value& value, const std::string& name, int& data)
    {
        // check if 'name' member exists and is of type 

        if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsInt() == false)
        {
            LOG("!! ERROR !! reading json data %s", name.c_str());
            return false;
        }

        // set data 
        data = value[name.c_str()].GetInt();

        return true;
    }

    bool Get(const rapidjson::Value& value, const std::string& name, float& data)
    {
        if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsNumber() == false)
        {
            LOG("!! ERROR !! reading json data %s", name.c_str());
            return false;
        }

        // set data 
        data = value[name.c_str()].GetFloat();

        return true;
    }

    bool Get(const rapidjson::Value& value, const std::string& name, bool& data)
    {
        if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsBool() == false)
        {
            LOG("!! ERROR !! reading json data %s", name.c_str());
            return false;
        }

        // set data 
        data = value[name.c_str()].GetBool();

        return true;
    }

    bool Get(const rapidjson::Value& value, const std::string& name, std::string& data)
    {
        if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsString() == false)
        {
            LOG("!! ERROR !! reading json data %s", name.c_str());
            return false;
        }

        // set data 
        data = value[name.c_str()].GetString();

        return true;
    }

    bool Get(const rapidjson::Value& value, const std::string& name, Vector2& data)
    {
        // check if 'name' member exists and is an array with 2 elements 
        if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsArray() == false || value[name.c_str()].Size() != 2)
        {
            LOG("!! ERROR !! reading json data %s", name.c_str());
            return false;

        }

        // create json array object 
        auto& array = value[name.c_str()];
        // get array values 
        for (rapidjson::SizeType i = 0; i < array.Size(); i++)
        {
            if (!array[i].IsNumber())
            {

                LOG("!! ERROR !! reading json data (not a float) %s", name.c_str());
                return false;
            }

            data[i] = array[i].GetFloat();
        }

        return true;
    }

    bool Get(const rapidjson::Value& value, const std::string& name, Color& data)
    {
        // check if 'name' member exists and is an array with 2 elements 
        if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsArray() == false || value[name.c_str()].Size() != 4)
        {
            LOG("!! ERROR !! reading json data %s", name.c_str());
            return false;

        }

        // create json array object 
        auto& array = value[name.c_str()];
        // get array values 
        for (rapidjson::SizeType i = 0; i < array.Size(); i++)
        {
            if (!array[i].IsInt())
            {

                LOG("!! ERROR !! reading json data (not a float) %s", name.c_str());
                return false;
            }

            data[i] = array[i].GetInt();
        }

        return true;
    }

    //[0,0,32,32]

    bool Get(const rapidjson::Value& value, const std::string& name, Rect& data)
    {
        // check if 'name' member exists and is an array with 2 elements 
        if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsArray() == false || value[name.c_str()].Size() != 4)
        {
            LOG("!! ERROR !! reading json data %s", name.c_str());
            return false;

        }
        // create json array object 
        auto& array = value[name.c_str()];

        //array values?
        data.x = array[0].GetInt();
        data.y = array[0].GetInt();
        data.w = array[0].GetInt();
        data.h = array[0].GetInt();

        return true;
    }
}
