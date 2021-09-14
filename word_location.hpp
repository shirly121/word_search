// word_location.hpp
struct WordLocation {
    WordLocation(): doc_id(0), pos(0) {}
    
    WordLocation(int doc_id, int pos) {
        this->doc_id = doc_id;
        this->pos = pos;
    }

    int doc_id;
    int pos;
};