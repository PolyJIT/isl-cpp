#ifndef ISL_CXX_UnionMapList_H
#define ISL_CXX_UnionMapList_H


#include "isl/union_map_list.h"
#include "isl/Ctx.h"
#include "isl/IslBase.h"
#include "isl/IslException.h"
#include <string>

#include "isl/IslFnPtr.h"

namespace isl {
class UnionMap;

class UnionMapList {
protected:
  Ctx ctx;
  void * This;
public:
  explicit UnionMapList(Ctx ctx, isl_union_map_list *That) : ctx(ctx), This(That) {}
  UnionMapList() : ctx(Ctx(nullptr)), This(nullptr) {}

  const Ctx &Context() const { return ctx; }

  __isl_give isl_union_map_list *GetCopy() const;
  /// \brief Release ownership of the wrapped object.
  ///
  /// You are on your own now buddy.
  /// The wrapper cannot be used anymore after calling Give()
  ///
  /// \returns the wrapped isl object.
  __isl_give isl_union_map_list *Give();
  /// \brief unwrap the stored isl object.
  /// \return a the wrapped isl object.
  __isl_give isl_union_map_list *Get() const;


  /// \brief Constructor for isl_union_map_list_alloc
  ///
  /// \param ctx
  /// \param n
  static UnionMapList alloc(const Ctx &ctx, int n);
public:
  virtual ~UnionMapList();
  /// \brief Generated from  ::<isl_union_map_list_add>
  ///
  /// \param [in] el
  ///
  /// \returns A new UnionMapList
  UnionMapList add(const UnionMap &el) const;

  UnionMapList(const UnionMapList &Other) : ctx(Other.Context()), This(Other.GetCopy()) {}
  UnionMapList &operator=(const UnionMapList &Other);
  UnionMapList (UnionMapList && Other) : ctx(Other.Context()), This(Other.Give()) {}
  UnionMapList &operator=(UnionMapList && Other) {
    isl_union_map_list *New = Other.Give();
    isl_union_map_list_free((isl_union_map_list *)This);
    This = New;
    ctx = Other.Context();
    return *this;
  }
  /// \brief Implement lt via pointer comparison of the
  ///         wrapped isl objects.
  bool operator<(const UnionMapList &RHS) const { return This < RHS.This; }

};
} // namespace isl
#endif //ISL_CXX_UnionMapList_H
