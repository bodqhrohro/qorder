#include "presetfile.h"
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

const Preset Preset::readFromFile(const std::string path)
{
    std::ifstream ifs(path);
    json jf = json::parse(ifs);

    std::vector<Category> categories;
    for (json category : jf["categories"]) {
        categories.push_back(Category(category["shortcut"], category["path"]));
    }
    return Preset(jf["sourceDirectory"], jf["targetDirectory"], categories);
}

void Preset::writeToFile(const std::string path, const Preset& preset)
{
    json jf;
    jf["sourceDirectory"] = preset.sourceDirectory;
    jf["targetDirectory"] = preset.targetDirectory;
    json categories;
    for (Category cat : preset.categories) {
	json category;
	category["shortcut"] = cat.shortcut;
	category["path"] = cat.path;
	categories += category;
    }
    jf["categories"] = categories;

    std::ofstream ofs(path);
    ofs << jf;
    if (!ofs) {
        throw std::runtime_error("Preset write error");
    }
}
