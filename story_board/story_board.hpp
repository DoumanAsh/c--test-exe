#pragma once

/* In this exercise we want to design a Storyboard. Our version of the Storyboard
 * contains arbitrary many notes (imagine it like putting sticky notes on a board).
 * Every note has a title, a text and a set of tags. E.g.
 * 	- title: "Test Traceplayer"
 * 	- text: "Implement a unit test for the class Traceplayer of the spark core framework."
 * 	- tags: {"unit test", "traceplayer", "testing", "spark core"}
 *
 * Our Storyboard should enable us to search for notes by title, text and tags.
 * E.g.:
 *      searchByTitle("Test Traceplayer")
 *      searchByTag({"testing", "unit test"})
 *   	searchByText("Implement a unit test for the class Traceplayer of the spark core framework.")
 * For the sake of simplicity we don't want to do any similiarity or prefix matching when
 * searching for a title, tag or text. Only an exact match should give results.
 *
 * The skeleton code below can be used as a starting point but doesn't have to.
 * The comments "fill in" are placeholders where you definitely have to put in some code when
 * you use this skeleton code. But this doesn't mean that you shouldn't or can't put code anywhere else.
 *
 * Also write some simple unit tests to show how you would test the functionality of the Storyboard.
 * Don't use any testing framework. Simple if-statements are sufficient for this exercise.
 *
 * Hint: Think about performance versus memory tradeoffs in your design, so you can give good
 *       reasons for your decision.
 */

#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <optional>
#include <type_traits>

class Note {
    public:
        std::string title;
        std::string text;
        std::unordered_set<std::string> tags;

        Note(std::string title, std::string text, std::unordered_set<std::string> tags) : title(title), text(text), tags(tags) {}

        template<class... T>
        Note(std::string title, std::string text, T&&... tags) : title(title), text(text), tags({std::forward<T>(tags)...}) {}
};

std::ostream &operator<<(std::ostream &os, const Note& note) {
    os << "Title: \"" << note.title << "\" | Text=\"" << note.text << "\" | Tags {";

    for (const auto& tag : note.tags) {
        os << "\"" << tag << "\",";
    }

    return os << "}";
}

class StoryBoard {
    private:
        std::vector<Note> notes;
        //Assume that titles are unique so use hashmap for fast look-up
        std::unordered_map<std::string, size_t> titles;

    public:
        ///Adds new note, and returns whether it is been added
        template<class... T>
        bool add_note(T&&... value) {
            Note new_note(std::forward<T>(value)...);

            if (this->titles.count(new_note.title) == 0) {
                this->notes.emplace_back(new_note);
                this->titles.emplace(new_note.title, this->notes.size() - 1);
                return true;
            } else {
                return false;
            }
        }

        ///Removes note by title, and returns whether actual note has been removed
        bool remove_note(const std::string& title) {
            auto find = this->titles.find(title);

            if (find == this->titles.end()) {
                return false;
            }

            size_t pos = find->second;
            size_t last_pos = this->notes.size() - 1;

            this->titles.erase(find);

            if (this->notes.size() > 1 && pos != last_pos) {
                std::swap(this->notes[pos], this->notes[last_pos]);
                this->titles[this->notes[pos].title] = pos;
            }

            this->notes.pop_back();

            return true;
        }

        const Note* search_title(const std::string& title) {
            auto find = this->titles.find(title);
            if (find != this->titles.end()) {
                return &this->notes[find->second];
            } else {
                return nullptr;
            }
        }

        ///Starts search from specified position.
        ///
        ///User must ensure that iterator is valid.
        ///I.e. no add/remove ops while holding iterator.
        template<class T>
        auto search_text(const std::string& text, T from) {
            static_assert(std::is_same<T, std::vector<Note>::const_iterator>::value, "from must be valid iterator");

            std::hash<std::string> hasher;
            auto text_hash = hasher(text);

            auto result = std::make_optional(this->notes.cend());

            for (auto it = from; it != this->notes.cend(); ++it) {
                if (text_hash == hasher(it->text)) {
                    result.emplace(it);
                    break;
                }
            }

            if (*result == this->notes.cend()) {
                result.reset();
            }

            return result;
        }

        //Returns iterator to resume search
        auto search_text(const std::string& text) {
            return search_text(text, this->notes.cbegin());
        }

        ///Starts search from specified position.
        ///
        ///User must ensure that iterator is valid.
        ///I.e. no add/remove ops while holding iterator.
        template<class T>
        auto search_tag(const std::string& tag, T from) {
            static_assert(std::is_same<T, std::vector<Note>::const_iterator>::value, "from must be valid iterator");

            auto result = std::make_optional(this->notes.cend());

            for (auto it = from; it != this->notes.cend(); ++it) {
                if (it->tags.count(tag) == 1) {
                    result.emplace(it);
                    break;
                }
            }

            if (*result == this->notes.cend()) {
                result.reset();
            }

            return result;

        }

        //Returns iterator to resume search
        auto search_tag(const std::string& tag) {
            return search_tag(tag, this->notes.cbegin());
        }
};
