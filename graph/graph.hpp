#pragma once

#include <algorithm>
#include <optional>
#include <set>
#include <utility>
#include <array>
#include <vector>
#include <cstddef>
#include <type_traits>

namespace tags {
    struct single_t { constexpr single_t() noexcept {} };
    constexpr single_t single;
    struct both_t { constexpr both_t() noexcept {} };
    constexpr both_t both;
}

/**
 * Graph representation with weights.
 *
 * Template parameters:
 * - T is type of elements.
 * - Size is number of nodes in graph.
 */
template<typename T, std::size_t Size>
class Graph {
    static_assert(std::is_integral<T>::value, "Only integer can be used to represent node in graph");
    static_assert(Size > 0, "Number of nodes in graph cannot be below 1");

    using Type = std::pair<T, int>;

    public:
        /**
         * Graph's edges.
         *
         * Each element of array corresponds to particular node
         * and contains list of connected nodes
         */
        std::array<std::vector<Type>, Size> edges;

        ///@constructor
        Graph() {
        }

        /**
         * Adds new edge to Graph.
         *
         * @param from Position of origin.
         * @param to Position of destination.
         * @param weight Weight of path from origin to destination.
         */
        template<typename D=tags::single_t>
        void add_path(T from, T to, int weight, D=tags::single) {
            static_assert(std::is_same<D, tags::single_t>::value || std::is_same<D, tags::both_t>::value);

            if (static_cast<size_t>(from) >= Size) throw "from is beyond Graph capacity";
            if (static_cast<size_t>(to) >= Size) throw "to is beyond Graph capacity";

            this->edges[static_cast<size_t>(from)].emplace_back(to, weight);
            if constexpr (std::is_same<D, tags::both_t>::value) {
                this->edges[static_cast<size_t>(to)].emplace_back(from, weight);
            }
        }

        /**
         * Returns weight of shortest path
         *
         * @param src Position of origin.
         * @param dest Position of destination.
         * @return Pair that constains sum of weights in destination from src to dest
         *         And sequence of nodes from src to dest.
         */
        std::pair<int, std::vector<T>> shortest_path(T src, T dest) const {
            if (static_cast<size_t>(src) >= Size) throw "src is beyond Graph capacity";
            if (static_cast<size_t>(dest) >= Size) throw "dest is beyond Graph capacity";

            //Map of distances from source to other nodes.
            //By default src -> src = 0
            std::vector<std::optional<int>> dist(Size, std::nullopt);
            dist[src] = 0;

            //Set of nodes to process.
            //First element is minimum weight, next is node's index
            //Lowest weight will come first, or lowest index if weight is the same
            std::set<std::pair<int, T>> to_process;
            to_process.emplace(0, src);

            std::vector<std::optional<T>> visited(Size, std::nullopt);

            while (!to_process.empty()) {
                //Take the first element with closest distance.
                auto [weight, node] = *(to_process.begin());
                to_process.erase(to_process.begin());

                //If we found shortest distance toward our destination we can finish
                if (node == dest) break;

                for (const auto& [neighbor_id, neighbor_weight] : this->edges[node]) {
                    const auto is_inf = !dist[neighbor_id].has_value();
                    const auto alt_weight = neighbor_weight + weight;

                    //if optional is None, then it is infinity.
                    //otherwise check diff and update only if new weight is lesser
                    if (is_inf || (*dist[neighbor_id] > alt_weight)) {
                        if (!is_inf) {
                            //If we already has some value for distnace
                            //we should remove previous value of it from set to process.
                            (void)to_process.erase(to_process.find(std::make_pair(*dist[neighbor_id], neighbor_id)));
                        }

                        dist[neighbor_id] = alt_weight;
                        visited[neighbor_id] = node;
                        to_process.emplace(alt_weight, neighbor_id);
                    }
                }
            }

            std::vector<T> path;
            for (T target = dest; visited[target].has_value(); target = *visited[target]) {
                path.push_back(target);
            }
            path.push_back(src);
            std::reverse(path.begin(), path.end());

            return std::make_pair(*dist[dest], path);
        }

        friend std::ostream& operator<< (std::ostream& stream, const Graph<T, Size>& self) {
            stream << "From\t\tTo\t\tWeight\n";
            for (size_t idx = 0; idx < self.edges.size(); idx++) {
                for (const auto& edge : self.edges[idx]) {
                    stream << idx << "\t->\t" << edge.first << "\t=\t" << edge.second << "\n";
                }
            }
            return stream;
        }
};
