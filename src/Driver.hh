#ifndef RBS_PARSER_DRIVER_HH
#define RBS_PARSER_DRIVER_HH

#include "File.hh"
#include "Parser.hh"
#include "ast.hh"

#include <string>
#include <vector>

namespace rbs_parser {
class Driver {
public:
    File *file;

    Driver(File *file) : file(file){};

    Loc loc(Parser::location_type begin, Parser::location_type end) {
        return Loc(Pos(begin.begin.line, begin.begin.column), Pos(end.end.line, end.end.column));
    }

    std::unique_ptr<NodeList> list() {
        return std::make_unique<NodeList>(Loc(Pos(0, 0), Pos(0, 0)));
    }

    std::unique_ptr<NodeList> list(unique_ptr<Node> node) {
        auto list = std::make_unique<NodeList>(node->loc);
        list->emplace_back(move(node));
        return list;
    }

    std::unique_ptr<NodeList> merge(unique_ptr<Node> node1, unique_ptr<Node> node2) {
        auto list = std::make_unique<NodeList>(node1->loc); // TODO merge locs
        list->emplace_back(move(node1));
        list->emplace_back(move(node2));
        return list;
    }

    std::unique_ptr<NodeList> merge(unique_ptr<Node> node, unique_ptr<NodeList> nodes) {
        auto list = std::make_unique<NodeList>(node->loc); // TODO merge locs
        list->emplace_back(move(node));
        list->concat(nodes.release());
        return list;
    }

    std::unique_ptr<NodeList> merge(unique_ptr<NodeList> nodes, unique_ptr<Node> node) {
        auto list = std::make_unique<NodeList>(node->loc); // TODO merge locs
        list->concat(nodes.release());
        list->emplace_back(move(node));
        return list;
    }

    std::unique_ptr<Type> type(std::unique_ptr<Node> const &node) {
        return cast_node<Type>(node);
    }

    std::string string(std::unique_ptr<Node> const &node) {
        if (node) {
            return cast_node<Token>(node)->str;
        }
        return "";
    }

    template<typename T>
    std::unique_ptr<T> cast_node(std::unique_ptr<Node> const &node) {
        return std::unique_ptr<T>(static_cast<T*>(node.get()));
    }

    template<typename T>
    std::vector<std::unique_ptr<T>> cast_list(std::unique_ptr<Node> const &list) {
        std::vector<std::unique_ptr<T>> v;
        for (auto &node : cast_node<NodeList>(list)->nodes) {
            v.emplace_back(cast_node<T>(move(node)));
        }
        return v;
    }
};
} // namespace rbs_parser

#endif
