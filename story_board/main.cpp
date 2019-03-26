#include "story_board.hpp"
#include <cassert>

int main() {
    StoryBoard board;

    std::cout << "Test Add/Remove\n";
    assert(board.add_note("Test", "Some description", "first", "second") == true);
    assert(board.add_note("Test", "Some description", "first", "second") == false);
    assert(board.remove_note("Testik") == false);
    assert(board.remove_note("Test") == true);
    assert(board.remove_note("Test") == false);

    std::cout << "Test Search\n";
    assert(board.add_note("Test", "Some description", "first", "second") == true);
    assert(board.add_note("MiniTest", "description", "smol") == true);

    auto test = board.search_title("Test");

    assert(test != nullptr);
    assert(test->title == "Test");
    assert(test->text == "Some description");
    assert(test->tags.count("first") == 1);
    assert(test->tags.count("second") == 1);
    assert(test->tags.count("smol") == 0);

    assert(board.remove_note("MiniTest") == true);

    test = board.search_title("MiniTest");
    assert(test == nullptr);

    std::cout << "Test Tags look-up\n";
    assert(board.add_note("Test2", "Some description", "first", "second") == true);

    auto search_res = board.search_tag("first");
    assert(search_res.has_value() == true);

    auto note = std::move(search_res.value());
    assert(note->title == "Test");
    assert(note->text == "Some description");

    search_res = board.search_tag("first", note + 1);
    assert(search_res.has_value() == true);

    note = std::move(search_res.value());
    assert(note->title == "Test2");
    assert(note->text == "Some description");

    search_res = board.search_tag("first", note + 1);
    assert(search_res.has_value() == false);

    //Iterator might be invalided after that
    assert(board.add_note("MiniTest", "description", "smol") == true);
    search_res = board.search_tag("smol");
    assert(search_res.has_value() == true);

    note = std::move(search_res.value());
    assert(note->title == "MiniTest");
    assert(note->text == "description");

    search_res = board.search_tag("smol", note + 1);
    assert(search_res.has_value() == false);

    std::cout << "Test Text look-up\n";
    search_res = board.search_text("Unknown");
    assert(search_res.has_value() == false);

    search_res = board.search_text("description");
    assert(search_res.has_value() == true);

    note = std::move(search_res.value());
    assert(note->title == "MiniTest");
    assert(note->text == "description");

    search_res = board.search_text("description", note + 1);
    assert(search_res.has_value() == false);

    return 0;
}
