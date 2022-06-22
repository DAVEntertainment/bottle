//
// Description: Qt json demo header.
//

#pragma once


#include <string_view>


namespace ms::demos {
    class MyJson final {
    public:
        static
        void
        WriteToFile(
            std::string_view filePath
        );
    }; // class "MyJson"
} // namespace "ms::demos"
