#include <cassert>

#include <string>
#include <vector>

/**
 * Returns whether text is present in dictionary
 *
 * We could do better with std::string_view
 *
 * @note assumes no duplicate words are present in dictionary.
 */
static inline size_t look_up_dict(const std::vector<std::string>& dictionary, const std::string& text, size_t start, size_t size) {
    for (const auto& word : dictionary) {
        //We need to make sure that range size is equal to word size
        //as compare will compare up to size so you can get partial match as full match
        //Reasoning to use this akward way: to replace std::string_view
        if (size != word.size() || text.compare(start, size, word) != 0) continue;
        else return word.size();
    }

    return std::string::npos;
}

/**
 * Determines whether the text can be broken into words from dictionary
 *
 * Complexity: text.size() * dictionary.size()
 */
bool break_into_words(const std::string& text, const std::vector<std::string>& dictionary) {
    if (dictionary.size() == 0) return false;

    size_t text_len = text.size();

    if (text_len == 0) return true;

    //Collect previous matches.
    //We add std::string::npos which is -1
    std::vector<size_t> matches(1, std::string::npos);

    for (size_t idx = 0; idx < text_len; idx++) {
        bool is_found = false;

        //The loop attempts to check all possible ranges of previous matches starting from the last one
        //If there is no match, then we try full range using std::string::npos.
        //
        //Unsigned overflow is well defined
        //std::string::npos + 1 = 0
        //idx - std::string::npos = idx + 1
        for (size_t m_idx = matches.size() - 1; m_idx != std::string::npos; m_idx--) {
            if (look_up_dict(dictionary, text, matches[m_idx] + 1, idx - matches[m_idx]) != std::string::npos) {
                is_found = true;
                break;
            }
        }

        if (is_found) {
            matches.push_back(idx);
        }
    }

    //if we were able to split using our dictionary fully
    //we're going to have text.size() - 1 as last match
    return matches[matches.size() - 1] == text_len - 1;
}

int main() {
    std::vector<std::string> dictionary{"a", "what", "an", "nice", "day"};

    //Test look-up
    {
        const std::string text = "whatacutie";

        assert(look_up_dict(dictionary, text, 0, 4) == 4);
        assert(look_up_dict(dictionary, text, 1, 4) == std::string::npos);
        assert(look_up_dict(dictionary, text, 4, 1) == 1);
    }

    assert(break_into_words("a", dictionary));
    assert(break_into_words("aaaaaa", dictionary));
    assert(break_into_words("day", dictionary));
    assert(break_into_words("whataniceday", dictionary));
    assert(break_into_words("niceday", dictionary));
    assert(break_into_words("nicedayan", dictionary));

    assert(!break_into_words("nicedayt", dictionary));
    assert(!break_into_words("whatanceday", dictionary));


    assert(break_into_words("niceday", {"n", "y", "i", "c", "e", "d", "a"}));
    assert(!break_into_words("niceday", {"n", "i", "c", "e", "d", "a"}));
    assert(!break_into_words("niceday", {"y", "i", "c", "e", "d", "a"}));
    assert(!break_into_words("niceday", {"n", "y", "i", "e", "d", "a"}));

    assert(!break_into_words("niceda", {"niceday"}));
    assert(!break_into_words("niceday", {"iceday"}));
    assert(!break_into_words("niceday", {"n", "y"}));
    assert(!break_into_words("niceday", {}));
    assert(!break_into_words("nice", {}));
    return 0;
}
