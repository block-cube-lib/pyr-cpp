/**
 * @file
 * @author    block
 * @copyright (c) 2017 block.
 */

#ifndef PYRITE_SINGLETON_HPP
#define PYRITE_SINGLETON_HPP

#include <memory>
#include <pyrite/core/noncopyable.hpp>

namespace pyrite
{
/*
 * The singleton_traits class defines the requirements necessary for the singleton class.
 */
template <typename T>
class singleton_traits
{
public:
  /**
   * Create an instance.
   * @return A pointer to the created instance.
   */
  static T* create() { return new T(); }

  /**
   * Destroy an instance.
   * Custom deleter of shared_ptr.
   */
  static void destroy( T*& pointer ) { delete pinter; }
};

/**
 * Classes that inherit the singleton class are guaranteed to have only one instance.
 */
template <typename T>
class singleton : pyrite::noncopyable
{
protected:
  /**
   * Default constructor.
   */
  singleton() = default;

  /**
   * Virtual destructor.
   */
  virtual ~singleton() = default;

public:
  /**
   * Get an instance.
   * If the instance does not exist, it is created.
   *
   * @return instance
   */
  static std::shared_ptr<T> instance()
  {
    auto ret_ptr = weak_instance.lock();

    if( ret_ptr )
    {
      return ret_ptr;
    }

    using traits  = singleton_traits<T>;
    ret_ptr       = std::shared_ptr<T>{traits::create(), traits::destroy};
    weak_instance = ret_ptr;

    return ret_ptr;
  }

private:
  static std::weak_ptr<T> weak_instance; // weak reference
};

template <typename T>
std::weak_ptr<T> singleton<T>::weak_instance;

} // namespace pyrite
#endif // PYRITE_SINGLETON_HPP
