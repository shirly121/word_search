#include <string>
#include <set>
#include <map>
#include <trie_node.hpp>
// <doc_id, pos, seq in the searching words>
typedef std::tuple<int, int, int> SearchWordIdx; 
class TrieIndex {
private:
    TrieNode* root;
public:
    TrieIndex(): root(new TrieNode()) {}
    
    // traverse all docs and build index
    void insert(const std::string& word, const WordLocation& word_loc) {
        TrieNode* p = root;
        for (const char c : word) {
            if (!p->children[c - 'a'])
                p->children[c - 'a'] = new TrieNode();
            p = p->children[c - 'a'];
        }
        (p->word_locations).push_back(word_loc);
    }

    // return all documents containing the word
    std::set<int> search(const std::string& word) const {
        const TrieNode* p = find(word);
        std::set<int> doc_ids;
        if(p) {
            const std::vector<WordLocation>& all_locs = p->word_locations;
            for (auto it = begin (all_locs); it != end (all_locs); ++it) {
                doc_ids.insert(it->doc_id);
            }
        }
        return doc_ids;
    }

    // return all documents containing the group of words
    std::set<int> search(const std::vector<std::string>& words) const {
        std::set<int> doc_ids;
        if(words.empty()) return doc_ids;
        std::map<SearchWordIdx, int> word_idx_map;
        for (int seq = 1; seq < words.size(); ++seq) {
            build_search_word_idx_for_each(seq, words[seq], word_idx_map);
        }
        const TrieNode* p = find(words[0]);
        if(!p) return doc_ids;
        const std::vector<WordLocation>& start_locs = p->word_locations;
        for (auto it = begin (start_locs); it != end (start_locs); ++it) {
            if (words_exist_from_start(*it, words, word_idx_map)) {
                doc_ids.insert(it->doc_id);
            }
        }
        return doc_ids;
    }

private: 
    const TrieNode* find(const std::string& prefix) const {
        const TrieNode* p = root;
        for (const char c : prefix) {
            p = p->children[c - 'a'];
            if (p == nullptr) break;
        }
        return p;
    }
    void build_search_word_idx_for_each(int seq, const std::string& word, std::map<SearchWordIdx, int> word_idx_map) const {
        const TrieNode* p = find(word);
        if(p) {
            const std::vector<WordLocation>& all_locs = p->word_locations;
            for (auto it = begin (all_locs); it != end (all_locs); ++it) {
                SearchWordIdx key = std::make_tuple(it->doc_id, it->pos, seq);
                word_idx_map.insert(std::make_pair(key, 1));
            }
        }
    }
    // check if continous words all exist from the location of the first word
    bool words_exist_from_start(const WordLocation& start_loc, 
        const std::vector<std::string>& words,
        const std::map<SearchWordIdx, int>& word_idx_map) const {
        WordLocation cur(start_loc.doc_id, start_loc.pos);
        int seq = 1;
        for(; seq < words.size(); ++seq) {
            SearchWordIdx key = std::make_tuple(cur.doc_id, ++cur.pos, seq);
            auto found = word_idx_map.find(key);
            if(found == word_idx_map.end()) break;
        }
        return seq >= words.size();
    }
};