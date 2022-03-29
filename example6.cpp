#include <cstdio>
#include <memory>
#include <string>

using ShoppingList = std::shared_ptr<std::FILE>;

void close_file(std::FILE* f)
{
    std::fclose(f);
}

ShoppingList makeFile(const char* filename, const char* flags)
{
    ShoppingList file(std::fopen(filename, flags), close_file);

    return file;
}

class Partner
{
public:
    void addToFile(std::string element)
    {
        std::fprintf(shoppingList.get(), "%s\n", element.c_str());
    }
    ShoppingList shoppingList;
};

int main()
{
    Partner boy{};
    boy.shoppingList = makeFile("ShoppingList", "wb");

    Partner girl{};
    girl.shoppingList = boy.shoppingList;
    girl.addToFile("Butter");
    girl.addToFile("Milk");
}
