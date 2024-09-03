#include <string>
#include <vector>

class Category
{
    public:
        std::string shortcut;
        std::string path;

        Category(std::string sc, std::string p)
            : shortcut{sc}, path{p} {}
};

class Preset
{
    public:
        std::string sourceDirectory;
        std::string targetDirectory;
        std::vector<Category> categories;

        Preset(std::string sd, std::string td, std::vector<Category> cat)
            : sourceDirectory{sd}, targetDirectory{td}, categories{cat} {}

        static const Preset readFromFile(const std::string path);
        static void writeToFile(const std::string path, const Preset& preset);
};
