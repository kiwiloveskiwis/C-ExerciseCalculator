#ifndef Utils_hpp
#define Utils_hpp

#include <stack>

#define TNum long double

template <typename T>
inline T popTop(std::stack<T> &s) {
  T result = s.top();
  s.pop();
  return result;
}

#endif // Utils_hpp
