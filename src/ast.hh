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
    virtual void acceptVisitor(Visitor *v) = 0;
};

class NodeList {
public:
    vector<Node *> nodes;

    NodeList() = default;

    NodeList(Node *node) { nodes.emplace_back(node); }
    NodeList(NodeList *list1, NodeList *list2) : NodeList() {
        concat(list1);
        concat(list2);
    }

    NodeList &operator=(const Node *&other) = delete;
    NodeList &operator=(Node *&&other) = delete;

    inline size_t size() const { return nodes.size(); }

    inline void emplace_back(Node *&ptr) { nodes.emplace_back(ptr); }

    inline Node *&at(size_t n) { return nodes.at(n); }

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
    virtual ~Type() {}
};

class TypeAny : public Type {
public:
    TypeAny(Loc loc) : Type(loc) {}
    virtual ~TypeAny() {}
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class TypeBool : public Type {
public:
    TypeBool(Loc loc) : Type(loc) {}
    virtual ~TypeBool() {}
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class TypeBot : public Type {
public:
    TypeBot(Loc loc) : Type(loc) {}
    virtual ~TypeBot() {}
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class TypeClass : public Type {
public:
    TypeClass(Loc loc) : Type(loc) {}
    virtual ~TypeClass() {}
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class TypeFalse : public Type {
public:
    TypeFalse(Loc loc) : Type(loc) {}
    virtual ~TypeFalse() {}
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class TypeGeneric : public Type {
public:
    string name;
    vector<Type *> types;

    TypeGeneric(Loc loc, string name) : Type(loc), name(name) {}

    virtual ~TypeGeneric() {
        for (auto type : types) {
            delete type;
        }
    }

    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class TypeInstance : public Type {
public:
    TypeInstance(Loc loc) : Type(loc) {}
    virtual ~TypeInstance() {}
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class TypeInteger : public Type {
public:
    string integer;

    TypeInteger(Loc loc, string integer) : Type(loc), integer(integer){};
    virtual ~TypeInteger() = default;
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class TypeIntersection : public Type {
public:
    vector<Type *> types;

    TypeIntersection(Loc loc) : Type(loc){};
    TypeIntersection(Loc loc, vector<Type *> types) : Type(loc), types(types){};

    virtual ~TypeIntersection() {
        for (auto type : types) {
            delete type;
        }
    }

    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class TypeNil : public Type {
public:
    TypeNil(Loc loc) : Type(loc) {}
    virtual ~TypeNil() {}
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class TypeNilable : public Type {
public:
    Type *type;
    TypeNilable(Loc loc, Type *type) : Type(loc), type(type) {}
    virtual ~TypeNilable() { delete type; }
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class Param : public Node {
public:
    string name;
    Type *type;
    bool keyword = false;
    bool optional = false;
    bool vararg = false;

    Param(Loc loc, string name, Type *type, bool keyword, bool optional, bool vararg)
        : Node(loc), name(name), type(type), keyword(keyword), optional(optional), vararg(vararg) {}

    virtual ~Param() { delete type; }

    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class TypeProc : public Type {
public:
    vector<Param *> params;
    Type *ret;

    TypeProc(Loc loc) : Type(loc){};
    TypeProc(Loc loc, Type *ret) : Type(loc), ret(ret){};
    TypeProc(Loc loc, vector<Param *> params, Type *ret) : Type(loc), params(params), ret(ret) {}

    virtual ~TypeProc() {
        for (auto param : params) {
            delete param;
        }
        delete ret;
    }

    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class TypeSelf : public Type {
public:
    TypeSelf(Loc loc) : Type(loc) {}
    virtual ~TypeSelf() {}
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class TypeSelfQ : public Type {
public:
    TypeSelfQ(Loc loc) : Type(loc) {}
    virtual ~TypeSelfQ() {}
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class TypeSimple : public Type {
public:
    string name;
    TypeSimple(Loc loc, string name) : Type(loc), name(name){};
    virtual ~TypeSimple() = default;
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class TypeSingleton : public TypeSimple {
public:
    TypeSingleton(Loc loc, string name) : TypeSimple(loc, name) {}
    virtual ~TypeSingleton() {}
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class TypeString : public Type {
public:
    string str;

    TypeString(Loc loc, string str) : Type(loc), str(str){};
    virtual ~TypeString() = default;
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class TypeSymbol : public Type {
public:
    string symbol;

    TypeSymbol(Loc loc, string symbol) : Type(loc), symbol(symbol){};
    virtual ~TypeSymbol() = default;
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class TypeTop : public Type {
public:
    TypeTop(Loc loc) : Type(loc) {}
    virtual ~TypeTop() {}
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class TypeTrue : public Type {
public:
    TypeTrue(Loc loc) : Type(loc) {}
    virtual ~TypeTrue() {}
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class TypeTuple : public Type {
public:
    vector<Type *> types;

    TypeTuple(Loc loc) : Type(loc){};

    virtual ~TypeTuple() {
        for (auto type : types) {
            delete type;
        }
    }

    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class TypeUnion : public Type {
public:
    vector<Type *> types;

    TypeUnion(Loc loc) : Type(loc){};
    TypeUnion(Loc loc, vector<Type *> types) : Type(loc), types(types){};

    virtual ~TypeUnion() {
        for (auto type : types) {
            delete type;
        }
    }

    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class TypeUntyped : public Type {
public:
    TypeUntyped(Loc loc) : Type(loc) {}
    virtual ~TypeUntyped() {}
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class TypeVoid : public Type {
public:
    TypeVoid(Loc loc) : Type(loc) {}
    virtual ~TypeVoid() {}
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

// Records

class RecordField : public Node {
public:
    string name;
    Type *type;

    RecordField(Loc loc, string name, Type *type) : Node(loc), name(name), type(type){};

    virtual ~RecordField() { delete type; }

    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class Record : public Type {
public:
    vector<RecordField *> fields;

    Record(Loc loc) : Type(loc) {}

    virtual ~Record() {
        for (auto field : fields) {
            delete field;
        }
    }

    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

// Classes

class TypeParam : public Node {
public:
    string name;
    string variance;
    bool unchecked;

    TypeParam(Loc loc, string name, string variance, bool unchecked)
        : Node(loc), name(name), variance(variance), unchecked(unchecked){};
    virtual ~TypeParam() = default;
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

// Declarations

class Decl : public Node {
public:
    Decl(Loc loc) : Node(loc) {}
    virtual ~Decl() {}
};

class Member : public Node {
public:
    Member(Loc loc) : Node(loc){};
    virtual ~Member() {}
};

class Scope : public Decl {
public:
    string name;
    vector<TypeParam *> typeParams;
    vector<Member *> members;

    Scope(Loc loc, string name) : Decl(loc), name(name){};

    virtual ~Scope() {
        for (auto type : typeParams) {
            delete type;
        }
        for (auto member : members) {
            delete member;
        }
    }
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
    Type *type;

    Const(Loc loc, string name, Type *type) : Decl(loc), name(name), type(type){};
    virtual ~Const() { delete type; }
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class Extension : public Scope {
public:
    string extensionName;

    Extension(Loc loc, string name, string extensionName) : Scope(loc, name), extensionName(extensionName){};
    virtual ~Extension() = default;
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class Global : public Decl {
public:
    string name;
    Type *type;

    Global(Loc loc, string name, Type *type) : Decl(loc), name(name), type(type){};
    virtual ~Global() { delete type; }
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class Interface : public Scope {
public:
    Interface(Loc loc, string name) : Scope(loc, name){};
    virtual ~Interface() {}
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class Module : public Scope {
public:
    Type *selfType;
    Module(Loc loc, string name) : Scope(loc, name), selfType(NULL){};
    virtual ~Module() { delete selfType; }
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class TypeDecl : public Decl {
public:
    string name;
    Type *type;

    TypeDecl(Loc loc, string name, Type *type) : Decl(loc), name(name), type(type){};
    virtual ~TypeDecl() { delete type; }
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

// Class members

class Alias : public Member {
public:
    string from;
    string to;
    bool singleton;

    Alias(Loc loc, string from, string to, bool singleton) : Member(loc), from(from), to(to), singleton(singleton){};
    virtual ~Alias() = default;
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class Attr : public Member {
public:
    string name;
    string ivar;
    Type *type;

    Attr(Loc loc, string name, string ivar, Type *type) : Member(loc), name(name), ivar(ivar), type(type){};
    virtual ~Attr() = default;
};

class AttrAccessor : public Attr {
public:
    AttrAccessor(Loc loc, string name, string ivar, Type *type) : Attr(loc, name, ivar, type){};

    virtual ~AttrAccessor() {}
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class AttrReader : public Attr {
public:
    AttrReader(Loc loc, string name, string ivar, Type *type) : Attr(loc, name, ivar, type){};

    virtual ~AttrReader() {}
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class AttrWriter : public Attr {
public:
    AttrWriter(Loc loc, string name, string ivar, Type *type) : Attr(loc, name, ivar, type){};

    virtual ~AttrWriter() {}
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class Include : public Member {
public:
    Type *type;

    Include(Loc loc, Type *type) : Member(loc), type(type) {}
    virtual ~Include() { delete type; }
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class Extend : public Member {
public:
    Type *type;

    Extend(Loc loc, Type *type) : Member(loc), type(type) {}
    virtual ~Extend() { delete type; }
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

// Methods

class Block : public Type {
public:
    TypeProc *sig;
    bool optional = false;

    Block(Loc loc, TypeProc *sig, bool optional) : Type(loc), sig(sig), optional(optional){};
    virtual ~Block() { delete sig; }
    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class MethodType : public Node {
public:
    vector<TypeParam *> typeParams;
    TypeProc *sig;
    Block *block;

    MethodType(Loc loc, TypeProc *sig) : Node(loc), sig(sig), block(NULL) {}

    virtual ~MethodType() {
        for (auto type : typeParams) {
            delete type;
        }
        delete sig;
        delete block;
    }

    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class Method : public Member {
public:
    string name;
    vector<MethodType *> types;
    bool instance;
    bool singleton;
    bool incompatible;

    Method(Loc loc, string name, bool instance, bool singleton, bool incompatible)
        : Member(loc), name(name), instance(instance), singleton(singleton), incompatible(incompatible){};

    virtual ~Method() {
        for (auto type : types) {
            delete type;
        }
    }

    virtual void acceptVisitor(Visitor *v) { v->visit(this); }
};

class Prepend : public Member {
public:
    Type *type;

    Prepend(Loc loc, Type *type) : Member(loc), type(type) {}
    virtual ~Prepend() { delete type; }
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
