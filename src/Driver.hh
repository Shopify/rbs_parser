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

    NodeList *list() { return new NodeList(Loc(Pos(0, 0), Pos(0, 0))); }

    NodeList *list(unique_ptr<Node> node) {
        NodeList *list = new NodeList(node->loc);
        list->emplace_back(move(node));
        return list;
    }

    NodeList *merge(unique_ptr<Node> node1, unique_ptr<Node> node2) {
        NodeList *list = new NodeList(node1->loc); // TODO merge locs
        list->emplace_back(move(node1));
        list->emplace_back(move(node2));
        return list;
    }

    NodeList *merge(unique_ptr<Node> node, NodeList *nodes) {
        NodeList *list = new NodeList(node->loc); // TODO merge locs
        list->emplace_back(move(node));
        list->concat(nodes);
        return list;
    }

    NodeList *merge(NodeList *nodes, unique_ptr<Node> node) {
        NodeList *list = new NodeList(node->loc); // TODO merge locs
        list->concat(nodes);
        list->emplace_back(move(node));
        return list;
    }

    std::unique_ptr<Type> type(Node *node) {
        return std::unique_ptr<Type>(static_cast<Type *>(node));
    }

    template<typename T>
    std::unique_ptr<T> cast_node(std::unique_ptr<Node> node) {
        return std::unique_ptr<T>(static_cast<T*>(node.release()));
    }

    template<typename T>
    std::vector<std::unique_ptr<T>> cast_list(NodeList *list) {
        std::vector<std::unique_ptr<T>> v;
        for (auto &node : list->nodes) {
            v.emplace_back(cast_node<T>(move(node)));
        }
        return v;
    }
};
} // namespace rbs_parser

#endif
