#include <assert.h>
#include <map>
#include <limits>

template<class K, class V>
class interval_map {
    static_assert(std::is_copy_assignable<K>::value, "Key type is no copy assignable");
    static_assert(std::is_copy_assignable<V>::value, "Value type is no copy assignable");

public:
    std::map<K,V> m_map;

    // constructor associates whole range of K with val by inserting (K_min, val)
    // into the map
    interval_map(V const& val) {
        m_map.insert(m_map.begin(), std::make_pair(std::numeric_limits<K>::lowest(), val));
    }

    // Assign value val to interval [keyBegin, keyEnd).
    // Overwrite previous values in this interval.
    // Do not change values outside this interval.
    // Conforming to the C++ Standard Library conventions, the interval
    // includes keyBegin, but excludes keyEnd.
    // If !( keyBegin < keyEnd ), this designates an empty interval,
    // and assign must do nothing.
    void assign(K const& keyBegin, K const& keyEnd, V const& val) {
// INSERT YOUR SOLUTION HERE
        if (!(keyBegin < keyEnd)) return;

        //We should ensure that next and previous ranges are not with the same values
        //No result so let's try to report error usage throw exceptions
        auto previous = this->m_map.lower_bound(keyBegin);
        if (previous == this->m_map.end() || !(previous->first < keyBegin)) {
            --previous;
        }
        if (previous->second == val) {
            throw "Previous range has the same value as new one";
        }

        auto next = previous;
        for (++next;next != this->m_map.end() && next->first < keyEnd; ++next) { }

        if (next != this->m_map.end() && keyEnd < next->first) {
            //Assume that overlapping range means extension of existing one
            if (next->second == val) {
                throw "Next range has the same value as new one";
            }
        }

        auto begin = this->m_map.emplace_hint(previous, keyBegin, val);
        //Failed to do something with keyEnd being inclusive.
        auto end = this->m_map.emplace_hint(next, keyEnd, val);
        end->second = val;

        for (;begin != end; ++begin) {
            begin->second = val;
        }
    }

    // look-up of the value associated with key
    V const& operator[]( K const& key ) const {
        return ( --m_map.upper_bound(key) )->second;
    }
};
