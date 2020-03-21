#ifndef RBS_PARSER_PRINT_RBI_HH
#define RBS_PARSER_PRINT_RBI_HH

#include "File.hh"
#include "PrintVisitor.hh"
#include <regex>
#include <set>

namespace rbs_parser {

class PrintRBI : public PrintVisitor {
public:
    PrintRBI(std::ostream &output) : PrintVisitor(output){};

    virtual void visit(File *file) {
        printl("# typed: true");
        bool lastWasBlock = true;
        for (int i = 0; i < file->decls.size(); i++) {
            auto *decl = file->decls[i];
            if (lastWasBlock) {
                printn();
            }
            if (dynamic_cast<Scope *>(decl)) {
                lastWasBlock = true;
            } else {
                lastWasBlock = false;
            }
            enterVisit(decl);
        }
    }

    void printDefName(std::string name) {
        if (name.length() > 1 && name.find("`", 0) == 0) {
            name = name.substr(1, name.length() - 2);
        }
        if (name == "undef") {
            name = "_undef";
        }
        print(name);
    }

    void printTypeName(std::string name) {
        if (name == "string") {
            print("String");
        } else if (name == "int") {
            print("Integer");
        } else if (name == "Array" || name == "::Array") {
            print("T::Array");
        } else if (name == "Hash" || name == "::Hash") {
            print("T::Hash");
        } else if (name == "Set" || name == "::Set") {
            print("T::Set");
        } else if (name == "Range" || name == "::Range") {
            print("T::Range");
        } else if (name == "Enumerator" || name == "::Enumerator") {
            print("T::Enumerator");
        } else if (name == "Enumerable" || name == "::Enumerable") {
            print("T::Enumerable");
            // } else if (name.length() > 1 && name.find("_", 0) == 0) {
            // print(name.substr(1, name.length() - 1));
        } else {
            print(name);
        }
    }

    void warnUnsupported(Node *node, std::string message) {
        std::cerr << node->loc.toString();
        std::cerr << ": Warning: ";
        std::cerr << message << std::endl;
    }

    // Types

    virtual void visit(TypeBool *type) { print("T::Boolean"); }

    virtual void visit(TypeNil *type) { print("NilClass"); }

    virtual void visit(TypeSelf *type) { print("T.self_type"); }

    virtual void visit(TypeUntyped *type) { print("T.untyped"); }

    virtual void visit(TypeVoid *type) { print("void"); }

    virtual void visit(TypeAny *type) { print("T.untyped"); }

    virtual void visit(TypeBot *type) {
        warnUnsupported(static_cast<Node *>(type), "Unsupported `bot`");
        print("T.untyped");
    }

    virtual void visit(TypeClass *type) { print("T.class_of(T.self_type)"); }

    virtual void visit(TypeFalse *type) { print("T::Boolean"); }

    virtual void visit(TypeTrue *type) { print("T::Boolean"); }

    virtual void visit(TypeSelfQ *type) {
        warnUnsupported(static_cast<Node *>(type), "Unsupported `self?`");
        print("T.untyped");
    }

    virtual void visit(TypeString *type) { print("String"); }

    virtual void visit(TypeInteger *type) { print("Integer"); }

    virtual void visit(TypeInstance *type) {
        warnUnsupported(static_cast<Node *>(type), "Unsupported `instance`");
        print("T.untyped");
    }

    virtual void visit(TypeSymbol *type) { print("Symbol"); }

    virtual void visit(TypeTop *type) {
        warnUnsupported(static_cast<Node *>(type), "Unsupported `top`");
        print("T.untyped");
    }

    virtual void visit(TypeNilable *type) {
        print("T.nilable(");
        enterVisit(type->type);
        print(")");
    }

    virtual void visit(TypeSimple *type) { printTypeName(*type->name); }

    virtual void visit(TypeSingleton *type) {
        print("T.class_of(");
        print(*type->name);
        print(")");
    }

