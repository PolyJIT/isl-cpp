#ifndef ISL_CXX_MapList_IMPL_H
#define ISL_CXX_MapList_IMPL_H

#include "isl/MapList.h"

#include "isl/Map.hpp"
#include "isl/Ctx.hpp"
#include "isl/IslBase.h"
#include "isl/IslException.h"
#include <string>

#include <cassert>

namespace isl {

inline isl_map_list *MapList::GetCopy() const {
  return isl_map_list_copy((isl_map_list *)This);
}
inline MapList &MapList::operator=(const MapList &Other) {
  isl_map_list *New = Other.GetCopy();
  ctx = Other.Context();
  isl_map_list_free((isl_map_list *)This);
  This = New;
  return *this;
}
inline MapList MapList::alloc(const Ctx &ctx, int n) {
  const Ctx &_ctx = ctx.Context();
  _ctx.lock();
  isl_map_list *That = isl_map_list_alloc((ctx.Get()), n);

  _ctx.unlock();
  if (_ctx.hasError()) {
    handleError("isl_map_list_alloc returned a NULL pointer.");
  }

  return MapList(_ctx, That);
}
inline MapList::~MapList() {
  isl_map_list_free((isl_map_list *)This);
  This = nullptr;
}
/// rief Release ownership of the wrapped object.
///
/// You are on your own now buddy.
/// The wrapper cannot be used anymore after calling Give()
///
///@return the wrapped isl object.
inline isl_map_list *MapList::Give() {
  isl_map_list *res = (isl_map_list *)This;
  This = nullptr;
  return res;
}
/// \brief Unwrap the stored isl object.
/// \returns A the wrapped isl object.
inline isl_map_list *MapList::Get() const {  return (isl_map_list *)This;
}

inline MapList MapList::add(const Map &el) const {
  ctx.lock();
  isl_map_list * res =  isl_map_list_add((*this).GetCopy(), (el).GetCopy());
  ctx.unlock();
  if (ctx.hasError()) {
    handleError("isl_map_list_add returned a NULL pointer.");
  }
  return MapList(ctx, res);
}

} // namespace isl
#endif //ISL_CXX_MapList_IMPL_H
