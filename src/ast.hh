#ifndef RBS_PARSER_AST_HH
#define RBS_PARSER_AST_HH

#include "classes.hh"

#include <memory>
#include <string>
#include <vector>

using namespace std;

namespace rbs_parser {
class Pos {
public:
    int line, column;
    Pos(int line, int column) : line(line), column(column) {}

    string toString() { return to_string(line) + ":" + to_string(column); }
};

class Loc {
public:
    Pos begin, end;
    Loc(Pos begin, Pos end) : begin(begin), end(end) {}

    string toString() { return begin.toString() + "-" + end.toString(); }
};

class Node {
public:
    Loc loc;
    Node(Loc loc) : loc(loc) {}
    virtual ~Node() = default;
    virtual void acceptVisitor(Visitor *v) = 0;
};

class NodeList {
public:
    vector<unique_ptr<Node>> nodes;

    NodeList() = default;

    inline void emplace_back(unique_ptr<Node> node) { nodes.emplace_back(move(node)); }

    inline void concat(NodeList *other) {
        nodes.insert(nodes.end(), make_move_iterator(other->nodes.begin()), make_move_iterator(other->nodes.end()));
    }
};

class Visitor {
public:
    virtual void enterVisit(Node *node) { node->acceptVisitor(this); }

    virtual void visit(File *file) = 0;

    virtual void visit(TypeAny *type) = 0;
    virtual void visit(TypeBool *type) = 0;
    virtual void visit(TypeBot *type) = 0;
    virtual void visit(TypeClass *type) = 0;
    virtual void visit(TypeFalse *type) = 0;
    virtual void visit(TypeGeneric *type) = 0;
    virtual void visit(TypeInstance *type) = 0;
    virtual void visit(TypeInteger *type) = 0;
    virtual void visit(TypeIntersection *type) = 0;
    virtual void visit(TypeNil *type) = 0;
    virtual void visit(TypeNilable *type) = 0;
    virtual void visit(TypeProc *type) = 0;
    virtual void visit(TypeSelf *type) = 0;
    virtual void visit(TypeSelfQ *type) = 0;
    virtual void visit(TypeSimple *type) = 0;
    virtual void visit(TypeSingleton *type) = 0;
    virtual void visit(TypeString *type) = 0;
    virtual void visit(TypeSymbol *type) = 0;
    virtual void visit(TypeTop *type) = 0;
    virtual void visit(TypeTrue *type) = 0;
    virtual void visit(TypeTuple *type) = 0;
    virtual void visit(TypeUnion *type) = 0;
    virtual void visit(TypeUntyped *type) = 0;
    virtual void visit(TypeVoid *type) = 0;

    virtual void visit(Record *type) = 0;
    virtual void visit(RecordField *field) = 0;

    virtual void visit(Class *decl) = 0;
    virtual void visit(Const *decl) = 0;
    virtual void visit(Extension *decl) = 0;
    virtual void visit(Global *decl) = 0;
    virtual void visit(Interface *decl) = 0;
    virtual void visit(Module *decl) = 0;
    virtual void visit(TypeDecl *decl) = 0;

    virtual void visit(Alias *decl) = 0;
    virtual void visit(AttrAccessor *decl) = 0;
    virtual void visit(AttrReader *decl) = 0;
    virtual void visit(AttrWriter *decl) = 0;
    virtual void visit(Extend *decl) = 0;
    virtual void visit(Include *decl) = 0;
    virtual void visit(Method *decl) = 0;
    virtual void visit(Prepend *decl) = 0;
    virtual void visit(Visibility *decl) = 0;

    virtual void visit(MethodType *type) = 0;
    virtual void visit(Block *type) = 0;
    virtual void visit(Param *param) = 0;