    void printTypes(std::vector<Type *> types) {
        for (int i = 0; i < types.size(); i++) {
            enterVisit(types[i]);
            if (i < types.size() - 1) {
                print(", ");
            }
        }
    }

    virtual void visit(TypeUnion *type) {
        print("T.any(");
        printTypes(type->types);
        print(")");
    }

    virtual void visit(TypeIntersection *type) {
        print("T.all(");
        printTypes(type->types);
        print(")");
    }

    virtual void visit(TypeTuple *type) {
        print("[");
        printTypes(type->types);
        print("]");
    }

    virtual void visit(TypeGeneric *type) {
        printTypeName(*type->name);
        print("[");
        printTypes(type->types);
        print("]");
    }

    virtual void visit(TypeProc *type) {
        print("T.proc");
        if (!type->params.empty()) {
            print(".params(");
            for (int i = 0; i < type->params.size(); i++) {
                printParam(type->params[i], i);
                if (i < type->params.size() - 1) {
                    print(", ");
                }
            }
            print(")");
        }
        print(".");
        if (TypeVoid *type_void = dynamic_cast<TypeVoid *>(type->ret)) {
            enterVisit(type_void);
        } else {
            print("returns(");
            enterVisit(type->ret);
            print(")");
        }
    }

    // Records
    virtual void visit(RecordField *field) {
        // TODO sanitize name
        if (field->name->find(":", 0) == 0) {
            print(field->name->substr(1, field->name->length() - 1));
        } else if (std::regex_match(*field->name, std::regex("[0-9]+"))) {
            print("\"" + *field->name + "\"");
        } else {
            print(*field->name);
        }
        print(": ");
        enterVisit(field->type);
    }

    virtual void visit(Record *type) {
        print("{ ");
        for (int i = 0; i < type->fields.size(); i++) {
            enterVisit(type->fields[i]);
            if (i < type->fields.size() - 1) {
                print(", ");
            }
        }
        print(" }");
    }

    // Declarations

    virtual void visit(TypeParam *param) {
        printn();
        printt();
        print(*param->name);
        print(" = type_member(");
        // TODO bound (fixed|upper|lower): type
        if (param->variance) {
            print(":" + *param->variance);
        }
        printn(")");
        if (param->unchecked) {
            warnUnsupported(static_cast<Node *>(param), "Unsupported `unchecked`");
        }
    }

    void printScope(std::string kind, std::string name, Scope *decl) {
        printl(kind + " " + name);
        indent();
        printl("extend T::Sig");
        if (!decl->typeParams.empty()) {
            printl("extend T::Generic");
            for (int i = 0; i < decl->typeParams.size(); i++) {
                enterVisit(decl->typeParams[i]);
            }
        }
        for (int i = 0; i < decl->members.size(); i++) {
            enterVisit(decl->members[i]);
        }
        dedent();
        printl("end");
    }

    virtual void visit(Class *decl) {
        printScope("class", *decl->name + (decl->parent ? " < " + *decl->parent : ""), decl);
    }

    virtual void visit(Module *decl) { printScope("module", *decl->name, decl); }

    virtual void visit(Interface *decl) {
        warnUnsupported(static_cast<Node *>(decl), "Unsupported `interface`");
        // printScope("module", decl->name->substr(1, decl->name->length() - 1), decl);
    }

    virtual void visit(Extension *decl) { warnUnsupported(static_cast<Node *>(decl), "Unsupported `extension`"); }

    virtual void visit(Const *decl) {
        printt();
        print(*decl->name + " = ");
        enterVisit(decl->type);
        printn();
    }

    virtual void visit(Global *decl) { warnUnsupported(static_cast<Node *>(decl), "Unsupported `global`"); }

    virtual void visit(TypeDecl *decl) {
        printt();
        print(*decl->name + " = T.type_alias { ");
        enterVisit(decl->type);
        printn(" }");
    }

    // Class members

