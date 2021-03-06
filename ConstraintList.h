#ifndef ISL_CXX_ConstraintList_H
#define ISL_CXX_ConstraintList_H


#include "isl/constraint.h"
#include "isl/Ctx.h"
#include "isl/IslBase.h"
#include "isl/IslException.h"
#include <string>

#include "isl/IslFnPtr.h"

namespace isl {
class Constraint;

class ConstraintList {
protected:
  Ctx ctx;
  void * This;
public:
  explicit ConstraintList(Ctx ctx, isl_constraint_list *That) : ctx(ctx), This(That) {}
  ConstraintList() : ctx(Ctx(nullptr)), This(nullptr) {}

  const Ctx &Context() const { return ctx; }

  __isl_give isl_constraint_list *GetCopy() const;
  /// \brief Release ownership of the wrapped object.
  ///
  /// You are on your own now buddy.
  /// The wrapper cannot be used anymore after calling Give()
  ///
  /// \returns the wrapped isl object.
  __isl_give isl_constraint_list *Give();
  /// \brief unwrap the stored isl object.
  /// \return a the wrapped isl object.
  __isl_give isl_constraint_list *Get() const;


  /// \brief Constructor for isl_constraint_list_alloc
  ///
  /// \param ctx
  /// \param n
  static ConstraintList alloc(const Ctx &ctx, int n);
public:
  virtual ~ConstraintList();
  /// \brief Generated from  ::<isl_constraint_list_add>
  ///
  /// \param [in] el
  ///
  /// \returns A new ConstraintList
  ConstraintList add(const Constraint &el) const;

  ConstraintList(const ConstraintList &Other) : ctx(Other.Context()), This(Other.GetCopy()) {}
  ConstraintList &operator=(const ConstraintList &Other);
  ConstraintList (ConstraintList && Other) : ctx(Other.Context()), This(Other.Give()) {}
  ConstraintList &operator=(ConstraintList && Other) {
    isl_constraint_list *New = Other.Give();
    isl_constraint_list_free((isl_constraint_list *)This);
    This = New;
    ctx = Other.Context();
    return *this;
  }
  /// \brief Implement lt via pointer comparison of the
  ///         wrapped isl objects.
  bool operator<(const ConstraintList &RHS) const { return This < RHS.This; }

};
} // namespace isl
#endif //ISL_CXX_ConstraintList_H
