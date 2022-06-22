//
// Description: Qt json demo source.
//


#include "qt_json.h"

#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <string>

#include <QByteArray>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>


namespace ms::demos {
    void
    MyJson::WriteToFile(
        std::string_view filePath
    )
    {
        std::string strJson = R"({ "name": "Wanglaoji", "age": 101 })";
        auto jsDoc1 = QJsonDocument::fromJson(QByteArray(strJson.c_str()));

        if (jsDoc1.isNull()) {
            throw std::exception("Parse json data from std::string failed!");
        }

        QJsonObject objJson;
        objJson["name"] = "JinLiFang";
        objJson["age"] = "43";

        QJsonArray jsContent;
        jsContent.append(jsDoc1.object());
        jsContent.append(objJson);

        auto jsByte = QJsonDocument(jsContent).toJson();

        auto path = std::filesystem::path(filePath);
        auto exportFile = std::ofstream(path, std::ios_base::trunc | std::ios_base::binary);
        exportFile << jsByte.toStdString();
    }
} // namespace "ms::demos"