    virtual void visit(Alias *alias) {
        printn();
        printt();
        print("alias ");
        printDefName(*alias->from);
        print(" ");
        printDefName(*alias->to);
        printn();
    }

    virtual void visit(Attr *decl) {}

    virtual void visit(AttrReader *decl) {
        printn();
        printt();
        print("sig { returns(");
        enterVisit(decl->type);
        printn(") }");
        printl("attr_reader :" + *decl->name);
    }

    virtual void visit(AttrWriter *decl) {
        printn();
        printt();
        print("sig { params(" + *decl->name + ": ");
        enterVisit(decl->type);
        printn(").void }");
        printl("attr_writer :" + *decl->name);
    }

    virtual void visit(AttrAccessor *decl) {
        printn();
        printt();
        print("sig { returns(");
        enterVisit(decl->type);
        printn(") }");
        printl("attr_accessor :" + *decl->name);
    }

    virtual void visit(Include *include) {
        printn();
        printl("include " + *include->name);
    }

    virtual void visit(Extend *extend) {
        printn();
        printl("extend " + *extend->name);
    }

    virtual void visit(Prepend *prepend) {
        printn();
        printl("prepend " + *prepend->name);
    }

    virtual void visit(Visibility *decl) {
        warnUnsupported(static_cast<Node *>(decl), "Unsupported `" + *decl->name + "`");
    }

    virtual void visit(Method *decl) {
        if (decl->incompatible) {
            warnUnsupported(static_cast<Node *>(decl), "Unsupported `incompatible`");
        }
        printn();
        for (int i = 0; i < decl->types.size(); i++) {
            enterVisit(decl->types[i]);
            // break; // TODO handle multiple signatures
        }
        printt();
        print("def ");
        if (decl->singleton) {
            print("self."); // TODO isBoth
        }
        printDefName(*decl->name);
        if (!decl->types.empty()) {
            auto type = decl->types[0];
            if (!type->sig->params.empty() || type->block != NULL) {
                print("(");
                for (int i = 0; i < type->sig->params.size(); i++) {
                    if (type->sig->params[i]->name) {
                        printDefName(*type->sig->params[i]->name);
                    } else {
                        print("arg" + std::to_string(i));
                    }
                    if (i < type->sig->params.size() - 1) {
                        print(", ");
                    }
                }
                if (type->block) {
                    if (!type->sig->params.empty()) {
                        print(", ");
                    }
                    print("_blk");
                }
                print(")");
            }
        }
        printn("; end");
        // TODO singleton
    }

    void printParam(Param *param, int count) {
        if (param->name) {
            printDefName(*param->name);
        } else {
            print("arg" + std::to_string(count));
        }
        print(": ");
        if (param->optional && !dynamic_cast<TypeNilable *>(param->type)) {
            print("T.nilable(");
            enterVisit(param->type);
            print(")");
        } else {
            enterVisit(param->type);
        }
    }

    void printSig(TypeProc *sig, Block *block) {
        printt();
        print("sig { ");
        if (!sig->params.empty() || block != NULL) {
            print("params(");
            for (int i = 0; i < sig->params.size(); i++) {
                printParam(sig->params[i], i);
                if (i < sig->params.size() - 1) {
                    print(", ");
                }
            }
            if (block) {
                if (!sig->params.empty()) {
                    print(", ");
                }
                print("_blk: ");
                enterVisit(block);
            }
            print(").");
        }
        if (TypeVoid *type_void = dynamic_cast<TypeVoid *>(sig->ret)) {
            enterVisit(type_void);
        } else {
            print("returns(");
            enterVisit(sig->ret);
            print(")");
        }
        printn(" }");
    }

    virtual void visit(MethodType *node) { printSig(node->sig, node->block); }

    virtual void visit(Block *block) {
        if (block->optional) {
            print("T.nilable(");
        }
        enterVisit(block->sig);
        if (block->optional) {
            print(")");
        }
    }

    virtual void visit(Param *param) {}
};
} // namespace rbs_parser

#endif
