#include <memory>
#include <pyrite/core/noncopyable.hpp>

namespace pyrite
{
template <typename T>
class singleton_traits
{
public:
  static T* create() { return new T(); }
};

template <typename T>
class singleton : pyrite::noncopyable
{
protected:
  singleton()          = default;
  virtual ~singleton() = default;

public:
  static std::shared_ptr<T> instance()
  {
    auto ret_ptr = weak_instance.lock();

    if( ret_ptr )
    {
      return ret_ptr;
    }

    ret_ptr = std::shared_ptr<T>( singleton_traits<T>::create() );
    weak_instance = ret_ptr;

    return ret_ptr;
  }

private:
  static std::weak_ptr<T> weak_instance;
};

template <typename T>
std::weak_ptr<T> singleton<T>::weak_instance;

} // namespace pyrite
