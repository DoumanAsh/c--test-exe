#include <algorithm>
#include <string>
#include <vector>
#include <unordered_set>
#include <iostream>
#include <chrono>
#include <functional>

class CRObject
{
    long                   m_level = 0;
    std::string            m_name;
    std::vector<CRObject*> m_parentList;
    std::vector<CRObject*> m_childList;

    public:
    CRObject() = default;
    explicit CRObject(const char* name) : m_name(name) {};
    void SetLevel(long level){ m_level = level; }
    long GetLevel() const { return m_level; }

    void               SetName( const char* name ){ m_name = name; }
    const std::string& GetName() const { return m_name; }

    size_t    GetNumParents() const { return m_parentList.size(); }
    CRObject* GetParent(size_t n) const { return n < m_parentList.size() ? m_parentList[ n ] : NULL; }
    void      AddParent( CRObject* parent ){ m_parentList.push_back( parent ); }

    size_t    GetNumChildren() const { return m_childList.size(); }
    CRObject* GetChild(size_t n) const { return n < m_childList.size() ? m_childList[ n ] : NULL; }
    void      AddChild(CRObject* child){ m_childList.push_back( child ); }
};

/**
 * Assign level to CRObject.
 */
static inline void assign_level(CRObject* object) {
    size_t size = object->GetNumParents();

    if (size == 0) {
        object->SetLevel(0);
    }
    else {
        long level = object->GetParent(0)->GetLevel();

        for (size_t idx = size - 1; idx > 0; idx--) {
            level = std::max(object->GetParent(idx)->GetLevel(), level);
        }

        object->SetLevel(level + 1);
    }
}

/**
 * Retrieve top elements of object.
 *
 * Complexity O(N)
 *
 * @param[in] allObjectList List of CRObject to inspect.
 */
std::unordered_set<CRObject*> find_top_elements(const std::vector<CRObject*>& allObjectList) {
    //Find top elements
    std::unordered_set<CRObject*> top_elements;

    //Recursive closure to handle nested objects.
    std::function<void(CRObject* object)> find_top_parents = [&top_elements, &find_top_parents](CRObject* object) {
        size_t size = object->GetNumParents();

        for (size_t idx = 0; idx < size; idx++) {
            CRObject* parent = object->GetParent(idx);

            if (parent->GetNumParents() > 0) {
                find_top_parents(parent);
            }
            else {
                top_elements.insert(parent);
            }
        }
    };

    for (CRObject* object : allObjectList) {
        find_top_parents(object);
    }

    return top_elements;
}

/**
 * Generates flatten list of objects in hierarchical order.
 *
 * Uses recursive calls to itself.
 *
 * Complexity: O(N)?
 */
std::vector<CRObject*> flatten_objects(std::unordered_set<CRObject*>&& top_elements) {
    std::unordered_set<CRObject*> next_top_elements;

    for (auto object : top_elements) {
        const auto size = object->GetNumChildren();
        for (size_t idx = 0; idx < size; idx++) {
            next_top_elements.insert(object->GetChild(idx));
        }
    }

    std::vector<CRObject*> result(next_top_elements.begin(), next_top_elements.end());

    if (!result.empty()) {
        auto sub_result = flatten_objects(std::move(next_top_elements));
        result.insert(result.end(), sub_result.begin(), sub_result.end());
    }

    return result;
}

/**
 * Assign for each object in list.
 *
 * Initial condition of objects: all have level zero.
 *
 * Child element's level should be always greater than max among its parents.
 *
 * @param[in] allObjectList Unsorted list of CRObject instances.
 */
void SetObjectLevel(std::vector<CRObject*>& allObjectList) {
    std::vector<CRObject*> sorted_objects(allObjectList.size());

    auto top_elements = find_top_elements(allObjectList);

    for (auto object : top_elements) {
        object->SetLevel(0);
    }

    const auto flatten_children = flatten_objects(std::move(top_elements));

    for (auto object : flatten_children) {
        assign_level(object);
    }
}

int main() {
    CRObject A("A"), B("B"), C("C"), E("E"), F("F"), D("D");

    A.AddChild(&B);
    B.AddParent(&A);

    B.AddChild(&E);
    E.AddParent(&B);

    C.AddChild(&E);
    E.AddParent(&C);

    C.AddChild(&F);
    F.AddParent(&C);

    E.AddChild(&D);
    D.AddParent(&E);

    std::vector<CRObject*> allObjectList = {&B, &C, &E, &F, &D, &A};
    auto start = std::chrono::system_clock::now();
    SetObjectLevel(allObjectList);
    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "SetObjectLevel took " << elapsed.count() << "ms\n";

    std::vector<long> allObjectList_expected_level = {1, 0, 2, 1, 3, 0};

    for (size_t idx = 0; idx < allObjectList.size(); idx++) {
        long level = allObjectList[idx]->GetLevel();

        if (level != allObjectList_expected_level[idx]) {
            std::cout << allObjectList[idx]->GetName() << ": level is " << level << " but expected " << allObjectList_expected_level[idx] << "\n";
        }
    }
}
