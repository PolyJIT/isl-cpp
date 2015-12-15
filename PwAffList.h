#ifndef ISL_CXX_PwAffList_H
#define ISL_CXX_PwAffList_H


#include "isl/aff.h"
#include "isl/Ctx.h"
#include "isl/IslBase.h"
#include "isl/IslException.h"
#include <string>
#include <ostream>

#include "isl/IslFnPtr.h"

namespace isl {
class PwAff;

class PwAffList {
protected:
  Ctx ctx;
  void * This;
  explicit PwAffList(Ctx ctx, isl_pw_aff_list *That) : ctx(ctx), This((void *)That) {}
  explicit PwAffList(Ctx ctx, void *That) : ctx(ctx), This(That) {}

public:
  const Ctx &Context() const { return ctx; }
  ///rief Wrap an existing isl object.
  ///
  /// This serves as an entry point into the C++ API.
  /// We take ownership of the isl object.
  ///
  /// \param That the isl_pw_aff_list we want to wrap.
  explicit PwAffList(isl_pw_aff_list *That) : PwAffList(Ctx(isl_pw_aff_list_get_ctx(That)), That) {}
  isl_pw_aff_list *GetCopy() const;
  /// \brief Release ownership of the wrapped object.
  ///
  /// You are on your own now buddy.
  /// The wrapper cannot be used anymore after calling Give()
  ///
  /// \returns the wrapped isl object.
  isl_pw_aff_list *Give();
  /// \brief unwrap the stored isl object.
  /// \return a the wrapped isl object.
  isl_pw_aff_list *Get() const;

  /// \brief Constructor for isl_pw_aff_list_alloc
  ///
  /// \param ctx
  /// \param n
  static PwAffList alloc(const Ctx &ctx, int n);
  virtual ~PwAffList();

  virtual PwAffList asPwAffList() const;

  /// \brief Generated from  ::<isl_pw_aff_list_add>
  ///
  /// \param [in] el
  ///
  /// \returns A new PwAffList
  PwAffList add(const PwAff &el) const;
  PwAffList(const PwAffList &Other) : PwAffList(Other.Context(), Other.GetCopy()) {}
  PwAffList &operator=(const PwAffList &Other);
  PwAffList (PwAffList && Other) : PwAffList(Other.Context(), Other.This) {}
  PwAffList &operator=(PwAffList && Other) {
    isl_pw_aff_list *New = Other.Give();
    isl_pw_aff_list_free((isl_pw_aff_list *)This);
    This = New;
    return *this;
  }
  /// \brief Implement lt via pointer comparison of the
  ///         wrapped isl objects.
  bool operator<(const PwAffList &RHS) const { return This < RHS.This; }

};
} // namespace isl
#endif //ISL_CXX_PwAffList_H