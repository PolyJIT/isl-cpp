#ifndef ISL_CXX_AstNode_H
#define ISL_CXX_AstNode_H


#include "isl/ast.h"
#include "isl/IslBase.h"
#include "isl/IslException.h"
#include <string>

#include "isl/IslFnPtr.h"

namespace isl {

class AstNode {
protected:
  Ctx ctx;
  void * This;
public:
  explicit AstNode(Ctx ctx, isl_ast_node *That) : ctx(ctx), This(That) {}
  AstNode() : ctx(Ctx(nullptr)), This(nullptr) {}

  const Ctx &Context() const { return ctx; }

  __isl_give isl_ast_node *GetCopy() const;
  /// \brief Release ownership of the wrapped object.
  ///
  /// You are on your own now buddy.
  /// The wrapper cannot be used anymore after calling Give()
  ///
  /// \returns the wrapped isl object.
  __isl_give isl_ast_node *Give();
  /// \brief unwrap the stored isl object.
  /// \return a the wrapped isl object.
  __isl_give isl_ast_node *Get() const;
public:
  virtual ~AstNode();
  AstNode(const AstNode &Other) : ctx(Other.Context()), This(Other.GetCopy()) {}
  AstNode &operator=(const AstNode &Other);
  AstNode (AstNode && Other) : ctx(Other.Context()), This(Other.Give()) {}
  AstNode &operator=(AstNode && Other) {
    isl_ast_node *New = Other.Give();
    isl_ast_node_free((isl_ast_node *)This);
    This = New;
    ctx = Other.Context();
    return *this;
  }
  /// \brief Implement lt via pointer comparison of the
  ///         wrapped isl objects.
  bool operator<(const AstNode &RHS) const { return This < RHS.This; }

};
} // namespace isl
#endif //ISL_CXX_AstNode_H
