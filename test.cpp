#include <iostream>
#include <unordered_set>
#include <vector>
#include <string>

int main() {
    // Test case with an unordered_set inside a vector
    std::vector<std::unordered_set<std::string> > vec;

    std::cout << "Size before push_back: " << vec.size() << std::endl;

    // Adding an unordered_set to the vector
    vec.push_back(std::unordered_set<std::string>());
    std::cout << "Size after push_back: " << vec.size() << std::endl;

    // Testing an insert into the unordered_set
    vec[0].insert("example");
    std::cout << "Inserted 'example' into set. Size: " << vec[0].size() << std::endl;

    return 0;
}