    virtual void visit(TypeParam *param) = 0;
};

// Types

class Type : public Node {
public:
    Type(Loc loc) : Node(loc){};
    virtual ~Type() = default;
};

class TypeAny : public Type {
public:
    TypeAny(Loc loc) : Type(loc) {}
    virtual ~TypeAny() = default;
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class TypeBool : public Type {
public:
    TypeBool(Loc loc) : Type(loc) {}
    virtual ~TypeBool() = default;
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class TypeBot : public Type {
public:
    TypeBot(Loc loc) : Type(loc) {}
    virtual ~TypeBot() = default;
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class TypeClass : public Type {
public:
    TypeClass(Loc loc) : Type(loc) {}
    virtual ~TypeClass() = default;
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class TypeFalse : public Type {
public:
    TypeFalse(Loc loc) : Type(loc) {}
    virtual ~TypeFalse() = default;
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class TypeGeneric : public Type {
public:
    string name;
    vector<unique_ptr<Type>> types;

    TypeGeneric(Loc loc, string name) : Type(loc), name(name) {}
    virtual ~TypeGeneric() = default;
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class TypeInstance : public Type {
public:
    TypeInstance(Loc loc) : Type(loc) {}
    virtual ~TypeInstance() = default;
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class TypeInteger : public Type {
public:
    string integer;

    TypeInteger(Loc loc, string integer) : Type(loc), integer(integer) {};
    virtual ~TypeInteger() = default;
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class TypeIntersection : public Type {
public:
    vector<unique_ptr<Type>> types;

    TypeIntersection(Loc loc) : Type(loc) {};
    TypeIntersection(Loc loc, vector<unique_ptr<Type>> types) : Type(loc), types(move(types)) {};
    virtual ~TypeIntersection() = default;
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class TypeNil : public Type {
public:
    TypeNil(Loc loc) : Type(loc) {}
    virtual ~TypeNil() = default;
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class TypeNilable : public Type {
public:
    unique_ptr<Type> type;

    TypeNilable(Loc loc, unique_ptr<Type> type) : Type(loc), type(move(type)) {}
    virtual ~TypeNilable() = default;
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class Param : public Node {
public:
    string name;
    unique_ptr<Type> type;
    bool keyword = false;
    bool optional = false;
    bool vararg = false;

    Param(Loc loc, string name, unique_ptr<Type> type, bool keyword, bool optional, bool vararg)
        : Node(loc), name(name), type(move(type)), keyword(keyword), optional(optional), vararg(vararg) {}
    virtual ~Param() = default;
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class TypeProc : public Type {
public:
    vector<unique_ptr<Param>> params;
    unique_ptr<Type> ret;

    TypeProc(Loc loc) : Type(loc){};
    TypeProc(Loc loc, unique_ptr<Type> ret) : Type(loc), ret(move(ret)){};
    TypeProc(Loc loc, vector<unique_ptr<Param>> params, unique_ptr<Type> ret) : Type(loc), params(move(params)), ret(move(ret)) {}
    virtual ~TypeProc() = default;
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class TypeSelf : public Type {
public:
    TypeSelf(Loc loc) : Type(loc) {}
    virtual ~TypeSelf() = default;
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class TypeSelfQ : public Type {
public:
    TypeSelfQ(Loc loc) : Type(loc) {}
    virtual ~TypeSelfQ() = default;
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class TypeSimple : public Type {
public:
    string name;

    TypeSimple(Loc loc, string name) : Type(loc), name(name) {};
    virtual ~TypeSimple() = default;
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class TypeSingleton : public TypeSimple {
public:
    TypeSingleton(Loc loc, string name) : TypeSimple(loc, name) {}
    virtual ~TypeSingleton() = default;
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class TypeString : public Type {
public:
    string str;

    TypeString(Loc loc, string str) : Type(loc), str(str) {};
    virtual ~TypeString() = default;
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class TypeSymbol : public Type {
public:
    string symbol;

    TypeSymbol(Loc loc, string symbol) : Type(loc), symbol(symbol) {};
    virtual ~TypeSymbol() = default;
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class TypeTop : public Type {
public:
    TypeTop(Loc loc) : Type(loc) {}
    virtual ~TypeTop() = default;
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class TypeTrue : public Type {
public:
    TypeTrue(Loc loc) : Type(loc) {}
    virtual ~TypeTrue() = default;
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class TypeTuple : public Type {
public:
    vector<unique_ptr<Type>> types;

    TypeTuple(Loc loc) : Type(loc){};
    virtual ~TypeTuple() = default;
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class TypeUnion : public Type {
public:
    vector<unique_ptr<Type>> types;

    TypeUnion(Loc loc) : Type(loc){};
    TypeUnion(Loc loc, vector<unique_ptr<Type>> types) : Type(loc), types(move(types)) {};

    virtual ~TypeUnion() = default;
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class TypeUntyped : public Type {
public:
    TypeUntyped(Loc loc) : Type(loc) {}
    virtual ~TypeUntyped() = default;
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class TypeVoid : public Type {
public:
    TypeVoid(Loc loc) : Type(loc) {}
    virtual ~TypeVoid() = default;
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

// Records

class RecordField : public Node {
public:
    string name;
    unique_ptr<Type> type;

    RecordField(Loc loc, string name, unique_ptr<Type> type) : Node(loc), name(name), type(move(type)) {};
    virtual ~RecordField() = default;
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class Record : public Type {
public:
    vector<unique_ptr<RecordField>> fields;

    Record(Loc loc) : Type(loc) {}
    virtual ~Record() = default;
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

// Classes

class TypeParam : public Node {
public:
    string name;
    string variance;
    bool unchecked;

    TypeParam(Loc loc, string name, string variance, bool unchecked)
        : Node(loc), name(name), variance(variance), unchecked(unchecked) {};
    virtual ~TypeParam() = default;
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

// Declarations

class Decl : public Node {
public:
    Decl(Loc loc) : Node(loc) {}
    virtual ~Decl() = default;
};

class Member : public Node {
public:
    Member(Loc loc) : Node(loc) {};
    virtual ~Member() = default;
};

class Scope : public Decl {
public:
    string name;
    vector<unique_ptr<TypeParam>> typeParams;
    vector<unique_ptr<Member>> members;

    Scope(Loc loc, string name) : Decl(loc), name(name) {};
    virtual ~Scope() = default;
};

class Class : public Scope {
public:
    string parent; // Should be a type

    Class(Loc loc, string name, string parent) : Scope(loc, name), parent(parent) {}
    virtual ~Class() = default;
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class Const : public Decl {
public:
    string name;
    unique_ptr<Type> type;

    Const(Loc loc, string name, unique_ptr<Type> type) : Decl(loc), name(name), type(move(type)) {};
    virtual ~Const() = default;
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class Extension : public Scope {
public:
    string extensionName;

    Extension(Loc loc, string name, string extensionName) : Scope(loc, name), extensionName(extensionName) {};
    virtual ~Extension() = default;
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class Global : public Decl {
public:
    string name;
    unique_ptr<Type> type;

    Global(Loc loc, string name, unique_ptr<Type> type) : Decl(loc), name(name), type(move(type)) {};
    virtual ~Global() = default;
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class Interface : public Scope {
public:
    Interface(Loc loc, string name) : Scope(loc, name) {};
    virtual ~Interface() = default;
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class Module : public Scope {
public:
    unique_ptr<Type> selfType;

    Module(Loc loc, string name) : Scope(loc, name) {};
    virtual ~Module() = default;
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class TypeDecl : public Decl {
public:
    string name;
    unique_ptr<Type> type;

    TypeDecl(Loc loc, string name, unique_ptr<Type> type) : Decl(loc), name(name), type(move(type)) {};
    virtual ~TypeDecl() = default;
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

// Class members

class Alias : public Member {
public:
    string from;
    string to;
    bool singleton;

    Alias(Loc loc, string from, string to, bool singleton) : Member(loc), from(from), to(to), singleton(singleton) {};
    virtual ~Alias() = default;
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class Attr : public Member {
public:
    string name;
    string ivar;
    unique_ptr<Type> type;

    Attr(Loc loc, string name, string ivar, unique_ptr<Type> type) : Member(loc), name(name), ivar(ivar), type(move(type)) {};
    virtual ~Attr() = default;
};

class AttrAccessor : public Attr {
public:
    AttrAccessor(Loc loc, string name, string ivar, unique_ptr<Type> type) : Attr(loc, name, ivar, move(type)) {};
    virtual ~AttrAccessor() = default;
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class AttrReader : public Attr {
public:
    AttrReader(Loc loc, string name, string ivar, unique_ptr<Type> type) : Attr(loc, name, ivar, move(type)) {};
    virtual ~AttrReader() = default;
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class AttrWriter : public Attr {
public:
    AttrWriter(Loc loc, string name, string ivar, unique_ptr<Type> type) : Attr(loc, name, ivar, move(type)) {};
    virtual ~AttrWriter() = default;
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class Include : public Member {
public:
    unique_ptr<Type> type;

    Include(Loc loc, unique_ptr<Type> type) : Member(loc), type(move(type)) {}
    virtual ~Include() = default;
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class Extend : public Member {
public:
    unique_ptr<Type> type;

    Extend(Loc loc, unique_ptr<Type> type) : Member(loc), type(move(type)) {}
    virtual ~Extend() = default;
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

// Methods

class Block : public Type {
public:
    unique_ptr<TypeProc> sig;
    bool optional = false;

    Block(Loc loc, unique_ptr<TypeProc> sig, bool optional) : Type(loc), sig(move(sig)), optional(optional) {};
    virtual ~Block() = default;
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class MethodType : public Node {
public:
    vector<unique_ptr<TypeParam>> typeParams;
    unique_ptr<TypeProc> sig;
    unique_ptr<Block> block;

    MethodType(Loc loc, unique_ptr<TypeProc> sig) : Node(loc), sig(move(sig)) {}
    virtual ~MethodType() = default;
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class Method : public Member {
public:
    string name;
    vector<unique_ptr<MethodType>> types;
    bool instance;
    bool singleton;
    bool incompatible;

    Method(Loc loc, string name, bool instance, bool singleton, bool incompatible)
        : Member(loc), name(name), instance(instance), singleton(singleton), incompatible(incompatible) {};

    virtual ~Method() = default;
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class Prepend : public Member {
public:
    unique_ptr<Type> type;

    Prepend(Loc loc, unique_ptr<Type> type) : Member(loc), type(move(type)) {}
    virtual ~Prepend() = default;
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class Visibility : public Member {
public:
    string name;

    Visibility(Loc loc, string name) : Member(loc), name(name) {}
    virtual ~Visibility() = default;
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};
} // namespace rbs_parser

#endif
