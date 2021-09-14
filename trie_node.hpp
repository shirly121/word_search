#include <vector>
#include <word_location.hpp>
struct TrieNode {
    TrieNode(): children(26, nullptr){}
    
    ~TrieNode() {
        for (TrieNode* child : children)
            if (child) delete child;
    }
      
    std::vector<WordLocation> word_locations;
    std::vector<TrieNode*> children;
};