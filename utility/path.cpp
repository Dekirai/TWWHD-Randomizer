#include "utility/path.hpp"

#include <version.hpp>
#include <utility/file.hpp>

#if defined(QT_GUI)
    #if defined(__APPLE__)
        #include <QStandardPaths>
    #else
        #include <QCoreApplication>
    #endif
#endif

namespace Utility {
    fspath get_data_path() {
        #if defined(QT_GUI)
            #if defined(EMBED_DATA)
                return ":/";
            #else
                return QString(QCoreApplication::applicationDirPath() + "/data/").toStdString().c_str();
            #endif
        #elif defined(DEVKITPRO)
            return "/vol/content/";
        #elif defined(APPLE)
            return "../../../data/";
        #else
            return "./data/";
        #endif
    }

    fspath get_app_save_path() {
        fspath path;
        #if defined(__APPLE__) && defined(QT_GUI)
            path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation).toStdU32String();
        #elif defined(QT_GUI)
            path = QCoreApplication::applicationDirPath().toStdU32String();
        #elif defined(DEVKITPRO)
            return "/vol/save/";
        #else
            return "./";
        #endif
        
        if (!std::filesystem::is_directory(path))
        {
            Utility::create_directories(path);
        }

        return path;
    }

    fspath get_logs_path() {
        const fspath path = get_app_save_path() / "logs/";

        if (!std::filesystem::is_directory(path))
        {
            Utility::create_directories(path);
        }

        return path;
    }

    fspath get_temp_dir() {
        // could get the OS-provided temp folder with Qt but it might be harder to find and debug should we use it for anything
        const fspath path = get_app_save_path() / "temp/";

        if (!std::filesystem::is_directory(path))
        {
            Utility::create_directories(path);
        }

        return path;
    }
}
